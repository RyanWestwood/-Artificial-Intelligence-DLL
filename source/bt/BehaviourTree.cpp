#include "bt/BehaviourTree.h"

namespace ai
{
  BehaviourTree::BehaviourTree()
  {
    m_Result = Status::Error;
  }

  BehaviourTree::BehaviourTree(std::unique_ptr<Node> node) :
    m_Root(std::move(node))
  {
    m_Result = Status::Running;
  }

  void BehaviourTree::Update()
  {
    if(m_Result == Status::Success) return;
    m_Result = m_Root->Update();
  }
} // namespace ai