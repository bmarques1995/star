#include "Callable.hh"

star::Callable::Callable()
{
	m_Arity = 0;
}

star::Callable::Callable(size_t arity, std::vector<std::pair<std::string, star::VariableType>> expectedTypes) :
	m_Arity(arity)
{
	for (auto& expectedType : expectedTypes)
	{
		Token virtualName{ TokenType::IDENTIFIER, expectedType.first, 0, 0, "::virtual" };
		m_ExpectedArgs.push_back(std::make_shared<star::Statement::FunctionArgument>(virtualName, expectedType.second));
	}
}

const std::vector<std::shared_ptr<star::Statement::FunctionArgument>>& star::Callable::ExpectedArgs() const
{
	return m_ExpectedArgs;
}

const size_t star::Callable::Arity() const
{
	return m_Arity;
}