#pragma once
#include <memory>
#include <vector>
#include "Node.h"

namespace ai { class Blackboard; }
class CompositeNode : public Node {
public:
	CompositeNode() : Node() {}
	CompositeNode(std::shared_ptr<ai::Blackboard> b) : Node(b) {}
	virtual Status Update() override;
	void AddNode(std::unique_ptr<Node>&& node);

protected:
	std::vector<std::unique_ptr<Node>> m_Children;
};