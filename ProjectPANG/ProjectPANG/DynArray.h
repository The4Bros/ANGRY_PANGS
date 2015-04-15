#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__

#define BLOCK_SIZE 8

template<class DynArrayTYPE> class DynArray
{
private:
	DynArrayTYPE* data;
	unsigned int size;
	unsigned int num_elements;

	void Alloc(unsigned int size)
	{
		DynArrayTYPE* tmp = data;
		this->size = size;
		data = new DynArrayTYPE[size];

		if (tmp != NULL)
		{
			for (unsigned int i = 0; i < num_elements; ++i) { data[i] = tmp[i]; }
			delete[] tmp;
		}
	}

public:
	DynArray() : size(0), num_elements(0), data(NULL) { Alloc(BLOCK_SIZE); }
	DynArray(unsigned int capacity) : size(0), num_elements(0), data(NULL) { Alloc(capacity); }

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
	void PushBack(const DynArrayTYPE& element)
	{
		if (num_elements >= size){ Alloc(size + BLOCK_SIZE); }
		data[num_elements++] = element;
	}

	void Pop()
	{
		if(num_elements > 0){ num_elements--; }
	}

	void Clear() { num_elements = 0; }

	DynArrayTYPE* At(unsigned int index)
	{
		if (index < num_elements){ return &data[index]; }
		return NULL;
	}

	const DynArrayTYPE* At(unsigned int index) const
	{
		if (index < num_elements){ return &data[index]; }
		return NULL;
	}


	// Utils
	unsigned int Size() const { return size; }
	unsigned int Count() const { return num_elements; }
	void Reduce_To(unsigned int size) { this->size = size; }

};

#endif