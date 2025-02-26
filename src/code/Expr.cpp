#include "Expr.hpp"

My::Binary::Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    left(std::move(left)),
    my_operator(std::move(op)),
    right(std::move(right))
{}

std::any My::Binary::accept(ExprVisitor& visitor)
{
    return visitor.visitBinaryExpr(shared_from_this());
}

My::Grouping::Grouping(std::shared_ptr<Expr> expression) : 
    expression(std::move(expression))
{}

std::any My::Grouping::accept(ExprVisitor& visitor)
{
    return visitor.visitGroupingExpr(shared_from_this());
}

My::Unary::Unary(Token op, std::shared_ptr<Expr> right) :
    my_operator(std::move(op)),
    right(std::move(right))
{}

std::any My::Unary::accept(ExprVisitor& visitor)
{
    return visitor.visitUnaryExpr(shared_from_this());
}

My::Literal::Literal(std::any value) :
    value(std::move(value))
{}

std::any My::Literal::accept(ExprVisitor& visitor)
{
    return visitor.visitLiteralExpr(shared_from_this());
}
