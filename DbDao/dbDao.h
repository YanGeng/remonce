#ifndef __DBDAO_H
#define __DBDAO_H

#include <string>
#include <memory>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <boost/shared_ptr.hpp>

class DbDao
{
	public:
		DbDao();
		DbDao(std::string url, std::string username, std::string pass);
		~DbDao();

		void setUrl(std::string url);
		void setUser(std::string username);
		void setPass(std::string pass);

		std::string getUrl() const;
		std::string getUser() const;
		std::string getPass() const;

		void closeConn();
		void getConnection();
		boost::shared_ptr< sql::ResultSet > query(const char *sql, ...);
		bool insert(const char *sql, ...);
		int update(const char *sql, ...);
		bool executeSql(const char *sql);
		void reset();
		void reset(std::string url, std::string username, std::string pass);

	private:
		void printSqlErr(sql::SQLException &e) const;

	private:
		boost::shared_ptr< sql::Connection > conn;
		std::string url;
		std::string username;
		std::string pass;
};

#endif
