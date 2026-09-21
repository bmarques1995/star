#pragma once


#include "StarMacro.hh"
#include "Token.hh"
#include "Value.hh"
#include "Interpreter.hh"
#include <memory>
#include <vector>
#include <map>
#include <utility>
#include "FunctionType.hh"

namespace star
{
	class STAR_API Resolver : public Expression::ExprVisitor, public Statement::StmtVisitor
	{
	private:
		std::shared_ptr<Interpreter> m_Interpreter;
		std::vector<std::map<std::string, bool>> scopes;
		std::vector<std::map<Token, std::pair<VariableType, size_t>>> identifiers;
		FunctionType m_CurrentFunctionType;

		void Resolve(std::shared_ptr<Statement::Stmt> statement);
		void Resolve(std::shared_ptr<Expression::Expr> expression);

		void ResolveLocal(std::shared_ptr<Expression::Expr> expression, Token& name);
		void ResolveFunction(std::vector<std::shared_ptr<Statement::FunctionArgument>> arguments, std::shared_ptr<Statement::Function> function, FunctionType type);

		void BeginScope();
		void EndScope();

		void Declare(Statement::FunctionArgument& name);
		void Define(Token& name);
	
	public:
		Resolver(std::shared_ptr<Interpreter>& interpreter);
		~Resolver();
		void Resolve(std::vector<std::shared_ptr<Statement::Stmt>>& statements);

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
	};
}