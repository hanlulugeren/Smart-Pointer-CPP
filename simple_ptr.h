#ifndef SMARTPTR_SIMPLE_H
#define SMARTPTR_SIMPLE_H

/// \brief Manages resources for a single object
/// \tparam T class or type
/// \details \p simple_ptr is used frequently in the library to manage resources and
///   ensure cleanup under the RAII pattern (Resource Acquisition Is Initialization).

/// \smart pointer for automatic resource management

template<class T> 
class simple_ptr
{
public:
	simple_ptr(T *p = nullptr)
		:m_p(p)
	{
	}

	~simple_ptr()
	{
		delete m_p;
		m_p=nullptr;
	}
	
	T *m_p;
};

#endif//SMARTPTR_SIMPLE_H