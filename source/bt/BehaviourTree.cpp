#include "bt/BehaviourTree.h"

BehaviourTree::BehaviourTree(std::unique_ptr<Node> node) : root(std::move(node)) 
{
	result = Status::Running;
}

Status BehaviourTree::Update()
{
	result = root->Update();
	return result;
}
