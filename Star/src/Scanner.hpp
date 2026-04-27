#pragma once

#include "StarCore.hpp"
#include "Token.hpp"
#include "Debug.hpp"
#include <iostream>
#include <vector>
#include <unordered_map>

namespace Star
{
	class STAR_API Scanner
	{
	public:
		Scanner(const std::string& source);
		std::vector<Token> ScanTokens();
	private:
		const std::string source;
		std::vector<Token> tokens;
		std::unordered_map<std::string, TokenType> keywords;
		size_t start = 0;
		size_t current = 0;
		size_t line = 1;
		
		bool IsAtEnd();
		bool IsAlpha(char c);

		bool IsDigit(char c);

		bool IsAlphaNumeric(char c);

		bool Match(char expected);

		void ScanToken();

		char Advance();

		void AddToken(TokenType type);
		void AddToken(TokenType type, std::any literal);

		char Peek();

		char PeekNext();

		void String();
		void Number();
		void Identifier();

		void GetNumberBody();
		void GetNumberExponent();
		void GetNumberSuffix();
		void ScanNumberType(const std::string& suffixStr, bool isDecimal, std::type_index* literalType);
	};
}