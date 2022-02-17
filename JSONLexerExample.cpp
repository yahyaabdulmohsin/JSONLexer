#include "JSONLexer.h"

int main(int argc, char **argv)
{
    system("CLS");
    JSONLexer jsonLexer(argv[1]);
    jsonLexer.lex();
    jsonLexer.printTokens();
    system("pause");
    return 0;
}