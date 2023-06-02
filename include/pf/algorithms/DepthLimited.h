#pragma once
#include "../Node.h"

namespace ai
{
  namespace path
  {
    std::vector<Vector2> DepthLimited(std::vector<Node*>& node_map,
                                      Node*               start_node,
                                      Node*               goal_node,
                                      Obstacle              layer);
  } // namespace path
} // namespace ai