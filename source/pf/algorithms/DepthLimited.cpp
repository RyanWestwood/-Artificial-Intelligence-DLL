#include "pf/algorithms/DepthLimited.h"
#include "pf/algorithms/Utils.h"
#include <algorithm>
#include <queue>
#include <unordered_set>

namespace ai
{
  namespace path
  {
    std::vector<Vector2> DLS(std::vector<NodePtr> nodes,
                             NodePtr              start_node,
                             NodePtr              end_node,
                             Obstacle             layer)
    {
      ResetNodeMap(nodes);

      std::deque<NodePtr>         frontier;
      std::unordered_set<NodePtr> frontier_set;
      std::unordered_set<NodePtr> explored;
      std::deque<int>             depths;

      frontier.push_back(start_node);
      frontier_set.insert(start_node);
      depths.push_back(0);
      int depth_limit = 10;

      while(!frontier.empty())
      {
        NodePtr current_node  = frontier.back();
        int     current_depth = depths.back();
        frontier.pop_back();
        frontier_set.erase(current_node);
        depths.pop_back();

        if(AtGoal(current_node, end_node))
        {
          return SolutionPath(current_node);
        }

        if(current_depth < depth_limit)
        {
          explored.insert(current_node);
          current_node->SetVisited(true);

          for(NodePtr& neighbour : current_node->GetNeighbours())
          {
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