#include "pf/algorithms/IterativeDeepeningDepthFirst.h"
#include "pf/algorithms/Utils.h"
#include <stack>
#include <unordered_set>

namespace ai
{
  namespace path
  {

    bool IDDFS_Visit(Node* current_node, Node* end_node, int depth, int limit, Obstacle layer, std::unordered_set<Node*>& visited)
    {
      visited.insert(current_node);

      if(AtGoal(current_node, end_node)) return true;
      if(depth >= limit) return false;

      Node** neighbours = current_node->GetNeighbours();
      for(int i = 0; i < 4; ++i)
      {
        Node* neighbour = neighbours[i];
        {
          if(!neighbour->IsObstacle(layer) && visited.count(neighbour) == 0)
          {
            if(IDDFS_Visit(neighbour, end_node, depth + 1, limit, layer, visited))
            {
              neighbour->SetParent(current_node);
              return true;
            }
          }
        }
      }

      return false;
    }

    std::vector<Vector2> IterativeDeepeningDepthFirst(std::vector<Node*>& node_map,
                                                      Node*               start_node,
                                                      Node*               goal_node,
                                                      Obstacle              layer)
    {
      ResetNodeMap(node_map);

      for(int limit = 1;; ++limit)
      {
        std::unordered_set<Node*> visited;

        if(IDDFS_Visit(start_node, goal_node, 0, limit, layer, visited))
        {
          return SolutionPath(goal_node);
        }
      }

      return std::vector<Vector2>(); // This line will never be reached.
    }

  } // namespace path
} // namespace ai