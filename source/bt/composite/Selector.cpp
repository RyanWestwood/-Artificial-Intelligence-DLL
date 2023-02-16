#include "bt/composite/Selector.h"

Status Selector::Update()
{
	for (auto& elem : m_Children) {
		auto result = elem->Update();
		if(result == Status::Success) return result;
	}
	return Status::Failure;
}