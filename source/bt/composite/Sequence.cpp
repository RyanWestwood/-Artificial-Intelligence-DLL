#include "bt/composite/Sequence.h"

Status Sequence::Update()
{
	for (auto& elem : m_Children) {
		auto result = elem->Update();
		if (result == Status::Failure) return result;
	}
	return Status::Success;
}