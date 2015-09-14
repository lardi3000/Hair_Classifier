#include "db_utils.hpp"


MYSQL connectToDb(){
		MYSQL *connection;
		char *servername     = "localhost";
		char *user            = "root";
		char *password        = "";
		char *database        = "hair_db";
		char *socket            = "/opt/lampp/var/mysql/mysql.sock";
		char *hostinfo;
		char *serverinfo;
		int  protoinfo;

		/* Intitialize connection to database, and MYSQL structure. */
		connection = mysql_init(NULL);

		/* Connect to database */
		if(!mysql_real_connect(connection, servername, user,
			password, database, 0, socket, 0)) {
				printf("%s\n", mysql_error(connection));
			}
		return *connection;
}

