#pragma once

#include "StarMacro.hh"
#include "Callable.hh"
#include "Scanner.hh"
#include "Parser.hh"
#include "Interpreter.hh"

namespace star
{
	class STAR_API Runtime
	{
	public:
		Runtime();
		Runtime(std::initializer_list<std::pair<std::string, std::shared_ptr<Callable>>> callables);
		virtual ~Runtime() = default;

		void RegisterCallable(const std::string& name, std::shared_ptr<Callable> callable);
		void Run(const std::string& source, const std::string& filepath = "::repl");

	private:
		Interpreter m_Interpreter;
	};
}