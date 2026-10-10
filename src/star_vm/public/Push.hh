#pragma once

#include "StarVMMacro.hh"
#include "Execute.hh"
#include "RegisterBuffer.hh"

namespace star
{
	class STAR_VM_API PushLow final : public Execute
	{
	public:
		PushLow();
		~PushLow() = default;

		void ExecuteTAC(size_t* registerOut, size_t* registerIn1, size_t* registerIn2, size_t instruction) const override;
	};

	class STAR_VM_API PushHigh final : public Execute
	{
	public:
		PushHigh();
		~PushHigh() = default;

		void ExecuteTAC(size_t* registerOut, size_t* registerIn1, size_t* registerIn2, size_t instruction) const override;
	};
}