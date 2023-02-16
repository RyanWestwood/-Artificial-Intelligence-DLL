#pragma once
#include "../CompositeNode.h"

class Selector : public CompositeNode {
public:
	Selector() = default;
	virtual Status Update() override;
};