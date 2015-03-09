#include <iostream>
#include <map>
using namespace std;

class Base
{
	public:
		virtual void Print() // 测试用
		{
			cout << "This is Base" << endl;
		}
	protected:
		typedef Base* (*ClassGen)(); // 声明函数指针
		static void Register(const char* class_name, ClassGen class_gen) // 注册函数
		{
			class_set.insert(map<const char*, ClassGen>::value_type(class_name, class_gen));
		}
	public:
		static Base* Create(const char* class_name) // 工厂函数
		{
			map<const char*, ClassGen>::iterator iter;
			if((iter = class_set.find(class_name)) != class_set.end())
			{
				return ((*iter).second)();
			}
			return NULL;
		} 
	protected:
		static map<const char*, ClassGen> class_set; // 存储子类信息
};

map<const char*, Base::ClassGen> Base::class_set; // 静态成员变量定义

class Derived : public Base
{
	public:
		struct DerivedRegister // 辅助类，用于注册 
		{
			DerivedRegister()
			{ // 注册子类，虽然map能保证唯一，但仍只注册一次
				static bool bRegistered = false;
				if(!bRegistered)
				{
					Base::Register("Derived", Derived::Create); // 注册子类信息 
					bRegistered = true;
				}
			}    
		};
		static Base* Create() // 工厂函数
		{
			return new Derived;
		}
	public:
		virtual void Print() // 测试用
		{
			cout << "This is Derived" << endl;
		}
};

static Derived::DerivedRegister Derived_for_registering; // 没有其它机制能够保证在全局空间调用注册函数，
// 不得已，定义一个全局变量来完成这项光荣的任务，看起来有点龌龊

int main()
{
	Base* pDerived = Base::Create("Derived"); // 类名可以动态输入
	if(pDerived) pDerived->Print(); // 创建成功调用虚函数
	else cout << "Create error" << endl;
	//system("pause");
	return 0;
} 
