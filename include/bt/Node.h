#pragma once
#include <memory>

enum class Status {
	Success = 0,
	Failure,
	Running,
	Error
};

namespace ai { class Blackboard; }
class Node {
public:
	Node() : m_Blackboard(nullptr), m_Status(Status::Error) {}
	Node(std::shared_ptr<ai::Blackboard> b) : m_Blackboard(b), m_Status(Status::Error) {}
	virtual Status Update();

	Status m_Status;
	std::shared_ptr<ai::Blackboard> m_Blackboard;
};

class ConditionalNode : public Node {
public:
	virtual Status Update() override;
};