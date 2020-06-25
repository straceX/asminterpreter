#include "test_state_machine.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>

#include "../src/sm_state_machine.h"
#include "../src/tp_tokenizer_parser.h"

using namespace TEST;

auto testStateMachine::test_state_machine(std::string filename) noexcept
	-> void
	{
		std::vector<std::string> rawOP;
		std::vector<std::tuple<int, std::string, std::optional<int>>> afterToken;
		[[maybe_unused]] auto result = TP::TokenizerParser::reader(filename, rawOP);
		TP::TokenizerParser::token(rawOP, afterToken);
		SM::StateMachine sm(afterToken);
		sm.execute();
	}

auto testStateMachine::executeAllTests() noexcept -> void
	{
	auto testFiles = std::vector<std::pair<std::string, std::string>>{ {"test/test_state_machine1.asm", "125"},
																	   {"test/test_state_machine2.asm", "9"},
																	   {"test/test_state_machine3.asm", "102"},
																	   {"test/test_state_machine4.asm", "0"},
																	   {"test/test_state_machine5.asm", "86"} };

	std::cout << "\n::::::::::::::::::::::::::::::ALL STATE MACHINE TESTS ARE STARTED::::::::::::::::::::::::::::::\n";

	for (const auto& [filename, result] : testFiles)
		{
		std::ostringstream oss;
		auto testStreambuf = std::cout.rdbuf();
		std::cout << "\n---------------" << filename << " started-----------------\n";
		std::cout.rdbuf(oss.rdbuf());
		
		test_state_machine(filename);
		
		std::cout.rdbuf(testStreambuf);
		assert(oss.str() == result);
		std::cout << "\n---------------" << filename << " finished----------------\n";
		}

	std::cout << "\n::::::::::::::::::::::::::::::ALL STATE MACHINE TESTS ARE SUCCEDED::::::::::::::::::::::::::::\n";
	}