#pragma once
#include "../math/Vector2.h"
#include "Line.h"
#include <memory>
#include <vector>

namespace ai
{
  namespace path
  {

    class Path;
    typedef std::shared_ptr<Path> PathPtr;

    class Path
    {
    public:
      Path();
      void UpdatePath(std::vector<Vector2> waypoints, Vector2 start_pos, float turn_distance, float stopping_distance);

    public:
      std::vector<Vector2> m_LookPoints;
      std::vector<Line>    m_TurnBoundaries;
      int                  m_FinishLineIndex;
      int                  m_SlowDownIndex;
    };

    PathPtr CreatePath();
  } // namespace path
} // namespace ai