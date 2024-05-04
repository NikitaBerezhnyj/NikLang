#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <vector>
#include <string>
#include "./Objects/TOKEN.hpp"

class Lexer {
public:
    Lexer(const std::string& input);

    std::vector<TOKEN> tokenize();

private:
    std::string input_;
    size_t current_pos_;
    std::vector<TOKEN> tokens_;

    char peek();
    char peekNext();
    char advance();
    void skipWhitespace();
    void handleKeywordOrIdentifier();
    void handleNumber();
    void handleString();
    void handleComments();
    void handleOperatorOrPunctuation();

    bool isOperatorOrPunctuation(char c);

    void tokenize(std::string token);

    void addToken(const std::string& type, const std::string& value);
};

#endif // LEXER_H