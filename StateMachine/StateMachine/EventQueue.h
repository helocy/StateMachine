/************************************************************
  Copyright (C), 2008-2010, Rockchip. Co., Ltd.
  FileName: StateMachine.h
  Author: YuZhiChao        Version : 1.0          Date: 2009-07-28
  Description: Event Queue, head file.      
  Version: 1.0
  History:
***********************************************************/
#ifndef _EVENTQUEUE_H_
#define _EVENTQUEUE_H_

#include <iostream>

#define TURE  1
#define FALSE 0

struct queue_node                            /* Define queue node structure. */
{
	int event;           /* Event. */
	queue_node *next;    /* Next node. */
};

struct queue                                 /* Define event queue structure. */
{
	queue_node *front;
	queue_node *rear;
};

queue *init_queue(void);                     /* Initialize an event queue. */

bool is_queue_empty(queue *p_queue);         /* If the queue is empty, return ture, else return false. */

void delete_queue(queue *p_queue);           /* Delete an event queue link list. */

void en_queue(queue *p_queue,int event);     /* Insert an event node to the event queue. */

int de_queue(queue *p_queue);                /* Delete an event node from an event queue. */

int queue_length(queue *p_queue);            /* Return the length of an event queue. */

#endif