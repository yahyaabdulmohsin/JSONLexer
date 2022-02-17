# Welcome to JSONLexer!

JSONLexer is a JSON file lexer that takes in a JSON file as a command line argument and it lexes it or in other words tokenize it!


# Why

I was planning to write a compiler; and the first step of compiling is lexing. I always wanted to try something with lexing to get an idea but I always pushed it off. In my C++ class I wanted to do an honors project and I had to either do something visual with the windows API, something that has to do with networking, or propose another idea. So I just decided to propose a lexer idea and do this instead.

## How to Build

I built this using [g++](https://www.mingw-w64.org/) with the following command:

    g++ -std=c++17 JSONLexerExample.cpp JSONLexer.cpp -o JSONLexer.exe

## How to Use it

To use this program you can simply do something like this:

    JSONLexer example.json
This will simply output the tokens in the command line. If you want to get full functionality you can download the files and use them as a library.

These are the available members in the JSONLexer class

    class JSONLexer
    {
    private:
	    std::ifstream file; // this is the ifstream file
	    std::string processedFile; // file without unnecessary spaces, tabs, and newlines
	    std::vector<std::pair<std::string, std::string>> finalTokens; // vector of final tokens
    public:
	    JSONLexer(std::string fileName); // constructor
	    void printJSON(); // prints the file in the console
	    void addToken(std::string key, std::string value); // adds a token to finalTokens
	    void preProcess(); // removes unnecessary spaces, tabs, and newlines
	    void lex(); // takes in processedFile and adds tokens to finalTokens
	    void printTokens(); // prints the final tokens to the console
    };