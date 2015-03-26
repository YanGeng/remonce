#include <stdarg.h>
#include <cppconn/prepared_statement.h>
#include "dbDao.h"
#include "macro.h"
#include "cFunc.h"


DbDao::DbDao() : conn(NULL) {
	url = std::string("");
	username = std::string("");
	pass = std::string("");
}


DbDao::DbDao(std::string url, std::string username, std::string pass) : url(url)
	,username(username)
	,pass(pass) 
	,conn(NULL) {
}


DbDao::~DbDao() {
	if (conn.get() != NULL && !conn->isClosed()) {
		try {
			conn->close();
		} catch (sql::SQLException &e) {
			// Never throw exception in the destructors func
			std::abort();
		}
	}
	conn.reset();
}


/***************************************************
 *	set & get function of the DbDao
 * ************************************************/
void DbDao::setUrl(std::string url) {
	this->url = url;
}

void DbDao::setUser(std::string username) {
	this->username = username;
}

void DbDao::setPass(std::string pass) {
	this->pass = pass;
}

std::string DbDao::getUrl() const {
	return url;
}

std::string DbDao::getUser() const {
	return username;
}

std::string DbDao::getPass() const {
	return pass;
}


/********************************************************************************
 *  func_name: 
 *  return: 
 *  parameters: 
 *  description:  print the ERR when get sql::SQLException
 *******************************************************************************/
void DbDao::printSqlErr(sql::SQLException &e) const {
	std::cout << "##################################################################################################\n";
	// Call the CURRENT_FILE_LINE to print the code info
	CURRENT_FILE_LINE;

	std::cout << "# ERROR: " << e.what();
	std::cout << " ( MySQL error code: " << e.getErrorCode();
	std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	std::cout << "##################################################################################################\n";
}


/***************************************************
 *	return the connection to mysql
 * ************************************************/
//std::auto_ptr< sql::Connection > DbDao::getConnection() {
void DbDao::getConnection() {
	if (!this->conn.get()) {
		sql::Driver *driver = get_driver_instance();
		this->conn = std::auto_ptr< sql::Connection > (driver->connect(url, username, pass));
	}
	//return this->conn;
}


/********************************************************************************
 *  func_name: 
 *  return: 
 *  parameters: 
 *  description:  close the connection of mysql
 *******************************************************************************/
void DbDao::closeConn() {
	if (conn.get() != NULL && !conn->isClosed()) {
		conn->close();
	}
	conn.reset();
}


/********************************************************************************
 *  func_name: 
 *  return: 
 *  parameters: 
 *  description:  reset the sql::Connection to NULL
 *******************************************************************************/
void DbDao::reset() {
	closeConn();
	url = std::string("");
	username = std::string("");
	pass = std::string("");
}


/********************************************************************************
 *  func_name: 
 *  return: 
 *  parameters: 
 *  description:  reset the sql::Connection to a new Connection(url, username, 
 *				  pass)
 *******************************************************************************/
void DbDao::reset(std::string url, std::string username, std::string pass) {
	closeConn();
	this->url = url;
	this->username = username;
	this->pass = pass;
	getConnection();
}


/***************************************************
 *	return the result of query sql
 * ************************************************/
std::auto_ptr< sql::ResultSet > DbDao::query(const char* sql, ...) {
	assert(sql);

#ifdef _DEBUG 
	CURRENT_FILE_LINE;
#endif

	va_list args;
	va_start(args, sql);

	// Call va_list2String to change the va_list to string. Support %d, %u, %i, %s and %f
	std::string qurSql = cfunc::va_list2String(sql, args);
	std::auto_ptr< sql::ResultSet > res;

	try {
		getConnection();

		std::auto_ptr< sql::PreparedStatement > prep_select(conn->prepareStatement(qurSql.c_str()));
		res = std::auto_ptr< sql::ResultSet >(prep_select->executeQuery());

	} catch (sql::SQLException &e) {
		printSqlErr(e);
	}

	return res;
}


/********************************************************************************
 *  func_name: 
 *  return: 
 *  parameters: 
 *  description:  run any sql to insert the value to mysql
 *******************************************************************************/
bool DbDao::executeSql(const char *sql) {
	assert(sql);

	return insert(sql);
}


/********************************************************************************
 *  func_name: 
 *  return: 
 *  parameters: 
 *  description:  run the insert sql to insert the value to mysql
 *******************************************************************************/
bool DbDao::insert(const char *sql, ...) {
	assert(sql);

#ifdef _DEBUG 
	CURRENT_FILE_LINE;
#endif

	va_list args;
	va_start(args, sql);

	// change the va_list to string
	std::string insertSql = cfunc::va_list2String(sql, args);

	try {
		getConnection();
		std::auto_ptr< sql::PreparedStatement > prep_insert(conn->prepareStatement(insertSql.c_str()));
		if (prep_insert->execute()) {
			return true;
		}
		return false;

	} catch (sql::SQLException &e) {
		printSqlErr(e);
		return false;
	}
}


/********************************************************************************
 *  func_name: 
 *  return: 
 *  parameters: 
 *  description:  run the modify sql to modify the value in mysql database
 *******************************************************************************/
int DbDao::update(const char *sql, ...) {
	assert(sql);

#ifdef _DEBUG 
	CURRENT_FILE_LINE;
#endif

	va_list args;
	va_start(args, sql);

	// change the va_list to string
	std::string updateSql = cfunc::va_list2String(sql, args);

	try {
		getConnection();
		std::auto_ptr< sql::PreparedStatement > prep_update(conn->prepareStatement(updateSql.c_str()));
		return prep_update->executeUpdate();

	} catch (sql::SQLException &e) {
		printSqlErr(e);
		return -1;
	}
}
