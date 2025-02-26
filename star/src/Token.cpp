#include "Token.hpp"
#include <magic_enum/magic_enum.hpp>

const std::unordered_map<std::type_index, std::function<std::string(std::any)>> Star::Token::literalToString =
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

Star::Token::Token(TokenType type, std::string lexeme, std::any literal, uint32_t line)
    : m_Type(type), m_Lexeme(lexeme), m_Literal(literal), m_Line(line)
{

}

std::string Star::Token::ToString()
{
    const std::string typeStr = magic_enum::enum_name(m_Type).data();
    std::stringstream ss_literal;
    if(m_Literal.has_value())
    {
        const std::type_index& typeAny = std::type_index(m_Literal.type());
        auto it = literalToString.find(typeAny);
        if(it != literalToString.end())
        {
            ss_literal << it->second(m_Literal);
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

    return typeStr + " " + m_Lexeme + " " + ss_literal.str();
}