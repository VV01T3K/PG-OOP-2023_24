_Pragma("once");
#include <iostream>

class Token {
   public:
    enum Type { NUMBER, OPERATOR, FUNCTION };
    Type type;
    int value;
    unsigned char arg_count;
    friend std::ostream& operator<<(std::ostream& out, const Token& token);
    Token(Type type, int value, unsigned char arg_count = 0)
        : type(type), value(value), arg_count(arg_count){};
    Token() : type(Type::NUMBER), value(0), arg_count(0){};
    Token(const char* string);
    void setArgCount(unsigned char arg_count) { this->arg_count = arg_count; };
    bool isOperator() const { return type == Type::OPERATOR; };
    bool isFunction() const { return type == Type::FUNCTION; };
    bool isNumber() const { return type == Type::NUMBER; };
    bool isLeftParenthesis() const { return value == '('; };
    bool isRightParenthesis() const { return value == ')'; };
    int precedence() const;
};