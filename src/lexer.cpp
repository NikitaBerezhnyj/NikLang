#include <iostream>
#include <algorithm>
#include <sstream>
#include "./include/lexer.hpp"
#include "./include/Objects/TOKEN.hpp"

using namespace std;

Lexer::Lexer(const std::string& input) : input_(input), current_pos_(0) {}

std::vector<TOKEN> Lexer::tokenize() {
    // Викликайте handleComments на початку tokenize
    handleComments();

    while (current_pos_ < input_.size()) {
        char current_char = peek();

        if (std::isalpha(current_char) || current_char == '_') {
            handleKeywordOrIdentifier();
        } else if (std::isdigit(current_char)) {
            handleNumber();
        } else if (current_char == '"') {
            handleString();
        } else if (isOperatorOrPunctuation(current_char)) {
            handleOperatorOrPunctuation();
        } else {
            advance();
        }
    }

    addToken("EOF", "END_OF_FILE");

    return tokens_;
}

char Lexer::peek() {
    if (current_pos_ < input_.size()) {
        return input_[current_pos_];
    } else {
        return '\0';
    }
}

char Lexer::peekNext() {
    if (current_pos_ + 1 < input_.size()) {
        return input_[current_pos_ + 1];
    } else {
        return '\0';
    }
}


char Lexer::advance() {
    if (current_pos_ < input_.size()) {
        return input_[current_pos_++];
    } else {
        return '\0';
    }
}

void Lexer::skipWhitespace() {
    while (std::isspace(peek())) {
        advance();
    }
}

void Lexer::handleKeywordOrIdentifier() {
    size_t start = current_pos_;
    while (std::isalnum(peek()) || peek() == '_') {
        advance();
    }
    std::string token = input_.substr(start, current_pos_ - start);
    tokenize(token);
}

void Lexer::handleNumber() {
    size_t start = current_pos_;
    while (std::isdigit(peek()) || peek() == '.') {
        advance();
    }
    std::string token = input_.substr(start, current_pos_ - start);
    tokenize(token);
}

void Lexer::handleString() {
    advance(); // Skip opening quote
    size_t start = current_pos_;
    while (peek() != '"' && peek() != '\0') {
        advance();
    }
    std::string token = input_.substr(start, current_pos_ - start);
    advance(); // Skip closing quote
    tokenize(token);
}

void Lexer::handleComments() {
    size_t start = current_pos_;
    while (current_pos_ + 1 < input_.size() && input_[current_pos_] == '/' && input_[current_pos_ + 1] == '/') {
        // Пропускаємо текст після "//" до кінця рядка
        while (current_pos_ < input_.size() && input_[current_pos_] != '\n') {
            advance();
        }
        // Зрізаємо коментарі зі вхідного рядка, замінюючи їх на пробіли
        std::string comment = input_.substr(start, current_pos_ - start);
        std::fill(input_.begin() + start, input_.begin() + current_pos_, ' ');
        start = current_pos_;
    }
}

void Lexer::handleOperatorOrPunctuation() {
    size_t start = current_pos_;
    while (isOperatorOrPunctuation(peek())) {
        advance();
    }
    std::string token = input_.substr(start, current_pos_ - start);
    tokenize(token);
}

bool Lexer::isOperatorOrPunctuation(char c) {
    static const std::string operators = "+-*/=<>!&|^%(){}[],.;";
    return operators.find(c) != std::string::npos;
}

bool isNumber(std::string str)
{
    for (char const &c : str) {
        if (std::isdigit(c) == 0)
          return false;
    }
    return true;
}

bool isFloat(const std::string& str) {
    try {
        std::stod(str);
        return true;
    } catch (const std::invalid_argument& ia) {
        return false;
    } catch (const std::out_of_range& oor) {
        return false;
    }
}

void Lexer::tokenize(std::string token) {
    // Ключові слова
    if (token == "print") { addToken("KEYWORD", "print"); }
    else if (token == "printL") { addToken("KEYWORD", "printL"); }
    else if (token == "input") { addToken("KEYWORD", "input"); }
    else if (token == "if") { addToken("KEYWORD", "if"); }
    else if (token == "else") { addToken("KEYWORD", "else"); }
    else if (token == "elif") { addToken("KEYWORD", "elif"); }
    else if (token == "for") { addToken("KEYWORD", "for"); }
    else if (token == "while") { addToken("KEYWORD", "while"); }
    else if (token == "func") { addToken("KEYWORD", "func"); }
    else if (token == "return") { addToken("KEYWORD", "return"); }
    else if (token == "add") { addToken("KEYWORD", "add"); }
    // Оператори
    else if (token == "+") { addToken("OPERATOR", "+"); }
    else if (token == "-") { addToken("OPERATOR", "-"); }
    else if (token == "*") { addToken("OPERATOR", "*"); }
    else if (token == "/") { addToken("OPERATOR", "/"); }
    else if (token == "=") { addToken("OPERATOR", "="); }
    else if (token == "+=") { addToken("OPERATOR", "+="); }
    else if (token == "-=") { addToken("OPERATOR", "-="); }
    else if (token == "*=") { addToken("OPERATOR", "*="); }
    else if (token == "++") { addToken("OPERATOR", "--"); }
    else if (token == "--") { addToken("OPERATOR", "--"); }
    // Типи даних
    else if (token == "int") { addToken("DATA_TYPE", "int"); }
    else if (token == "string") { addToken("DATA_TYPE", "string"); }
    else if (token == "char") { addToken("DATA_TYPE", "char"); }
    else if (token == "float") { addToken("DATA_TYPE", "float"); }
    else if (token == "bool") { addToken("DATA_TYPE", "bool"); }
    // Дані
    else if (isNumber(token)) { addToken("Number", token); }
    else if (isFloat(token)) { addToken("F_Number", token); }
    // Інші токени
    else if (token == ";") { addToken("SEPARATOR", ";"); }
    else if (token == ":") { addToken("SEPARATOR", ":"); }
    else if (token == ".") { addToken("SEPARATOR", "."); }
    else if (token == ",") { addToken("SEPARATOR", ","); }
    else if (token == "==") { addToken("SEPARATOR", "=="); }
    else if (token == "!=") { addToken("SEPARATOR", "!="); }
    else if (token == ">") { addToken("SEPARATOR", ">"); }
    else if (token == "<") { addToken("SEPARATOR", "<"); }
    else if (token == ">=") { addToken("SEPARATOR", ">="); }
    else if (token == "<=") { addToken("SEPARATOR", "<="); }
    else if (token == "(") { addToken("SEPARATOR", "("); }
    else if (token == ")") { addToken("SEPARATOR", ")"); }
    else if (token == "()") { addToken("SEPARATOR", "("); addToken("SEPARATOR", ")"); }
    else if (token == ");") { addToken("SEPARATOR", ")"); addToken("SEPARATOR", ";"); }
    else if (token == "();") { addToken("SEPARATOR", "("); addToken("SEPARATOR", ")"); addToken("SEPARATOR", ";"); }
    else if (token == "{") { addToken("BRACES", "{"); }
    else if (token == "};") { addToken("BRACES", "}"); addToken("SEPARATOR", ";"); }
    else if (token == "[") { addToken("SEPARATOR", "["); }
    else if (token == "]") { addToken("SEPARATOR", "]"); }
    else if (token == "//") { return; }
    else { addToken("IDENTIFIER", token); }
}

void Lexer::addToken(const std::string& type, const std::string& value) {
    TOKEN token;
    token.type = type;
    token.value = value;
    tokens_.push_back(token);
}