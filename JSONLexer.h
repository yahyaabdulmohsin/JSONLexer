#pragma once

#include <iostream>
#include <fstream>
#include <vector>

class JSONLexer
{
private:
    std::ifstream file;
    std::string processedFile;
    std::vector<std::pair<std::string, std::string>> finalTokens;

public:
    JSONLexer(std::string fileName);
    void printJSON();
    void addToken(std::string key, std::string value);
    void preProcess();
    void lex();
    void printTokens();
};