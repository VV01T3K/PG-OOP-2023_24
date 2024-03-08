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
};