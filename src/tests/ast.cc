#include <gtest/gtest.h>
#include <string>
#include "Scanner.hh"
#include "TokenType.hh"
#include "Parser.hh"
#include "AstPrinter.hh"
#include "mockPrint.hh"

namespace star
{
    TEST(ast, keyword)
    {
		std::string source = R"(
auto a = "global"

{
    fun showA()
    {
        print(a)
    }

    showA()
    auto a = "local"
    showA()
}
		)";

		Scanner scanner(source);
		auto tokens = scanner.ScanTokens();
		Parser parser{ tokens };
		auto statements = parser.Parse();
        AstPrinter printer;

        for (auto& statement : statements)
        {
            printer.Print(statement);
        }

        EXPECT_TRUE(true);
    }

    TEST(ast, grouping)
    {
        std::string source = R"(
auto a = 6u32 * (2u32 + 3u32)
auto b = 6u32 * 2u32 + 3u32

		)";

        Scanner scanner(source);
        auto tokens = scanner.ScanTokens();
        Parser parser{ tokens };
        auto statements = parser.Parse();
        AstPrinter printer;

        for (auto& statement : statements)
        {
            printer.Print(statement);
        }

        EXPECT_TRUE(true);
    }
}