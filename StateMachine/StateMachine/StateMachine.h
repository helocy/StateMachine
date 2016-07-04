/************************************************************
  Copyright (C), 2008-2010, Rockchip. Co., Ltd.
  FileName: StateMachine.h
  Author: YuZhiChao        Version : 1.0          Date: 2009-07-27
  Description: State machine module's head file.      
  Version: 1.0
  History:
***********************************************************/
#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_

typedef void (*OPERATOR) (void * arg);        /* The address of a operator function. */

int state_machine_init(void);                 /* Initialize a state machine. */

/* Add a state node to a state machine link list. */
void state_machine_add(int stateMachineid,    /* The state machine id. */
                       int state,             /* State of the state machine. */
                       int event,             /* Event of the state machine. */
                       OPERATOR p_operator,   /* Pointer of the operator function. */
                       int nextstate);        /* The state of the next state machine. */

void state_machine_run(int stateMachineid);   /* Run a state machine. */

void state_machine_show(int stateMachineid);  /* Show a state machine's state. */

#endif