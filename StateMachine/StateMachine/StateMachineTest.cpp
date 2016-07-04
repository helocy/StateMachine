/************************************************************
  Copyright (C), 2008-2010, Rockchip. Co., Ltd.
  FileName: StateMachineTest.cpp
  Author: YuZhiChao        Version : 1.0          Date: 2009-07-27
  Description: Test state machine.      
  Version: 1.0
  History:
***********************************************************/
#include "StateMachine.h"
#include "StateMachineTest.h"
#include "EventQueue.h"

int main(void)
{
	int stateMachineid;

	stateMachineid = state_machine_init(); /* Construct a state machine. */

	cout << "Create a new state machine, id=" << stateMachineid << endl << endl;

	/* Add 5 state nodes for test. */
	state_machine_add(stateMachineid, STATE_NEW,     EVENT_INTO_READY_QUEUE, operator_new,     STATE_READY   );
	state_machine_add(stateMachineid, STATE_READY,   EVENT_SCHEDUL,          operator_ready,   STATE_RUNNING );
	state_machine_add(stateMachineid, STATE_RUNNING, EVENT_END_TIME_SLICE,   operator_running, STATE_READY   );
	state_machine_add(stateMachineid, STATE_RUNNING, EVENT_WAIT_EVENT,       operator_running, STATE_BLOCKED );
	state_machine_add(stateMachineid, STATE_BLOCKED, EVENT_EVENT_OCCUR,      operator_blocked, STATE_READY   );
	state_machine_add(stateMachineid, STATE_RUNNING, EVENT_END,              operator_running, STATE_EXIT    );
	state_machine_add(stateMachineid, STATE_EXIT,    NULL,                   operator_exit,    NULL          );

	/* Run state machine */
	state_machine_run(stateMachineid);

	system("pause");
	return 0;
}
