#include "Token.hpp"
#include <magic_enum/magic_enum.hpp>

const std::unordered_map<std::type_index, std::function<std::string(std::any)>> My::Token::literalToString =
{
    { 
        std::type_index(typeid(std::string)),
        [](std::any literal) -> std::string
        { 
            return std::any_cast<std::string>(literal); 
        }
    },
    {
        std::type_index(typeid(int)),
        [](std::any literal) -> std::string
        {
            std::stringstream ss;
            ss << std::any_cast<int>(literal);
            std::string str = ss.str();
            return str;
        }
    },
    {
        std::type_index(typeid(double)),
        [](std::any literal) -> std::string
        {
            std::stringstream ss;
            ss << std::any_cast<double>(literal);
            std::string str = ss.str();
            return str;
        }
    },
};

My::Token::Token(TokenType type, std::string lexeme, std::any literal, uint32_t line)
    : type(type), lexeme(lexeme), literal(literal), line(line)
{

}

std::string My::Token::toString()
{
    const std::string typeStr = magic_enum::enum_name(type).data();
    std::stringstream ss_literal;
    if(literal.has_value())
    {
        const std::type_index& typeAny = std::type_index(literal.type());
        auto it = literalToString.find(typeAny);
        if(it != literalToString.end())
        {
            ss_literal << it->second(literal);
        }
        else
        {
            ss_literal << "null";
        }
    }
    else
    {
        ss_literal << "[no literal]";
    }

    return typeStr + " " + lexeme + " " + ss_literal.str();
}