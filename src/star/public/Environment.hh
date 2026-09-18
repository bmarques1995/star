#pragma once

#include <unordered_map>
#include "Value.hh"
#include <memory>
#include "Token.hh"
#include "StarMacro.hh"

namespace star
{
	class STAR_API Environment : public std::enable_shared_from_this<Environment>
	{
	private:
		std::unordered_map<std::string, Value> m_Values;
		std::weak_ptr<Environment> m_Parent;

		void TempUnlock(std::shared_ptr<Environment>* dest, std::weak_ptr<Environment>* src);
	public:
		Environment();
		Environment(std::weak_ptr<Environment> parent);

		void Define(const Token& name, Value value);
		void Reassign(const Token& name, Value value);
		Value Get(const Token& name);
		Value* GetAsPtr(const Token& name);
		void ReassignAt(const Token& name, Value value, size_t distance);
		Value GetAt(const Token& name, size_t distance);
		Value* GetAsPtrAt(const Token& name, size_t distance);

#ifdef STAR_DEBUG
		void SetEnvName(std::string name);
	private:
		std::string m_EnvName;
	public:
#endif

		std::weak_ptr<Environment> Anchestor(size_t distance);
	};
}