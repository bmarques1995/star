#pragma once

#include "StarMacro.hh"
#include "TACTable.hh"
#include "Token.hh"

namespace star
{
	class STAR_API TAC
	{
	public:
		TAC(TACSymbol symbol, Token& operand1, Token& operand2);
		virtual ~TAC() = default;

		const Token& GetOperand1() const;
		const Token& GetOperand2() const;
		const Token& GetResult() const;
		const TACSymbol& GetSymbol() const;

	protected:

		TACSymbol m_Symbol;
		Token m_Operand1;
		Token m_Operand2;
		Token m_Result;
	};
}