#include "Token.hpp"
#include <magic_enum/magic_enum.hpp>

//({ {typeid(std::string), [](std::stringstream* ss, const std::any& value) { *ss << std::any_cast<std::string>(value); }} })

Star::Token::Token(TokenType type, const std::string& lexeme, const std::any& literal, size_t line)
    : type(type), lexeme(lexeme), literal(literal), line(line)
{
    literalProcessors =
    {
        { typeid(std::string), [](std::stringstream* ss, const std::any& value) { *ss << std::any_cast<std::string>(value); } },
        { typeid(double), [](std::stringstream* ss, const std::any& value) { *ss << std::any_cast<double>(value); } },
        { typeid(int64_t), [](std::stringstream* ss, const std::any& value) { *ss << std::any_cast<int64_t>(value); } },
        { typeid(uint64_t), [](std::stringstream* ss, const std::any& value) { *ss << std::any_cast<uint64_t>(value); } },
        { typeid(bool), [](std::stringstream* ss, const std::any& value) { *ss << std::boolalpha << std::any_cast<bool>(value); } }
	};
}

std::string Star::Token::ToString() const
{
    const std::string strEnum = magic_enum::enum_name(type).data();
    std::stringstream ss;
    if(literal.has_value())
        ProcessLiteral(&ss);
    else
        ss << strEnum << " " << lexeme;
    return strEnum +  " " + lexeme + ss.str();
}

void Star::Token::ProcessLiteral(std::stringstream* ss) const
{
    if(literal.has_value())
    {
        auto it = literalProcessors.find(std::type_index(literal.type()));
        if(it != literalProcessors.end())
            it->second(ss, literal);
        else
            *ss << " [unsupported literal type]";
    }
    else
    {
        *ss << " [empty]";
    }
}