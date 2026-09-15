#include "Environment.hh"
#include "RuntimeError.hh"
star::Environment::Environment() :
	m_Parent()
{
}

star::Environment::Environment(std::weak_ptr<Environment> parent) :
	m_Parent(parent)
{
}

void star::Environment::Define(const Token& name, Value value)
{
	auto it = m_Values.find(name.GetLexeme());
	if (it != m_Values.end())
	{
		throw RuntimeError(name, "Variable already defined: '" + name.GetLexeme() + "'.");
	}
	m_Values.insert_or_assign(name.GetLexeme(), std::move(value));
}

void star::Environment::Reassign(const Token& name, Value value)
{
	auto it = m_Values.find(name.GetLexeme());
	if (it == m_Values.end())
	{
		auto tempParent = m_Parent.lock();
		if (tempParent != nullptr)
			tempParent->Reassign(name, value);
		else
		{
			throw RuntimeError(name, "Cannot reassign undefined variable: '" + name.GetLexeme() + "'.");
		}
		return;
	}
	if(it->second.GetType() != VariableType::Dynamic && it->second.GetType() != value.GetAssignedType())
	{
		throw RuntimeError(name, "Cannot reassign variable with different type: '" + name.GetLexeme() + "'.");
	}
	if(it->second.GetType() != VariableType::Dynamic && value.GetType() == VariableType::Dynamic)
	{
		value.LockType();
	}
	m_Values.insert_or_assign(name.GetLexeme(), std::move(value));
}

star::Value star::Environment::Get(const Token& name) 
{
	auto tempParent = m_Parent.lock();
	auto elem = m_Values.find(name.GetLexeme());
	if (elem != m_Values.end()) {
		return elem->second;
	}
	if (tempParent != nullptr) {
		return tempParent->Get(name);
	}
	throw RuntimeError(name, "Undefined variable: '" + name.GetLexeme() + "'.");
}

star::Value* star::Environment::GetAsPtr(const Token& name)
{
	auto tempParent = m_Parent.lock();
	auto elem = m_Values.find(name.GetLexeme());
	if (elem != m_Values.end()) {
		return &m_Values.at(name.GetLexeme());
	}
	if (tempParent != nullptr) {
		return tempParent->GetAsPtr(name);
	}
	throw RuntimeError(name, "Undefined variable: '" + name.GetLexeme() + "'.");
}
