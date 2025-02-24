#pragma once

#include <vector>
#include <unordered_map>
#include "Token.hpp"
#include "DLLDef.hpp"
#include "Debug.hpp"

namespace My
{
    class MYLANG_API Scanner
    {
    private:
        uint32_t line = 1;
        uint32_t start = 0;
        uint32_t current = 0;
        std::string source;
        std::vector<Token> tokens;
        static const std::unordered_map<std::string, TokenType> keywords;
    
        bool isAlpha(char c);
        bool isDigit(char c);
        bool isAlphaNumeric(char c);

        bool match(char expected);
        void scanToken();
        char advance();

        void addToken(TokenType type);
        void addToken(TokenType type, std::any literal);

        char peek();
        char peekNext();

        void string();

        void number();

        void identifier();
    public:
        Scanner(const std::string&  source);
        std::vector<Token> scanTokens();
        bool isAtEnd();
    };
} // namespace My
