#pragma once

enum class Status {
	Success = 0,
	Failure,
	Running,
	Error
};

class INode {
public:
	virtual Status Update() = 0;
};

class Node : public INode {
public:
	virtual Status Update() override;
};