
#ifndef __Queue_H__
#define __Queue_H__

template <class DoubleNodeDataTYPE>struct DoubleNode
{
	DoubleNodeDataTYPE data;
	DoubleNode* previous;
	DoubleNode* next;

	inline DoubleNode(const DoubleNodeDataTYPE& item)
	{
		data = item;
		next = previous = NULL;
	}

	~DoubleNode(){}
};

template <class QueueTYPE> class DoubleNodedQueue
{
private:

	DoubleNode<QueueTYPE>* init;
	DoubleNode<QueueTYPE>* last;

public:

	inline DoubleNodedQueue(){ init = last = NULL; }

	~DoubleNodedQueue(){ clear(); }

	DoubleNode<QueueTYPE>* getStart(){ return init; }

	DoubleNode<QueueTYPE>* getLast(){ return last; }

	void push(const QueueTYPE& data)
	{
		DoubleNode<QueueTYPE>* node = NULL;
		node = new DoubleNode<QueueTYPE>(data);
		if (init == NULL)
		{
			last = init = node;
		}
		else
		{
			last->next = node;
			node->previous = last;
			last = node;
		}
	}

	void clear()
	{
		while (init != NULL)
		{
			delete init->data;
			init = init->next;
		}
		last = NULL;
	}

	void ReduceTo(const int quantity)
	{
		DoubleNode<QueueTYPE>* tmp = init;

		for (int i = 1; i < quantity; i++){ tmp = tmp->next; }

		last = tmp->previous->next;
		last->previous = tmp->previous;

		delete tmp;
	}

};

#endif