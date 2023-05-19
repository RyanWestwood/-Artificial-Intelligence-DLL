#pragma once
#include "../Node.h"

namespace ai
{
  namespace path
  {
    bool AtGoal(Node* current, Node* destination);
    std::vector<Vector2> SimplifyPath(std::vector<Vector2> path);
    std::vector<Vector2> SolutionPath(Node* solution_node);                          
  } // namespace path
} // namespace ai