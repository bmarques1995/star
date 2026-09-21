#include "Class.hh"
#include "Interpreter.hh"
#include "Instance.hh"

star::Class::Class(const Token& name,
	std::vector<std::shared_ptr<Statement::Function>> methods,
	std::vector<std::shared_ptr<Statement::Stmt>> fields,
	Interpreter& interpreter
	)
	: m_Name(name)
{
	for(const auto& method : methods)
		m_Methods[method->m_Name.GetLexeme()] = std::make_shared<Function>(method, interpreter.m_CurrentEnv);
	for(const auto& field : fields)
	{
		if(const auto varField = std::dynamic_pointer_cast<Statement::Variable>(field))
			if(varField->m_Init != nullptr)
				m_Fields[varField->m_Name.GetLexeme()] = varField->m_Init->Accept(interpreter);
		if (const auto autoField = std::dynamic_pointer_cast<Statement::Auto>(field))
			if (autoField->m_Init != nullptr)
				m_Fields[autoField->m_Name.GetLexeme()] = autoField->m_Init->Accept(interpreter);
	}
}

const size_t star::Class::Arity() const
{
	return 0;
}

std::string star::Class::ToString() const
{
	return m_Name.GetLexeme();
}

std::optional<std::shared_ptr<star::Function>> star::Class::FindMethod(const std::string& name) const
{
	auto it = m_Methods.find(name);
	if (it != m_Methods.end())
		return it->second;
	else
		return std::nullopt;
}

star::Value star::Class::Call(Interpreter& interpreter, std::vector<Value> args)
{
	auto instance = std::make_shared<Instance>(shared_from_this());
	return { instance };
}
