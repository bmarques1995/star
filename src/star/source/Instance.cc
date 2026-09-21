#include "Instance.hh"
#include "Class.hh"
#include "RuntimeError.hh"

star::Instance::Instance(std::shared_ptr<Class> className) :
	m_Class(std::move(className))
{}

star::Value star::Instance::Get(const Token & name)
{
	if (m_Fields.find(name.GetLexeme()) != m_Fields.end()) {
		return m_Fields[name.GetLexeme()];
	}

	auto method = m_Class->FindMethod(name.GetLexeme());
	if (method.has_value()) {
		return { method.value() };
	}
	return Value();
}

void star::Instance::Set(const Token& name, Value& value)
{
	if (m_Fields.find(name.GetLexeme()) == m_Fields.end())
	{
		throw RuntimeError(name, "Variable not defined: '" + name.GetLexeme() + "'.");
	}
	m_Fields[name.GetLexeme()] = std::move(value);
}

const size_t star::Instance::Arity() const
{
	return size_t();
}

star::Value star::Instance::Call(Interpreter& interpreter, std::vector<Value> arguments)
{
	return Value();
}

std::string star::Instance::ToString() const
{
	return m_Class->ToString() + " instance";
}
