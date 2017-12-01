#include "mysql.h"

	MySQL::MySQL() {
		conn = NULL;
		res = NULL;
		fields = NULL;
	}
	MySQL::~MySQL() {
		if (res != NULL) mysql_free_result(res);
		if (conn != NULL) mysql_close(conn);
	}
	bool MySQL::init() {
		conn = mysql_init(NULL);
		if (conn == NULL) {
			cout << "Error: can't create MySQL-descriptor" << endl;
			return false;
		}
		cout << "MySQL-descriptor was created!" << endl;
		return true;
	}
	bool MySQL::connect(string host, string user, string password, string db) {
		cout << "MySQL connect" << endl;
		try {
			if (!mysql_real_connect(conn, host.c_str(), user.c_str(), password.c_str(), db.c_str(), 0, NULL, 0)) {
				cout << "Error: can't connect to database" << endl;
				return false;
			}
		}
		catch (...) {
			cout << "connect catch" << endl;
			return false;
		}
		cout << "Connected to database!" << endl;
		return true;
	}
	
	
	bool MySQL::exec(string sql) {
		if (res != NULL) mysql_free_result(res);
		if (mysql_query(conn, sql.c_str()) != 0)
		{
			cout << "Error: mistake in SQL" << endl;
			return false;
		}
		return true;
	}

	bool MySQL::storeResult() { 
		if (res != NULL) mysql_free_result(res);
		res = mysql_store_result(conn);
		fields = mysql_fetch_fields(res);
		if (res) return true;
		return false;
	}

	string MySQL::getFieldValue(int rowIndex, int fieldIndex) {
		mysql_data_seek(res, rowIndex);
		MYSQL_ROW row = mysql_fetch_row(res);
		if (row[fieldIndex] == NULL) return "";
		return (string)row[fieldIndex];
	}

	int MySQL::getRowCount() {
		return mysql_num_rows(res);
	}
	int MySQL::getFieldCount() {
		int count = mysql_num_fields(res);
		return count;
	}

	int MySQL::active(string sql) {
		if (exec(sql)) {
			if (storeResult()) {
				int count = getRowCount();
				return count;
			}
		}
		return 0;
	}

	string MySQL::getFieldValue(int rowIndex, string fieldName) {
		//	MYSQL_ROW row = mysql_fetch_row(res);
		int count = mysql_num_fields(res);
		for (int i = 0; i < count; i++) {
			if (fieldName == (string)fields[i].name) {
				return getFieldValue(rowIndex, i);
			}
		}
		return "";
	}
	/*
	bool MySQL::query(string sql) {
		if (res != NULL) mysql_free_result(res);
		if (mysql_query(conn, sql.c_str()) != 0) {
			cout << "Error: mistake in SQL" << endl;
			return false;
		}
		return true;
	}

	void MySQL::freeResult() {
		if (res != NULL) mysql_free_result(res);
		res = NULL;
		fields = NULL;
	}
	String MySQL::getEscapeString(String s) {
		int len = s.getLength();
		char *res = (char*)malloc(len * 2 + 1);
		//MYSQL *mysql, char *to,const char *from, unsigned long length
		mysql_real_escape_string(conn, res, s.to_string().c_str(), len);
		String sRes = res;
		free(res);

		return sRes;
	}
	String MySQL::getEscapeString(char *s, int len) {
		char *res = (char*)malloc(len * 2 + 1);
		//MYSQL *mysql, char *to,const char *from, unsigned long length
		mysql_real_escape_string(conn, res, s, len);
		String sRes = res;
		free(res);

		return sRes;
	}
	int MySQL::getLastId() {
		String sql = "select LAST_INSERT_ID();";
		if (this->exec(sql)) {
			if (this->storeResult()) {
				int count = this->getRowCount();
				if (count > 0) {
					String lastSiteId = this->getFieldValue(0, "LAST_INSERT_ID()");
					return lastSiteId.toInt();
				}
			}
		}
		return 0;
	}*/
