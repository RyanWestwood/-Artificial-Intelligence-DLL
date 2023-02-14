#pragma once
#include <memory>
#include "Node.h"
#include "CompositeNode.h"
	
class NodeFactory {
public:
	template <class Derived, typename ...Args>
	static std::unique_ptr<Node> createNode(Args && ...args) {
		return std::make_unique<Derived>(std::forward<Args>(args)...);
	}

	template <class Derived, typename ...Args>
	static std::unique_ptr<CompositeNode> createCompositeNode(Args && ...args) {
		return std::make_unique<Derived>(std::forward<Args>(args)...);
	}
};