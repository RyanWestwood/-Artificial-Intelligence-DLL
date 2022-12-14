#pragma once
#include "../CompositeNode.h"

class Blackboard;
class Sequence : public CompositeNode
{
public:
  Sequence();
  Sequence(ai::Blackboard& b);
  virtual Status Update() override;
};
