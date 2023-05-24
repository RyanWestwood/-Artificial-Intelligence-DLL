#include "pf/Node.h"
#include <cstring>

namespace ai
{
  namespace path
  {

    Node::Node()
    {
      m_ObstacleLayer = Obstacle::None;
      m_Visited       = false;
      m_Costs         = {0, 0, 0};
      m_Position      = {0, 0};
      m_Parent        = nullptr;
      memset(m_Neighbours, 0, 4);
    }

    void AddNeighbour(std::vector<Node*>& map, int map_index, int neighbour_index, int side, bool statement)
    {
      if(statement)
      {
        map[map_index]->AddNeighbour(neighbour_index, map[map_index + side]);
      }
      else
      {
        Node* wall_node = new Node();
        wall_node->SetObstacle(All);
        map[map_index]->AddNeighbour(neighbour_index, wall_node);
      }
    }

    std::vector<Node*> CreateNodeMap(int map_width, int map_height)
    {
      std::vector<Node*> map{};
      map.reserve(map_width * map_height);
      for(int y = 0; y < map_height; y++)
      {
        for(int x = 0; x < map_width; x++)
        {
          auto node = new Node();
          node->SetObstacle(Obstacle::None);
          node->SetVisited(false);
          node->SetPosition({(float)x, (float)y});
          node->SetParent(nullptr);
          map.push_back(node);
        }
      }

      for(int y = 0; y < map_height; y++)
      {
        for(int x = 0; x < map_width; x++)
        {
          int current_index = y * map_width + x;
          AddNeighbour(map, current_index, 0, -map_width, (y > 0));             // Above
          AddNeighbour(map, current_index, 2, map_width, (y < map_height - 1)); // Below
          AddNeighbour(map, current_index, 3, -1, (x > 0));                     // Left
          AddNeighbour(map, current_index, 1, 1, (x < map_width - 1));          // Right
        }
      }
      return map;
    }

    void DeleteNodeMap(std::vector<Node*>& map)
    {
      for(Node* node : map)
      {
        delete node;
      }
    }

    void ResetNodeMap(std::vector<Node*>& nodes)
    {
      for(auto& node : nodes)
      {
        node->SetCosts({FLT_MAX, FLT_MAX, FLT_MAX});
        node->SetVisited(false);
        node->SetParent(nullptr);
        // node->SetBiDirectionalParent(nullptr);
      }
    }
  } // namespace path
} // namespace ai
