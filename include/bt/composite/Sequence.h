#pragma once
#include "../CompositeNode.h"

namespace ai { class Blackboard; }
class Sequence : public CompositeNode {
public:
	Sequence() : CompositeNode() {}
	Sequence(ai::Blackboard& b) :CompositeNode(b) {};
	virtual Status Update() override;
};