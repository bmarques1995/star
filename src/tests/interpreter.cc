#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Callable.hh"
#include "Scanner.hh"
#include "Parser.hh"
#include "Interpreter.hh"
#include "mockPrint.hh"

namespace star
{

	class MockInterpreter : public Interpreter
	{
	public:
		MockInterpreter()
		{
			RegisterCallable("print", std::make_shared<MockPrint>(&m_Result));
		}

		~MockInterpreter() = default;

		const std::string& GetText()
		{
			return m_Result;
		}

	private:
		mutable std::string m_Result;
	};

	TEST(interpreter, expression)
	{
		/*
		print(\"Hello String\")
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER, "print", 1, 0, "::repl"},
			{ TokenType::LEFT_PAREN, "(", 1, 5, "::repl"},
			{ TokenType::STRING, "Hello String", 1, 6, "::repl"},
			{ TokenType::RIGHT_PAREN, ")", 1, 20, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 21, "::repl"},
			{ TokenType::ST_EOF, "", 3, 0, "::repl"},
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "Hello String");
	}

	TEST(interpreter, ternary_true_expression)
	{
		/*
		print(4 < 5 ? 12 : 7)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 6, "::repl" },
			{ TokenType::LESS ,"<", 1, 8, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 10, "::repl" },
			{ TokenType::QUESTION ,"?", 1, 12, "::repl" },
			{ TokenType::NUMBER ,"12", 1, 14, "::repl" },
			{ TokenType::COLON ,":", 1, 17, "::repl" },
			{ TokenType::NUMBER ,"7", 1, 19, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 20, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 21, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "12");
	}

	TEST(interpreter, ternary_false_expression)
	{
		/*
		print(4 > 5 ? 12 : 7)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 6, "::repl" },
			{ TokenType::GREATER ,">", 1, 8, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 10, "::repl" },
			{ TokenType::QUESTION ,"?", 1, 12, "::repl" },
			{ TokenType::NUMBER ,"12", 1, 14, "::repl" },
			{ TokenType::COLON ,":", 1, 17, "::repl" },
			{ TokenType::NUMBER ,"7", 1, 19, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 20, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 21, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "7");
	}

	TEST(interpreter, equal_equal_ternary)
	{
		/*
		print(4 == 5 ? 12 : 7)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER, "print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 6, "::repl" },
			{ TokenType::EQUAL_EQUAL ,"==", 1, 8, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 11, "::repl" },
			{ TokenType::QUESTION ,"?", 1, 13, "::repl" },
			{ TokenType::NUMBER ,"12", 1, 15, "::repl" },
			{ TokenType::COLON ,":", 1, 18, "::repl" },
			{ TokenType::NUMBER ,"7", 1, 20, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 21, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 22, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "7");
	}

	TEST(interpreter, bang_equal_ternary)
	{
		/*
		print(4 != 5 ? 12 : 7)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 6, "::repl" },
			{ TokenType::BANG_EQUAL ,"!=", 1, 8, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 11, "::repl" },
			{ TokenType::QUESTION ,"?", 1, 13, "::repl" },
			{ TokenType::NUMBER ,"12", 1, 15, "::repl" },
			{ TokenType::COLON ,":", 1, 18, "::repl" },
			{ TokenType::NUMBER ,"7", 1, 20, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 21, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 22, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		//for(auto& token : tokens) std::cout << token.StringSerialize() << "," << std::endl;
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "12");
	}

	TEST(interpreter, linear_expression)
	{
		/*
		print(6 * 2 + 3)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER, "print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"6", 1, 6, "::repl" },
			{ TokenType::STAR ,"*", 1, 8, "::repl" },
			{ TokenType::NUMBER ,"2", 1, 10, "::repl" },
			{ TokenType::PLUS ,"+", 1, 12, "::repl" },
			{ TokenType::NUMBER ,"3", 1, 14, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 15, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 16, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "15");
	}

	TEST(interpreter, grouped_expression)
	{
		/*
		print(6 * (2 + 3))
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"6", 1, 6, "::repl" },
			{ TokenType::STAR ,"*", 1, 8, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 10, "::repl" },
			{ TokenType::NUMBER ,"2", 1, 11, "::repl" },
			{ TokenType::PLUS ,"+", 1, 13, "::repl" },
			{ TokenType::NUMBER ,"3", 1, 15, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 16, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 17, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 18, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "30");
	}

	TEST(interpreter, negate_true_expression)
	{
		/*
		print(!true);
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::BANG ,"!", 1, 6, "::repl" },
			{ TokenType::ST_TRUE ,"true", 1, 7, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 11, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 12, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		/*std::cout << "std::vector<Token> tokens = \n{\n";
		for (auto& token : tokens) std::cout << token.StringSerialize() << "," << std::endl;
		std::cout << "};\n";*/
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "false");
	}

	TEST(interpreter, negate_false_expression)
	{
		/*
		print(!false)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::BANG ,"!", 1, 6, "::repl" },
			{ TokenType::ST_FALSE ,"false", 1, 7, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 12, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 13, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "true");
	}

	TEST(interpreter, negate_number)
	{
		/*
		print(-5)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::MINUS ,"-", 1, 6, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 7, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 8, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 9, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" },
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "-5");
	}

	TEST(interpreter, template_string)
	{
		/*
		print(`This is a template string, to prove, use these expressions: ${1995/35}$ and ${143-13}$`)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::TEMPLATE_STRING_START ,"`", 1, 6, "::repl" },
			{ TokenType::TEMPLATE_SUBSTRING ,"This is a template string, to prove, use these expressions: ", 1, 7, "::repl" },
			{ TokenType::STR_EXPR_START ,"", 1, 69, "::repl" },
			{ TokenType::NUMBER ,"1995", 1, 69, "::repl" },
			{ TokenType::SLASH ,"/", 1, 73, "::repl" },
			{ TokenType::NUMBER ,"35", 1, 74, "::repl" },
			{ TokenType::STR_EXPR_END ,"", 1, 78, "::repl" },
			{ TokenType::TEMPLATE_SUBSTRING ," and ", 1, 78, "::repl" },
			{ TokenType::STR_EXPR_START ,"", 1, 85, "::repl" },
			{ TokenType::NUMBER ,"143", 1, 85, "::repl" },
			{ TokenType::MINUS ,"-", 1, 88, "::repl" },
			{ TokenType::NUMBER ,"13", 1, 89, "::repl" },
			{ TokenType::STR_EXPR_END ,"", 1, 93, "::repl" },
			{ TokenType::TEMPLATE_STRING_END ,"", 1, 94, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 94, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 95, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "This is a template string, to prove, use these expressions: 57 and 130");
	}

	TEST(interpreter, greater_tests)
	{
		/*
		print(4 > 5 ? 4 > 5 : 5 > 4)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 6, "::repl" },
			{ TokenType::GREATER ,">", 1, 8, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 10, "::repl" },
			{ TokenType::QUESTION ,"?", 1, 12, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 14, "::repl" },
			{ TokenType::GREATER ,">", 1, 16, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 18, "::repl" },
			{ TokenType::COLON ,":", 1, 20, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 22, "::repl" },
			{ TokenType::GREATER ,">", 1, 24, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 26, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 27, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 28, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "true");
	}

	TEST(interpreter, greater_equal_tests)
	{
		/*
		print(4 >= 5 ? 4 >= 5 : 5 >= 4)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 6, "::repl" },
			{ TokenType::GREATER_EQUAL ,">=", 1, 8, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 11, "::repl" },
			{ TokenType::QUESTION ,"?", 1, 13, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 15, "::repl" },
			{ TokenType::GREATER_EQUAL ,">=", 1, 17, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 20, "::repl" },
			{ TokenType::COLON ,":", 1, 22, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 24, "::repl" },
			{ TokenType::GREATER_EQUAL ,">=", 1, 26, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 29, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 30, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 31, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "true");
	}

	TEST(interpreter, less_tests)
	{
		/*
		print(4 < 5 ? 5 < 4 : 4 < 5)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 6, "::repl" },
			{ TokenType::LESS ,"<", 1, 8, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 10, "::repl" },
			{ TokenType::QUESTION ,"?", 1, 12, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 14, "::repl" },
			{ TokenType::LESS ,"<", 1, 16, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 18, "::repl" },
			{ TokenType::COLON ,":", 1, 20, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 22, "::repl" },
			{ TokenType::LESS ,"<", 1, 24, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 26, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 27, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 28, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "false");
	}

	TEST(interpreter, less_equal_tests)
	{
		/*
		print(4 <= 5 ? 5 <= 4 : 4 <= 5)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 6, "::repl" },
			{ TokenType::LESS_EQUAL ,"<=", 1, 8, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 11, "::repl" },
			{ TokenType::QUESTION ,"?", 1, 13, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 15, "::repl" },
			{ TokenType::LESS_EQUAL ,"<=", 1, 17, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 20, "::repl" },
			{ TokenType::COLON ,":", 1, 22, "::repl" },
			{ TokenType::NUMBER ,"4", 1, 24, "::repl" },
			{ TokenType::LESS_EQUAL ,"<=", 1, 26, "::repl" },
			{ TokenType::NUMBER ,"5", 1, 29, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 30, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 31, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr);
		EXPECT_EQ(interpreter.GetText(), "false");
	}

	TEST(interpreter, mod_tests)
	{
		/*
		print(3%2)
		*/
		std::vector<Token> tokens =
		{
			{ TokenType::IDENTIFIER ,"print", 1, 0, "::repl" },
			{ TokenType::LEFT_PAREN ,"(", 1, 5, "::repl" },
			{ TokenType::NUMBER ,"3", 1, 6, "::repl" },
			{ TokenType::MOD ,"%", 1, 7, "::repl" },
			{ TokenType::NUMBER ,"2", 1, 8, "::repl" },
			{ TokenType::RIGHT_PAREN ,")", 1, 9, "::repl" },
			{ TokenType::NEWLINE, "\n", 1, 10, "::repl" },
			{ TokenType::ST_EOF ,"", 3, 0, "::repl" }
		};
		Parser parser{ tokens };
		auto expr = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(expr).ToString();
		EXPECT_EQ(interpreter.GetText(), "1");
	}

	TEST(interpreter, block_tests)
	{
		/*
		auto a = 1u32
		
			auto a = 2u32
			print(a)
		
		*/
		std::vector<Token> tokens =
		{
		{ TokenType::AUTO ,"auto", 2, 1, "::repl" },
		{ TokenType::IDENTIFIER ,"a", 2, 6, "::repl" },
		{ TokenType::EQUAL ,"=", 2, 8, "::repl" },
		{ TokenType::NUMBER ,"1u32", 2, 10, "::repl" },
		{ TokenType::NEWLINE ,"\n", 2, 14, "::repl" },
		{ TokenType::NEWLINE ,"\n", 3, 1, "::repl" },
		{ TokenType::INDENT ,"    ", 4, 1, "::repl" },
		{ TokenType::AUTO ,"auto", 4, 5, "::repl" },
		{ TokenType::IDENTIFIER ,"a", 4, 10, "::repl" },
		{ TokenType::EQUAL ,"=", 4, 12, "::repl" },
		{ TokenType::NUMBER ,"2u32", 4, 14, "::repl" },
		{ TokenType::NEWLINE, "\n", 4, 18, "::repl" },
		{ TokenType::IDENTIFIER ,"print", 5, 5, "::repl" },
		{ TokenType::LEFT_PAREN ,"(", 5, 10, "::repl" },
		{ TokenType::IDENTIFIER ,"a", 5, 11, "::repl" },
		{ TokenType::RIGHT_PAREN ,")", 5, 12, "::repl" },
		{ TokenType::NEWLINE, "\n", 5, 13, "::repl" },
		{ TokenType::NEWLINE, "\n", 6, 1, "::repl" },
		{ TokenType::NEWLINE, "\n", 7, 1, "::repl" },
		{ TokenType::NEWLINE, "\n", 8, 1, "::repl" },
		{ TokenType::UNINDENT, "", 9, 0, "::repl" },
		{ TokenType::ST_EOF, "", 10, 0, "::repl" },
		};
		Parser parser{ tokens };
		auto statements = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(statements);
		EXPECT_EQ(interpreter.GetText(), "2");
	}

	TEST(interpreter, if_false_test)
	{
		/*
		auto a = 1u32

		if (a % 2u32 == 0u32)
			print("Even")

		print(a)
		*/

		std::vector<Token> tokens =
		{
		{ TokenType::AUTO, "auto", 2, 1, "::repl" },
		{ TokenType::IDENTIFIER, "a", 2, 6, "::repl" },
		{ TokenType::EQUAL, "=", 2, 8, "::repl" },
		{ TokenType::NUMBER, "1u32", 2, 10, "::repl" },
		{ TokenType::NEWLINE, "\n", 2, 14, "::repl" },
		{ TokenType::IF, "if", 3, 1, "::repl" },
		{ TokenType::LEFT_PAREN ,"(", 3, 4, "::repl" },
		{ TokenType::IDENTIFIER ,"a", 3, 5, "::repl" },
		{ TokenType::MOD ,"%", 3, 7, "::repl" },
		{ TokenType::NUMBER ,"2u32", 3, 9, "::repl" },
		{ TokenType::EQUAL_EQUAL ,"==", 3, 11, "::repl" },
		{ TokenType::NUMBER ,"0u32", 3, 14, "::repl" },
		{ TokenType::RIGHT_PAREN ,")", 3, 15, "::repl" },
		{ TokenType::NEWLINE, "\n", 3, 16, "::repl" },
		{ TokenType::INDENT ,"    ", 4, 1, "::repl" },
		{ TokenType::IDENTIFIER ,"print", 4, 5, "::repl" },
		{ TokenType::LEFT_PAREN ,"(", 4, 10, "::repl" },
		{ TokenType::STRING ,"Even\n", 4, 11, "::repl" },
		{ TokenType::RIGHT_PAREN ,")", 4, 18, "::repl" },
		{ TokenType::NEWLINE, "\n", 4, 19, "::repl" },
		{ TokenType::UNINDENT, "", 5, 1, "::repl" },
		{ TokenType::IDENTIFIER ,"print", 5, 1, "::repl" },
		{ TokenType::LEFT_PAREN ,"(", 5, 6, "::repl" },
		{ TokenType::IDENTIFIER ,"a", 5, 7, "::repl" },
		{ TokenType::RIGHT_PAREN ,")", 5, 8, "::repl" },
		{ TokenType::NEWLINE, "\n", 5, 9, "::repl" },
		{ TokenType::NEWLINE, "\n", 6, 1, "::repl" },
		{ TokenType::ST_EOF ,"", 8, 0, "::repl" },
		};
		Parser parser{ tokens };
		auto statements = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(statements);
		EXPECT_EQ(interpreter.GetText(), "1");
	}

	TEST(interpreter, if_true_test)
	{
		/*
		auto a = 4u32

		if (a % 2u32 == 0u32)
			print("Even")

		print(a)
		*/
		std::vector<Token> tokens =
		{
		{ TokenType::AUTO, "auto", 1, 0, "::repl" },
		{ TokenType::IDENTIFIER, "a", 1, 5, "::repl" },
		{ TokenType::EQUAL, "=", 1, 7, "::repl" },
		{ TokenType::NUMBER, "4u32", 1, 9, "::repl" },
		{ TokenType::NEWLINE, "\n", 1, 13, "::repl" },
		{ TokenType::IF ,"if", 2, 1, "::repl" },
		{ TokenType::LEFT_PAREN ,"(", 2, 4, "::repl" },
		{ TokenType::IDENTIFIER ,"a", 2, 5, "::repl" },
		{ TokenType::MOD ,"%", 2, 7, "::repl" },
		{ TokenType::NUMBER ,"2u32", 2, 9, "::repl" },
		{ TokenType::EQUAL_EQUAL ,"==", 2, 14, "::repl" },
		{ TokenType::NUMBER ,"0u32", 2, 17, "::repl" },
		{ TokenType::RIGHT_PAREN ,")", 2, 21, "::repl" },
		{ TokenType::NEWLINE, "\n", 2, 22, "::repl" },
		{ TokenType::INDENT ,"    ", 3, 1, "::repl" },
		{ TokenType::IDENTIFIER, "print", 3, 5, "::repl" },
		{ TokenType::LEFT_PAREN, "(", 3, 10, "::repl" },
		{ TokenType::STRING ,"Even\n", 3, 11, "::repl" },
		{ TokenType::RIGHT_PAREN ,")", 3, 18, "::repl" },
		{ TokenType::NEWLINE, "\n", 3, 19, "::repl" },
		{ TokenType::UNINDENT ,"p", 4, 1, "::repl" },
		{ TokenType::IDENTIFIER ,"print", 4, 1, "::repl" },
		{ TokenType::LEFT_PAREN ,"(", 4, 6, "::repl" },
		{ TokenType::IDENTIFIER ,"a", 4, 7, "::repl" },
		{ TokenType::RIGHT_PAREN ,")", 4, 8, "::repl" },
		{ TokenType::NEWLINE, "", 4, 9, "::repl" },
		{ TokenType::NEWLINE, "\n", 5, 1, "::repl" },
		{ TokenType::ST_EOF, "", 7, 0, "::repl" },
		};
		/*std::cout << "std::vector<Token> tokens = \n{\n";
		for (auto& token : tokens) std::cout << token.StringSerialize() << "," << std::endl;
		std::cout << "};\n";*/
		Parser parser{ tokens };
		auto statements = parser.Parse();
		MockInterpreter interpreter{};
		interpreter.Interpret(statements);
		EXPECT_EQ(interpreter.GetText(), "Even\n4");
	}
}