#pragma once
#include "../math/Vector2.h"
#include "Node.h"

namespace ai
{
  namespace path
  {
    std::vector<Vector2> A_Star(std::vector<NodePtr> nodes,
                                NodePtr              start_node,
                                NodePtr              end_node,
                                Obstacle             layer);

    std::vector<Vector2> BFS(std::vector<NodePtr> nodes,
                             NodePtr              start_node,
                             NodePtr              end_node,
                             Obstacle             layer);

    std::vector<Vector2> Greedy_BFS(std::vector<NodePtr> nodes,
                                    NodePtr              start_node,
                                    NodePtr              end_node,
                                    Obstacle             layer);

    std::vector<Vector2> DFS(std::vector<NodePtr> nodes,
                             NodePtr              start_node,
                             NodePtr              end_node,
                             Obstacle             layer);

    std::vector<Vector2> DLS(std::vector<NodePtr> nodes,
                             NodePtr              start_node,
                             NodePtr              end_node,
                             Obstacle             layer);
  } // namespace path
} // namespace ai