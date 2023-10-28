#define SDL_MAIN_HANDLED
#include "Renderer.h"
#include <ai/pf/Algorithms.h>

#define SEARCH_ALGORITHM_CASE(algorithm)                                    \
  case SearchAlgorithm::algorithm:                                          \
    solution_path = ai::path::algorithm(map, start_node, goal_node, layer); \
    break;

constexpr int MAP_WIDTH  = 80;
constexpr int MAP_HEIGHT = 45;
constexpr int TILE_SIZE  = 16;

std::vector<Vector2> CreatePath(std::vector<ai::path::Node*>& map,
                                Vector2                       start,
                                Vector2                       goal,
                                SearchAlgorithm               algorithm = SearchAlgorithm::A_Star,
                                ai::path::Obstacle            layer     = ai::path::Obstacle::None)
{
  ai::path::Node*      start_node = map.at(start.x + (start.y * MAP_WIDTH));
  ai::path::Node*      goal_node  = map.at(goal.x + (goal.y * MAP_WIDTH));
  std::vector<Vector2> solution_path{};
  switch(algorithm)
  {
    SEARCH_ALGORITHM_CASE(A_Star)
    SEARCH_ALGORITHM_CASE(BestFirst)
    SEARCH_ALGORITHM_CASE(BiDirectional)
    SEARCH_ALGORITHM_CASE(DepthFirst)
    SEARCH_ALGORITHM_CASE(DepthLimited)
    SEARCH_ALGORITHM_CASE(GreedyBestFirst)
    SEARCH_ALGORITHM_CASE(IterativeDeepeningDepthFirst)
  }
  return solution_path;
}

int main(int argc, char* args[])
{
  auto renderer = InitializeRenderer(MAP_WIDTH * TILE_SIZE, MAP_HEIGHT * TILE_SIZE);

  std::vector<ai::path::Node*> map = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  TextureData white_block = LoadSolidColourTexture({255, 255, 255, 255}, {32, 32}, renderer.renderer);
  TextureData black_block = LoadSolidColourTexture({0, 0, 0, 255}, {32, 32}, renderer.renderer);
  TextureData green_block = LoadSolidColourTexture({0, 255, 0, 255}, {32, 32}, renderer.renderer);
  TextureData red_block   = LoadSolidColourTexture({255, 0, 0, 255}, {32, 32}, renderer.renderer);
  TextureData blue_block  = LoadSolidColourTexture({0, 0, 255, 255}, {32, 32}, renderer.renderer);

  SDL_Rect src    = {0, 0, 32, 32};
  Vector2  start  = {10, 10};
  Vector2  goal   = {40, 40};
  int      offset = 1;
  while(1)
  {
    SDL_RenderClear(renderer.renderer);

    for(int y = 0; y < 45; y++)
    {
      for(int x = 0; x < 80; x++)
      {
        SDL_Rect dest = {16 * x + offset, 16 * y + offset, 16 - offset, 16 - offset};
        SDL_RenderCopy(renderer.renderer, white_block.m_Texture, &src, &dest);
      }
    }

    for(int i = 0; i < 5; i++)
    {
      int a = map.size();
      map.at(23 * 80 + 7)->SetObstacle(ai::path::All);
    }
    std::vector<Vector2> path = CreatePath(map, start, goal, SearchAlgorithm::A_Star, ai::path::All);

    for(auto& node : map)
    {
      if(node->IsObstacle(ai::path::All))
      {
        auto     pos  = node->GetPosition();
        SDL_Rect dest = {16 * pos.x + offset, 16 * pos.y + offset, 16 - offset, 16 - offset};
        SDL_RenderCopy(renderer.renderer, red_block.m_Texture, &src, &dest);
      }
    }

    for(auto& pos : path)
    {
      SDL_Rect dest = {16 * pos.x + offset, 16 * pos.y + offset, 16 - offset, 16 - offset};
      SDL_RenderCopy(renderer.renderer, blue_block.m_Texture, &src, &dest);
    }

    SDL_Rect dest = {16 * start.x + offset, 16 * start.y + offset, 16 - offset, 16 - offset};
    SDL_RenderCopy(renderer.renderer, green_block.m_Texture, &src, &dest);

    SDL_Rect dest1 = {16 * goal.x + offset, 16 * goal.y + offset, 16 - offset, 16 - offset};
    SDL_RenderCopy(renderer.renderer, black_block.m_Texture, &src, &dest1);

    SDL_RenderPresent(renderer.renderer);
  }

  return 0;
}