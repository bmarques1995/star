#pragma once

#include <any>
#include <memory>
#include "DLLDef.hpp"

namespace Star
{
    struct STARLANG_API Binary;
    struct STARLANG_API Grouping;
    struct STARLANG_API Literal;
    struct STARLANG_API Unary;

    struct STARLANG_API ExprVisitor
    {
        virtual ~ExprVisitor() = default;
        virtual std::any visitBinaryExpr(std::shared_ptr<Binary> expr) = 0;
        virtual std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) = 0;
        virtual std::any visitLiteralExpr(std::shared_ptr<Literal> expr) = 0;
        virtual std::any visitUnaryExpr(std::shared_ptr<Unary> expr) = 0;
    };

    struct STARLANG_API Expr
    {
        virtual ~Expr() = default;
        virtual std::any Accept(ExprVisitor& visitor) = 0;
    };
} // namespace My
