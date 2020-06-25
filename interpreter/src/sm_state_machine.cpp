#include "sm_state_machine.h"

#include <functional>
#include <iostream>


using namespace SM;

StateMachine::StateMachine(std::vector<std::tuple<int, std::string, std::optional<int>>> &afterTokens)
   {
   for (const auto &line : afterTokens)
      m_stackExecute.emplace_back(std::make_pair(std::get<1>(line), std::get<2>(line)));
   m_stackExecute.emplace_back(std::make_pair("NULL", std::nullopt));
   }

//READ: reads an integer on stdin and push the value on the stack, or exit if input is invalid
auto StateMachine::READ() noexcept
   -> void
   {
   int pushIval;
   std::cin >> pushIval;
   if (std::cin.fail())
      return;
   m_stateMachineStack.push(pushIval);
   //std::cout << "User entered integer: " << pushIval;
   ++m_stackExecuteIndex;
   }

//WRITE : pops the top value of the stack, and prints it on stdout
auto StateMachine::WRITE() noexcept
   -> void
   {
   std::cout << *m_stateMachineStack.pop();
   ++m_stackExecuteIndex;
   }

//DUP : duplicate the value on top of the stack
auto StateMachine::DUP() noexcept
   -> void
   {
   m_stateMachineStack.push(*m_stateMachineStack.top());
   ++m_stackExecuteIndex;
   }

//MUL : pops the two top value of the stack, multiply them and push the result on top of the stack
auto StateMachine::MUL() noexcept
   -> void
   {
    if (m_stateMachineStack.getSize() < 2)
    {
        ++m_stackExecuteIndex;
        return;
    }
    auto ivalTop    = *m_stateMachineStack.pop();
    auto ivalBottom = *m_stateMachineStack.pop();
    m_stateMachineStack.push(ivalTop * ivalBottom); //TODO: stack safe
    ++m_stackExecuteIndex;
   }

//ADD : pops the two top value of the stack, add them and push the result on top of the stack
auto StateMachine::ADD() noexcept
   -> void
   {
   auto ivalTop    = *m_stateMachineStack.pop();
   auto ivalBottom = *m_stateMachineStack.pop();
   m_stateMachineStack.push(ivalTop + ivalBottom);
   ++m_stackExecuteIndex;
   }

//SUB : pops the two top value of the stack, sub the TOP with the SECOND and push the result on the stack
auto StateMachine::SUB() noexcept
   -> void
   {
   auto ivalTop    = *m_stateMachineStack.pop();
   auto ivalBottom = *m_stateMachineStack.pop();
   m_stateMachineStack.push(ivalTop - ivalBottom);
   ++m_stackExecuteIndex;
   }

//GT : pops the two top values from the stack, compare them for TOP > SECOND and push the result as 0 or 1 on the stack
auto StateMachine::GT() noexcept
   -> void
   {
   auto ivalTop    = *m_stateMachineStack.pop();
   auto ivalBottom = *m_stateMachineStack.pop();
   m_stateMachineStack.push(ivalTop > ivalBottom ? 1 : 0);
   ++m_stackExecuteIndex;
   }
//LT : pops the two top values from the stack, compare them for TOP < SECOND and push the result as 0 or 1 on the stack
auto StateMachine::LT() noexcept
   -> void
   {
   auto ivalTop = *m_stateMachineStack.pop();
   auto ivalBottom = *m_stateMachineStack.pop();
   m_stateMachineStack.push(ivalTop < ivalBottom ? 1 : 0);
   ++m_stackExecuteIndex;
   }
//EQ : pops the two top values from the stack, compare them for TOP == SECOND and push the result as 0 or 1 on the stack
auto StateMachine::EQ() noexcept
   -> void
   {
   auto ivalTop    = *m_stateMachineStack.pop();
   auto ivalBottom = *m_stateMachineStack.pop();
   m_stateMachineStack.push(ivalTop == ivalBottom ? 1 : 0);
   ++m_stackExecuteIndex;
   }

//JMPZ : pops the two top value of the stack. Jump to the <n>th instruction, where <n> was the first value on the stack, 
//if the second value is null. Otherwise just drop these two values
auto StateMachine::JMPZ() noexcept
   -> void
   {
   //m_stateMachineStack.printStack();
   auto ivalTop = *m_stateMachineStack.pop();
   if (auto ivalBottom = m_stateMachineStack.pop(); ivalBottom.has_value() && *ivalBottom == 0) {
       m_stackExecuteIndex = ivalTop;
       return;
   }
   //m_stateMachineStack.printStack();
   ++m_stackExecuteIndex;
   }

//PUSH <n> : push the integer value <n> on the stack
auto StateMachine::PUSH(int newElement) noexcept
   -> void
   {
   m_stateMachineStack.push(newElement); //TODO: emplace(C++11)
   ++m_stackExecuteIndex;
   }

//POP <n> : pop n value from the stack
auto StateMachine::POP(int deleteCount) noexcept
   -> void
   {
   if (deleteCount < 1) return;
   m_stateMachineStack.deleteStackElements(deleteCount);
   ++m_stackExecuteIndex;
   }

//ROT <n> : perform a circular rotation on the first n value of the stack toward the top
//for instance the stack : BOTTOM[1, 2, 4, 8] TOP becomes BOTTOM [1, 8, 2, 4] TOP after ROT 3
auto StateMachine::ROT(int rotateNumber) noexcept
   -> void
   {
   if (rotateNumber > m_stateMachineStack.getSize()) return;
   m_stateMachineStack.rotate(rotateNumber);
   ++m_stackExecuteIndex;
   }

auto StateMachine::convertKeytoExecute(std::string key, std::optional<int> extraCommand = std::nullopt) noexcept
   -> void
   {
   if (extraCommand.has_value())
      {
       if (const auto res = m_executeMapOneParam.find(key); res != m_executeMapOneParam.cend())
           {
           std::invoke(res->second, this, *extraCommand);
           }
       else
           {
            std::cout << key << "...\n";
           std::cerr << "Error: " << __FILE__ << ':' << __LINE__ << '\n';
           m_stackExecuteIndex++;
           }
       return;
      }

   if (const auto res = m_executeMap.find(key); res != m_executeMap.cend())
      {
      std::invoke(res->second, this);
      }
   else
      {
        std::cout << key << ",,,\n";
      std::cerr << "Error: " << __FILE__ << ':' << __LINE__ << '\n';
      m_stackExecuteIndex++;
      }
   }

auto StateMachine::execute() noexcept
   -> void
   {
   while (m_stackExecute[m_stackExecuteIndex].first != "NULL")
      {
      convertKeytoExecute(m_stackExecute[m_stackExecuteIndex].first, m_stackExecute[m_stackExecuteIndex].second);
      }
   }