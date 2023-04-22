#pragma once
#include "../Node.h"

namespace ai
{
  namespace path
  {
    bool AtGoal(NodePtr current, NodePtr destination);
    std::vector<Vector2> SimplifyPath(std::vector<Vector2> path);
    std::vector<Vector2> SolutionPath(NodePtr solution_node);                          
  } // namespace path
} // namespace ai