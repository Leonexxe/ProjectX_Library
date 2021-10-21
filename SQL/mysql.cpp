#include <string>
#include <projectX/sysout/sysout.cpp>
#include <mysql/mysql.h>

struct connection_details
{
    const char *server, *user, *password, *database;
};

MYSQL* mysql_connection_setup(struct connection_details mysql_details)
{
    MYSQL *connection = mysql_init(NULL);
    if(!mysql_real_connect(
        connection, 
        mysql_details.server,
        mysql_details.user,
        mysql_details.password,
        mysql_details.database,
        0,
        NULL,
        0))
    {
        sysError("mysql error: " + std::string(mysql_error(connection)));
        exit(1);
    }
    return connection;
}

MYSQL_RES* mysql_execute_query(MYSQL* connection, const char* sql_query)
{
    if(mysql_query(connection, sql_query))
    {
        sysError("mysql error: " + std::string(mysql_error(connection)));
        return nullptr;
    }
    return mysql_use_result(connection);
}

/*
*
*
*
*
*
*
*
*
*/

const char getSQLRequest_SELECT(std::string* columns[],std::string table)
{
    return '-';
}
const char getSQLRequest_INSERT(std::string* columns[],std::string* values[],std::string table)
{
    return '-';
}

class mySQL
{
public:
    connection_details CD;
    MYSQL conn;
    mySQL(connection_details* connD)
    {
        this->CD = *connD;
        this->conn = *mysql_connection_setup(this->CD);
    }

    std::string query(std::string sql,int colcount) //std::list<std::list<std::string>>
    {
        const char *convert = sql.c_str();
        MYSQL_RES* res = mysql_execute_query(&this->conn, convert);
        if(res == nullptr){return "<-994>";}
        std::cout << "data: " << std::endl;
        MYSQL_ROW row;
        while((row = mysql_fetch_row(res)))
        {
            for(int i = 0;i < colcount;i++)
            {
                std::cout << row[i] << " | ";
            }
            std::cout << std::endl;
        }
        return "<1>";
    }
};