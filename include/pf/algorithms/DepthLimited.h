#pragma once
#include "../Node.h"

namespace ai
{
  namespace path
  {
    std::vector<Vector2> DepthLimited(std::vector<NodePtr> nodes,
                                      NodePtr              start_node,
                                      NodePtr              end_node,
                                      Obstacle             layer);
  } // namespace path
} // namespace ai