#pragma once

#include <utility>
#include <vector>
#include "Visitor.hpp"
#include "Token.hpp"

namespace My
{
    struct MYLANG_API Binary final : public Expr, public std::enable_shared_from_this<Binary>
    {
        std::shared_ptr<Expr> left;
        Token my_operator;
        std::shared_ptr<Expr> right;

        Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right);
        std::any accept(ExprVisitor& visitor) override;

        ~Binary() = default;
    };

    struct MYLANG_API Grouping final : public Expr, public std::enable_shared_from_this<Grouping>
    {
        std::shared_ptr<Expr> expression;

        Grouping(std::shared_ptr<Expr> expression);
        std::any accept(ExprVisitor& visitor) override;
        
        ~Grouping() = default;
    };

    struct MYLANG_API Unary final : public Expr, public std::enable_shared_from_this<Unary>
    {
        Token my_operator;
        std::shared_ptr<Expr> right;

        Unary(Token op, std::shared_ptr<Expr> right);
        std::any accept(ExprVisitor& visitor) override;
        
        ~Unary() = default;
    };

    struct MYLANG_API Literal final : public Expr, public std::enable_shared_from_this<Literal>
    {
        std::any value;

        Literal(std::any value);
        std::any accept(ExprVisitor& visitor) override;

        ~Literal() = default;
    };
} // namespace My
