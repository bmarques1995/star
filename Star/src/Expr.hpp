#pragma once

#include <utility>
#include <vector>
#include "Token.hpp"
#include "Visitor.hpp"
#include "StarCore.hpp"
#include <memory>

namespace Star
{
	struct STAR_API Binary final : public Expr, public std::enable_shared_from_this<Binary>
	{
		std::shared_ptr<Expr> left;
		Token oper;
		std::shared_ptr<Expr> right;

		Binary(std::shared_ptr<Expr> left, Token oper, std::shared_ptr<Expr> right);
		std::any Accept(ExprVisitor& visitor) override;
		~Binary() = default;
	};

	struct STAR_API Grouping final : public Expr, public std::enable_shared_from_this<Grouping>
	{
		std::shared_ptr<Expr> expression;

		Grouping(std::shared_ptr<Expr> expression);
		std::any Accept(ExprVisitor& visitor) override;
		~Grouping() = default;
	};

	struct STAR_API Unary final : public Expr, public std::enable_shared_from_this<Unary>
	{
		Token oper;
		std::shared_ptr<Expr> right;

		Unary(Token oper, std::shared_ptr<Expr> right);
		std::any Accept(ExprVisitor& visitor) override;
		~Unary() = default;
	};

	struct STAR_API Literal final : public Expr, public std::enable_shared_from_this<Literal>
	{
		std::any value;

		Literal(std::any value);
		std::any Accept(ExprVisitor& visitor) override;
		~Literal() = default;
	};
}
