#include "Parser.hpp"


Star::Parser::Parser(const std::vector<Token>& tokens)
    : m_Tokens(tokens)
{
}

std::shared_ptr<Star::Expr> Star::Parser::Parse()
{
    try
    {
        return Expression();
    }
    catch(const std::exception& error)
    {
        //std::cerr << "[Exception parse]: " << error.what() << std::endl;
        return nullptr;
    }
}

Star::Token Star::Parser::Advance()
{
    if (!IsAtEnd())
        m_Current++;
    return Previous();
}

Star::Token Star::Parser::Peek()
{
    return m_Tokens.at(m_Current);
}

Star::Token Star::Parser::Previous()
{
    return m_Tokens.at(m_Current > 0 ? m_Current - 1 : 0);   
}

Star::Token Star::Parser::Consume(const TokenType& type, const std::string& message)
{
    if(Check(type))
        return Advance();
    throw Error(Peek(), message);
}

std::shared_ptr<Star::Expr> Star::Parser::Expression()
{
    return Equality();
}

std::shared_ptr<Star::Expr> Star::Parser::Equality()
{
    auto expr = Comparison();

    while(Match(TokenType::BANG_EQUAL, TokenType::EQUAL_EQUAL))
    {
        auto op = Previous();
        auto right = Comparison();
        expr = std::make_shared<Binary>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Star::Expr> Star::Parser::Comparison()
{
    auto expr = Term();

    while(Match(TokenType::GREATER, TokenType::GREATER_EQUAL, TokenType::LESS, TokenType::LESS_EQUAL))
    {
        auto op = Previous();
        auto right = Term();
        expr = std::make_shared<Binary>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Star::Expr> Star::Parser::Term()
{
    auto expr = Factor();

    while(Match(TokenType::MINUS, TokenType::PLUS))
    {
        auto op = Previous();
        auto right = Factor();
        expr = std::make_shared<Binary>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Star::Expr> Star::Parser::Factor()
{
    auto expr = Unary();

    while(Match(TokenType::SLASH, TokenType::MUL_STAR))
    {
        auto op = Previous();
        auto right = Unary();
        expr = std::make_shared<Binary>(expr, op, right);
    }

    return expr;
}

std::shared_ptr<Star::Expr> Star::Parser::Unary()
{
    while(Match(TokenType::BANG, TokenType::MINUS))
    {
        auto op = Previous();
        auto right = Unary();
        return std::make_shared<Star::Unary>(op, right);
    }
    return Primary();
}

std::shared_ptr<Star::Expr> Star::Parser::Primary()
{
    if(Match(TokenType::STAR_FALSE))
        return std::make_shared<Literal>(false);
    if(Match(TokenType::STAR_TRUE))
        return std::make_shared<Literal>(true);
    if(Match(TokenType::NIL))
        return std::make_shared<Literal>(nullptr);

    if(Match(TokenType::NUMBER, TokenType::STRING))
        return std::make_shared<Literal>(Previous().m_Literal);

    if(Match(TokenType::LEFT_PAREN))
    {
        auto expr = Expression();
        Consume(TokenType::RIGHT_PAREN, "Expect ')' after expression.");
        return std::make_shared<Grouping>(expr);
    }

    throw Error(Peek(), "Expect expression.");
}

bool Star::Parser::Check(const TokenType& type)
{
    if(IsAtEnd())
        return false;
    return Peek().m_Type == type;
}

bool Star::Parser::IsAtEnd()
{
    return Peek().m_Type == TokenType::STAR_EOF;
}

Star::Parser::ParseError Star::Parser::Error(const Token& token, const std::string& message)
{
    Debug::Error(token, message);
    return ParseError(message);
}
        
void Star::Parser::Synchronize()
{
    Advance();
    
    while(!IsAtEnd())
    {
        if(Previous().m_Type == TokenType::SEMICOLON)
            return;
        switch(Peek().m_Type)
        {
            case TokenType::CLASS:
            case TokenType::FUN:
            case TokenType::VAR:
            case TokenType::FOR:
            case TokenType::IF:
            case TokenType::WHILE:
            case TokenType::PRINT:
            case TokenType::RETURN:
                return;
            default:
                return;
        }
        Advance();
    }
    
}
