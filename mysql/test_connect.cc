#include <iostream>
#include <string>
#include <mysql/mysql.h>

const std::string host = "127.0.0.1";
const std::string user = "connector";
const std::string passwd = "123456";
const std::string db = "conn";
const unsigned int port = 3306;

int main()
{
    //std::cout << "mysql client version: " << mysql_get_client_info() << std::endl;

    MYSQL *my = mysql_init(nullptr);
    if (nullptr == my)
    {
        std::cerr << "init MYSQL error: " << mysql_error(my) << std::endl;
        return 1;
    }

    if(mysql_real_connect(my, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, nullptr, 0) == nullptr)
    {
        std::cerr << "connect MySQL error: " << mysql_error(my) << std::endl;
        return 2;
    }
    mysql_set_character_set(my, "utf8");
    std::cout << "connect success" << std::endl;

    std::string sql = "update user set name='李四' where id=2";
    int n = mysql_query(my, sql.c_str());
    if(n == 0)
    {
        std::cout << sql << " success" << std::endl;
    }
    else
    {
    std::cout << sql << " failed: " << mysql_error(my) << std::endl;
    return 3;
    }

/*




*/
    MYSQL_RES *res = mysql_store_result(my);
    if(nullptr == res)
    {
        std::cerr << "mysql_store_result error: " << mysql_error(my) << std::endl;
        return 4;
    }
    
    mysql_close(my);
    return 0;
} 