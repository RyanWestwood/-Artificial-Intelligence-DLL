#pragma once
#include <memory>
#include "Node.h"

class BehaviourTree {
public:
	BehaviourTree(){}
	BehaviourTree(std::unique_ptr<Node> node);
	void Update();

	std::unique_ptr<Node> root;
	Status result;
};