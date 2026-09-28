#include "Print.hh"
#include "Console.hh"

star::Print::Print() 
	: Callable(1, { { "printArg", VariableType::String }})
{
}

std::string star::Print::ToString() const
{
	return "<print: void>";
}

const star::VariableType star::Print::ExpectedReturnType() const
{
	return VariableType::Void;
}

star::Value star::Print::Call(Interpreter& m_Interpreter, std::vector<Value> args)
{
	NeutralConsole() << args[0].ToString() << "\n";
	return {TokenType::VOID, ""};
}
