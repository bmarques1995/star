#pragma once

#include "StarMacro.hh"
#include "Callable.hh"

namespace star
{
	// fun exit(code#u32)#void
	class STAR_API Escape : public Callable
	{
	public:
		Escape();
		~Escape() = default;

		const VariableType ExpectedReturnType() const override;
		std::string ToString() const override;
		
		Value Call(Interpreter& interpreter, std::vector<Value> args) override;
	private:
		size_t m_Arity;
	};
}