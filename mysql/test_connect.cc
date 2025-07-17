#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include <cstring>

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

    std::string sql = "select * from user";
    int n = mysql_query(my, sql.c_str());
    if(n == 0)
    {
        std::cout << sql << " success" << std::endl;
        // 判断是否为SELECT语句
        if(sql.size() >= 6 && strncasecmp(sql.c_str(), "select", 6) == 0)
        {
            MYSQL_RES *res = mysql_store_result(my);
            if(nullptr == res)
            {
                std::cerr << "mysql_store_result error: " << mysql_error(my) << std::endl;
                mysql_close(my);
                return 4;
            }
            int num_fields = mysql_num_fields(res);
            int num_rows = mysql_num_rows(res);
            std::cout << "行: " << num_rows << std::endl;
            std::cout << "列: " << num_fields << std::endl;

        //    typedef char** MYSQL_ROW;
        //    typedef struct st_mysql_row {
        //     char **data;
        //     unsigned long *lengths;
        //    } MYSQL_ROW;

            // 打印内容
            for(int i = 0; i < num_rows; i++)
            {
                MYSQL_ROW row = mysql_fetch_row(res);
                for(int j = 0; j < num_fields; j++)
                {
                    std::cout << (row[j] ? row[j] : "NULL") << "\t";
                }
                std::cout << std::endl;
            }
            mysql_free_result(res);
        }
    }
    else
    {
        std::cout << sql << " failed: " << mysql_error(my) << std::endl;
        mysql_close(my);
        return 3;
    }


    // The following block is removed as per the edit hint.
    // MYSQL_RES *res = mysql_store_result(my);
    // if(nullptr == res)
    // {
    //     std::cerr << "mysql_store_result error: " << mysql_error(my) << std::endl;
    //     return 4;
    // }
    
    // int num_fields = mysql_num_fields(res);
    // int num_rows = mysql_num_rows(res);
    // std::cout << "行: " << num_rows << std::endl;
    // std::cout << "列: " << num_fields << std::endl;

    mysql_close(my);
    return 0;
} 