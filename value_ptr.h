#ifndef SMARTPTR_VALUE_H
#define SMARTPTR_VALUE_H

#include"member_ptr.h"

/// \This smart pointer will create a new object based on another object by using new operator.
/// \The new object is a copy of another object.

/// \brief Value pointer
/// \tparam T class or type
template<class T> 
class value_ptr : public member_ptr<T>
{
public:
	value_ptr(const T &obj)
		: member_ptr<T>(new T(obj)) 
	{
	}

	value_ptr(T *p = nullptr) 
		: member_ptr<T>(p) 
	{
	}

	value_ptr(const value_ptr<T>& rhs)
		: member_ptr<T>(rhs.m_p ? new T(*rhs.m_p) : nullptr) 
	{
	}

	value_ptr<T>& operator=(const value_ptr<T>& rhs);

	bool operator==(const value_ptr<T>& rhs)
	{
		return (!this->m_p && !rhs.m_p) || (this->m_p && rhs.m_p && *this->m_p == *rhs.m_p);
	}
};

template <class T> 
value_ptr<T>& value_ptr<T>::operator=(const value_ptr<T>& rhs)
{
	T *old_p = this->m_p;
	this->m_p = rhs.m_p ? new T(*rhs.m_p) : nullptr;
	delete old_p;
	return *this;
}

#endif//SMARTPTR_VALUE_H
