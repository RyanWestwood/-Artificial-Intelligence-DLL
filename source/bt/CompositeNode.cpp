#include "bt/CompositeNode.h"
#include <iostream>

Status CompositeNode::Update()
{
	std::cout << "This should be overridden!\n";
	return Status::Error;
}

void CompositeNode::AddNode(std::unique_ptr<Node>&& node)
{
	m_Children.emplace_back(std::move(node));
}