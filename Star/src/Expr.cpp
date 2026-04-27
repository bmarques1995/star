#include "Expr.hpp"

Star::Binary::Binary(std::shared_ptr<Expr> left, Token oper, std::shared_ptr<Expr> right) :
	left(std::move(left)), oper(oper), right(std::move(right))
{
}

std::any Star::Binary::Accept(ExprVisitor& visitor)
{
	return visitor.VisitBinaryExpr(shared_from_this());
}

Star::Grouping::Grouping(std::shared_ptr<Expr> expression) :
	expression(std::move(expression))
{
}

std::any Star::Grouping::Accept(ExprVisitor& visitor)
{
	return visitor.VisitGroupingExpr(shared_from_this());
}

Star::Unary::Unary(Token oper, std::shared_ptr<Expr> right) :
	oper(oper), right(std::move(right))
{
}

std::any Star::Unary::Accept(ExprVisitor& visitor)
{
	return visitor.VisitUnaryExpr(shared_from_this());
}

Star::Literal::Literal(std::any value) :
	value(std::move(value))
{
}

std::any Star::Literal::Accept(ExprVisitor& visitor)
{
	return visitor.VisitLiteralExpr(shared_from_this());
}
