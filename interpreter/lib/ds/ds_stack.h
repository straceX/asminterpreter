#pragma once

#include <memory>
#include <optional>
#include <utility>

namespace DS
   {
   class Stack final
      {
      public:
         explicit Stack(int size = 10);
         ~Stack() = default;

         Stack(const Stack &)             noexcept = delete;
         Stack &operator=(const Stack &)  noexcept = delete;
         Stack(const Stack &&)            noexcept = delete;
         Stack &operator=(const Stack &&) noexcept = delete;

         auto dublicateTop()                       noexcept -> void;
         auto isEmpty() const                      noexcept -> bool;
         auto pop()                                noexcept -> std::optional<int>;
         auto push(int val)                        noexcept -> bool;
         auto rotate(int rotateCount)              noexcept -> bool;
         auto top() const                          noexcept -> std::optional<int>;
         auto deleteStackElements(int deleteCount) noexcept -> void;  //will use for pop <n>
         auto getSize()                            noexcept -> int;
         auto printStack()             const noexcept -> void;

      
      private:
         auto clearStack()                   noexcept -> void;
         auto extendStack(int newSize)       noexcept -> std::pair<bool, int *>;
         //auto printStack()             const noexcept -> void;

         int                   *m_stackImplPtr;
         int                    m_stackSize;
         int                    m_topIndex;
         std::unique_ptr<int[]> m_stackImplUniquePtr;
      };
   }