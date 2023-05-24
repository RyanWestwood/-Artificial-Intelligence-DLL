#include <benchmark/benchmark.h>
#include <ai/pf/Algorithms.h>

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
}
BENCHMARK(BM_SmallAStar)->Unit(benchmark::kMicrosecond);

BENCHMARK_MAIN();