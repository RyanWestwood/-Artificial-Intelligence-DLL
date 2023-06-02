#include "pf/algorithms/GreedyBestFirst.h"
#include "pf/algorithms/Utils.h"
#include <algorithm>
#include <unordered_set>

namespace ai
{
  namespace path
  {
    namespace
    {
      auto Compare = [](const Node* lhs, const Node* rhs) {
        return lhs->m_Costs.m_TotalCost > rhs->m_Costs.m_TotalCost;
      };
    }

    std::vector<Vector2> GreedyBestFirst(std::vector<Node*>& node_map,
                                         Node*               start_node,
                                         Node*               goal_node,
                                         Obstacle              layer)
    {
      ResetNodeMap(node_map);

      start_node->m_Costs.m_FromCost  = 0.f;
      start_node->m_Costs.m_ToCost    = 0;
      start_node->m_Costs.m_TotalCost = start_node->m_Costs.m_FromCost + start_node->m_Costs.m_ToCost;

      std::vector<Node*>        frontier;
      std::unordered_set<Node*> explored;

      frontier.push_back(start_node);
      std::make_heap(frontier.begin(), frontier.end(), Compare);

      while(!frontier.empty())
      {
        std::pop_heap(frontier.begin(), frontier.end(), Compare);
        Node* current_node = frontier.back();
        if(AtGoal(current_node, goal_node))
        {
          return SolutionPath(current_node);
        }
        frontier.pop_back();
        explored.insert(current_node);
        current_node->SetVisited(true);

        Node** neighbours = current_node->GetNeighbours();
        for(int i = 0; i < 4; ++i)
        {
          Node* neighbour = neighbours[i];
          if(!neighbour->IsObstacle(layer))
          {
            float gPossibleLowerGoal = current_node->m_Costs.m_FromCost;
            if(gPossibleLowerGoal < neighbour->m_Costs.m_FromCost)
            {
              neighbour->SetParent(current_node);
              neighbour->m_Costs.m_FromCost  = current_node->m_Costs.m_FromCost + 1;
              neighbour->m_Costs.m_ToCost    = 0;
              neighbour->m_Costs.m_TotalCost = neighbour->m_Costs.m_FromCost + neighbour->m_Costs.m_ToCost;
              frontier.push_back(neighbour);
              std::push_heap(frontier.begin(), frontier.end(), Compare);
            }
          }
        }
      }
      return std::vector<Vector2>(); // This will only happen if no solution was available.
    }

  } // namespace path
} // namespace ai