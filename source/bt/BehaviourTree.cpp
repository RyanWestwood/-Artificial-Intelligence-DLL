#include "bt/BehaviourTree.h"

namespace ai{
BehaviourTree::BehaviourTree(std::unique_ptr<Node> node) : root(std::move(node)) 
{
	result = Status::Running;
}

void BehaviourTree::Update()
{
	if (result == Status::Success) return;
	result = root->Update();
}
}