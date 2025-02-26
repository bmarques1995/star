#pragma once

#include <vector>
#include <unordered_map>
#include "Token.hpp"
#include "DLLDef.hpp"
#include "Debug.hpp"

namespace Star
{
    class STARLANG_API Scanner
    {
    private:
        uint32_t m_Line = 1;
        uint32_t m_Start = 0;
        uint32_t m_Current = 0;
        std::string m_Source;
        std::vector<Token> m_Tokens;
        static const std::unordered_map<std::string, TokenType> s_Keywords;
    
        bool IsAlpha(char c);
        bool IsDigit(char c);
        bool IsAlphaNumeric(char c);

        bool Match(char expected);
        void ScanToken();
        char Advance();

        void AddToken(TokenType type);
        void AddToken(TokenType type, std::any literal);

        char Peek();
        char PeekNext();

        void String();

        void Number();

        void Identifier();
    public:
        Scanner(const std::string&  source);
        std::vector<Token> ScanTokens();
        bool IsAtEnd();
    };
} // namespace My
