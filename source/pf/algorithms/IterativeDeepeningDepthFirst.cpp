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

    std::vector<Vector2> IterativeDeepeningDepthFirst(std::vector<NodePtr> nodes,
                                                      NodePtr              start_node,
                                                      NodePtr              end_node,
                                                      Obstacle             layer)
    {
      ResetNodeMap(nodes);

      for(int limit = 1;; ++limit)
      {
        std::unordered_set<NodePtr> visited;

        if(IDDFS_Visit(start_node, end_node, 0, limit, layer, visited))
        {
          return SolutionPath(end_node);
        }
      }

      return std::vector<Vector2>(); // This line will never be reached.
    }

  } // namespace path
} // namespace ai