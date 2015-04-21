
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

template <class QueueTYPE> class DoubleNodedList
{
private:

	DoubleNode<QueueTYPE>* init;
	DoubleNode<QueueTYPE>* last;
	unsigned int num_elements;

public:

	inline DoubleNodedList(){ init = last = NULL; num_elements = 0; }

	~DoubleNodedList(){ clear(); }

	DoubleNode<QueueTYPE>* getStart(){ return init; }
	DoubleNode<QueueTYPE>* getLast(){ return last; }
	unsigned int Count(){ return num_elements; }

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
		num_elements++;
	}

	void clear()
	{
		while (init != NULL)
		{
			delete init->data;
			init = init->next;
		}
		last = NULL;
		num_elements = 0;
	}

	void ReduceTo(const int quantity)
	{
		last = init;
		num_elements = quantity;
		for (unsigned int i = 1; i < num_elements; i++){ last = last->next; }
		last->next = NULL;
	}
	
	bool at(unsigned int index, QueueTYPE& data) const
	{
		DoubleNode<QueueTYPE>* p_data = init;

		for (unsigned int i = 0; i < index && p_data != NULL; ++i) { p_data = p_data->next; }

		if (p_data != NULL)
		{
			data = p_data->data;
			return true;
		}

		return false;
	}

};

#endif