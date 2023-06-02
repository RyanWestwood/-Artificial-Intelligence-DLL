#include <ai/math/Vector2.h>
#include <ai/pf/Algorithms.h>
#include <benchmark/benchmark.h>

static void BM_SmallAStar(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 10;
  constexpr int                MAP_HEIGHT = 10;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (2 * MAP_WIDTH));
    ai::path::Node*      goal_node  = MAP.at(5 + (5 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_Star(MAP, start_node, goal_node, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_SmallAStar)->Unit(benchmark::kMicrosecond);

static void BM_MediumAStar(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 100;
  constexpr int                MAP_HEIGHT = 100;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (2 * MAP_WIDTH));
    ai::path::Node*      goal_node  = MAP.at(98 + (98 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_Star(MAP, start_node, goal_node, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_MediumAStar)->Unit(benchmark::kMicrosecond);

static void BM_BigAStar(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 1000;
  constexpr int                MAP_HEIGHT = 1000;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (2 * MAP_WIDTH));
    ai::path::Node*      goal_node  = MAP.at(998 + (998 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_Star(MAP, start_node, goal_node, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_BigAStar)->Unit(benchmark::kMillisecond);

static void BM_SuperBigAStar(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 10000;
  constexpr int                MAP_HEIGHT = 10000;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (2 * MAP_WIDTH));
    ai::path::Node*      goal_node  = MAP.at(9998 + (9998 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_Star(MAP, start_node, goal_node, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_SuperBigAStar)->Unit(benchmark::kMillisecond);

static void BM_GameAStar(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 48;
  constexpr int                MAP_HEIGHT = 27;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(17 + (5 * MAP_WIDTH));
    ai::path::Node*      goal_node  = MAP.at(24 + (24 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_Star(MAP, start_node, goal_node, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_GameAStar)->Unit(benchmark::kMicrosecond);

static void BM_GameAStarStatic(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 48;
  constexpr int                MAP_HEIGHT = 27;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);
  ai::path::Node*              GOAL_NODE  = MAP.at(24 + (24 * MAP_WIDTH));
  ai::path::PrecomputeHeuristics(MAP, GOAL_NODE);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(17 + (5 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_StarStatic(MAP, start_node, GOAL_NODE, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_GameAStarStatic)->Unit(benchmark::kMicrosecond);

static void BM_BigAStarStatic(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 1000;
  constexpr int                MAP_HEIGHT = 1000;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);
  ai::path::Node*              GOAL_NODE  = MAP.at(998 + (998 * MAP_WIDTH));
  ai::path::PrecomputeHeuristics(MAP, GOAL_NODE);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (2 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_StarStatic(MAP, start_node, GOAL_NODE, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_BigAStarStatic)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();