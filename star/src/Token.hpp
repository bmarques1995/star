#pragma once

#include <iostream>
#include "DLLDef.hpp"
#include "TokenType.hpp"
#include <any>
#include <sstream>
#include <functional>
#include <unordered_map>
#include <typeinfo>
#include <typeindex>

namespace Star
{

    class STARLANG_API Token
    {
    public:
        Token(TokenType type, std::string lexeme, std::any literal, uint32_t line);
        std::string ToString();

        TokenType m_Type;
        std::string m_Lexeme;
        std::any m_Literal;
        uint32_t m_Line;

    private:
        static const std::unordered_map<std::type_index, std::function<std::string(std::any)>> literalToString;
    };
}