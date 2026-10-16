#include "mockPrint.hh"
#include <sstream>

star::MockPrint::MockPrint(std::string* outBuffer) 
	: m_Arity(1), m_OutBuffer(outBuffer)
{
}

const size_t star::MockPrint::Arity() const
{
	return m_Arity;
}

std::string star::MockPrint::ToString() const
{
	return "<print>";
}

star::Value star::MockPrint::Call(Interpreter& m_Interpreter, std::vector<Value> args)
{
	std::stringstream ss;
	ss << *m_OutBuffer << args[0].ToString() << "\n";
    *m_OutBuffer = ss.str();
	return {TokenType::VOID, ""};
}