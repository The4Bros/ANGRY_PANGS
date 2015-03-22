
#pragma once

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
	inline DoubleNodedQueue()
	{
		init = last = NULL;
	}
	void const push(const QueueTYPE& data)
	{
		DoubleNode<QueueTYPE>* node;
		node = new DoubleNode<QueueTYPE>(data);
		if (init == NULL)
		{
			last = init = node;
			return;
		}
		last->next = node;
		last->next->previous = last;
		last = last->next;
	}

	void clear()
	{
		while (init->next != NULL)
		{
			init = init->next;
			delete init->previous;
		}
		delete init;
		init = last = NULL;
	}

	DoubleNode<QueueTYPE>* start(){ return init; }
	DoubleNode<QueueTYPE>* getLast(){ return last; }
};












