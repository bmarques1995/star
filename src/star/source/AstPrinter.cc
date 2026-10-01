#include "AstPrinter.hh"
#include "Expr.hh"
#include "Value.hh"
#include <memory>
#include <sstream>

void star::AstPrinter::Print(std::shared_ptr<Statement::Stmt> stmt)
{
    stmt->Accept(*this);
}

star::Value star::AstPrinter::VisitPostIncrementExpr(std::shared_ptr<Expression::PostIncrement> expr)
{
    return Value();
}

star::Value star::AstPrinter::VisitBinaryExpr(std::shared_ptr<Expression::Binary> expr)
{
    return Value{};
}

star::Value star::AstPrinter::VisitGroupingExpr(std::shared_ptr<Expression::Grouping> expr)
{
    return Value{};
}

star::Value star::AstPrinter::VisitLiteralExpr(std::shared_ptr<Expression::Literal> expr)
{
    return expr->m_Value;
}

star::Value star::AstPrinter::VisitUnaryExpr(std::shared_ptr<Expression::Unary> expr)
{
  return Value{};
}

star::Value star::AstPrinter::VisitPreIncrementExpr(std::shared_ptr<Expression::PreIncrement> expr)
{
    return Value();
}

star::Value star::AstPrinter::VisitTemplateLiteralExpr(std::shared_ptr<Expression::TemplateLiteral> expr)
{
    return Value{};
}

star::Value star::AstPrinter::VisitTernaryExpr(std::shared_ptr<Expression::Ternary> expr)
{
    return Value{};
}

star::Value star::AstPrinter::VisitVariableExpr(std::shared_ptr<Expression::Variable> expr)
{
    return Value();
}

star::Value star::AstPrinter::VisitAssignmentExpr(std::shared_ptr<Expression::Assignment> expr)
{
    return Value();
}

star::Value star::AstPrinter::VisitLogicalExpr(std::shared_ptr<Expression::Logical> expr)
{
    return Value();
}

star::Value star::AstPrinter::VisitCallExpr(std::shared_ptr<Expression::Call> expr)
{
    return Value();
}

star::Value star::AstPrinter::VisitGetExpr(std::shared_ptr<Expression::Get> expr)
{
    return Value();
}

star::Value star::AstPrinter::VisitSetExpr(std::shared_ptr<Expression::Set> expr)
{
    return Value();
}

star::Value star::AstPrinter::VisitExpressionStmt(std::shared_ptr<Statement::Expression> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitVariableStmt(std::shared_ptr<Statement::Variable> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitAutoStmt(std::shared_ptr<Statement::Auto> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitBlockStmt(std::shared_ptr<Statement::Block> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitIfStmt(std::shared_ptr<Statement::If> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitWhileStmt(std::shared_ptr<Statement::While> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitForStmt(std::shared_ptr<Statement::ForLoop> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitFunctionStmt(std::shared_ptr<Statement::Function> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitFunctionArgumentStmt(std::shared_ptr<Statement::FunctionArgument> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitReturnStmt(std::shared_ptr<Statement::Return> stmt)
{
    return Value();
}

star::Value star::AstPrinter::VisitClassStmt(std::shared_ptr<Statement::Class> stmt)
{
    return Value();
}
