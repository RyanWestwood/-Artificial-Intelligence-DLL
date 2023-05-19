#include <iostream>
#include <pf/Node.h>

int main()
{
  std::cout << sizeof(ai::path::Node);
  std::cout << "\n" << sizeof(ai::path::TestNode);

  return 0;
}