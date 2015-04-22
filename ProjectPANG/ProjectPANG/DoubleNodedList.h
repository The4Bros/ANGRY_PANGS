
#ifndef __Queue_H__
#define __Queue_H__

template <class DoubleNodeDataTYPE>struct DoubleNode
{
	DoubleNodeDataTYPE data;
	DoubleNode* previous;
	DoubleNode* next;

	inline DoubleNode()
	{
		data = NULL;
		next = previous = NULL;
	}

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
		DoubleNode<QueueTYPE>* node;
		node = new DoubleNode<QueueTYPE>();
		node->data = data;

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
		DoubleNode<QueueTYPE>* p_data;
		DoubleNode<QueueTYPE>* p_next;
		p_data = init;

		while (p_data != NULL)
		{
			p_next = p_data->next;
			delete p_data;
			p_data = p_next;
		}

		init = last = NULL;
		num_elements = 0;
	}

	void ReduceTo(const unsigned int quantity)
	{
		if (quantity == 0) { clear(); }

		else if (quantity < num_elements)
		{
			DoubleNode<QueueTYPE>* p_data;
			DoubleNode<QueueTYPE>* p_next;
			p_data = init;

			for (unsigned int i = 0; i < quantity; i++){ p_data = p_data->next; }

			while (p_data != NULL)
			{
				p_next = p_data->next;
				delete p_data;
				p_data = p_next;
			}

			last = init;
			for (unsigned int i = 1; i < quantity; i++){ last = last->next; }
			last->next = NULL;
			num_elements = quantity;
		}
	}
	
	bool at(unsigned int index, QueueTYPE& data) const
	{
		DoubleNode<QueueTYPE>* tmp = init;

		for (unsigned int i = 0; i < index && tmp != NULL; ++i) { tmp = tmp->next; }

		if (tmp != NULL)
		{
			data = tmp->data;
			return true;
		}

		return false;
	}

};

#endif