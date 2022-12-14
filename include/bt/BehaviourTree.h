#pragma once
#include "Node.h"
#include <memory>

namespace ai
{
  class BehaviourTree
  {
  public:
    BehaviourTree();
    BehaviourTree(std::unique_ptr<Node> node);
    void Update();

    std::unique_ptr<Node> m_Root;
    Status                m_Result;
  };
} // namespace ai