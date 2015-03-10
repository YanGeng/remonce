#include <iostream>
#include <map>
using namespace std;

// 用于声明具有动态创建功能的基类 
#define DECLARE_DYNCRT_BASE(base) /
public: /
typedef base* (*ClassGen)(); /
static void Register(const char* class_name, ClassGen class_gen) /
{ /
	class_set.insert(map<const char*, ClassGen>::value_type(class_name, class_gen)); /
} /
public: /
static base* Create(const char* class_name) /
{ /
	map<const char*, ClassGen>::iterator iter; /
	if((iter = class_set.find(class_name)) != class_set.end()) /
	{ /
		return ((*iter).second)(); /
	} /
	return NULL; /
} /
protected: /
static map<const char*, ClassGen> class_set; 

// 用于实现基类 
#define IMPLEMENT_DYNCRT_BASE(base) /
map<const char*, base::ClassGen> base::class_set;

// 用于声明一个能够被动态创建的类 
#define DECLARE_DYNCRT_CLASS(derived, base) /
public: /
struct derived##Register /
{ /
	derived##Register() /
	{ /
		static bool bRegistered = false; /
		if(!bRegistered) /
		{ /
			base::Register(#derived, Create); /
			bRegistered = true; /
		} /
	} /
}; /
static base* Create() /
{ /
	return new derived; /
}

// 用于实现一个能够被动态创建的类  
#define IMPLEMENT_DYNCRT_CLASS(derived) /
static derived::derived##Register derived##_for_registering; 

// 测试
class Base
{
	DECLARE_DYNCRT_BASE(Base) // 声明动态基类 
		DECLARE_DYNCRT_CLASS(Base, Base) // 基类自己也可以动态创建 
	public:
		virtual void Print() 
		{
			cout << "This is Base" << endl;
		}
};

	IMPLEMENT_DYNCRT_BASE(Base) // 实现动态基类 
IMPLEMENT_DYNCRT_CLASS(Base) // 实现动态类

	class Derived : public Base
{
	DECLARE_DYNCRT_CLASS(Derived, Base) // 声明动态类 
	public:
		virtual void Print() 
		{
			cout << "This is Derived" << endl;
		}
};

IMPLEMENT_DYNCRT_CLASS(Derived) // 实现动态类

int main()
{
	Base* pBase = Base::Create("Base"); // 类名可以动态输入
	if(pBase) pBase->Print(); // 创建成功调用虚函数
	else cout << "Create Base error" << endl;

	Base* pDerived = Base::Create("Derived"); // 类名可以动态输入
	if(pDerived) pDerived->Print(); // 创建成功调用虚函数
	else cout << "Create Derived error" << endl;

	system("pause");
	return 0;
}
