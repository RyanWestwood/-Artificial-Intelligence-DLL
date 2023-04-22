#include "pf/algorithms/bfs.h"
#include "pf/algorithms/algo_utils.h"
#include <algorithm>
#include <queue>
#include <set>

namespace ai
{
  namespace path
  {
    std::vector<Vector2> BFS(std::vector<NodePtr> nodes,
                             NodePtr              start_node,
                             NodePtr              end_node,
                             Obstacle             layer)
    {

      ResetNodeMap(nodes);

      std::deque<NodePtr> frontier;
      std::set<NodePtr>   explored;

      frontier.push_back(start_node);

      while(!frontier.empty())
      {
        NodePtr current_node = frontier.front();
        if(GoalTest(current_node, end_node))
        {
          return GetPath(current_node);
        }
        frontier.pop_front();
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
      }
      return std::vector<Vector2>(); // This will only happen if no solution was available.
    }

  } // namespace path
} // namespace ai