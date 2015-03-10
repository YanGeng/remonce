#include <iostream> 
#include <map> 
#include <string> 
#include <vector>
using  namespace std; 

typedef  void *(*CREATE_FUNC)(); 

class DynObjectFactory 
{ 
	public: 
		static  void *CreateObject( const string &name) 
		{ 
			map<string, CREATE_FUNC>::const_iterator it; 
			it = mapCls_.find(name); 
			if (it == mapCls_.end()) 
				return  0; 
			else 
				return it->second();  //func();

		} 

		static  void Register( const string &name, CREATE_FUNC func) 
		{ 
			mapCls_[name] = func; 
		} 
	private: 
		static map<string, CREATE_FUNC> mapCls_; 
}; 

// g++
// __attribute ((weak))
//__declspec(selectany) 
map<string, CREATE_FUNC> DynObjectFactory::mapCls_; 
//头文件被包含多次，也只定义一次mapCls_;

class Register 
{ 
	public: 
		Register( const string &name, CREATE_FUNC func) 
		{ 
			DynObjectFactory::Register(name, func); 
		} 
}; 

#define REGISTER_CLASS(class_name) \ 
class class_name##Register { \ 
	public: \ 
			static  void* NewInstance() \ 
			{ \ 
				return  new class_name; \ 
			} \ 
	private: \ 
			 static Register reg_; \ 
}; \ 
Register class_name##Register::reg_(#class_name, class_name##Register::NewInstance) 
	//CircleRegister


class Shape 
{ 
	public: 
	     virtual  void Draw() =  0; 
		      virtual ~Shape() {} 
}; 

class Circle :  public Shape 
{ 
	public: 
	     void Draw(); 
		     ~Circle(); 
}; 

class Square :  public Shape 
{ 
	public: 
	     void Draw(); 
		     ~Square(); 
}; 

class Rectangle :  public Shape 
{ 
	public: 
	     void Draw(); 
		     ~Rectangle(); 
}; 

void Circle::Draw() 
{ 
	    cout <<  "Circle::Draw() ..." << endl; 
} 
Circle::~Circle() 
{ 
	    cout <<  "~Circle ..." << endl; 
} 

void Square::Draw() 
{ 
	    cout <<  "Square::Draw() ..." << endl; 
} 
Square::~Square() 
{ 
	    cout <<  "~Square ..." << endl; 
} 

void Rectangle::Draw() 
{ 
	cout <<  "Rectangle::Draw() ..." << endl; 
} 

Rectangle::~Rectangle() 
{ 
	cout <<  "~Rectangle ..." << endl; 
} 

REGISTER_CLASS(Circle); 
REGISTER_CLASS(Square); 
REGISTER_CLASS(Rectangle); 


void DrawAllShapes( const vector<Shape *> &v) 
{ 
	vector<Shape *>::const_iterator it; 
	for (it = v.begin(); it != v.end(); ++it) 
	{ 
		(*it)->Draw(); 
	} 
} 

void DeleteAllShapes( const vector<Shape *> &v) 
{ 
	vector<Shape *>::const_iterator it; 
	for (it = v.begin(); it != v.end(); ++it) 
	{ 
		delete(*it); 
	} 
} 


int main( void) 
{ 
	vector<Shape *> v; 

	Shape *ps; 
	ps =  static_cast<Shape *>(DynObjectFactory::CreateObject( "Circle")); 
	v.push_back(ps); 
	ps =  static_cast<Shape *>(DynObjectFactory::CreateObject( "Square")); 
	v.push_back(ps); 
	ps =  static_cast<Shape *>(DynObjectFactory::CreateObject( "Rectangle")); 
	v.push_back(ps); 

	DrawAllShapes(v); 
	DeleteAllShapes(v); 


	return  0; 
}
