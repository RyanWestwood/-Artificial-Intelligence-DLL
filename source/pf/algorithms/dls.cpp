#include "pf/algorithms/dls.h"
#include "pf/algorithms/algo_utils.h"
#include <algorithm>
#include <queue>
#include <set>

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

      std::deque<NodePtr> frontier; // use back to imitate stack
      std::set<NodePtr>   explored;

      frontier.push_back(start_node);

      int depth_limit   = 3;
      int current_depth = 0;
      while(!frontier.empty())
      {
        if(current_depth < depth_limit)
        {
          NodePtr current_node = frontier.back();
          if(GoalTest(current_node, end_node))
          {
            return GetPath(current_node);
          }
          frontier.pop_back();
          explored.insert(current_node);
          current_node->SetVisited(true);

          for(NodePtr& neighbour : current_node->GetNeighbours())
          {
            auto it = std::find(frontier.begin(), frontier.end(), neighbour);
            if(!(it != frontier.end()) && !neighbour->IsObstacle(layer))
            {
              if(!explored.contains(neighbour))
              {
                neighbour->SetParent(current_node);
                frontier.push_back(neighbour);
              }
            }
          }
          current_depth++;
        }
        else
        {
          current_depth--;
          // break;// Error is here quits while as soon as depth_limit is
          // reached
        }
      }
      return std::vector<Vector2>(); // This will only happen if no solution was available.
    }

  } // namespace path
} // namespace ai