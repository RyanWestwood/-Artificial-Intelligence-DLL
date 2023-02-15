#pragma once
#include "../CompositeNode.h"

class Sequence : public CompositeNode {
public:
	Sequence() = default;
	virtual Status Update() override;
};