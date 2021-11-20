#include <string>
#include <projectX/sysout/sysout.cpp>
#ifndef PX_ARM64
    #include <mysql/mysql.h>
#else
    #include "arm64IntelliSubstitute.cpp"
#endif

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
        px::sysError("mysql error: " + std::string(mysql_error(connection)));
        exit(1);
    }
    return connection;
}

MYSQL_RES* mysql_execute_query(MYSQL* connection, const char* sql_query)
{
    if(mysql_query(connection, sql_query))
    {
        px::sysError("mysql error: " + std::string(mysql_error(connection)));
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

    std::list<std::list<std::string>> query(std::string sql,int colcount) //std::list<std::list<std::string>>
    {
        std::list<std::list<std::string>> result;
        const char *convert = sql.c_str();
        MYSQL_RES* res = mysql_execute_query(&this->conn, convert);
        if(res == nullptr)
            px::sysError("error while accessing mysql results, pointer to result was nullptr");
        std::cout << "data: " << std::endl;
        MYSQL_ROW row;
        while((row = mysql_fetch_row(res)))
        {
            std::list<std::string> subres;
            for(int i = 0;i < colcount;i++)
            {
                std::cout << row[i] << " | ";
                subres.push_back(row[i]);
            }
            std::cout << std::endl;
            result.push_back(subres);
        }
        return result;
    }

    bool VoidQuery(std::string sql)
    {
        const char *convert = sql.c_str();
        MYSQL_RES* res = mysql_execute_query(&this->conn, convert);
        if(res == nullptr)
            px::sysError("error while accessing mysql results, pointer to result was nullptr");
        if(res)
            return 1;
        return 0;
    }
};