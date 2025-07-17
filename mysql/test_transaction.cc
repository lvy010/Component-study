#include <iostream>
#include <mysql/mysql.h>

int main() {
    const char* host = "127.0.0.1";
    const char* user = "connector";
    const char* passwd = "123456";
    const char* db = "conn";
    unsigned int port = 3306;

    MYSQL *my = mysql_init(nullptr);
    if (my == nullptr) {
        std::cerr << "init MYSQL error: " << mysql_error(my) << std::endl;
        return 1;
    }

    if (mysql_real_connect(my, host, user, passwd, db, port, nullptr, 0) == nullptr) {
        std::cerr << "connect MySQL error: " << mysql_error(my) << std::endl;
        mysql_close(my);
        return 2;
    }
    mysql_set_character_set(my, "utf8");
    std::cout << "connect success" << std::endl;

    // 关闭自动提交，开启事务
    if (mysql_autocommit(my, 0)) {
        std::cerr << "关闭自动提交失败: " << mysql_error(my) << std::endl;
        mysql_close(my);
        return 3;
    }
    std::cout << "已关闭自动提交，开始事务" << std::endl;

    // 执行插入
    const char* sql = "INSERT INTO user(name) VALUES('事务测试')";
    if (mysql_query(my, sql) == 0) {
        std::cout << "插入成功，准备回滚" << std::endl;
        // 回滚
        if (mysql_rollback(my) == 0) {
            std::cout << "回滚成功，数据不会被插入" << std::endl;
        } else {
            std::cerr << "回滚失败: " << mysql_error(my) << std::endl;
        }
    } else {
        std::cerr << "插入失败: " << mysql_error(my) << std::endl;
    }

    // 再次插入
    if (mysql_query(my, sql) == 0) {
        std::cout << "插入成功，准备提交" << std::endl;
        // 提交
        if (mysql_commit(my) == 0) {
            std::cout << "提交成功，数据已写入" << std::endl;
        } else {
            std::cerr << "提交失败: " << mysql_error(my) << std::endl;
        }
    } else {
        std::cerr << "插入失败: " << mysql_error(my) << std::endl;
    }

    // 恢复自动提交
    mysql_autocommit(my, 1);

    mysql_close(my);
    return 0;
} 