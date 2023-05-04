#include "pf/algorithms/DepthFirst.h"
#include "pf/algorithms/Utils.h"
#include <algorithm>
#include <queue>
#include <unordered_set>

namespace ai
{
  namespace path
  {
    std::vector<Vector2> DepthFirst(std::vector<NodePtr>& node_map,
                                    NodePtr               start_node,
                                    NodePtr               goal_node,
                                    Obstacle              layer)
    {

      ResetNodeMap(node_map);

      std::deque<NodePtr>         frontier;
      std::unordered_set<NodePtr> frontier_set;
      std::unordered_set<NodePtr> explored;

      frontier.push_back(start_node);
      frontier_set.insert(start_node);

      while(!frontier.empty())
      {
        NodePtr current_node = frontier.back();
        if(AtGoal(current_node, goal_node))
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