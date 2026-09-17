#include "Runtime.hh"
#include "Scanner.hh"
#include "Parser.hh"
#include "Resolver.hh"

star::Runtime::Runtime() :
	m_Interpreter(std::make_shared<Interpreter>())
{
}

star::Runtime::Runtime(std::initializer_list<std::pair<std::string, std::shared_ptr<Callable>>> callables) :
	m_Interpreter(std::make_shared<Interpreter>())
{
	for (auto& callable : callables)
		m_Interpreter->RegisterCallable(callable.first, callable.second);
}

void star::Runtime::RegisterCallable(const std::string& name, std::shared_ptr<Callable> callable)
{
	m_Interpreter->RegisterCallable(name, callable);
}

void star::Runtime::Run(const std::string& source, const std::string& filepath)
{
	Scanner scanner{source, filepath};
	auto tokens = scanner.ScanTokens();
	Parser parser{tokens};
	auto statements = parser.Parse();
	Resolver resolver{ m_Interpreter };
	resolver.Resolve(statements);
	m_Interpreter->Interpret(statements);
}
