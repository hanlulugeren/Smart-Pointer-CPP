#ifndef SMARTPTR_MEMBER_H
#define SMARTPTR_MEMBER_H

/// \brief Pointer that overloads operator ->
/// \tparam T class or type
/// \details member_ptr is used frequently in the library to avoid the issues related to
///   std::auto_ptr in C++11 (deprecated) and std::unique_ptr in C++03 (non-existent).
/// \bug <a href="http://github.com/weidai11/cryptopp/issues/48">Issue 48: "Use of auto_ptr causes dirty compile under C++11"</a>

template <class T> class member_ptr
{
public:
	explicit member_ptr(T *p = nullptr) : m_p(p) 
	{
	}

	~member_ptr();

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
		return m_p; 
	}

	const T* get() const 
	{ 
		return m_p; 
	}

	T* get() 
	{ 
		return m_p; 
	}

	T* release()
	{
		T *old_p = m_p;
		m_p = nullptr;
		return old_p;
	}

	void reset(T *p = 0);

protected:
	member_ptr(const member_ptr<T>& rhs);		// copy not allowed
	void operator=(const member_ptr<T>& rhs);	// assignment not allowed

	T *m_p;
};

template <class T> 
member_ptr<T>::~member_ptr() 
{
	delete m_p;
}

template <class T> 
void member_ptr<T>::reset(T *p) 
{
	delete m_p; m_p = p;
}

#endif//SMARTPTR_MEMBER_H
