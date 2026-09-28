#include "builtin/Escape.hh"
#include "RuntimeError.hh"
#include "EscapeObject.hh"

star::Escape::Escape() :
	Callable(1, { {"escapeArg", VariableType::Integer32} })
{
}

std::string star::Escape::ToString() const
{
	return "<escape: void>";
}

const star::VariableType star::Escape::ExpectedReturnType() const
{
	return VariableType::Void;
}

star::Value star::Escape::Call(Interpreter& interpreter, std::vector<Value> args)
{
	Token token{ TokenType::FUN, "<exit>", 1, 1, "::native" };
	if(args.size() != m_Arity)
		throw RuntimeError(token, "Invalid number of arguments for exit function");

	if(args[0].GetAssignedType() != VariableType::Integer32)
		throw RuntimeError(token, "Invalid argument type for exit function");

	int32_t exitCode = std::get<int32_t>(args[0].GetRValue());
	throw EscapeObject(exitCode);
	return { TokenType::VOID, "" };
}
