#ifndef SMARTPTR_AUTO_H
#define SMARTPTR_AUTO_H

/// \The definition below is from : Visual Studio 2012's Installation path\Microsoft Visual Studio 11.0\VC\include\xmemory(868)

/// \In order to test this code in the Visual Studio 2012 and avoid to confilict with the microsoft's source code,
/// \we use auto_ptr_test_test and auto_ptr_ref_test instead of standard name auto_ptr and auto_ptr_ref.

// TEMPLATE CLASS auto_ptr_test
/// \auto_ptr replaced by auto_ptr_test_test
template<class _Ty>
class auto_ptr_test;

/// \auto_ptr_ref replaced by auto_ptr_ref_test
template<class _Ty>
struct auto_ptr_ref_test
{/// \proxy reference for auto_ptr_test copying
	explicit auto_ptr_ref_test(_Ty *_Right)
		:_Ref(_Right)
	{/// \construct from generic pointer to auto_ptr_test ptr
	}

	/// \generic pointer to auto_ptr_test ptr
	_Ty *_Ref;	
};

template<class _Ty>
class auto_ptr_test
{/// \wrap an object pointer to ensure destruction
public:
	typedef auto_ptr_test<_Ty> _Myt;
	typedef _Ty  element_type;

	explicit auto_ptr_test(_Ty *_Ptr = 0) throw()
		: _Myptr(_Ptr)
	{	// construct from object pointer
	}

	auto_ptr_test(_Myt& _Right) throw()
		: _Myptr(_Right.release())
	{/// \construct by assuming pointer from _Right auto_ptr_test
	}

	auto_ptr_test(auto_ptr_ref_test<_Ty> _Right) throw()
	{/// \construct by assuming pointer from _Right auto_ptr_test_ref
		_Ty *_Ptr = _Right._Ref;
		/// \release old
		_Right._Ref = 0;
		/// \reset this
		_Myptr = _Ptr;	
	}

	template<class _Other>
	operator auto_ptr_test<_Other>()throw()
	{/// \convert to compatible auto_ptr_test
		return (auto_ptr_test<_Other>(*this));
	}


	template<class _Other>
	operator auto_ptr_ref_test<_Other>() throw()
	{	// convert to compatible auto_ptr_test_ref
		_Other *_Cvtptr = _Myptr;	// test implicit conversion
		auto_ptr_ref_test<_Other> _Ans(_Cvtptr);
		_Myptr = 0;	// pass ownership to auto_ptr_test_ref
		return (_Ans);
	}

	template<class _Other>
	_Myt& operator=(auto_ptr_test<_Other>& _Right) throw()
	{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
	}

	template<class _Other>
	auto_ptr_test(auto_ptr_test<_Other>& _Right) throw()
		: _Myptr(_Right.release())
	{	// construct by assuming pointer from _Right
	}

	_Myt& operator=(_Myt& _Right) throw()
	{	// assign compatible _Right (assume pointer)
		reset(_Right.release());
		return (*this);
	}

	_Myt& operator=(auto_ptr_ref_test<_Ty> _Right) throw()
	{	// assign compatible _Right._Ref (assume pointer)
		_Ty *_Ptr = _Right._Ref;
		_Right._Ref = 0;	// release old
		reset(_Ptr);	// set new
		return (*this);
	}

	~auto_ptr_test() throw ()
	{	// destroy the object
		delete _Myptr;
	}

	_Ty& operator*() const throw()
	{	// return designated value
		return (*get());
	}

	_Ty *operator->() const throw()
	{	// return pointer to class object
		return (get());
	}

	_Ty *get() const throw()
	{	// return wrapped pointer
		return (_Myptr);
	}

	_Ty *release() throw()
	{	// return wrapped pointer and give up ownership
		_Ty *_Tmp = _Myptr;
		_Myptr = 0;
		return (_Tmp);
	}

	void reset(_Ty *_Ptr = 0)
	{	// destroy designated object and store new pointer
		if (_Ptr != _Myptr)
			delete _Myptr;
		_Myptr = _Ptr;
	}
private:
	/// \the wrapped object pointer
	_Ty *_Myptr;	
};

#endif//SMARTPTR_AUTO_H