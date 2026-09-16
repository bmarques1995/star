#include "Runtime.hh"
#include <deque>

star::Runtime::Runtime()
{
}

star::Runtime::Runtime(std::initializer_list<std::pair<std::string, std::shared_ptr<Callable>>> callables)
{
	for (auto& callable : callables)
		m_Interpreter.RegisterCallable(callable.first, callable.second);
}

void star::Runtime::RegisterCallable(const std::string& name, std::shared_ptr<Callable> callable)
{
	m_Interpreter.RegisterCallable(name, callable);
}

void star::Runtime::Run(const std::string& source, const std::string& filepath)
{
	Scanner scanner{source, filepath};
	auto tokens = scanner.ScanTokens();
	Parser parser{tokens};
	auto statements = parser.Parse();
	m_Interpreter.Interpret(statements);
}
