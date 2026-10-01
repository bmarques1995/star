#pragma once

namespace star
{
	enum class TACSymbol
	{
		ADD,
		SUB,
		MUL,
		DIV,
		MOD,
		ADDI,
		SUBI,
		MULI,
		DIVI,
		MODI,
		CALL,
		JUMP,
		RJUMP,
		SCOPE,
		ENDSCOPE,
		ENDSCOPEDECL,

		LESS,
		LESS_EQUAL,
		GREATER,
		GREATER_EQUAL
	};
}