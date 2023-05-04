#include "pf/algorithms/IterativeDeepeningDepthFirst.h"
#include "pf/algorithms/Utils.h"
#include <stack>
#include <unordered_set>

namespace ai
{
  namespace path
  {

    bool IDDFS_Visit(NodePtr current_node, NodePtr end_node, int depth, int limit, Obstacle layer, std::unordered_set<NodePtr>& visited)
    {
      visited.insert(current_node);

      if(AtGoal(current_node, end_node)) return true;
      if(depth >= limit) return false;

      for(NodePtr& neighbor : current_node->GetNeighbours())
      {
        if(!neighbor->IsObstacle(layer) && visited.count(neighbor) == 0)
        {
          if(IDDFS_Visit(neighbor, end_node, depth + 1, limit, layer, visited))
          {
            neighbor->SetParent(current_node);
            return true;
          }
        }
      }

      return false;
    }

    std::vector<Vector2> IterativeDeepeningDepthFirst(std::vector<NodePtr>& node_map,
                                                      NodePtr               start_node,
                                                      NodePtr               goal_node,
                                                      Obstacle              layer)
    {
      ResetNodeMap(node_map);

      for(int limit = 1;; ++limit)
      {
        std::unordered_set<NodePtr> visited;

        if(IDDFS_Visit(start_node, goal_node, 0, limit, layer, visited))
        {
          return SolutionPath(goal_node);
        }
      }

      return std::vector<Vector2>(); // This line will never be reached.
    }

  } // namespace path
} // namespace ai