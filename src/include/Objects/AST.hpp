#ifndef AST_H
#define AST_H

#include <vector>
#include <string>

// NodeType definition
enum class NodeType {
    Program,
    NumericLiteral,
    Identifier,
    BinaryExpr
};

// Forward declaration for Expr
struct Expr;

// Stmt definition
struct Stmt {
    NodeType kind;
};

// Program definition
struct Program : Stmt {
    std::vector<Stmt> body;
};

// Expr definition (inherits from Stmt)
struct Expr : Stmt {};

// BinaryExpr definition (inherits from Expr)
struct BinaryExpr : Expr {
    NodeType kind;
    Expr left;
    Expr right;
    std::string operatorStr; // C++ doesn't have string literal types like TypeScript
};

// Identifier definition (inherits from Expr)
struct Identifier : Expr {
    NodeType kind;
    std::string symbol;
};

// NumericLiteral definition (inherits from Expr)
struct NumericLiteral : Expr {
    NodeType kind;
    double value;
};


#endif // AST_H