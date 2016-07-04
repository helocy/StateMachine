/************************************************************
  Copyright (C), 2008-2010, Rockchip. Co., Ltd.
  FileName: EventQueue.cpp
  Author: YuZhiChao        Version : 1.0         Date: 2009-07-28
  Description: Define event queue module for state machine.  
  Version: 1.0
  History: 
***********************************************************/
#include "EventQueue.h"

/*************************************************
  Function:       init_queue     
  Description:    Initialize an event queue.
  Input:          
  Return:         A pointer to the new event queue. 
  Others:         
*************************************************/
queue *init_queue(void)
{
	queue *event_queue = new queue;
	event_queue->front = event_queue->rear = NULL;

	return event_queue;
}

/*************************************************
  Function:       is_queue_empty     
  Description:    If the queue is empty, return ture,
                  else return false.
  Input:          p_queue, a pointer to an event queue.
  Return:         A boolean value. 
  Others:         
*************************************************/
bool is_queue_empty(queue *p_queue)
{
	if (p_queue->rear == NULL)
	{
		return TURE;
	}
	else
	{
		return FALSE;
	}
}

/*************************************************
  Function:       delete_queue     
  Description:    Delete an event queue.
  Input:          p_queue, a pointer to an event queue.
  Return:         
  Others:         
*************************************************/
void delete_queue(queue *p_queue)
{
	queue_node *current_queue_node = NULL;
	queue_node *p_tmp = NULL;

	current_queue_node = p_queue->front;

	if (current_queue_node != NULL)
	{
		p_tmp = current_queue_node->next;
		while (p_tmp != NULL)
		{
			delete current_queue_node;
			current_queue_node = p_tmp;
			p_tmp = current_queue_node->next;
		}
	}
	delete p_queue;
}

/*************************************************
  Function:       en_queue     
  Description:    Insert an event node to the event 
                  queue.
  Input:          p_queue, a pointer to an event queue.
                  event, value of event.
  Return:         
  Others:         
*************************************************/
void en_queue(queue *p_queue, int event)
{
	queue_node *new_node = NULL;
	new_node = new queue_node;

	new_node->event = event;
	new_node->next = NULL;

	if (p_queue->rear == NULL)
	{
		p_queue->front = new_node;
		p_queue->rear = new_node;
	}
	else
	{
		p_queue->rear->next = new_node;
		p_queue->rear = new_node;
	}
}

/*************************************************
  Function:       de_queue     
  Description:    Delete an event node from an event queue.
  Input:          p_queue, a pointer to an event queue.
  Return:         An event value from the node deleted.
  Others:         
*************************************************/
int de_queue(queue *p_queue)
{
	queue_node *queue_front;
	int event;

	if (p_queue->rear == NULL)
	{
		return 0;
	}

	/* Only one element. */
	if (p_queue->front == p_queue->rear)
	{
		queue_front = p_queue->front;
		p_queue->front = NULL;
		p_queue->rear = NULL;
	}
	else
	{
		queue_front = p_queue->front;
		p_queue->front = p_queue->front->next;
	}

	event = queue_front->event;
	delete queue_front;

	return event;
}

/*************************************************
  Function:       queue_length     
  Description:    Return the length of an event queue.
  Input:          p_queue, a pointer to an event queue.
  Return:         Length of the queue.
  Others:         
*************************************************/
int queue_length(queue *p_queue)
{
	int length = 0;
	queue_node *p_node = p_queue->front;

	while (p_node != NULL)
	{
		p_node = p_node->next;
		length++;
	}

	return length;
}