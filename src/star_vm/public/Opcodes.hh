#pragma once

#include "StarVMMacro.hh"
#include <cstdint>

namespace star
{
	enum class Opcode : uint16_t
	{
		NOP = 0x0000,
		EXIT = 0x4000,
		PUSH_LOW = 0x4001,
		PUSH_HIGH = 0x4002,
	};
}