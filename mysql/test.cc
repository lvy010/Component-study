#include <iostream>
#include <mysql/mysql.h>

int main()
{
    MYSQL *my = mysql_init(nullptr);
    if (nullptr == my)
    {
        std::cerr << "init MYSQL error" << std::endl;
        return 1;
    }
    std::cout << "mysql client version: " << mysql_get_client_info() << std::endl;
    return 0;
} 