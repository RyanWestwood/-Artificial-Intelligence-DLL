#include <gtest/gtest.h>
#include <pf/algorithms.h>
#include <pf/Node.h>

// The function we want to test
int add(int a, int b)
{
  return a + b;
}

// A basic test case
TEST(AddTest, PositiveNumbers)
{
  // Basic equality assertions
  EXPECT_EQ(add(2, 2), 4);
  EXPECT_EQ(add(0, 0), 0);

  // Basic inequality assertions
  EXPECT_NE(add(1, 1), 3);
  EXPECT_NE(add(-2, 2), 1);

  // Basic less than assertions
  EXPECT_LT(add(-2, 2), 1);
  EXPECT_LT(add(0, -1), 0);

  // Basic less than or equal to assertions
  EXPECT_LE(add(2, 2), 5);
  EXPECT_LE(add(-1, 0), 0);

  // Basic greater than assertions
  EXPECT_GT(add(2, 2), 3);
  EXPECT_GT(add(1, -1), -1);

  // Basic greater than or equal to assertions
  EXPECT_GE(add(2, 2), 3);
  EXPECT_GE(add(-1, 0), -1);

  // Basic floating point assertions
  EXPECT_FLOAT_EQ(0.1f + 0.2f, 0.3f);
  EXPECT_DOUBLE_EQ(0.1 + 0.2, 0.3);
}

// Run the tests
constexpr int MAP_WIDTH  = 10;
constexpr int MAP_HEIGHT = 10;

//std::vector<Vector2> CreatePath(std::vector<ai::path::NodePtr>& map,
//                                Vector2                         start,
//                                Vector2                         goal,
//                                SearchAlgorithm                 algorithm = SearchAlgorithm::A_Star,
//                                ai::path::Obstacle              layer     = ai::path::Obstacle::None)
//{
//  ai::path::NodePtr start_node = map.at(start.x + (start.y * MAP_WIDTH));
//  ai::path::NodePtr goal_node  = map.at(goal.x + (goal.y * MAP_WIDTH));
//  return A_Star(map, start_node, goal_node, layer);
//}

int main(int argc, char** argv)
{
  // std::vector<ai::path::NodePtr> map  = ai::path::CreateNodeMap(MAP_WIDTH, MAP_HEIGHT);
  //std::vector<Vector2>           path = CreatePath(map, Vector2{0, 0}, Vector2{5, 5}, SearchAlgorithm::A_Star);
  return 0;
}