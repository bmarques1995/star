#pragma once

#include "Callable.hh"

namespace star
{
	//fun print(value)#void;
	class MockPrint : public Callable
	{
	public:
		MockPrint(std::string* outBuffer);
		~MockPrint() = default;
		
		const size_t Arity() const override;
		std::string ToString() const override;

		Value Call(Interpreter& m_Interpreter, std::vector<Value> args) override;
	public:
		size_t m_Arity;
		std::string* m_OutBuffer;
	};
}