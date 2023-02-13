#pragma once
#include "../math/Vector2.h"
#include "Node.h"

namespace ai {
	namespace path {

		struct DLS_Data {
			NodePtr found;
			bool remaining;
		};

		std::vector<Vector2> A_Star(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);
		std::vector<Vector2> BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);
		std::vector<Vector2> Greedy_BFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);
		std::vector<Vector2> DFS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);
		std::vector<Vector2> DLS(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer);
		std::vector<Vector2> IDDFS_Caller(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer, int depth);
		std::vector<Vector2> DLS_Caller(std::vector<NodePtr> nodes, NodePtr start_node, NodePtr end_node, Obstacle layer, int depth);
	} // namespace PATH
} // namespace AI