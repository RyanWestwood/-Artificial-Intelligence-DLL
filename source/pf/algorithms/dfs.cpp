#include "pf/algorithms/dfs.h"
#include "pf/algorithms/algo_utils.h"
#include <algorithm>
#include <queue>
#include <unordered_set>

namespace ai
{
  namespace path
  {
    std::vector<Vector2> DFS(std::vector<NodePtr> nodes,
                             NodePtr              start_node,
                             NodePtr              end_node,
                             Obstacle             layer)
    {

      ResetNodeMap(nodes);

      std::deque<NodePtr>         frontier;
      std::unordered_set<NodePtr> frontier_set;
      std::unordered_set<NodePtr> explored;

      frontier.push_back(start_node);
      frontier_set.insert(start_node);

      while(!frontier.empty())
      {
        NodePtr current_node = frontier.back();
        if(AtGoal(current_node, end_node))
        {
          return SolutionPath(current_node);
        }
        frontier.pop_back();
        frontier_set.erase(current_node);
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
          }
        }
      }
      return std::vector<Vector2>(); // This will only happen if no solution was available.
    }

  } // namespace path
} // namespace ai