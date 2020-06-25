#pragma once

#include <string>

namespace TEST
	{
	class testStateMachine
		{
		public:
			static auto executeAllTests() noexcept -> void;

		private:
			static auto test_state_machine(std::string filename) noexcept -> void;
		};
}