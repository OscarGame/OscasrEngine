template<typename R, typename A1, typename A2, class C>
class Delegate
{
public:
	Delegate()
	{
		m_p = NULL;
		m_F = NULL;
	}
	~Delegate() {}
public:
	typedef R(*F)(A1, A2);
	typedef R(C::*CF)(A1, A2);
	typedef R(*FNew)(void *p, A1, A2);
	void *m_p;
	FNew m_F;

	template<CF cf>
	static int MethodStub(void *p, A1 a1, A2 a2)
	{
		A * Ap = (A *)p;
		return (Ap->*cf)(a1, a2);
	}

	template<F f>
	static int FunStub(void *p, A1 a1, A2 a2)
	{
		return(f)(a1, a2);
	}

	static Delegate Create(void*p, FNew f)
	{
		Delegate Temp;
		Temp.m_F =f;
		Temp.m_p =p;
		return Temp;
	}
public:
	template<CF cf>
	static Delegate FromMethod(C *p)
	{
		return Create(p, &MethodStub<cf>);
	}
	template<F f>
	static Delegate FromFun() 
	{
		return Create(NULL, &FunStub<f>);
	}
	int Excute(int a1, int a2)
	{
		return (*m_F)(m_p, a1, a2);
	}
};




class DelegateTestClass
{
public:
	DelegateTestClass()
	{
	}

	~DelegateTestClass()
	{

	}
	int ExeAdd(int a, int b)
	{
		return a + b;
	}

};



typedef int(*AddFun)(int, int);
int add(int a, int b)
{
	return (a + b);
}
/*
AddFun af = &add;
cout << af(1, 3) << "\n***\n";
*/


template<AddFun f>
static int MethodStub(int a, int b)
{
	return f(a, b);
}
/*
cout << MethodStub<&add>(1, 2) << "\n***\n";
*/



//CPP定义一个类的方法指针
typedef int (DelegateTestClass::*CPPFunction)(int, int);
/*
DelegateClass dc;
CPPFunction cppf = &DelegateClass::ExeAdd;
cout << (dc.*cppf)(1, 2) << "\n***\n";
cout << (&dc->*cppf)(1, 5) << "\n***\n";
*/



/*
这里的CPPFunction需要使用上面的typedef中定义的CPPFunction来找类型名才行
*/
template<CPPFunction cf>
static int CPPMethodStub(void* objPtr, int a, int b)
{
	DelegateClass* dc = (DelegateClass*)objPtr;
	return (dc->*cf)(a, b);
}
/*
DelegateClass* dc = new DelegateClass();
int w = CPPMethodStub<&DelegateClass::ExeAdd>(dc,2,3);
cout << w << "\n***\n";
*/