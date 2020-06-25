#pragma once

#include <iosfwd>
#include <optional>
#include <unordered_map>
#include <vector>

#include "../lib/ds/ds_stack.h"

namespace SM
   {
   class StateMachine final
      {
      public:
         StateMachine(std::vector<std::tuple<int, std::string, std::optional<int>>>&);
         ~StateMachine() = default;

         StateMachine(const StateMachine &)             = delete;
         StateMachine(const StateMachine &&)            = delete;
         StateMachine &operator=(const StateMachine &)  = delete;
         StateMachine &operator=(const StateMachine &&) = delete;

         auto execute() noexcept -> void;
      
         auto ADD()                 noexcept -> void;
         auto DUP()                 noexcept -> void;
         auto EQ()                  noexcept -> void;
         auto GT()                  noexcept -> void;
         auto JMPZ()                noexcept -> void;
         auto LT()                  noexcept -> void;
         auto MUL()                 noexcept -> void;
         auto POP(int deleteCount)  noexcept -> void;
         auto PUSH(int newElement)  noexcept -> void;
         auto READ()                noexcept -> void;
         auto ROT(int rotateNumber) noexcept -> void;
         auto SUB()                 noexcept -> void;
         auto WRITE()               noexcept -> void;

         auto convertKeytoExecute(std::string key, std::optional<int> extraCommand) noexcept -> void;
         
         typedef void (StateMachine::*functionPtr)()noexcept;
         std::unordered_map<std::string, functionPtr> m_executeMap{ {"ADD",   &StateMachine::ADD},
                                                                    {"DUP",   &StateMachine::DUP},
                                                                    {"EQ",    &StateMachine::EQ},
                                                                    {"GT",    &StateMachine::GT},
                                                                    {"JMPZ",  &StateMachine::JMPZ},
                                                                    {"LT",    &StateMachine::LT},
                                                                    {"MUL",   &StateMachine::MUL},
                                                                    {"READ",  &StateMachine::READ},
                                                                    {"SUB",   &StateMachine::SUB},
                                                                    {"WRITE", &StateMachine::WRITE} };
         typedef void (StateMachine::*functionPtrWithParam)(int) noexcept;
         std::unordered_map<std::string, functionPtrWithParam> m_executeMapOneParam{ {"POP",  &StateMachine::POP},
                                                                                     {"PUSH", &StateMachine::PUSH},
                                                                                     {"ROT",  &StateMachine::ROT} };
         DS::Stack m_stateMachineStack;
         int       m_stackExecuteIndex{0};
         std::vector<std::pair<std::string, std::optional<int>>> m_stackExecute;
      };
   }