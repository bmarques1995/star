#pragma once

#include <any>
#include <memory>
#include "DLLDef.hpp"

namespace My
{
    struct MYLANG_API Binary;
    struct MYLANG_API Grouping;
    struct MYLANG_API Literal;
    struct MYLANG_API Unary;

    struct MYLANG_API ExprVisitor
    {
        virtual ~ExprVisitor() = default;
        virtual std::any visitBinaryExpr(std::shared_ptr<Binary> expr) = 0;
        virtual std::any visitGroupingExpr(std::shared_ptr<Grouping> expr) = 0;
        virtual std::any visitLiteralExpr(std::shared_ptr<Literal> expr) = 0;
        virtual std::any visitUnaryExpr(std::shared_ptr<Unary> expr) = 0;
    };

    struct MYLANG_API Expr
    {
        virtual ~Expr() = default;
        virtual std::any accept(ExprVisitor& visitor) = 0;
    };
} // namespace My
