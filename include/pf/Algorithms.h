#pragma once
#include "algorithms/A_Star.h"
#include "algorithms/BestFirst.h"
#include "algorithms/BiDirectional.h"
#include "algorithms/DepthFirst.h"
#include "algorithms/DepthLimited.h"
#include "algorithms/GreedyBestFirst.h"
#include "algorithms/IterativeDeepeningDepthFirst.h"

enum class SearchAlgorithm : uint8_t
{
  A_Star = 0,
  A_StarStatic,
  BestFirst,
  BiDirectional,
  DepthFirst,
  DepthLimited,
  GreedyBestFirst,
  IterativeDeepeningDepthFirst
};