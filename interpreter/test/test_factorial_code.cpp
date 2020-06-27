#include "test_factorial_code.h"

#include "../src/sm_state_machine.h"
#include "../src/tp_tokenizer_parser.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

using namespace TEST;

auto testFactorialCode::test_factorial_code(const std::string& filename) noexcept
	-> void
	{
	std::vector<std::string> rawOP;
	std::vector<std::tuple<int, std::string, std::optional<int>>> afterToken;
	[[maybe_unused]] auto result = TP::TokenizerParser::reader(filename, rawOP);
	TP::TokenizerParser::token(rawOP, afterToken);
	SM::StateMachine sm(afterToken);
	sm.execute();
	}

auto testFactorialCode::executeAllTests() noexcept 
	-> void
	{
	auto testFiles = std::vector<std::pair<std::string, std::string>>{ {"test/test_factorial_code0.asm", "1"},
																	   {"test/test_factorial_code1.asm", "1"},
																	   {"test/test_factorial_code2.asm", "2"},
																	   {"test/test_factorial_code3.asm", "6"},
																	   {"test/test_factorial_code6.asm", "720"},
																	   {"test/test_factorial_code10.asm", "3628800"} };

	std::cout << "\n::::::::::::::::::::::::::::::ALL FACTORIAL TESTS ARE STARTED::::::::::::::::::::::::::::::\n";

	for (const auto& [filename, result] : testFiles)
	{
		std::ostringstream oss;
		auto testStreambuf = std::cout.rdbuf();
		std::cout << "\n---------------" << filename << " started-----------------\n";
		std::cout.rdbuf(oss.rdbuf());

		test_factorial_code(filename);

		std::cout.rdbuf(testStreambuf);
		assert(oss.str() == result);
		std::cout << "\n---------------" << filename << " finished----------------\n";
	}

	std::cout << "\n::::::::::::::::::::::::::::::ALL FACTORIAL TESTS ARE SUCCEDED::::::::::::::::::::::::::::::\n";
}
