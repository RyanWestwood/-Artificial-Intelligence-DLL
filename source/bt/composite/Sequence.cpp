#include "bt/composite/Sequence.h"

Sequence::Sequence() :
  CompositeNode()
{
}

Sequence::Sequence(ai::Blackboard& b) :
  CompositeNode(b)
{
}

Status Sequence::Update()
{
  Status result = Status::Error;
  for(auto& elem : m_Children)
  {
    result = elem->Update();
    if(result == Status::Failure) return result;
    if(result == Status::Running) return result;
  }
  return result;
}