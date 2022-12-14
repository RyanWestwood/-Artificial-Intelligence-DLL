#include "bt/Node.h"
#include <iostream>

Status Node::Update()
{
	return m_Func();
}