#pragma once

#include "StarCore.hpp"
#include "TokenType.hpp"
#include <iostream>
#include <any>
#include <sstream>
#include <utility>
#include <cstdint>
#include <typeindex>
#include <unordered_map>

namespace Star
{
    using TokenHandler = void(*)(std::stringstream*, const std::any&);
    class STAR_API Token
    {
    public:
        TokenType type;
        std::string lexeme;
        std::any literal;
        uint32_t line;

        Token(TokenType type, const std::string& lexeme, const std::any& literal, uint32_t line);
        std::string ToString() const;
    private:
        void ProcessLiteral(std::stringstream* ss) const;
        std::unordered_map<std::type_index, TokenHandler> literalProcessors;
    };
}