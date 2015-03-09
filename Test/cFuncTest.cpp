#include "cFunc.h"
#include "dbDao.h"
#include <iostream>
#include <memory>

#include <mysql_connection.h>  
#include <mysql_driver.h>  
#include <cppconn/driver.h> 
#include <cppconn/prepared_statement.h>

//#define DBHOST "tcp://127.0.0.1:3306"  
#define DBHOST "tcp://10.1.77.22:3306"  
#define USER "aspnet_dianping"      //"midas_data"  
#define PASSWORD "dp!@OpQW34bn"     //"dp!@VcoOM24cU"  
//
///*
//
//   midasDataConnStr="-j jdbc:mysql://10.1.101.216:3306/DPMidasData?useUnicode=true&characterEncoding=UTF-8 \
//      -u midas_data -w dp!@VcoOM24cU"
//         midasBetaDataConnStr="-j jdbc:mysql://10.1.77.22:3306/DPMidasData?useUnicode=true&characterEncoding=UTF-8 \
//            -u aspnet_dianping -w dp!@OpQW34bn "
//
//            */

using namespace std;

void vaTest(const char *str, ...) {
	va_list args;
	va_start(args, str);
	std::string printed = cfunc::va_list2String(str, args);
	va_end(args);
	std::cout << printed << std::endl;
}

int main(void) {
	char str[32] = "Hello, %d, world!%s! $$%f";
	vaTest(str, 5, "Add %s test", 1.25);

	std::auto_ptr<int> auto_p;
	
	std::cout << auto_p.get() << std::endl;
	auto_p = std::auto_ptr<int> (new int);

	std::cout << auto_p.get() << std::endl;
	*auto_p.get() = 100;

	std::cout << *auto_p << std::endl << *auto_p.get() << std::endl;


	sql::Driver *driver;  
	sql::Connection *conn;  
	driver = get_driver_instance();  
	conn = driver->connect(DBHOST, USER, PASSWORD);  

	sql::PreparedStatement *stmt = conn->prepareStatement("SELECT product_type,shop_id,account_name FROM DPMidasData.cpm_sht_shop_account limit 10;");
	sql::ResultSet *resStand = stmt->executeQuery();
	int row = 1;
	while (resStand->next()) {
		cout << "#\t\t Row " << row << " - shop_id = " << resStand->getInt("shop_id");
		cout << ", account_name = '" << resStand->getString("account_name") << "'" << endl;
		row ++;
	}            
	delete stmt;

	conn->setAutoCommit(0);  
	std::cout<<"DataBase connection autocommit mode = "<<conn->getAutoCommit() << std::endl;  
	delete conn;  
	driver = NULL;  
	conn = NULL;  

	cout << "hello\n";
	DbDao *dbDao = new DbDao();
	string dbHost = string("tcp://10.1.77.22:3306");
	string user = string("aspnet_dianping");
	string pass = string("dp!@OpQW34bn");
	 
	cout << "?????\n";

	dbDao->setUrl(dbHost);
	dbDao->setUser(user);
	dbDao->setPass(pass);
	
	cout << "%%%%%\n";
	
	std::cout << dbDao->getUrl() << dbDao->getUser() << dbDao->getPass() << std::endl;

//	std::auto_ptr< sql::Connection > autoConn(dbDao->getConnection());

	//std::string queSql = "SELECT product_type, shop_id, city_name, account_name FROM DPMidasData.cpm_sht_shop_account limit 10;";
	std::string queSql = "SELECT product_type,shop_id,account_name FROM DPMidasData.cpm_sht_shop_account limit 10;";
	std::auto_ptr< sql::ResultSet > res = dbDao->query("SELECT product_type,shop_id,account_name FROM DPMidasData.cpm_sht_shop_account limit 10;");
	//std::auto_ptr< sql::ResultSet > res(dbDao->query(queSql.c_str()));

	while (res->next()) {
		std::cout << "The account_name is: " << res->getString("account_name") << std::endl;
	}

	std::string createSql = "CREATE TABLE `DPMidasData`.`tonyTest` (`id` INT NOT NULL,`user` VARCHAR(45) NOT NULL,`pass` VARCHAR(45) NULL,`age` INT NULL,PRIMARY KEY (`id`, `user`));";
	dbDao->insert(createSql.c_str());
	 
	dbDao->executeSql(createSql.c_str());

	delete dbDao;

}
