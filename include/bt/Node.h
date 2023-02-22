#pragma once
#include <memory>
#include <functional>
#include "../Blackboard.h"

enum class Status {
	Success = 0,
	Failure,
	Running,
	Error
};

namespace ai { class Blackboard; }

class Node {
public:
	Node() {}
	Node(ai::Blackboard& b) : m_Blackboard(b), m_Func(nullptr) {}
	Node(ai::Blackboard& b, std::function<Status()> func) : m_Blackboard(b), m_Func(func) {}
	Node(std::function<Status()> func) : m_Func(func) {}

	virtual Status Update();

private:
	ai::Blackboard m_Blackboard;
	std::function<Status()> m_Func;
};