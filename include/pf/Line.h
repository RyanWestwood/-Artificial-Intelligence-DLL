#pragma once
#include "../math/Vector2.h"

namespace ai
{
  namespace path
  {

    class Line
    {
    public:
      Line(Vector2 point_on_line, Vector2 point_perpendiculat_to_line);
      bool  GetSide(Vector2 point);
      bool  HasCrossedLine(Vector2 point);
      float DistanceFromPoint(Vector2 point);

    private:
      const float m_VerticalLineGradient = 1e5f;
      bool        m_ApproachSide;
      float       m_Gradient;
      float       m_InterceptY;
      float       m_PerpendiculatGradient;
      Vector2     m_PointOnLine1;
      Vector2     m_PointOnLine2;
    };
  } // namespace path
} // namespace ai