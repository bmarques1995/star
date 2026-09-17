#include <gtest/gtest.h>
#include <string>
#include "Scanner.hh"
#include "Parser.hh"
#include "Interpreter.hh"

namespace star
{

    class MockInterpreter : public Interpreter
    {
    public:
        MockInterpreter()
        {

        }
        ~MockInterpreter() = default;

        const std::string& GetText()
        {
            return m_Result;
        }

    private:
        mutable std::string m_Result;
    };

    TEST(m_Interpreter, expression)
    {
        std::string input = "print(\"Hello String\");";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "Hello String");
    }

    TEST(m_Interpreter, ternary_true_expression)
    {
        std::string input = "print(4 < 5 ? 12 : 7);";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "12");
    }

    TEST(m_Interpreter, ternary_false_expression)
    {
        std::string input = "print(4 > 5 ? 12 : 7);";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "7");
    }

    TEST(m_Interpreter, equal_equal_ternary)
    {
        std::string input = "print(4 == 5 ? 12 : 7);";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "7");
    }

    TEST(m_Interpreter, bang_equal_ternary)
    {
        std::string input = "print(4 != 5 ? 12 : 7);";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "12");
    }

    TEST(m_Interpreter, linear_expression)
    {
        std::string input = "print(6 * 2 + 3);";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "15");
    }

    TEST(m_Interpreter, grouped_expression)
    {
        std::string input = "print(6 * (2 + 3));";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "30");
    }

    TEST(m_Interpreter, negate_true_expression)
    {
        std::string input = "print(!true);";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "false");
    }

    TEST(m_Interpreter, negate_false_expression)
    {
        std::string input = "print(!false);";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "true");
    }

    TEST(m_Interpreter, negate_number)
    {
        std::string input = "print(-5);";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "-5");
    }

    TEST(m_Interpreter, template_string)
    {
        std::string input = R"(print(`This is a template string, to prove, use these expressions: ${1995/35}$ and ${143-13}$`);)";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "This is a template string, to prove, use these expressions: 57 and 130");
    }

    TEST(m_Interpreter, greater_tests)
    {
        std::string input = R"(print(4 > 5 ? 4 > 5 : 5 > 4);)";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "true");
    }

    TEST(m_Interpreter, greater_equal_tests)
    {
        std::string input = R"(print(4 >= 5 ? 4 >= 5 : 5 >= 4);)";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "true");
    }

    TEST(m_Interpreter, less_tests)
    {
        std::string input = R"(print(4 < 5 ? 5 < 4 : 4 < 5);)";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "false");
    }

    TEST(m_Interpreter, less_equal_tests)
    {
        std::string input = R"(print(4 <= 5 ? 5 <= 4 : 4 <= 5);)";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr);
        EXPECT_EQ(m_Interpreter.GetText(), "false");
    }

    TEST(m_Interpreter, mod_tests)
    {
        std::string input = R"(print(3%2);)";
        Scanner scanner(input);
        auto tokens = scanner.ScanTokens();
        Parser parser{tokens};
        auto expr = parser.Parse();
        MockInterpreter m_Interpreter{};
        m_Interpreter.Interpret(expr).ToString();
        EXPECT_EQ(m_Interpreter.GetText(), "1");
    }
}