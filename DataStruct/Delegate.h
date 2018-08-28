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