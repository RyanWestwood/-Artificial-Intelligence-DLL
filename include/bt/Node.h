#pragma once
#include <memory>
#include <functional>

enum class Status {
	Success = 0,
	Failure,
	Running,
	Error
};

namespace ai { class Blackboard; }
class Node {
public:
	Node() : m_Blackboard(nullptr) {}
	Node(std::shared_ptr<ai::Blackboard> b) : m_Blackboard(b), m_Func(nullptr) {}
	Node(std::shared_ptr<ai::Blackboard> b, std::function<Status()> func) : m_Blackboard(b), m_Func(func) {}
	Node(std::function<Status()> func) : m_Blackboard(nullptr), m_Func(func) {}

	virtual Status Update();

private:
	std::shared_ptr<ai::Blackboard> m_Blackboard;
	std::function<Status()> m_Func;
};