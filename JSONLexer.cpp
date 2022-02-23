#include "JSONLexer.h"

void JSONLexer::addToken(std::string key, std::string value)
{
    finalTokens.push_back(std::make_pair(key, value));
}

JSONLexer::JSONLexer(std::string fileName)
{
    file.open(fileName);
    if (!file.is_open())
        std::cout << "File(" << fileName << ") couldn't be opened\n";
}

void JSONLexer::printJSON()
{
    char c;
    while (file.get(c))
    {
        std::cout << c;
    }
    std::cout << '\n';
}

void JSONLexer::preProcess()
{
    bool inQuotation = false;
    char c;
    while (file.get(c))
    {
        if (c != ' ' && c != '\n' && c != '\t')
        {
            processedFile += c;
        }
        else if (c != '\n' && inQuotation)
        {
            processedFile += c;
        }
        else if (c != '\t' && inQuotation)
        {
            processedFile += c;
        }

        if (c == '\"' && inQuotation)
        {
            inQuotation = false;
        }
        else if (c == '\"' && !inQuotation)
        {
            inQuotation = true;
        }
    }
}

void JSONLexer::lex()
{
    preProcess();

    bool inArray = false;
    bool expectingKey = false;
    bool expectingValue = false;

    std::string tempKey;
    bool lastKeyC = false;

    std::string tempValue;
    std::string valueType;
    bool firstValueC = true;

    for (int i = 0; i < processedFile.size(); i++)
    {
        char c = processedFile[i];

        if (expectingKey)
        {
            if (c == '{')
            {
                expectingKey = false;
                i--;
                continue;
            }
            if (c != '\"')
            {
                tempKey += c;
                continue;
            }
            else
            {
                if (lastKeyC)
                {
                    addToken("key", tempKey);
                    expectingKey = false;
                    tempKey = "";
                    lastKeyC = false;
                    continue;
                }
                else
                {
                    lastKeyC = true;
                    continue;
                }
            }
        }
        else if (expectingValue)
        {
            if (firstValueC)
            {
                switch (c)
                {
                case '[':
                    expectingValue = false;
                    i--;
                    continue;
                case '{':
                    expectingValue = false;
                    i--;
                    continue;
                case ']':
                    expectingValue = false;
                    i--;
                    continue;
                case '\"':
                    valueType = "strng";
                    firstValueC = false;
                    continue;
                case 't':
                    valueType = "bool";
                    tempValue += c;
                    firstValueC = false;
                    continue;
                case 'f':
                    valueType = "bool";
                    tempValue += c;
                    firstValueC = false;
                    continue;
                case 'n':
                    valueType = "null";
                    tempValue += c;
                    firstValueC = false;
                    continue;
                default:
                    valueType = "numb";
                    tempValue += c;
                    firstValueC = false;
                    continue;
                }
            }
            else
            {
                if (valueType == "strng")
                {
                    if (c == '\"')
                    {
                        addToken(valueType, tempValue);
                        expectingValue = false;
                        tempValue = "";
                        valueType = "";
                        firstValueC = true;
                        continue;
                    }
                    else
                    {
                        tempValue += c;
                        continue;
                    }
                }
                else
                {
                    if (c == ',' || c == ']' || c == '}')
                    {
                        addToken(valueType, tempValue);
                        expectingValue = false;
                        tempValue = "";
                        valueType = "";
                        firstValueC = true;
                        if (c == ',' && !inArray)
                        {
                            expectingKey = true;
                            continue;
                        }
                        else if (c == ',' && inArray)
                        {
                            expectingValue = true;
                            continue;
                        }
                    }
                    else
                    {
                        tempValue += c;
                        continue;
                    }
                }
            }
            if (c == ']' || c == '}')
            {
                expectingValue = false;
                i--;
                continue;
            }
        }
        else
        {
            switch (c)
            {
            case '{':
                addToken("LBrce", "{");
                expectingKey = true;
                expectingValue = false;
                inArray = false;
                break;
            case '}':
                addToken("RBrce", "}");
                break;
            case '[':
                addToken("LSqBr", "[");
                expectingKey = false;
                inArray = true;
                expectingValue = true;
                break;
            case ']':
                addToken("RSqBr", "]");
                inArray = false;
                break;
            case ':':
                expectingKey = false;
                expectingValue = true;
                break;
            case ',':
                if (inArray)
                {
                    expectingKey = false;
                    expectingValue = true;
                }
                else
                {
                    expectingKey = true;
                    expectingValue = false;
                }
                break;
            default:
                break;
            }
        }
    }
}

void JSONLexer::printTokens()
{
    std::cout << "Type\tValue\n";
    for (int i = 0; i < finalTokens.size(); i++)
    {
        std::cout << finalTokens[i].first << '\t' << finalTokens[i].second << '\n';
    }
}