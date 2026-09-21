#pragma once

#include "StarMacro.hh"
#include "Callable.hh"
#include "Environment.hh"
#include "Interpreter.hh"
#include "Stmt.hh"
#include <initializer_list>
#include <optional>

namespace star
{
	class STAR_API Class : public Callable, public std::enable_shared_from_this<Class>
	{
	public:
		Class(const Token& name, 
			std::vector<std::shared_ptr<Statement::Function>> methods,
			std::vector<std::shared_ptr<Statement::Stmt>> fields,
			Interpreter& interpreter
		);

		const size_t Arity() const override;
		std::string ToString() const override;
		std::optional<std::shared_ptr<Function>> FindMethod(const std::string& name) const;

		Value Call(Interpreter& interpreter, std::vector<Value> args) override;
	protected:
		Token m_Name;
		std::unordered_map<std::string, std::shared_ptr<Function>> m_Methods;
		std::unordered_map<std::string, Value> m_Fields;

	};
}