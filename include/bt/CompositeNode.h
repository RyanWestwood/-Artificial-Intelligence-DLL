#pragma once
#include <memory>
#include <vector>
#include "bt/Node.h"

class CompositeNode : public Node {
public:
	virtual Status Update() override;
	void AddNode(std::unique_ptr<Node>&& node);

protected:
	std::vector<std::unique_ptr<Node>> m_Children;
};