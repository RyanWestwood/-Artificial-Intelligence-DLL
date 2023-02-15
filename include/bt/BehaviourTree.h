#pragma once
#include <memory>
#include "Node.h"

class BehaviourTree {
public:
	BehaviourTree(std::unique_ptr<Node> node);
	Status Update();

	std::unique_ptr<Node> root;
	Status result;
};