#include "Function.hh"
#include "RuntimeError.hh"
#include "Interpreter.hh"
#include <magic_enum/magic_enum.hpp>

star::Function::Function(std::shared_ptr<Statement::Function> declaration, std::weak_ptr<Environment> chaining) :
	m_Declaration(declaration), m_Chaining(chaining)
{
}

const size_t star::Function::Arity() const
{
	return m_Declaration->m_Parameters.size();
}

std::string star::Function::ToString() const
{
	return "<fun: " + m_Declaration->m_Name.GetLexeme() + ">";
}

star::Value star::Function::Call(Interpreter& interpreter, std::vector<Value> args)
{
	auto env = std::make_shared<Environment>(m_Chaining);
	for (size_t i = 0; i < m_Declaration->m_Parameters.size(); i++)
	{
		if (!(m_Declaration->m_Parameters[i]->m_ExpectedType == VariableType::Dynamic) &&
			m_Declaration->m_Parameters[i]->m_ExpectedType != args[i].GetAssignedType())
		{
			std::string actualType = magic_enum::enum_name(args[i].GetAssignedType()).data();
			std::string expectedType = magic_enum::enum_name(m_Declaration->m_Parameters[i]->m_ExpectedType).data();
			throw RuntimeError(m_Declaration->m_Parameters[i]->m_Name, "Argument type mismatch, expected " + expectedType + ", but got " + actualType);
		}
		args[i].LockType();
		env->Define(m_Declaration->m_Parameters[i]->m_Name, args[i]);
	}
	try
	{
		interpreter.ExecuteBlock(m_Declaration->m_Body, env);
	}
	catch (Returner& returnValue)
	{
		if (m_Declaration->m_ExpectedType != VariableType::Dynamic &&
			m_Declaration->m_ExpectedType != returnValue.value.GetAssignedType())
			throw RuntimeError(m_Declaration->m_Name, "Return type mismatch");
		return returnValue.value;
	}
	catch (RuntimeError& e)
	{
		throw RuntimeError(m_Declaration->m_Name, e.what());
	}
	return {TokenType::VOID, ""};
}
