#pragma once

#include <string>
#include <vector>
#include <tuple>
#include <optional>

namespace TP
   {
   class TokenizerParser
      {
      public:
        static auto reader(const std::string &fileName, std::vector<std::string> &raw) noexcept -> bool;
        static auto checker(std::string opcode) noexcept -> bool;
        static auto token(std::vector<std::string> &rawLines, std::vector<std::tuple<int, std::string, std::optional<int>>> &afterToken) noexcept -> bool;
      
      private:
        static auto print(std::vector<std::tuple<int, std::string, std::optional<int>>> &rhs) noexcept -> void;
      };
   }