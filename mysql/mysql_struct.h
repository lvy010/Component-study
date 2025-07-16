#ifndef MYSQL_STRUCT_H
#define MYSQL_STRUCT_H

#include <stddef.h>

// 结构体定义来源于 MySQL 源码

typedef struct st_mysql
{
    NET net;                             /* Communication parameters */
    unsigned char *connector_fd;         /* ConnectorFd for SSL */
    char *host, *user, *passwd, *unix_socket, *server_version, *host_info;
    char *info, *db;
    struct charset_info_st *charset;
    MYSQL_FIELD *fields;
    MEM_ROOT field_alloc;
    my_ulonglong affected_rows;
    my_ulonglong insert_id;              /* id if insert on table with NEXTNR */
    my_ulonglong extra_info;             /* Not used */
    unsigned long thread_id;             /* Id for connection in server */
    unsigned long packet_length;
    unsigned int port;
    unsigned long client_flag, server_capabilities;
    unsigned int protocol_version;
    unsigned int field_count;
    unsigned int server_status;
    unsigned int server_language;
    unsigned int warning_count;
    struct st_mysql_options options;
    enum mysql_status status;
    my_bool free_me;                     /* If free in mysql_close */
    my_bool reconnect;                   /* set to 1 if automatic reconnect */
    char scramble[SCRAMBLE_LENGTH+1];    /* session-wide random string */
    my_bool unused1;
    void *unused2, *unused3, *unused4, *unused5;
    LIST *stmts;                         /* list of all statements */
    const struct st_mysql_methods *methods;
    void *thd;
    /*
      Points to boolean flag in MYSQL_RES or MYSQL_STMT. We set this flag
      from mysql_stmt_close if close had to cancel result set of this object.
    */
    my_bool *unbuffered_fetch_owner;
    /* needed for embedded server - no net buffer to store the 'info' */
    char *info_buffer;
    void *extension;
} MYSQL;

// ... existing code ...

typedef struct st_mysql_res {
    my_ulonglong row_count;
    MYSQL_FIELD *fields;
    MYSQL_DATA *data;
    MYSQL_ROWS *data_cursor;
    unsigned long *lengths; /* column lengths of current row */
    MYSQL *handle;          /* for unbuffered reads */
    const struct st_mysql_methods *methods;
    MYSQL_ROW row;          /* If unbuffered read */
    MYSQL_ROW current_row;  /* buffer to current row */
    MEM_ROOT field_alloc;
    unsigned int field_count, current_field;
    my_bool eof;            /* Used by mysql_fetch_row */
    my_bool unbuffered_fetch_cancelled; /* mysql_stmt_close() had to cancel this result */
    void *extension;
} MYSQL_RES;

#endif // MYSQL_STRUCT_H 