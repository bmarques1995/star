#pragma once

#include <utility>
#include <vector>
#include "Visitor.hpp"
#include "Token.hpp"

namespace Star
{
    struct STARLANG_API Binary final : public Expr, public std::enable_shared_from_this<Binary>
    {
        std::shared_ptr<Expr> m_Left;
        Token m_Operator;
        std::shared_ptr<Expr> m_Right;

        Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
        std::any Accept(ExprVisitor& visitor) override;

        ~Binary() = default;
    };

    struct STARLANG_API Grouping final : public Expr, public std::enable_shared_from_this<Grouping>
    {
        std::shared_ptr<Expr> m_Expression;

        Grouping(std::shared_ptr<Expr> expression);
        std::any Accept(ExprVisitor& visitor) override;
        
        ~Grouping() = default;
    };

    struct STARLANG_API Unary final : public Expr, public std::enable_shared_from_this<Unary>
    {
        Token m_Operator;
        std::shared_ptr<Expr> m_Right;

        Unary(Token op, std::shared_ptr<Expr> m_Right);
        std::any Accept(ExprVisitor& visitor) override;
        
        ~Unary() = default;
    };

    struct STARLANG_API Literal final : public Expr, public std::enable_shared_from_this<Literal>
    {
        std::any m_Value;

        Literal(std::any value);
        std::any Accept(ExprVisitor& visitor) override;

        ~Literal() = default;
    };
} // namespace My
