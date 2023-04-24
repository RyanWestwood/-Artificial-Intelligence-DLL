#include <ai/pf/Algorithms.h>

#define SEARCH_ALGORITHM_CASE(algorithm)                                    \
  case SearchAlgorithm::algorithm:                                          \
    solution_path = ai::path::algorithm(map, start_node, goal_node, layer); \
    break;

constexpr int MAP_WIDTH  = 10;
constexpr int MAP_HEIGHT = 10;

std::vector<Vector2> CreatePath(std::vector<ai::path::NodePtr>& map,
                                Vector2                         start,
                                Vector2                         goal,
                                SearchAlgorithm                 algorithm = SearchAlgorithm::A_Star,
                                ai::path::Obstacle              layer     = ai::path::Obstacle::None)
{
  ai::path::NodePtr    start_node = map.at(start.x + (start.y * MAP_WIDTH));
  ai::path::NodePtr    goal_node  = map.at(goal.x + (goal.y * MAP_WIDTH));
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

int main()
{
  std::vector<ai::path::NodePtr> map  = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);
  std::vector<Vector2>           path = CreatePath(map, Vector2{0, 0}, Vector2{5, 5}, SearchAlgorithm::A_Star);

  return 0;
}