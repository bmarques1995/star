#pragma once

#include "StarVMMacro.hh"
#include <cstdint>
#include "RegisterName.hh"

namespace star
{
	class STAR_VM_API RegisterBuffer
	{
		friend class VM;
	public:
		RegisterBuffer();
		virtual ~RegisterBuffer() = default;

		size_t* GetRegister(RegisterName index);

	private:

		size_t m_Registers[256];
	};
}