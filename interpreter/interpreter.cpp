#include "src/sm_state_machine.h"
#include "test/test_state_machine.h"
#include "test/test_factorial_code.h"
#include "src/tp_tokenizer_parser.h"

#include <iostream>

int main()
	{
	TEST::testStateMachine::executeAllTests();
	TEST::testFactorialCode::executeAllTests();
	
	std::cout << "Please use this functionality for 0-12 factorial calculation.\n";
	std::cout << "Insert fac(val) value:\n";

	auto rawOP		= std::vector<std::string>{};
	auto afterToken = std::vector<std::tuple<int, std::string, std::optional<int>>>{};
	[[maybe_unused]] auto result = TP::TokenizerParser::reader("factorial.asm", rawOP);
	TP::TokenizerParser::token(rawOP, afterToken);
	SM::StateMachine sm(afterToken);
	sm.execute();
	exit(EXIT_SUCCESS);
	}