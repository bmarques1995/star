#pragma once

#include <vector>
#include <stdexcept>
#include "Scanner.hpp"
#include "Expr.hpp"
#include "Debug.hpp"
#include "DLLDef.hpp"
#include <cassert>

namespace Star
{
    class Parser
    {
    public:
        struct ParseError : public std::runtime_error
        {
            using std::runtime_error::runtime_error;
        };

        const std::vector<Token>& m_Tokens;
        uint32_t m_Current = 0;

        ParseError Error(const Token& token, const std::string& message);
        
        void Synchronize();
        
        template<class... T>
        bool Match(T... types)
        {
            assert((... && std::is_same_v<T, TokenType>));
            if((... || Check(types)))
            {
                Advance();
                return true;
            }
            return false;
        }
        
        bool Check(const TokenType& type);
        bool IsAtEnd();

        Token Advance();
        Token Peek();
        Token Previous();
        Token Consume(const TokenType& type, const std::string& message);

        std::shared_ptr<Expr> Expression();
        std::shared_ptr<Expr> Equality();
        std::shared_ptr<Expr> Comparison();
        std::shared_ptr<Expr> Term();
        std::shared_ptr<Expr> Factor();
        std::shared_ptr<Expr> Unary();
        std::shared_ptr<Expr> Primary();
    public:
        Parser(const std::vector<Token>& tokens);
        std::shared_ptr<Expr> Parse();
    };
}