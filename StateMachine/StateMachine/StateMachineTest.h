/************************************************************
  Copyright (C), 2008-2010, Rockchip. Co., Ltd.
  FileName: StateMachineTest.h
  Author: YuZhiChao        Version : 1.0          Date: 2009-07-27
  Description: Test state machine, head file.      
  Version: 1.0
  History:
***********************************************************/
#ifndef _STATEMACHINETEST_H_
#define _STATEMACHINETEST_H_

#include <iostream>

using namespace std;

/* Define five test states. */
#define STATE                      0             /* States start from 0. */
#define STATE_NEW            STATE+1                       /* New state. */
#define STATE_READY          STATE+2                     /* Ready state. */
#define STATE_RUNNING        STATE+3                       /* Run state. */
#define STATE_BLOCKED        STATE+4                     /* Block state. */
#define STATE_EXIT           STATE+5                      /* Exit state. */

/* Define six test events. */
#define EVENT                      10000           /* Event start from 10000. */
#define EVENT_INTO_READY_QUEUE   EVENT+1           /* Into ready queue event. */
#define EVENT_SCHEDUL            EVENT+2                  /* Scheduled event. */
#define EVENT_END_TIME_SLICE     EVENT+3             /* End time slice event. */
#define EVENT_WAIT_EVENT         EVENT+4                       /* Wait event. */
#define EVENT_EVENT_OCCUR        EVENT+5                /* Event occur event. */
#define EVENT_END                EVENT+6                        /* End event. */

/* Define five test operators. */
void operator_new(void *arg)            /* New operator. */
{
	cout << "NEW operator has been executed" << endl << endl;
}

void operator_ready(void *arg)          /* Ready operator. */
{
	cout << "READY operator has been executed" << endl << endl;
}

void operator_running(void *arg)        /* Running operator. */
{
	cout << "RUNNING operator has been executed" << endl << endl;
}

void operator_blocked(void *arg)        /* Blocked operator. */
{
	cout << "BLOCKED operator has been executed" << endl << endl;
}

void operator_exit(void *arg)           /* Exit operator. */
{
	cout << "EXIT operator has been executed" << endl << endl;
}

#endif