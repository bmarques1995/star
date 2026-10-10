#pragma once

#include "StarVMMacro.hh"
#include <cstdlib>

namespace star
{
    class STAR_VM_API Execute
    {
    public:
        virtual ~Execute() = default;
        virtual void ExecuteTAC(size_t* registerOut, size_t* registerIn1, size_t* registerIn2, size_t instruction) const = 0;
    };
}