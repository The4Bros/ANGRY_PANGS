
#include <stdio.h>

template <class DoubleNodeDataTYPE> class DoubleNode
{
private:
	DoubleNodeDataTYPE data;
	DoubleNode* previous;
	DoubleNode* next;

public:
	DoubleNode(){}
	DoubleNode(DoubleNodeDataTYPE const data)
	{
		this->data = data;
	}
	DoubleNode(DoubleNodeDataTYPE const data, DoubleNode* previous, DoubleNode* next)
	{
		this->data = data;
		this->previous = previous;
		this->next = next;
	}

	DoubleNode* const getThis()
	{
		return *this;
	}

	void const setData(DoubleNodeDataTYPE const data)
	{
		this->data = data;
	}
	DoubleNodeDataTYPE getData()
	{
		return data;
	}

	void const setPrevious(DoubleNode* const previous)
	{
		this->previous = previous;
	}
	DoubleNode* const getPrevious()
	{
		return previous;
	}

	void const setNext(Node* const next)
	{
		this->next = next;
	}
	DoubleNode* const getNext()
	{
		return next;
	}

};

template <class DoubleNodedStackTYPE> class DoubleNodedStack
{
private:
	DoubleNode* init;
	DoubleNode* last;
public:
	DoubleNodedStack(){}
	DoubleNodedStack(DoubleNode* const node)
	{
		init = node;
		last = node;
	}

	void const push(DoubleNodedStackTYPE const data)
	{
		if (data != NULL){ push(new DoubleNode(data)); }
	}
	void const push(DoubleNode* const node)
	{
		if (init == NULL) // empty stack
		{
			init = node;
			last = node;
			return;
		}
		DoubleNode<DoubleNodedStackTYPE*>* tmp = init;
		init = node;
		init->setNext(tmp);
		init->getNext()->setPrevious(init);
		delete[] tmp;
	}

	DoubleNode& start(){ return init; }
	DoubleNode& getLast(){ return last; }

	~DoubleNodedStack{}
};












