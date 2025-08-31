# MySQL C++ 连接器示例

一个基于 MySQL C API 的 C++ 示例项目，演示了如何使用 MySQL 的原生 C 库进行数据库连接、查询和事务操作。

## 项目概述

本项目包含了三个主要的示例程序，展示了 MySQL C++ 编程的基础操作：

- **基础连接测试** - 验证 MySQL 客户端库的初始化
- **数据库连接与查询** - 完整的数据库连接、查询和结果处理
- **事务处理** - 演示事务的提交和回滚机制

## 项目结构

```
mysql/
├── Makefile              # 项目构建配置
├── mysql_struct.h        # MySQL 核心数据结构定义
├── test.cc              # 基础 MySQL 客户端测试
├── test_connect.cc      # 数据库连接与查询示例
├── test_transaction.cc  # 事务处理示例
└── README.md           # 项目文档
```

## 功能特性

### 📡 基础连接测试 (`test.cc`)
- MySQL 客户端库初始化
- 版本信息获取
- 基础错误处理

### 🔗 数据库连接与查询 (`test_connect.cc`)
- 完整的数据库连接流程
- SQL 查询执行
- 结果集处理和数据提取
- 字符集设置 (UTF-8)
- 资源管理和清理

### 💾 事务处理 (`test_transaction.cc`)
- 自动提交控制
- 事务开启和管理
- 提交 (commit) 操作
- 回滚 (rollback) 操作
- 事务状态恢复

### 🏗️ 数据结构定义 (`mysql_struct.h`)
- MySQL 核心结构体定义
- `MYSQL` 连接对象结构
- `MYSQL_RES` 结果集结构
- `MYSQL_FIELD` 字段信息结构

## 环境要求

### 系统依赖
- **编译器**: GCC 4.8+ (支持 C++11)
- **MySQL**: MySQL 5.7+ 或 MariaDB 10.2+
- **开发库**: libmysqlclient-dev

### Ubuntu/Debian 安装
```bash
sudo apt-get update
sudo apt-get install build-essential
sudo apt-get install libmysqlclient-dev
sudo apt-get install mysql-server  # 可选：本地 MySQL 服务器
```

### CentOS/RHEL 安装
```bash
sudo yum groupinstall "Development Tools"
sudo yum install mysql-devel
sudo yum install mysql-server  # 可选：本地 MySQL 服务器
```

## 快速开始

### 1. 克隆项目
```bash
git clone <repository-url>
cd mysql
```

### 2. 数据库准备

在 MySQL 中创建测试数据库和用户：

```sql
-- 创建数据库
CREATE DATABASE conn CHARACTER SET utf8mb4 COLLATE utf8mb4_unicode_ci;

-- 创建用户并授权
CREATE USER 'connector'@'localhost' IDENTIFIED BY '123456';
GRANT ALL PRIVILEGES ON conn.* TO 'connector'@'localhost';
FLUSH PRIVILEGES;

-- 创建测试表
USE conn;
CREATE TABLE user (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(100) NOT NULL
);

-- 插入测试数据
INSERT INTO user (name) VALUES ('张三'), ('李四'), ('王五');
```

### 3. 编译项目

```bash
# 编译所有示例
make all

# 或单独编译
make test              # 基础测试
make test_connect      # 连接查询测试
make test_transaction  # 事务测试
```

### 4. 运行示例

```bash
# 基础测试
./test

# 连接查询测试
./test_connect

# 事务测试
./test_transaction
```

## 配置说明

### 数据库连接参数

在 `test_connect.cc` 和 `test_transaction.cc` 中修改以下连接参数：

```cpp
const std::string host = "127.0.0.1";    // 数据库主机地址
const std::string user = "connector";     // 数据库用户名
const std::string passwd = "123456";      // 数据库密码
const std::string db = "conn";            // 数据库名称
const unsigned int port = 3306;           // 数据库端口
```

### Makefile 配置

```makefile
CXX = g++                                 # 编译器
CXXFLAGS = -Wall -std=c++11              # 编译选项
LDFLAGS = -lmysqlclient                  # 链接库
```

## 示例输出

### 基础测试输出
```
mysql client version: 8.0.33
```

### 连接查询测试输出
```
connect success
select * from user success
行: 3
列: 2
1    张三
2    李四
3    王五
```

### 事务测试输出
```
connect success
已关闭自动提交，开始事务
插入成功，准备回滚
回滚成功，数据不会被插入
插入成功，准备提交
提交成功，数据已写入
```

## 最佳实践

### 🔒 安全性
- 避免在代码中硬编码密码
- 使用参数化查询防止 SQL 注入
- 及时关闭数据库连接释放资源

### ⚡ 性能优化
- 使用连接池管理数据库连接
- 合理使用事务，避免长时间锁定
- 对大结果集使用 `mysql_use_result()` 而非 `mysql_store_result()`

### 🛠️ 错误处理
- 检查每个 MySQL API 调用的返回值
- 使用 `mysql_error()` 获取详细错误信息
- 实现适当的资源清理机制

## 常见问题

### Q: 编译时出现 "mysql.h: No such file" 错误
**A**: 需要安装 MySQL 开发库：
```bash
# Ubuntu/Debian
sudo apt-get install libmysqlclient-dev

# CentOS/RHEL
sudo yum install mysql-devel
```

### Q: 连接时出现 "Access denied" 错误
**A**: 检查以下配置：
1. 用户名和密码是否正确
2. 数据库用户是否有相应权限
3. MySQL 服务是否正常运行
4. 防火墙设置是否允许连接

### Q: 中文显示乱码
**A**: 确保：
1. 数据库字符集为 UTF-8
2. 代码中设置了正确的字符集：`mysql_set_character_set(my, "utf8")`
3. 终端支持 UTF-8 显示

## 进阶学习

### 推荐阅读
- [MySQL C API 官方文档](https://dev.mysql.com/doc/c-api/8.0/en/)
- [MySQL 事务处理机制](https://dev.mysql.com/doc/refman/8.0/en/innodb-transaction-model.html)
- [C++ MySQL 连接器最佳实践](https://dev.mysql.com/doc/connector-cpp/8.0/en/)

### 扩展功能
- [ ] 连接池实现
- [ ] 预处理语句 (Prepared Statements)
- [ ] 异步操作支持
- [ ] SSL 连接配置
- [ ] 多线程安全处理

## 许可证

本项目仅用于学习和研究目的。请遵循 MySQL 的相关许可证条款。

## 贡献

欢迎提交 Issue 和 Pull Request 来改进这个项目！

---

**注意**: 本项目仅为学习示例，在生产环境中使用时请添加适当的错误处理、安全检查和性能优化。
