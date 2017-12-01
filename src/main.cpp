#include "mysql.h"

int main()
{
	MySQL sql;
	cout << sql.init() << endl;
	cout << sql.connect("localhost", "root", "root", "mysql") << endl;
	//cout << sql.exec("select * from user") << endl;
	//cout << sql.storeResult() << endl;
	cout << sql.active("select * from user") << endl;
	cout << sql.getFieldValue(1, "User") << endl;
}
