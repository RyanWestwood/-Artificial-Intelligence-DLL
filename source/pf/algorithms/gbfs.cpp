#include "pf/algorithms/gbfs.h"
#include "pf/algorithms/algo_utils.h"
#include <algorithm>
#include <unordered_set>

namespace ai
{
  namespace path
  {
    namespace
    {
      auto Compare = [](const NodePtr& lhs, const NodePtr& rhs) {
        return lhs->m_Costs.m_TotalCost > rhs->m_Costs.m_TotalCost;
      };
    }

    std::vector<Vector2> GBFS(std::vector<NodePtr> nodes,
                                    NodePtr              start_node,
                                    NodePtr              end_node,
                                    Obstacle             layer)
    {
      ResetNodeMap(nodes);

      start_node->m_Costs.m_FromCost  = 0.f;
      start_node->m_Costs.m_ToCost    = 0;
      start_node->m_Costs.m_TotalCost = start_node->m_Costs.m_FromCost + start_node->m_Costs.m_ToCost;

      std::vector<NodePtr>        frontier;
      std::unordered_set<NodePtr> explored;

      frontier.push_back(start_node);
      std::make_heap(frontier.begin(), frontier.end(), Compare);

      while(!frontier.empty())
      {
        std::pop_heap(frontier.begin(), frontier.end(), Compare);
        NodePtr current_node = frontier.back();
        if(AtGoal(current_node, end_node))
        {
          return SolutionPath(current_node);
        }
        frontier.pop_back();
        explored.insert(current_node);
        current_node->SetVisited(true);

        for(NodePtr& neighbour : current_node->GetNeighbours())
        {
          auto it = std::find(frontier.begin(), frontier.end(), neighbour);
          if(it == frontier.end() && !neighbour->IsObstacle(layer))
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