#ifndef __MYSQL_H__
#define __MYSQL_H__

#include <iostream>
#include <mysql/mysql.h>

using namespace std;

class MySQL{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_FIELD *fields;
	virtual bool exec(string sql);
	virtual bool storeResult();
	virtual int getRowCount();
	virtual int getFieldCount();
	virtual string getFieldValue(int rowIndex, int fieldIndex);
public:
	MySQL();
	~MySQL();
	virtual bool init();
	virtual bool connect(string host, string user, string password, string db);
	virtual int active(string sql);
	virtual string getFieldValue(int rowIndex, string fieldName);
	/*virtual bool query(String sql);
	virtual void freeResult();

	virtual String getEscapeString(String s);
	virtual String getEscapeString(char *s, int len);


	virtual int getLastId();*/
};

#endif
