#ifndef SMARTPTR_COUNTED_H
#define SMARTPTR_COUNTED_H

/// \brief Reference counted pointer
/// \tparam T class or type
/// \details users should declare \p m_referenceCount as <tt>std::atomic<unsigned></tt>
///   (or similar) under C++ 11

/// \class T must has the interface of Clone() and the static variable of m_referenceCount.
template<class T> 
class counted_ptr
{
public:
	explicit counted_ptr(T *p = 0);

	counted_ptr(const T &r) : m_p(0) 
	{
		attach(r);
	}

	counted_ptr(const counted_ptr<T>& rhs);

	~counted_ptr();

	const T& operator*() const 
	{ 
		return *m_p; 
	}

	T& operator*() 
	{ 
		return *m_p; 
	}

	const T* operator->() const 
	{ 
		return m_p; 
	}

	T* operator->() 
	{ 
		return get(); 
	}

	const T* get() const 
	{ 
		return m_p; 
	}

	T* get();

	void attach(const T &p);

	counted_ptr<T> & operator=(const counted_ptr<T>& rhs);

private:
	T *m_p;
};

template <class T> 
counted_ptr<T>::counted_ptr(T *p)
	: m_p(p)
{
	if (m_p)
		m_p->m_referenceCount = 1;
}

template <class T> 
counted_ptr<T>::counted_ptr(const counted_ptr<T>& rhs)
	: m_p(rhs.m_p)
{
	if (m_p)
		m_p->m_referenceCount++;
}

template <class T> 
counted_ptr<T>::~counted_ptr()
{
	if (m_p && --m_p->m_referenceCount == 0)
		delete m_p;
}

template <class T> 
void counted_ptr<T>::attach(const T &r)
{
	if (m_p && --m_p->m_referenceCount == 0)
		delete m_p;
	if (r.m_referenceCount == 0)
	{
		m_p = r.clone();
		m_p->m_referenceCount = 1;
	}
	else
	{
		m_p = const_cast<T *>(&r);
		m_p->m_referenceCount++;
	}
}

template <class T> 
T* counted_ptr<T>::get()
{
	if (m_p && m_p->m_referenceCount > 1)
	{
		T *temp = m_p->clone();
		m_p->m_referenceCount--;
		m_p = temp;
		m_p->m_referenceCount = 1;
	}
	return m_p;
}

template <class T> 
counted_ptr<T> & counted_ptr<T>::operator=(const counted_ptr<T>& rhs)
{
	if (m_p != rhs.m_p)
	{
		if (m_p && --m_p->m_referenceCount == 0)
			delete m_p;
		m_p = rhs.m_p;
		if (m_p)
			m_p->m_referenceCount++;
	}
	return *this;
}


#endif//SMARTPTR_COUNTED_H