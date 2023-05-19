#include "pf/algorithms/DepthLimited.h"
#include "pf/algorithms/Utils.h"
#include <algorithm>
#include <queue>
#include <unordered_set>

namespace ai
{
  namespace path
  {
    std::vector<Vector2> DepthLimited(std::vector<Node*>& node_map,
                                      Node*               start_node,
                                      Node*               goal_node,
                                      Obstacle              layer)
    {
      ResetNodeMap(node_map);

      std::deque<Node*>         frontier;
      std::unordered_set<Node*> frontier_set;
      std::unordered_set<Node*> explored;
      std::deque<int>             depths;

      frontier.push_back(start_node);
      frontier_set.insert(start_node);
      depths.push_back(0);
      int depth_limit = 10;

      while(!frontier.empty())
      {
        Node* current_node  = frontier.back();
        int     current_depth = depths.back();
        frontier.pop_back();
        frontier_set.erase(current_node);
        depths.pop_back();

        if(AtGoal(current_node, goal_node))
        {
          return SolutionPath(current_node);
        }

        if(current_depth < depth_limit)
        {
          explored.insert(current_node);
          current_node->SetVisited(true);

          Node** neighbours = current_node->GetNeighbours();
          for(int i = 0; i < 4; ++i)
          {
            Node* neighbour = neighbours[i];
            if(!neighbour->IsObstacle(layer) &&
               !explored.count(neighbour) &&
               !frontier_set.count(neighbour))
            {
              neighbour->SetParent(current_node);
              frontier.push_back(neighbour);
              frontier_set.insert(neighbour);
              depths.push_back(current_depth + 1);
            }
          }
        }
      }
      return std::vector<Vector2>(); // This will only happen if no solution was available.
    }

  } // namespace path
} // namespace ai