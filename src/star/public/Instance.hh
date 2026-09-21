#pragma once

#include <optional>
#include "Token.hh"
#include "Callable.hh"
#include "Function.hh"
#include "StarMacro.hh"
#include <memory>
#include <unordered_map>

namespace star
{
    class Class;
    class STAR_API Instance : public Callable
    {
    public:
        Instance(std::shared_ptr<Class> className);

        std::shared_ptr<Class> m_Class;
        std::unordered_map<std::string, Value> m_Fields;

        Value Get(const Token& name);
        void Set(const Token& name, Value& value);

        const size_t Arity() const override;
        Value Call(Interpreter& interpreter, std::vector<Value> arguments) override;
        std::string ToString() const override;
    };
}