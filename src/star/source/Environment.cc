#include "Environment.hh"
#include "RuntimeError.hh"
#include <memory>
#include <stdexcept>

star::Environment::Environment() :
	m_Parent()
{
#ifdef STAR_DEBUG
	m_EnvName = "";
#endif
}

star::Environment::Environment(std::weak_ptr<Environment> parent) :
	m_Parent(parent)
{
#ifdef STAR_DEBUG
	m_EnvName = "";
#endif
}

void star::Environment::Define(const Token& name, Value value, bool lockType)
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
	auto tempParent = m_Parent.expired() ? nullptr : m_Parent.lock();
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

void star::Environment::ReassignAt(const Token& name, Value value, size_t distance)
{
	auto desiredEnv = Anchestor(distance);
	std::shared_ptr<Environment> tempParent;
	try
	{
		TempUnlock(&tempParent, &desiredEnv);
	}
	catch (const std::exception& e)
	{
		throw RuntimeError(name, "Undefined variable: '" + name.GetLexeme() + "'.");
	}
	tempParent->Reassign(name, value);
}

star::Value star::Environment::GetAt(const Token& name, size_t distance)
{
	auto desiredEnv = Anchestor(distance);
	std::shared_ptr<Environment> tempParent;
	try
	{
		TempUnlock(&tempParent, &desiredEnv);
	}
	catch (const std::exception& e)
	{
		throw RuntimeError(name, "Undefined variable: '" + name.GetLexeme() + "'.");
	}
	return tempParent->Get(name);
}

star::Value* star::Environment::GetAsPtrAt(const Token& name, size_t distance)
{
	auto desiredEnv = Anchestor(distance);
	std::shared_ptr<Environment> tempParent;
	try
	{
		TempUnlock(&tempParent, &desiredEnv);
	}
	catch (const std::runtime_error& e)
	{
		throw RuntimeError(name, "Undefined variable: '" + name.GetLexeme() + "'.");
	}
	return tempParent->GetAsPtr(name);
}

#ifdef STAR_DEBUG

void star::Environment::SetEnvName(std::string name)
{
	m_EnvName = name;
}

#endif

std::weak_ptr<star::Environment> star::Environment::Anchestor(size_t distance)
{
	std::weak_ptr<Environment> tempParent = weak_from_this();
	for (size_t i = 0; i < distance; i++)
	{
		tempParent = !tempParent.expired() ? tempParent.lock()->m_Parent : std::weak_ptr<Environment>(); //!tempParent.expired()
	}
	return tempParent;
}

void star::Environment::TempUnlock(std::shared_ptr<Environment>* dest, std::weak_ptr<Environment>* src)
{
	if (src->expired())
	{
		throw std::runtime_error("Undefined scope ");
	}
	else
	{
		*dest = src->lock();
	}
}
