#ifndef SMARTPTR__VECTOR_MEMBER_H
#define SMARTPTR__VECTOR_MEMBER_H

#include"member_ptr.h"
#include<assert.h>

/// \brief Manages resources for an array of objects
/// \tparam T class or type
template <class T> 
class vector_member_ptrs
{
public:
	/// Construct an arry of \p T
	/// \param size the size of the array, in elements
	/// \details If \p T is a Plain Old Dataype (POD), then the array is uninitialized.
	vector_member_ptrs(size_t size=0)
		: m_size(size), m_ptr(new member_ptr<T>[size]) 
	{
	}

	~vector_member_ptrs()
	{
		delete [] this->m_ptr;
	}

	member_ptr<T>& operator[](size_t index)
	{
		assert(index<this->m_size); 
		return this->m_ptr[index];
	}

	const member_ptr<T>& operator[](size_t index) const
	{
		assert(index<this->m_size); 
		return this->m_ptr[index];
	}

	size_t size() const 
	{
		return this->m_size;
	}

	void resize(size_t newSize)
	{
		member_ptr<T> *newPtr = new member_ptr<T>[newSize];
		for (size_t i=0; i<this->m_size && i<newSize; i++)
			newPtr[i].reset(this->m_ptr[i].release());
		delete [] this->m_ptr;
		this->m_size = newSize;
		this->m_ptr = newPtr;
	}

private:
	vector_member_ptrs(const vector_member_ptrs<T> &c);	// copy not allowed
	void operator=(const vector_member_ptrs<T> &x);		// assignment not allowed

	size_t m_size;
	member_ptr<T> *m_ptr;
};


#endif//SMARTPTR__VECTOR_MEMBER_H