#include <iostream>
#include <sstream>  
#include <memory>  
#include <string>  
#include <stdexcept>  
  
#include <mysql_connection.h>  
#include <mysql_driver.h>  
#include <cppconn/driver.h>  

using namespace sql;  
using namespace std;  

//#define DBHOST "tcp://127.0.0.1:3306"  
#define DBHOST "tcp://10.1.77.22:3306"  
#define USER "aspnet_dianping"		//"midas_data"  
#define PASSWORD "dp!@OpQW34bn"		//"dp!@VcoOM24cU"  

/*

   midasDataConnStr="-j jdbc:mysql://10.1.101.216:3306/DPMidasData?useUnicode=true&characterEncoding=UTF-8 \
   -u midas_data -w dp!@VcoOM24cU"
   midasBetaDataConnStr="-j jdbc:mysql://10.1.77.22:3306/DPMidasData?useUnicode=true&characterEncoding=UTF-8 \
   -u aspnet_dianping -w dp!@OpQW34bn "

*/

int main() {   
	Driver *driver;  
	Connection *conn;  
	driver = get_driver_instance();  
	conn = driver->connect(DBHOST, USER, PASSWORD);  
	conn->setAutoCommit(0);  
	cout<<"DataBase connection autocommit mode = "<<conn->getAutoCommit()<<endl;  
	delete conn;  
	driver = NULL;  
	conn = NULL;  
	return 0;  
}  
