#include "ds_stack.h"

#include <iostream>
#include <cstring>

using namespace DS;

Stack::Stack(int size) 
   : m_stackSize{size}
   , m_topIndex{-1}
   {
   m_stackImplUniquePtr = std::make_unique<int[]>(size);
   m_stackImplPtr = m_stackImplUniquePtr.get();
   }

auto Stack::printStack() const noexcept
   -> void
   {
   using std::cout;
   for (int i = 0; i <= m_topIndex; ++i)
      cout << m_stackImplUniquePtr[i] << " ";
   cout << '\n';
   }

auto Stack::clearStack() noexcept
   -> void
   {
   m_topIndex = -1;
   }

auto Stack::deleteStackElements(int deleteCount) noexcept
   -> void
   {
   if (m_topIndex + 1 < deleteCount)
      return;
   if (m_topIndex + 1 == deleteCount)
      {
      clearStack();
      return;
      }
   m_topIndex -= deleteCount;
   }

auto Stack::extendStack(int newSize) noexcept 
   -> std::pair<bool, int *>
   {
   if (m_stackSize >= newSize)
      return {false, m_stackImplUniquePtr.get()};
   auto tmp = std::make_unique<int[]>(newSize);
   std::memcpy(tmp.get(), m_stackImplUniquePtr.get(), sizeof(int) * m_stackSize);
   m_stackSize = newSize;
   m_stackImplPtr = tmp.get();
   m_stackImplUniquePtr.reset();
   m_stackImplUniquePtr = std::move(tmp);
   return {true, m_stackImplPtr};
   }

auto Stack::push(int val) noexcept
   -> bool
   {
   if (m_topIndex >= (m_stackSize - 1))
      {
      auto result = extendStack(m_stackSize * 2);
      return result.first;
      }
   else
      {
      m_stackImplPtr[++m_topIndex] = val;
      return true;
      }
   }

auto Stack::pop() noexcept
   -> std::optional<int>
   {
   if (m_topIndex < 0)
      return std::nullopt;
   else
      {
      auto rVal = m_stackImplPtr[m_topIndex--];
      return rVal;
      }
   }

auto Stack::top() const noexcept
   -> std::optional<int>
   {
   if (m_topIndex < 0)
      return std::nullopt;
   else
      return m_stackImplPtr[m_topIndex];
   }

auto Stack::isEmpty() const noexcept
   -> bool
   {
   return (m_topIndex < 0);
   }

auto Stack::rotate(int rotateCount) noexcept
   -> bool
   {
   if (rotateCount > m_topIndex + 1)
      return false;
   int tmp = m_stackImplPtr[m_topIndex];
   auto arr = m_stackImplPtr + m_topIndex - rotateCount + 1;
   for (auto iter = rotateCount; iter > 0; iter--)
      arr[iter] = arr[iter - 1];
   arr[0] = tmp;
   return true;
   }

auto Stack::dublicateTop() noexcept
   -> void
   {
   push(m_stackImplUniquePtr[m_topIndex]);
   }

auto Stack::getSize() noexcept
   -> int
   {
    return m_topIndex + 1;
   }