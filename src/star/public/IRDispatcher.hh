#pragma once

#include "StarMacro.hh"
#include "Visitor.hh"

namespace star
{
	class STAR_API IRDispatcher : public Expression::ExprVisitor, Statement::StmtVisitor
	{
		friend class Function;
		friend class Class;
	public:
		IRDispatcher();
		virtual ~IRDispatcher() = default;

		void Stmt2IR(Statement::Stmt& stmt);
		
		Value VisitGroupingExpr(std::shared_ptr<Expression::Grouping> expr) override;
		Value VisitLiteralExpr(std::shared_ptr<Expression::Literal> expr) override;
		Value VisitTemplateLiteralExpr(std::shared_ptr<Expression::TemplateLiteral> expr) override;
		Value VisitUnaryExpr(std::shared_ptr<Expression::Unary> expr) override;
		Value VisitPreIncrementExpr(std::shared_ptr<Expression::PreIncrement> expr) override;
		Value VisitPostIncrementExpr(std::shared_ptr<Expression::PostIncrement> expr) override;
		Value VisitBinaryExpr(std::shared_ptr<Expression::Binary> expr) override;
		Value VisitTernaryExpr(std::shared_ptr<Expression::Ternary> expr) override;
		Value VisitVariableExpr(std::shared_ptr<Expression::Variable> expr) override;
		Value VisitAssignmentExpr(std::shared_ptr<Expression::Assignment> expr) override;
		Value VisitLogicalExpr(std::shared_ptr<Expression::Logical> expr) override;
		Value VisitCallExpr(std::shared_ptr<Expression::Call> expr) override;
		Value VisitGetExpr(std::shared_ptr<Expression::Get> expr) override;
		Value VisitSetExpr(std::shared_ptr<Expression::Set> expr) override;

		Value VisitExpressionStmt(std::shared_ptr<Statement::Expression> stmt) override;
		Value VisitVariableStmt(std::shared_ptr<Statement::Variable> stmt) override;
		Value VisitAutoStmt(std::shared_ptr<Statement::Auto> stmt) override;
		Value VisitBlockStmt(std::shared_ptr<Statement::Block> stmt) override;
		Value VisitIfStmt(std::shared_ptr<Statement::If> stmt) override;
		Value VisitWhileStmt(std::shared_ptr<Statement::While> stmt) override;
		Value VisitForStmt(std::shared_ptr<Statement::ForLoop> stmt) override;
		Value VisitFunctionStmt(std::shared_ptr<Statement::Function> stmt) override;
		Value VisitFunctionArgumentStmt(std::shared_ptr<Statement::FunctionArgument> stmt) override;
		Value VisitReturnStmt(std::shared_ptr<Statement::Return> stmt) override;
		Value VisitClassStmt(std::shared_ptr<Statement::Class> stmt) override;
	protected:


	};
}