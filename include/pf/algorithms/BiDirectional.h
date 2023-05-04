#pragma once
#include "../Node.h"

namespace ai
{
  namespace path
  {
    std::vector<Vector2> BiDirectional(std::vector<NodePtr>& node_map,
                                       NodePtr               start_node,
                                       NodePtr               goal_node,
                                       Obstacle              layer);
  } // namespace path
} // namespace ai