/************************************************************
  Copyright (C), 2008-2010, Rockchip. Co., Ltd.
  FileName: StateMachine.cpp
  Author: YuZhiChao        Version : 1.0          Date: 2009-07-27
  Description: Structures and functions of state machine are defined.
  Version: 1.0
  History:
***********************************************************/
#include <iostream>
#include "StateMachine.h"
#include "EventQueue.h"

using namespace std;

/* Define state path structure. */
struct state_path
{
	int event;
	int nextstate;
	state_path *next_path; /* A pointer point to a state_path structure. */
};

/* Define state node structure. */
struct state_node
{
	int state;
	state_path *state_path_head;
	OPERATOR   p_operator; 
	state_node *p_nextstate;
};

/* Define state machine structure. */
struct state_machine
{
	int stateMachineid;
	queue         *event_queue;
	state_node    *current_state_node;      /* If the state machine is running, 
											   this pointer point to the current state node. */

	state_node    *state_machine_entrance;  /* State machine entry. */
	state_machine *p_next_state_machine;
};

state_machine *state_machine_head=NULL;     /* A pointer point to a state machine link list. */

/*************************************************
  Function:       get_state_machine_by_id     
  Description:    Get a state machine pointer by state machine id.
  Input:          p_head, pointer of state machine head;
                  stateMachineid, state machine id.
  Return:         A pointer to state machine. 
  Others:         
*************************************************/
state_machine *get_state_machine_by_id(state_machine *p_head, int stateMachineid)
{
	state_machine *state_machine_head = p_head;

	state_machine *current_state_machine = state_machine_head->p_next_state_machine;    /* Scan from first state machine. */

	/* Start to Scan. */
	while (current_state_machine->stateMachineid != stateMachineid)
	{
		if (current_state_machine->p_next_state_machine == NULL)
		{
			cout << "Cannot find state machine id=" << stateMachineid << endl;
			return NULL;
		}

		current_state_machine = current_state_machine->p_next_state_machine;
	}

	return current_state_machine;
}

/*************************************************
  Function:       get_state_node_by_state     
  Description:    Get a state node pointer by state node's state.
  Input:          p_state_machine, pointer of a state machine;
                  state, state of a state machine.
  Return:         A pointer to state node. 
  Others:         
*************************************************/
state_node *get_state_node_by_state(state_machine *p_state_machine, int state)
{
	state_node *state_node_head = p_state_machine->state_machine_entrance;
	state_node *current_state_node = NULL;

	/* None of state node in the state machine. */
	if (state_node_head->p_nextstate == NULL)
	{
		return NULL;
	}
	else
	{
		current_state_node = state_node_head->p_nextstate;
	}

	/* Start to scan. */
	while (current_state_node->state != state)
	{
		if (current_state_node->p_nextstate == NULL)    /* There is not such a state node whose state is state. */
		{
			return NULL;
		}
		else
		{
			current_state_node = current_state_node->p_nextstate;
		}
	}

	return current_state_node;
}

/*************************************************
  Function:       get_state_path_by_event     
  Description:    Get a state path pointer by state node event.
  Input:          current_state_node, pointer of a state node;
                  event, event of a state node.
  Return:         A pointer to state path. 
  Others:         
*************************************************/
state_path *get_state_path_by_event(state_node *current_state_node, int event)
{
	state_path *state_path_head = current_state_node->state_path_head;
	state_path *current_state_path = state_path_head->next_path;

	while (current_state_path->event != event)
	{
		if (current_state_path->next_path == NULL)      /* There is not such a state path whose event is event. */
		{
			return NULL;
		}
		else
		{
			current_state_path = current_state_path->next_path;
		}
	}

	return current_state_path;
}

/*************************************************
  Function:       state_machine_eof     
  Description:    Find the last state machine of the 
                  state machine link list.
  Input:          p_head, pointer of a state machine
                  link list head.
  Return:         A pointer to the last state machine. 
  Others:         
*************************************************/
state_machine *state_machine_eof(state_machine *p_head)
{
	state_machine *current_state_machine = p_head;

	while (current_state_machine->p_next_state_machine != NULL)
	{
		current_state_machine = current_state_machine->p_next_state_machine;
	}

	return current_state_machine;
}

/*************************************************
  Function:       state_node_eof     
  Description:    Find the last state node of the 
                  state machine link list.
  Input:          stateMachineid, state machine id.
  Return:         A pointer to the last state ndoe. 
  Others:         
*************************************************/
state_node *state_node_eof(int stateMachineid)
{
	state_node *current_state_node = get_state_machine_by_id(state_machine_head, 
		                             stateMachineid)->state_machine_entrance;      

	while (current_state_node->p_nextstate != NULL)
	{
		current_state_node = current_state_node->p_nextstate;
	}

	return current_state_node;
}

/*************************************************
  Function:       state_path_eof     
  Description:    Find the last state path of the 
                  state path link list.
  Input:          state_path_head, the head of state 
                  path link list.
  Return:         A pointer to the last state path. 
  Others:         
*************************************************/
state_path *state_path_eof(state_path *state_path_head)
{
	state_path *current_state_path = state_path_head;

	while (current_state_path->next_path != NULL)
	{
		current_state_path=current_state_path->next_path;
	}

	return current_state_path;
}

/*************************************************
  Function:       next_state     
  Description:    Find the next state node.
  Input:          p_state_machine, pointer of the
                  state machine;
				  state_path, pointer of the state path.
  Return:
  Others:         
*************************************************/
state_node *next_state(state_machine *p_state_machine,
					   state_path    *p_state_path)
{
	state_node *next_state_node = NULL;

	/* Find the next state node, then return it. */
	next_state_node = get_state_node_by_state(p_state_machine, p_state_path->nextstate);
	return next_state_node;
}

/*************************************************
  Function:       state_machine_init     
  Description:    Interface function used to initialize
                  a state machine.
  Input:
  Return:         ID of the new state machine. 
  Others:         
*************************************************/
int state_machine_init(void)
{
	state_machine *p_stateMachine_eof  = NULL;
	state_machine *p_new_state_machine = NULL;

	/* 
	 * If there is not a state machine link list,
	 * then create a state machine link list. 
	 */
	if (state_machine_head == NULL)
	{
		state_machine_head = new state_machine;
		state_machine_head->stateMachineid         = NULL;
		state_machine_head->event_queue            = NULL;
		state_machine_head->p_next_state_machine   = NULL;
		state_machine_head->state_machine_entrance = NULL;
	}

	/* Create a new state machine. */
	p_stateMachine_eof = state_machine_eof(state_machine_head);
	p_stateMachine_eof->p_next_state_machine = new state_machine;
	p_new_state_machine = p_stateMachine_eof->p_next_state_machine;

	/* Initialize the values of the new state machine. */
	p_new_state_machine->p_next_state_machine   = NULL;
	p_new_state_machine->current_state_node     = NULL; 
	p_new_state_machine->state_machine_entrance = new state_node;
	p_new_state_machine->state_machine_entrance->p_nextstate     = NULL;
	p_new_state_machine->state_machine_entrance->state_path_head = NULL;
	p_new_state_machine->state_machine_entrance->p_operator      = NULL;
	p_new_state_machine->state_machine_entrance->state           = NULL;
	p_new_state_machine->event_queue = init_queue();

	/* Insert some events into the event queue for state machine test. */
	en_queue(p_new_state_machine->event_queue, 10001);
	en_queue(p_new_state_machine->event_queue, 10002);
	en_queue(p_new_state_machine->event_queue, 10004);
	en_queue(p_new_state_machine->event_queue, 10005);
	en_queue(p_new_state_machine->event_queue, 10002);
	en_queue(p_new_state_machine->event_queue, 10003);
	en_queue(p_new_state_machine->event_queue, 10002);
	en_queue(p_new_state_machine->event_queue, 10006);

	/*
	 * Convert the pointer of the new state machine to an int type value,
	 * then return the value as the new state machine's id.
	 */
	p_new_state_machine->stateMachineid = (int)p_new_state_machine;
	return p_new_state_machine->stateMachineid;
}

/*************************************************
  Function:       state_machine_add     
  Description:    Interface function used to add a
                  state node to a state machine.
  Input:          stateMachineid, the state machine id;
                  state, state of the state machine;
				  event, event of the state machine;
				  p_operator, pointer of the operator function;
				  nextstate, the state of the next state machine.
  Return:
  Others:         
*************************************************/
void state_machine_add(int stateMachineid,
                       int state,
                       int event,
                       OPERATOR p_operator,
                       int nextstate)
{
	state_machine *p_state_machine = NULL;
	state_node    *p_stateNode_eof = NULL;
	state_node    *new_state_node  = NULL;
	state_node    *p_state_node    = NULL;
	state_path    *new_state_path  = NULL;

	/* 
	 * Scan state node link list to find out if there had a same state node.
	 * If p_state_node is NULL, that means there is not a same state node.
	 */
	p_state_machine = get_state_machine_by_id(state_machine_head, stateMachineid);
	p_state_node    = get_state_node_by_state(p_state_machine, state);

	/* Not the same as the state of the node, create a new state node. */
	if (p_state_node == NULL)
	{
 		p_stateNode_eof = state_node_eof(stateMachineid);
		new_state_node = new state_node;
		p_stateNode_eof->p_nextstate = new_state_node;

		/* Initialize the values of the new state node. */
		new_state_node->state_path_head                       = new state_path;
		new_state_node->state_path_head->event                = NULL;
		new_state_node->state_path_head->nextstate            = NULL;
		new_state_node->state_path_head->next_path            = new state_path;
		new_state_node->state_path_head->next_path->event     = event;
		new_state_node->state_path_head->next_path->nextstate = nextstate;
		new_state_node->state_path_head->next_path->next_path = NULL;
		new_state_node->p_nextstate = NULL;
		new_state_node->p_operator  = p_operator;
		new_state_node->state       = state;
	}
	else
	/* Fine a same state node, add the new event to the state path of the state node. */
	{
		new_state_path = new state_path;
		state_path_eof(p_state_node->state_path_head)->next_path = new_state_path;

		new_state_path->event     = event;
		new_state_path->nextstate = nextstate;
		new_state_path->next_path = NULL;
	}
}

/*************************************************
  Function:       state_machine_run     
  Description:    Interface function used to run a
                  state machine.
  Input:          stateMachineid, the id of a state 
                  machine to run.
  Return:
  Others:         
*************************************************/
void state_machine_run(int stateMachineid)
{
	state_machine *p_state_machine    = NULL;
	state_node    *current_state_node = NULL;
	state_path    *p_state_path       = NULL;

	p_state_machine = get_state_machine_by_id(state_machine_head, stateMachineid);

	/* There is not such a state machine. */
	if (p_state_machine == NULL)
	{
		cout << "Cannot find state machine id=" << stateMachineid << endl;
		return;
	}

	current_state_node = p_state_machine->state_machine_entrance->p_nextstate;
	p_state_machine->current_state_node = current_state_node;

	/* Run. */
	while (1)
	{
		/* The state machine has no such a state node. */
		if (current_state_node == NULL)
		{
			cout << "The state machine has no such a state node" << endl;
			return;
		}

		/* The last state node? */
		if (current_state_node->state_path_head->next_path->event == NULL)
		{
			current_state_node->p_operator(&stateMachineid);
			cout << "Last state, exit" << endl;
			return;
		}

		/* Wait the trigger event. */
		p_state_path = get_state_path_by_event(current_state_node, 
			                                   de_queue(p_state_machine->event_queue));
		if (p_state_path != NULL && current_state_node->p_nextstate != NULL)
		{
			state_machine_show(stateMachineid);
			cout << "Trigger event=" << p_state_path->event << ", next state=" << 
				    p_state_path->nextstate << endl << endl;

			current_state_node->p_operator(&stateMachineid); 

			current_state_node = next_state(p_state_machine, p_state_path);

			p_state_machine->current_state_node = current_state_node;
		}
	}
}

/*************************************************
  Function:       state_machine_show     
  Description:    Interface function used to show a
                  state machine's state.
  Input:          stateMachineid, the id of a state machine to show.
  Return:
  Others:         
*************************************************/
void state_machine_show(int stateMachineid)
{
	state_machine *p_state_machine = NULL;
	state_path    *current_path    = NULL;

	p_state_machine = get_state_machine_by_id(state_machine_head, stateMachineid);

	/* Can not find the state machine of such id. */
	if (p_state_machine == NULL)
	{
		cout << "cannot found state machine, id=" << stateMachineid << endl;
		return;
	}
	else if (p_state_machine->current_state_node == NULL)        /* The state machine didn't run. */
	{
		cout << "state machine didn't run, id=" << stateMachineid << endl;
		return;
	}
	else       /* Show the state machine's state. */
	{
		cout << "----------------- State Machine Information -----------------" << endl << endl;
		cout << "ID:                 " << stateMachineid << endl;
		cout << "Event Queue Length: " << queue_length(p_state_machine->event_queue) << endl;
		cout << "State:              " << p_state_machine->current_state_node->state << endl;

		current_path = p_state_machine->current_state_node->state_path_head;
		if (current_path->next_path == NULL)
		{
			cout << "The last state" << endl << endl;
		}
		else
		{
			cout << "Next state: " << endl << endl;
			current_path=current_path->next_path;

			while (current_path != NULL)
			{
				cout << "If event=" << current_path->event << "       " << 
						"The next state=" << current_path->nextstate <<endl;
				current_path = current_path->next_path;
			}
		}
		cout << "\n---------------------------- End ----------------------------" << endl << endl;
	}
}