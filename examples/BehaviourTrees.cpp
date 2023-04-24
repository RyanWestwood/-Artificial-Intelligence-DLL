#include <ai/Blackboard.h>
#include <ai/bt/BehaviourTree.h>
#include <ai/bt/composite/Selector.h>
#include <ai/bt/composite/Sequence.h>
#include <ai/bt/CompositeNode.h>
#include <ai/bt/Node.h>
#include <ai/bt/NodeFactory.h>

#include <bitset>
#include <functional>
#include <iostream>
#include <random>

int               door_attempts = 0;
std::bitset<8>    tree_conditions;
ai::BehaviourTree tree;

auto while_not_dead = [&]() -> Status {
  if(tree_conditions[0]) return Status::Success;
  tree_conditions.reset();
  door_attempts = 0;
  return Status::Running;
};

auto open_door_lam = [&]() -> Status {
  if(tree_conditions[1]) return Status::Success;
  if(door_attempts >= 10)
  {
    std::cout << "Opening door!\n";
    return Status::Success;
  }
  door_attempts++;
  std::cout << "Attempting to open door!\n";
  return Status::Running;
};

auto walk_door_lam = [&]() -> Status {
  if(tree_conditions[2]) return Status::Success;
  std::cout << "Walking to door!\n";
  tree_conditions.set(2);
  return Status::Success;
};

auto close_door_lam = [&]() -> Status {
  if(tree_conditions[3]) return Status::Success;
  std::cout << "Closing door!\n	\n";
  tree_conditions.set(3);
  return Status::Success;
};

int main()
{
  auto blackboard    = ai::Blackboard("door_test.csv");
  auto door_sequence = NodeFactory::createCompositeNode<Sequence>(blackboard);

  auto alive_condition = NodeFactory::createNode<Node>(blackboard, while_not_dead);
  auto open_door       = NodeFactory::createNode<Node>(blackboard, open_door_lam);
  auto walk_to_door    = NodeFactory::createNode<Node>(blackboard, walk_door_lam);
  auto closing_door    = NodeFactory::createNode<Node>(blackboard, close_door_lam);

  door_sequence->AddNode(std::move(walk_to_door));
  door_sequence->AddNode(std::move(open_door));
  door_sequence->AddNode(std::move(closing_door));
  door_sequence->AddNode(std::move(alive_condition));

  tree = ai::BehaviourTree(std::move(door_sequence));

  for(int i = 0; i < 10; i++)
  {
    tree.Update();
  }

  return 0;
}