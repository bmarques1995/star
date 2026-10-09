#include "AstPrinter.hh"
#include "Value.hh"
#include <memory>
#include <iostream>
#include "Stmt.hh"
#include "Expr.hh"

const std::unordered_map<star::VariableType, std::string> star::AstPrinter::s_TypeToString = 
{
	{star::VariableType::Null, "null"},
    {star::VariableType::Boolean, "boolean"},
	{star::VariableType::Character, "char"},
    {star::VariableType::String, "string"},
	{star::VariableType::Integer8, "i8"},
	{star::VariableType::Integer16, "i16"},
	{star::VariableType::Integer32, "i32"},
	{star::VariableType::Integer64, "i64"},
	{star::VariableType::Unsigned8, "u8"},
	{star::VariableType::Unsigned16, "u16"},
	{star::VariableType::Unsigned32, "u32"},
	{star::VariableType::Unsigned64, "u64"},
    {star::VariableType::Float32, "float"},
    {star::VariableType::Float64, "double"},

	{star::VariableType::Callable, "callable"},
	{star::VariableType::Class, "class"},
	{star::VariableType::Instance, "instance"},
	{star::VariableType::Dynamic, "dynamic"},
	{star::VariableType::Void, "void"},
};
const std::unordered_map<star::TokenType, std::string> star::AstPrinter::s_TokenToString = 
{
    {star::TokenType::PLUS, "+"},
    {star::TokenType::MINUS, "-"},
    {star::TokenType::STAR, "*"},
    {star::TokenType::SLASH, "/"},
    {star::TokenType::MOD, "%"},
    {star::TokenType::REC_PLUS, "+="},
	{star::TokenType::REC_MINUS, "-="},
	{star::TokenType::REC_STAR, "*="},
	{star::TokenType::REC_SLASH, "/="},
	{star::TokenType::REC_MOD, "%="},
	{star::TokenType::INCREMENT, "++"},
	{star::TokenType::DECREMENT, "--"},
	{star::TokenType::BANG, "!"},
	{star::TokenType::QUESTION, "?"},
	{star::TokenType::AND, "&&"},
	{star::TokenType::OR, "||"},
	{star::TokenType::GREATER, ">"},
	{star::TokenType::GREATER_EQUAL, ">="},
	{star::TokenType::LESS, "<"},
	{star::TokenType::LESS_EQUAL, "<="},
	{star::TokenType::EQUAL_EQUAL, "=="},
    {star::TokenType::BANG_EQUAL, "!="},
    {star::TokenType::LEFT_BRACE, "{"},
    {star::TokenType::RIGHT_BRACE, "}"},
	{star::TokenType::LEFT_PAREN, "("},
	{star::TokenType::RIGHT_PAREN, ")"},
	{star::TokenType::COMMA, ","},
	{star::TokenType::DOT, "."},
	{star::TokenType::COLON, ":"},
	{star::TokenType::SEMICOLON, ";"},
	{star::TokenType::HASHTAG, "#"},
};

void star::AstPrinter::Print(std::shared_ptr<Statement::Stmt> stmt)
{
    stmt->Accept(*this);
}

star::Value star::AstPrinter::VisitPostIncrementExpr(std::shared_ptr<Expression::PostIncrement> expr)
{
	auto it = s_TokenToString.find(expr->m_Operator.GetTokenType());
	std::string op = it != s_TokenToString.end() ? it->second : "";
    std::cout << expr->m_Name.GetLexeme() << op << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitBinaryExpr(std::shared_ptr<Expression::Binary> expr)
{
    auto it = s_TokenToString.find(expr->m_Operator.GetTokenType());
    std::string op = it != s_TokenToString.end() ? it->second : "";
	expr->m_Left->Accept(*this);
	std::cout << " " << op << " ";
	expr->m_Right->Accept(*this);
	std::cout << '\n';
    return Value{};
}

star::Value star::AstPrinter::VisitGroupingExpr(std::shared_ptr<Expression::Grouping> expr)
{
	expr->m_Expression->Accept(*this);
    return Value{};
}

star::Value star::AstPrinter::VisitLiteralExpr(std::shared_ptr<Expression::Literal> expr)
{
	std::cout << expr->m_Value;
    return Value{};
}

star::Value star::AstPrinter::VisitUnaryExpr(std::shared_ptr<Expression::Unary> expr)
{
	auto it = s_TokenToString.find(expr->m_Operator.GetTokenType());
	std::string op = it != s_TokenToString.end() ? it->second : "";
	std::cout << op;
	expr->m_Right->Accept(*this);
	std::cout << '\n';
    return Value{};
}

star::Value star::AstPrinter::VisitPreIncrementExpr(std::shared_ptr<Expression::PreIncrement> expr)
{
    auto it = s_TokenToString.find(expr->m_Operator.GetTokenType());
    std::string op = it != s_TokenToString.end() ? it->second : "";
    std::cout << op << expr->m_Name.GetLexeme() << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitTemplateLiteralExpr(std::shared_ptr<Expression::TemplateLiteral> expr)
{
	auto& shards = expr->m_TemplateShards;
	std::cout << "template string: " << '\n';
    for(auto& shard : shards)
    {
        std::visit([this](const auto& shard) -> void
            {
                using T = std::decay_t<decltype(shard)>;
                if constexpr (std::is_same_v<T, std::pair<std::shared_ptr<Expression::Expr>, std::string>>)
                {
					shard.first->Accept(*this);
                    std::cout << " format: {" << shard.second << '}' << '\n';
                }
				else
				{
					std::cout << shard << '\n';
				}
            }, 
        shard);
    }
    return Value{};
}

star::Value star::AstPrinter::VisitTernaryExpr(std::shared_ptr<Expression::Ternary> expr)
{
	expr->m_Condition->Accept(*this);
	std::cout << " ? ";
	expr->m_TrueSentence->Accept(*this); 
	std::cout << " : ";
	expr->m_FalseSentence->Accept(*this);
	std::cout << '\n';
    return Value{};
}

star::Value star::AstPrinter::VisitVariableExpr(std::shared_ptr<Expression::Variable> expr)
{
	std::cout << expr->m_Name.GetLexeme() << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitAssignmentExpr(std::shared_ptr<Expression::Assignment> expr)
{
	std::cout << expr->m_Name.GetLexeme() << " = ";
	expr->m_Value->Accept(*this);
	std::cout << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitLogicalExpr(std::shared_ptr<Expression::Logical> expr)
{
	auto it = s_TokenToString.find(expr->m_Operator.GetTokenType());
	std::string op = it != s_TokenToString.end() ? it->second : "";
	expr->m_Left->Accept(*this);
	std::cout << " " << op << " ";
	expr->m_Right->Accept(*this);
	std::cout << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitCallExpr(std::shared_ptr<Expression::Call> expr)
{
	expr->m_Callee->Accept(*this);
	std::cout << "(";
	for (auto it = expr->m_Arguments.begin(); it != expr->m_Arguments.end(); ++it)
	{
		std::cout << '\n';
		(*it)->Accept(*this);
		if (it + 1 != expr->m_Arguments.end())
		{
			std::cout << ", ";
		}
	}
	std::cout << ")" << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitGetExpr(std::shared_ptr<Expression::Get> expr)
{
	expr->m_Object->Accept(*this);
    std::cout << "." << expr->m_Name.GetLexeme() << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitSetExpr(std::shared_ptr<Expression::Set> expr)
{
	expr->m_Object->Accept(*this);
	std::cout << "." << expr->m_Name.GetLexeme() << " = ";
	expr->m_Value->Accept(*this);
	std::cout << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitExpressionStmt(std::shared_ptr<Statement::Expression> stmt)
{
	stmt->m_Expression->Accept(*this);
    std::cout << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitVariableStmt(std::shared_ptr<Statement::Variable> stmt)
{
	std::cout << stmt->m_Name.GetLexeme() << " : " << s_TypeToString.at(stmt->m_ExpectedType) << " = ";
	stmt->m_Init->Accept(*this);
	std::cout << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitAutoStmt(std::shared_ptr<Statement::Auto> stmt)
{
	std::cout << stmt->m_Name.GetLexeme() << " = ";
	stmt->m_Init->Accept(*this);
	std::cout << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitBlockStmt(std::shared_ptr<Statement::Block> stmt)
{
	std::cout << "{\n";
	for (auto& statement : stmt->m_Statements)
	{
		statement->Accept(*this);
	}
	std::cout << "}\n";
    return Value();
}

star::Value star::AstPrinter::VisitIfStmt(std::shared_ptr<Statement::If> stmt)
{
	std::cout << "if (" << stmt->m_Condition->Accept(*this) << ") ";
	stmt->m_ThenBranch->Accept(*this);
	if (stmt->m_ElseBranch != nullptr)
	{
		std::cout << "else ";
		stmt->m_ElseBranch->Accept(*this);
	}
    return Value();
}

star::Value star::AstPrinter::VisitWhileStmt(std::shared_ptr<Statement::While> stmt)
{
    std::cout << "while (" << stmt->m_Condition->Accept(*this) << ") ";
	stmt->m_Body->Accept(*this);
    return Value();
}

star::Value star::AstPrinter::VisitForStmt(std::shared_ptr<Statement::ForLoop> stmt)
{
	std::cout << "for (";
	stmt->m_Start->Accept(*this);
	std::cout << " ; ";
	stmt->m_Condition->Accept(*this);
	std::cout << " ; ";
	stmt->m_LastCommand->Accept(*this);
	std::cout << ") ";
	stmt->m_Body->Accept(*this);
    return Value();
}

star::Value star::AstPrinter::VisitFunctionStmt(std::shared_ptr<Statement::Function> stmt)
{
	std::cout << "function " << stmt->m_Name.GetLexeme() << "(";
	for (auto it = stmt->m_Parameters.begin(); it != stmt->m_Parameters.end(); ++it)
	{
		(*it)->Accept(*this);
		if (it + 1 != stmt->m_Parameters.end())
		{
			std::cout << ", ";
		}
	}
	std::cout << ") : " << s_TypeToString.at(stmt->m_ExpectedType) << "\n{\n";
	for (auto& statement : stmt->m_Body)
	{
		statement->Accept(*this);
	}
	std::cout << "}\n";
    return Value();
}

star::Value star::AstPrinter::VisitFunctionArgumentStmt(std::shared_ptr<Statement::FunctionArgument> stmt)
{
	std::cout << stmt->m_Name.GetLexeme() << " : " << s_TypeToString.at(stmt->m_ExpectedType) << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitReturnStmt(std::shared_ptr<Statement::Return> stmt)
{
	std::cout << "return ";
	stmt->m_Value->Accept(*this);
	std::cout << '\n';
    return Value();
}

star::Value star::AstPrinter::VisitClassStmt(std::shared_ptr<Statement::Class> stmt)
{
	std::cout << "class " << stmt->m_Name.GetLexeme() << "\n{\n";
	for (auto& method : stmt->m_Methods)
	{
		std::cout << method->Accept(*this);
	}
	for (auto& field : stmt->m_Fields)
	{
		std::cout << field->Accept(*this);
	}
	std::cout << "}\n";
    return Value();
}