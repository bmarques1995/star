#pragma once

#include <memory>
#include <vector>
#include "Value.hh"
#include "StarMacro.hh"
#include "Stmt.hh"

namespace star
{
	class Interpreter;

    class STAR_API Callable
    {
    public:
        Callable();
        Callable(size_t arity, std::vector<std::pair<std::string, star::VariableType>> expectedTypes);

        virtual ~Callable() = default;

		const size_t Arity() const;
		virtual std::string ToString() const = 0;

        virtual const VariableType ExpectedReturnType() const = 0;
        const std::vector<std::shared_ptr<Statement::FunctionArgument>>& ExpectedArgs() const;

        virtual Value Call(Interpreter& interpreter, std::vector<Value> args) = 0;
    protected:
        std::vector<std::shared_ptr<Statement::FunctionArgument>> m_ExpectedArgs;
        size_t m_Arity;
    };
}