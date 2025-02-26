#include "Expr.hpp"

Star::Binary::Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right) :
    m_Left(std::move(left)),
    m_Operator(std::move(op)),
    m_Right(std::move(right))
{}

std::any Star::Binary::Accept(ExprVisitor& visitor)
{
    return visitor.visitBinaryExpr(shared_from_this());
}

Star::Grouping::Grouping(std::shared_ptr<Expr> expression) : 
    m_Expression(std::move(expression))
{}

std::any Star::Grouping::Accept(ExprVisitor& visitor)
{
    return visitor.visitGroupingExpr(shared_from_this());
}

Star::Unary::Unary(Token op, std::shared_ptr<Expr> m_Right) :
    m_Operator(std::move(op)),
    m_Right(std::move(m_Right))
{}

std::any Star::Unary::Accept(ExprVisitor& visitor)
{
    return visitor.visitUnaryExpr(shared_from_this());
}

Star::Literal::Literal(std::any value) :
    m_Value(std::move(value))
{}

std::any Star::Literal::Accept(ExprVisitor& visitor)
{
    return visitor.visitLiteralExpr(shared_from_this());
}
