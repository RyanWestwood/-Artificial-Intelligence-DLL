#pragma once
#include "../CompositeNode.h"

namespace ai { class Blackboard; }
class Sequence : public CompositeNode {
public:
	Sequence() : CompositeNode() {}
	Sequence(std::shared_ptr<ai::Blackboard> b) :CompositeNode(b) {};
	virtual Status Update() override;
};