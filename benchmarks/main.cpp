#include <ai/math/Vector2.h>
#include <ai/pf/Algorithms.h>
#include <benchmark/benchmark.h>

constexpr float g_MIN_TIME        = 2.f;
constexpr float g_MIN_REPITITIONS = 1000000;

static void BM_GameAStar(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 48;
  constexpr int                MAP_HEIGHT = 27;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (5 * MAP_WIDTH));
    ai::path::Node*      goal_node  = MAP.at(24 + (24 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_Star(MAP, start_node, goal_node, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_GameAStar)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMicrosecond);

static void BM_GameAStarStatic(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 48;
  constexpr int                MAP_HEIGHT = 27;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);
  ai::path::Node*              GOAL_NODE  = MAP.at(24 + (24 * MAP_WIDTH));
  ai::path::PrecomputeHeuristics(MAP, GOAL_NODE);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (5 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_StarStatic(MAP, start_node, GOAL_NODE, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_GameAStarStatic)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMicrosecond);

static void BM_100AStar(benchmark::State& state)
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
BENCHMARK(BM_100AStar)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMicrosecond);

static void BM_100AStarStatic(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 10;
  constexpr int                MAP_HEIGHT = 10;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);
  ai::path::Node*              GOAL_NODE  = MAP.at(5 + (5 * MAP_WIDTH));
  ai::path::PrecomputeHeuristics(MAP, GOAL_NODE);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (2 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_StarStatic(MAP, start_node, GOAL_NODE, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_100AStarStatic)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMicrosecond);

static void BM_5kAStar(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 100;
  constexpr int                MAP_HEIGHT = 50;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (2 * MAP_WIDTH));
    ai::path::Node*      goal_node  = MAP.at(98 + (48 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_Star(MAP, start_node, goal_node, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_5kAStar)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMicrosecond);

static void BM_5kAStarStatic(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 100;
  constexpr int                MAP_HEIGHT = 50;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  ai::path::Node* GOAL_NODE = MAP.at(98 + (48 * MAP_WIDTH));
  ai::path::PrecomputeHeuristics(MAP, GOAL_NODE);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (2 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_Star(MAP, start_node, GOAL_NODE, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_5kAStarStatic)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMicrosecond);

static void BM_10kAStar(benchmark::State& state)
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
BENCHMARK(BM_10kAStar)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMicrosecond);

static void BM_10kAStarStatic(benchmark::State& state)
{
  constexpr int                MAP_WIDTH  = 100;
  constexpr int                MAP_HEIGHT = 100;
  std::vector<ai::path::Node*> MAP        = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);

  ai::path::Node* GOAL_NODE = MAP.at(98 + (98 * MAP_WIDTH));
  ai::path::PrecomputeHeuristics(MAP, GOAL_NODE);

  for(auto _ : state)
  {
    ai::path::Node*      start_node = MAP.at(2 + (2 * MAP_WIDTH));
    std::vector<Vector2> path       = ai::path::A_Star(MAP, start_node, GOAL_NODE, ai::path::Obstacle::None);
  }
  ai::path::DeleteNodeMap(MAP);
}
BENCHMARK(BM_10kAStarStatic)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMicrosecond);

static void BM_1mStar(benchmark::State& state)
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
BENCHMARK(BM_1mStar)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMillisecond);

static void BM_1mStarStatic(benchmark::State& state)
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
BENCHMARK(BM_1mStarStatic)
  ->MinTime(g_MIN_TIME)
  ->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();