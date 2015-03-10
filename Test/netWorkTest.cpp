#include <iostream>
#include "dynServiceFactory.h"
#include "service.h"
#include <vector>
#include <string>

using namespace std;

void DrawAllShapes( const vector<Service *> &v) 
{ 
	vector<Service *>::const_iterator it; 
	for (it = v.begin(); it != v.end(); ++it) 
	{   
		(*it)->run(); 
	}   
} 

void DeleteAllShapes( const vector<Service *> &v) 
{ 
	vector<Service *>::const_iterator it; 
	for (it = v.begin(); it != v.end(); ++it) 
	{   
		delete(*it); 
	}   
} 

int main () {
	vector<Service *> v;  

	Service *ps; 
	ps =  static_cast<Service *>(DynServiceFactory::createService( "DbService")); 
	v.push_back(ps); 

/*
	ps =  static_cast<Shape *>(DynObjectFactory::CreateObject( "Square")); 
	v.push_back(ps); 
	ps =  static_cast<Shape *>(DynObjectFactory::CreateObject( "Rectangle")); 
	v.push_back(ps); 
*/

	DrawAllShapes(v); 
	DeleteAllShapes(v); 

	return  0;  
}
