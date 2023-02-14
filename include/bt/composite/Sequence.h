#pragma once
#include "../CompositeNode.h"

class Sequence : public CompositeNode {
public:
	Sequence() = default;

	virtual Status Update() override {
		for (auto& elem : m_Children) {
			elem->Update();
		}
		return Status::Success;
	}
};