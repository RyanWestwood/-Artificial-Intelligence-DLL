#include "pf/Algorithms.h"
#include <algorithm>
#include <iostream>
#include <math.h>
#include <queue>
#include <set>
#include <stack>

namespace ai
{
  namespace path
  {
    auto GoalTest = [](NodePtr current, NodePtr destination) -> bool {
      bool same_x = current->GetPosition().x == destination->GetPosition().x;
      bool same_y = current->GetPosition().y == destination->GetPosition().y;
      return same_x && same_y;
    };

    std::vector<Vector2> SimplifyPath(std::vector<Vector2> path)
    {
      std::vector<Vector2> way_points{};
      Vector2              old_direction{0, 0};

      for(int i = 1; i < path.size(); i++)
      {
        Vector2 new_direction = {
          path.at(i - 1).x - path.at(i).x,
          path.at(i - 1).y - path.at(i).y,
        };
        if(new_direction != old_direction)
        {
          way_points.push_back(path.at(i));
        }
        old_direction = new_direction;
      }
      return way_points;
    }

    std::vector<Vector2> GetPath(NodePtr solution_node)
    {
      if(!solution_node)
        return {};

      std::vector<Vector2> path;
      while(solution_node->GetParent() != nullptr)
      {
        path.push_back(solution_node->GetPosition());
        solution_node = solution_node->GetParent();
      }
      path.push_back(solution_node->GetPosition());
      std::vector<Vector2> simplified_path = SimplifyPath(path);
      std::reverse(std::begin(simplified_path), std::end(simplified_path));
      return simplified_path;
    }

    std::vector<Vector2> A_Star(std::vector<NodePtr> nodes,
                                NodePtr              start_node,
                                NodePtr              end_node,
                                Obstacle             layer)
    {
      ResetNodeMap(nodes);

      auto Heuristic = [](NodePtr current, NodePtr destination) {
        auto current_pos     = current->GetPosition();
        auto destination_pos = destination->GetPosition();

        float xDist = std::abs(current_pos.x - destination_pos.x);
        float yDist = std::abs(current_pos.y - destination_pos.y);

        return (xDist * xDist) + (yDist * yDist);
      };

      auto Compare = [](const NodePtr& lhs, const NodePtr& rhs) {
        return lhs->m_Costs.m_TotalCost > rhs->m_Costs.m_TotalCost;
      };

      start_node->m_Costs.m_FromCost  = 0.f;
      start_node->m_Costs.m_ToCost    = Heuristic(start_node, end_node);
      start_node->m_Costs.m_TotalCost = start_node->m_Costs.m_FromCost + start_node->m_Costs.m_ToCost;

      std::vector<NodePtr> frontier;
      std::set<NodePtr>    explored;

      frontier.push_back(start_node);
      std::make_heap(frontier.begin(), frontier.end(), Compare);

      while(!frontier.empty())
      {
        std::pop_heap(frontier.begin(), frontier.end(), Compare);
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
          if(it == frontier.end() && !neighbour->IsObstacle(layer))
          {
            float gPossibleLowerGoal = current_node->m_Costs.m_FromCost + Heuristic(neighbour, end_node);
            if(gPossibleLowerGoal < neighbour->m_Costs.m_FromCost)
            {
              neighbour->SetParent(current_node);
              neighbour->m_Costs.m_FromCost  = current_node->m_Costs.m_FromCost + 1;
              neighbour->m_Costs.m_ToCost    = Heuristic(neighbour, end_node);
              neighbour->m_Costs.m_TotalCost = neighbour->m_Costs.m_FromCost + neighbour->m_Costs.m_ToCost;
              frontier.push_back(neighbour);
              std::push_heap(frontier.begin(), frontier.end(), Compare);
            }
          }
        }
      }
      return std::vector<Vector2>(); // This will only happen if no solution was available.
    }

    std::vector<Vector2> Greedy_BFS(std::vector<NodePtr> nodes,
                                    NodePtr              start_node,
                                    NodePtr              end_node,
                                    Obstacle             layer)
    {
      ResetNodeMap(nodes);

      auto Compare = [](const NodePtr& lhs, const NodePtr& rhs) {
        return lhs->m_Costs.m_TotalCost > rhs->m_Costs.m_TotalCost;
      };

      start_node->m_Costs.m_FromCost  = 0.f;
      start_node->m_Costs.m_ToCost    = 0;
      start_node->m_Costs.m_TotalCost = start_node->m_Costs.m_FromCost + start_node->m_Costs.m_ToCost;

      std::vector<NodePtr> frontier;
      std::set<NodePtr>    explored;

      frontier.push_back(start_node);
      std::make_heap(frontier.begin(), frontier.end(), Compare);

      while(!frontier.empty())
      {
        std::pop_heap(frontier.begin(), frontier.end(), Compare);
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

    std::vector<Vector2> BFS(std::vector<NodePtr> nodes,
                             NodePtr              start_node,
                             NodePtr              end_node,
                             Obstacle             layer)
    {

      ResetNodeMap(nodes);

      std::deque<NodePtr> frontier;
      std::set<NodePtr>   explored;
      NodePtr             solution_node;

      frontier.push_back(start_node);

      while(!frontier.empty())
      {
        NodePtr current_node = frontier.front();
        if(GoalTest(current_node, end_node))
        {
          solution_node = current_node;
          break;
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
      return GetPath(solution_node);
    }

    std::vector<Vector2> DFS(std::vector<NodePtr> nodes,
                             NodePtr              start_node,
                             NodePtr              end_node,
                             Obstacle             layer)
    {

      ResetNodeMap(nodes);

      std::deque<NodePtr> frontier;
      std::set<NodePtr>   explored;
      NodePtr             solution_node;

      frontier.push_back(start_node);

      while(!frontier.empty())
      {
        NodePtr current_node = frontier.back();
        if(GoalTest(current_node, end_node))
        {
          solution_node = current_node;
          break;
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
      }
      return GetPath(solution_node);
    }

    std::vector<Vector2> DLS(std::vector<NodePtr> nodes,
                             NodePtr              start_node,
                             NodePtr              end_node,
                             Obstacle             layer)
    {

      ResetNodeMap(nodes);

      std::deque<NodePtr> frontier; // use back to imitate stack
      std::set<NodePtr>   explored;
      NodePtr             solution_node;

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
            solution_node = current_node;
            break;
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
      return GetPath(solution_node);
    }
  } // namespace path
} // namespace ai