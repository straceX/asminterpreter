#pragma once

#include <string>

namespace TEST
{
	class testFactorialCode
	{
	public:
		static auto executeAllTests() noexcept -> void;

	private:
		static auto test_factorial_code(const std::string& filename) noexcept -> void;
	};
}