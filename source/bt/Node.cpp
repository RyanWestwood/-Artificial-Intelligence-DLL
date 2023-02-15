#include "bt/Node.h"
#include <iostream>

Status Node::Update()
{
	std::cout << "This should be overridden!\n";
	return Status::Error;
}

Status ConditionalNode::Update()
{
	return Node::Update();
}