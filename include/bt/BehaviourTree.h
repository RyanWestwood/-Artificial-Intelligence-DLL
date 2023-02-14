#pragma once
#include <memory>
#include "bt/Node.h">

class BehaviourTree {
public:
	BehaviourTree(std::unique_ptr<Node> node) : root(std::move(node)) {}
	void Update() { root->Update(); }

	std::unique_ptr<Node> root;
};