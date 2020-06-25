#include "tp_tokenizer_parser.h"

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <iterator>

namespace
   {
   const std::map<std::string, unsigned short> checkVector{ {"ADD",   0},
                                                            {"DUP",   0},
                                                            {"EQ",    0},
                                                            {"GT",    0},
                                                            {"JMPZ",  0},
                                                            {"LT",    0},
                                                            {"MUL",   0},
                                                            {"POP",   1},
                                                            {"PUSH",  1},
                                                            {"READ",  0},
                                                            {"SUB",   0},
                                                            {"WRITE", 0} };
   }

using namespace TP;

auto TokenizerParser::reader(const std::string &fileName, std::vector<std::string> &raw) noexcept
   -> bool
   {
   std::string line;
   std::ifstream ifs(fileName);
   while (std::getline(ifs, line))
      {
      if (line.empty()) continue;
      raw.emplace_back(line);
      }
   return true;
   }

auto TokenizerParser::checker(std::string opcode) noexcept
   -> bool
   {
   if (auto res = checkVector.find(opcode); res == checkVector.end())
      {
      return res->second == 1;
      }
   else
      {
      std::cerr << "Error: " << __FILE__ << ':' << __LINE__ << '\n';
      return false;
      }
   }

auto TokenizerParser::token(std::vector<std::string> &rawLines, std::vector<std::tuple<int, std::string, std::optional<int>>> &afterToken) noexcept
   -> bool
   {
   afterToken.reserve(rawLines.size());
   for (auto& line : rawLines)
   {
       std::istringstream iss(line);
       std::vector<std::string> result(std::istream_iterator<std::string>{iss}, std::istream_iterator<std::string>());
       auto extraParam = std::optional<int>{std::nullopt};
       if (result.size() == 3)
          extraParam = std::stoi(result[2]);
       afterToken.emplace_back(std::stoi(result[0]), result[1], extraParam);
    }      
   return true;
   }

auto TokenizerParser::print(std::vector<std::tuple<int, std::string, std::optional<int>>> &rhs) noexcept
   -> void
   {
   for (const auto &line : rhs)
      {
      std::cout << std::get<0>(line) << " " << std::get<1>(line);
      if (std::get<2>(line).has_value())
         std::cout << " " << std::get<2>(line).value();
      std::cout << "\n";
      }
   }