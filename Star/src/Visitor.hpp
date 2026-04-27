#pragma once

#include "StarCore.hpp"
#include <any>
#include <memory>

namespace Star
{
	struct Binary;
	struct Grouping;
	struct Literal;
	struct Unary;

	struct STAR_API ExprVisitor
	{
		virtual std::any VisitBinaryExpr(std::shared_ptr<Binary> binary) = 0;
		virtual std::any VisitGroupingExpr(std::shared_ptr<Grouping> grouping) = 0;
		virtual std::any VisitLiteralExpr(std::shared_ptr<Literal> literal) = 0;
		virtual std::any VisitUnaryExpr(std::shared_ptr<Unary> unary) = 0;
		
		virtual ~ExprVisitor() = default;
	};

	struct STAR_API Expr
	{
		virtual std::any Accept(ExprVisitor& visitor) = 0;

		virtual ~Expr() = default;
	};
}
