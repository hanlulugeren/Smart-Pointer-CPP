#ifndef SMARTPTR_CLONABLE_H
#define SMARTPTR_CLONABLE_H


/// \brief A pointer which can be copied and cloned
/// \tparam T class or type
/// \details \p T should adhere to the \p Clonable interface
template<class T> 
class clonable_ptr : public member_ptr<T>
{
public:
	clonable_ptr(const T &obj) 
		: member_ptr<T>(obj.Clone()) 
	{
	}

	clonable_ptr(T *p = NULLPTR) 
		: member_ptr<T>(p) 
	{
	}

	clonable_ptr(const clonable_ptr<T>& rhs)
		: member_ptr<T>(rhs.m_p ? rhs.m_p->Clone() : nullptr) 
	{
	}

	clonable_ptr<T>& operator=(const clonable_ptr<T>& rhs);
};

template <class T> 
clonable_ptr<T>& clonable_ptr<T>::operator=(const clonable_ptr<T>& rhs)
{
	T *old_p = this->m_p;
	this->m_p = rhs.m_p ? rhs.m_p->Clone() : nullptr;
	delete old_p;
	return *this;
}

#endif//SMARTPTR_CLONABLE_H
