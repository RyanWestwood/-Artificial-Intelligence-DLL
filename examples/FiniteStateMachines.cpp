#include <ai/fsm/StateManager.h>
#include <iostream>

double timer = 0;
ai::fsm::ManagerPtr state_machine = ai::fsm::GetStateManager();

ai::fsm::StatePtr idle_state = ai::fsm::CreateState(state_machine, "Idle", [&](const float delta_time) {
  if(timer >= 2.f)
  {
    timer = 0.f;
    std::cout << "Idle state ended.\n";
    state_machine->SetState(wander_state);
  }
});

ai::fsm::StatePtr wander_state = ai::fsm::CreateState(state_machine, "Wander", [&](const float delta_time) {
  if(m_Timer >= 1.f)
  {
    m_Timer = 0;
    std::cout << "Wanter state ended.\n";
    m_EnemyFsm->SetState(idle_state);
  }
});

int main()
{
  while(timer < 20)
  {
    state_machine->Update(0.0f);
  }
  return 0;
}