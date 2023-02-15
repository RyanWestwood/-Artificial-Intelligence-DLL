#include "bt/BehaviourTree.h"

BehaviourTree::BehaviourTree(std::unique_ptr<Node> node) : root(std::move(node)) 
{
	
}

void BehaviourTree::Update()
{
	Status result = Status::Running;
	while(result != Status::Success){
		result = root->Update();
	}
}
