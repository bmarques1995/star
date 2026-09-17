#include "Resolver.hh"
#include "RuntimeError.hh"

void star::Resolver::Resolve(std::shared_ptr<Statement::Stmt> statement)
{
	statement->Accept(*this);
}

void star::Resolver::Resolve(std::shared_ptr<Expression::Expr> expression)
{
	expression->Accept(*this);
}

void star::Resolver::ResolveLocal(std::shared_ptr<Expression::Expr> expression, Token& name)
{
	size_t scopeSize = scopes.size();
	for (size_t i = 0; i < scopeSize; i++)
	{
		size_t index = scopeSize - i - 1;
		if (scopes[index].find(name.GetLexeme()) != scopes[index].end()) {
			identifiers[index].erase(name);
			m_Interpreter->Resolve(expression, i);
			return;
		}
	}
}

void star::Resolver::ResolveFunction(std::vector<std::shared_ptr<Statement::FunctionArgument>> arguments, std::shared_ptr<Statement::Function> function, FunctionType type)
{
	FunctionType chainingFunction = m_CurrentFunctionType;
	FunctionType currentType = type;
	BeginScope();
	for (auto& argument : arguments)
	{
		Declare(*(argument.get()));
		Define(argument->m_Name);
	}
	Resolve(function->m_Body);
	EndScope();
	m_CurrentFunctionType = chainingFunction;
}

void star::Resolver::BeginScope()
{
	identifiers.push_back(std::map<Token, std::pair<VariableType, size_t>>());
	scopes.push_back(std::map<std::string, bool>());
}

void star::Resolver::EndScope()
{
	identifiers.pop_back();
	scopes.pop_back();
}

void star::Resolver::Declare(Statement::FunctionArgument& name)
{
	if(scopes.empty() && identifiers.empty())
		return;
	auto currentBlock = identifiers.rbegin();
	auto currentScope = scopes.rbegin();

	if (currentBlock->find(name.m_Name) != currentBlock->end() && 
		currentScope->find(name.m_Name.GetLexeme()) != currentScope->end())
	{
		throw RuntimeError(name.m_Name, "Variable already defined: '" + name.m_Name.GetLexeme() + "'.");
	}

	currentBlock->insert_or_assign(name.m_Name, std::make_pair(name.m_ExpectedType, 0));
	currentScope->insert_or_assign(name.m_Name.GetLexeme(), false);
}

void star::Resolver::Define(Token& name)
{
	if(scopes.empty() && identifiers.empty())
		return;
	auto currentScope = scopes.rbegin();
	currentScope->insert_or_assign(name.GetLexeme(), true);
}

star::Resolver::Resolver(std::shared_ptr<Interpreter>& interpreter) :
	m_Interpreter(interpreter)
{
	BeginScope();
}

star::Resolver::~Resolver()
{
	EndScope();
}

void star::Resolver::Resolve(std::vector<std::shared_ptr<Statement::Stmt>>& statements)
{
	for(auto& statement : statements)
		Resolve(statement);
}

star::Value star::Resolver::VisitGroupingExpr(std::shared_ptr<Expression::Grouping> expr)
{
	Resolve(expr->m_Expression);
	return {};
}

star::Value star::Resolver::VisitLiteralExpr(std::shared_ptr<Expression::Literal> expr)
{
	if (expr.get() != nullptr) {}
	return {};
}

star::Value star::Resolver::VisitTemplateLiteralExpr(std::shared_ptr<Expression::TemplateLiteral> expr)
{
	if (expr.get() != nullptr){}
	return {};
}

star::Value star::Resolver::VisitUnaryExpr(std::shared_ptr<Expression::Unary> expr)
{
	Resolve(expr->m_Right);
	return {};
}

star::Value star::Resolver::VisitPreIncrementExpr(std::shared_ptr<Expression::PreIncrement> expr)
{
	Resolve(expr->m_Right);
	return {};
}

star::Value star::Resolver::VisitPostIncrementExpr(std::shared_ptr<Expression::PostIncrement> expr)
{
	Resolve(expr->m_Left);
	return {};
}

star::Value star::Resolver::VisitBinaryExpr(std::shared_ptr<Expression::Binary> expr)
{
	Resolve(expr->m_Left);
	Resolve(expr->m_Right);
	return {};
}

star::Value star::Resolver::VisitTernaryExpr(std::shared_ptr<Expression::Ternary> expr)
{
	Resolve(expr->m_Condition);
	Resolve(expr->m_TrueSentence);
	Resolve(expr->m_FalseSentence);
	return {};
}

star::Value star::Resolver::VisitVariableExpr(std::shared_ptr<Expression::Variable> expr)
{
	if (!scopes.empty()) {
		auto& currentScope = scopes.back();
		auto elem = currentScope.find(expr->m_Name.GetLexeme());
		if (elem != currentScope.end() && elem->second == false) {
			throw RuntimeError(expr->m_Name, "Can't read local variable in this own initializer.");
		}
	}
	ResolveLocal(expr, expr->m_Name);
	return {};
}

star::Value star::Resolver::VisitAssignmentExpr(std::shared_ptr<Expression::Assignment> expr)
{
	Resolve(expr->m_Value);
	ResolveLocal(expr, expr->m_Name);
	return {};
}

star::Value star::Resolver::VisitLogicalExpr(std::shared_ptr<Expression::Logical> expr)
{
	Resolve(expr->m_Left);
	Resolve(expr->m_Right);
	return {};
}

star::Value star::Resolver::VisitCallExpr(std::shared_ptr<Expression::Call> expr)
{
	Resolve(expr->m_Callee);
	for (auto& argument : expr->m_Arguments)
		Resolve(argument);
	return {};
}

star::Value star::Resolver::VisitExpressionStmt(std::shared_ptr<Statement::Expression> stmt)
{
	Resolve(stmt->m_Expression);
	return {};
}

star::Value star::Resolver::VisitVariableStmt(std::shared_ptr<Statement::Variable> stmt)
{
	Statement::FunctionArgument name{ stmt->m_Name, stmt->m_ExpectedType };
	Declare(name);
	if (stmt->m_Init != nullptr)
	{
		Resolve(stmt->m_Init);
	}
	Define(stmt->m_Name);
	return {};
}

star::Value star::Resolver::VisitAutoStmt(std::shared_ptr<Statement::Auto> stmt)
{
	Statement::FunctionArgument name{ stmt->m_Name, stmt->m_Init->Accept(*m_Interpreter).GetAssignedType() };
	Declare(name);
	if (stmt->m_Init != nullptr)
	{
		Resolve(stmt->m_Init);
	}
	Define(stmt->m_Name);
	return Value();
}

star::Value star::Resolver::VisitBlockStmt(std::shared_ptr<Statement::Block> stmt)
{
	BeginScope();
	Resolve(stmt->m_Statements);
	EndScope();
	return {};
}

star::Value star::Resolver::VisitIfStmt(std::shared_ptr<Statement::If> stmt)
{
	Resolve(stmt->m_Condition);
	Resolve(stmt->m_ThenBranch);
	if (stmt->m_ElseBranch != nullptr) Resolve(stmt->m_ElseBranch);
	return {};
}

star::Value star::Resolver::VisitWhileStmt(std::shared_ptr<Statement::While> stmt)
{
	Resolve(stmt->m_Condition);
	Resolve(stmt->m_Body);
	return {};
}

star::Value star::Resolver::VisitFunctionStmt(std::shared_ptr<Statement::Function> stmt)
{
	Statement::FunctionArgument name{ stmt->m_Name, stmt->m_ExpectedType };
	Declare(name);
	Define(name.m_Name);
	ResolveFunction(stmt->m_Parameters, stmt, FunctionType::FUNCTION);
	return {};
}

star::Value star::Resolver::VisitFunctionArgumentStmt(std::shared_ptr<Statement::FunctionArgument> stmt)
{
	Statement::FunctionArgument name{ stmt->m_Name, stmt->m_ExpectedType };
	Declare(name);
	Define(name.m_Name);
	return {};
}

star::Value star::Resolver::VisitReturnStmt(std::shared_ptr<Statement::Return> stmt)
{
	if (m_CurrentFunctionType == FunctionType::NONE)
		throw RuntimeError(stmt->m_Keyword, "Can't return from top level code.");
	if (stmt->m_Value != nullptr) 
		Resolve(stmt->m_Value);
	return {};
}
