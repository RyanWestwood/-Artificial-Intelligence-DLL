#include "bt/composite/Sequence.h"

Status Sequence::Update()
{
	for (auto& elem : m_Children) {
		auto result = elem->Update();
		if (result == Status::Failure) return result;
		if (result == Status::Running) return result;
	}
	return Status::Success;
}