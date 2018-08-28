#pragma

#define DECLARE_DELEGATE(TypeName) \
template<typename ReturnType> \
class TypeName \
{\
 public: \
		TypeName() \
	{\
		m_p = NULL;\
		m_F = NULL;\
	}\
	~TypeName()\
	{ \
	} \
	typedef ReturnType(* F)(void * p);\
	void * m_p;\
	F m_F;\
	template<class T,ReturnType (T::*FunName)()>\
	static ReturnType MethodStub(void * p)\
	{\
		T * Ap = (T *)p;\
		return (Ap->*FunName)();\
	}\
}; 