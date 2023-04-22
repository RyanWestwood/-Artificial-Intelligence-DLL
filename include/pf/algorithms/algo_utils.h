#pragma once
#include "../Node.h"

namespace ai
{
  namespace path
  {
    bool GoalTest(NodePtr current, NodePtr destination);
    std::vector<Vector2> SimplifyPath(std::vector<Vector2> path);
    std::vector<Vector2> GetPath(NodePtr solution_node);                          
  } // namespace path
} // namespace ai