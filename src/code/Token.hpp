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

namespace My
{

    class MYLANG_API Token
    {
    public:
        Token(TokenType type, std::string lexeme, std::any literal, uint32_t line);
        std::string toString();

        TokenType type;
        std::string lexeme;
        std::any literal;
        uint32_t line;

    private:
        static const std::unordered_map<std::type_index, std::function<std::string(std::any)>> literalToString;
    };
}