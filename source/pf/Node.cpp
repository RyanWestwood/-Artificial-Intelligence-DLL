#include "pf/Node.h"
#include <float.h>

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
          if(y > 0)
            map[y * map_width + x]->AddNeighbour(0, map[(y - 1) * map_width + x]);
          if(y < map_height - 1)
            map[y * map_width + x]->AddNeighbour(2, map[(y + 1) * map_width + x]);
          if(x > 0)
            map[y * map_width + x]->AddNeighbour(3, map[y * map_width + (x - 1)]);
          if(x < map_width - 1)
            map[y * map_width + x]->AddNeighbour(1, map[y * map_width + (x + 1)]);
        }
      }
      return map;
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
