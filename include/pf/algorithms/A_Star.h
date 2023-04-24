#pragma once
#include "../Node.h"

namespace ai
{
  namespace path
  {
    /**
     * @brief A simple A_Star implementation
     *
     * This is just a test to see how doxygen works.
     */
    std::vector<Vector2> A_Star(std::vector<NodePtr> nodes,
                                NodePtr              start_node,
                                NodePtr              end_node,
                                Obstacle             layer);
  } // namespace path
} // namespace ai