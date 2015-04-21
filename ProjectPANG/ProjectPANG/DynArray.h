#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#define BLOCK_SIZE 8

template<class DynArrayTYPE> class DynArray
{
private:
	DynArrayTYPE* data;
	unsigned int capacity;
	unsigned int num_elements;

	void Alloc(unsigned int capacity)
	{
		DynArrayTYPE* tmp = data;
		this->capacity = capacity;
		data = new DynArrayTYPE[capacity];

		if (tmp != NULL)
		{
			for (unsigned int i = 0; i < num_elements; ++i) { data[i] = tmp[i]; }
			delete[] tmp;
		}
	}

public:
	DynArray() : capacity(0), num_elements(0), data(NULL) { Alloc(BLOCK_SIZE); }
	DynArray(unsigned int capacity) : capacity(0), num_elements(0), data(NULL) { Alloc(capacity); }

	~DynArray(){ delete[] data; }


	// Operators []
	DynArrayTYPE& operator[](unsigned int index)
	{
		if (index >= num_elements) { return NULL; }
		return data[index];
	}

	const DynArrayTYPE& operator[](unsigned int index) const
	{
		if (index >= num_elements) { return NULL; }
		return data[index];
	}


	// Data Management
	void push_back(const DynArrayTYPE& element)
	{
		if (num_elements >= capacity){ Alloc(capacity + BLOCK_SIZE); }
		data[num_elements++] = element;
	}

	void Pop()
	{
		if(num_elements > 0){ num_elements--; }
	}

	void clear() { num_elements = 0; }

	DynArrayTYPE* at(unsigned int index)
	{
		if (index < num_elements){ return &data[index]; }
		return NULL;
	}

	const DynArrayTYPE* at(unsigned int index) const
	{
		if (index < num_elements){ return &data[index]; }
		return NULL;
	}

	void Delete_Element_At(const unsigned int index)
	{
		if (index < num_elements)
		{
			delete data[index];
			data[i] = NULL;

			DynArrayTYPE* tmp = data;
			for (unsigned int i = index; i < num_elements - 1; i++)
			{
				data[i] = tmp[i + 1];
			}
			
			delete[] tmp;
			delete data[num_elements];
			data[--num_elements] = NULL;
		}
	}

	void Reduce_To(unsigned int quantity)
	{
		if (quantity < num_elements)
		{
			for (unsigned int i = num_elements - 1; i >= quantity; i--)
			{
				delete data[i];
				data[i] = NULL;
			}

			num_elements = quantity;
		}
	}


	// Utils
	unsigned int size() const { return capacity; }
 	unsigned int Count() const { return num_elements; }
	bool empty(){ return num_elements == 0; }

};

#endif