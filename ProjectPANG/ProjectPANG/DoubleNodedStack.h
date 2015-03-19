
#include <stdio.h>

template <class DoubleNodeDataTYPE>class DoubleNode
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

	void const setNext(DoubleNode* const next)
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
	DoubleNode<DoubleNodedStackTYPE*>* init;
	DoubleNode<DoubleNodedStackTYPE*>* last;
public:
	DoubleNodedStack(){}
	DoubleNodedStack(DoubleNode<DoubleNodedStackTYPE*>* const node)
	{
		init = node;
		last = node;
	}

	void const push(DoubleNodedStackTYPE const data)
	{
		if (data != NULL){ push(new DoubleNode(data)); }
	}
	void const push(DoubleNode<DoubleNodedStackTYPE*>* const node)
	{
		if (init == NULL) // empty stack
		{
			last = init = node;
			return;
		}
		DoubleNode<DoubleNodedStackTYPE*>* tmp = init;
		init = node;
		init->setNext(tmp);
		init->getNext()->setPrevious(init);
		delete[] tmp;
	}

	bool pop()
	{
		if (init == NULL)
		{
			return false;
		}
		init = init->getNext();
		delete[] init->getPrevious->getThis();
		return true;
	}

	bool deleteContents()
	{
		if (init == NULL)
		{
			return false;
		}
		while (init != last)
		{
			init = init->getNext();
			delete[] init->getPrevious->getThis();
		}
		delete[] init;
		delete[] last->getThis();
		delete[] last;
		return true;
	}

	DoubleNode<DoubleNodedStackTYPE>* start(){ return init; }
	DoubleNode<DoubleNodedStackTYPE>* getLast(){ return last; }


};












