#pragma once
#include "../math/Vector2.h"
#include "Line.h"
#include <memory>
#include <vector>

namespace ai
{
  namespace path
  {

    class Path
    {
    public:
      Path();
      Path(const std::vector<Vector2>& waypoints, Vector2 start_pos, float turn_distance, float stopping_distance);

    public:
      std::vector<Vector2> m_LookPoints;
      std::vector<Line>    m_TurnBoundaries;
      int                  m_FinishLineIndex;
      int                  m_SlowDownIndex;
    };

  } // namespace pat
} // namespace ai