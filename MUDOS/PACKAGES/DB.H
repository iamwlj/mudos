#ifndef PACKAGES_DB_H
#define PACKAGES_DB_H

#ifdef PACKAGE_DB

#ifdef USE_MSQL
/* MSQL v2 requires this so that it knows the right prototypes */
#define _OS_UNIX

#ifdef INCL_LOCAL_MSQL_H
#include "/usr/local/include/msql.h"
#endif
#ifdef INCL_LOCAL_MSQL_MSQL_H
#include "/usr/local/msql/include/msql.h"
#endif
#ifdef INCL_LOCAL_MINERVA_MSQL_H
#include "/usr/local/Minerva/include/msql.h"
#endif
#ifdef INCL_LIB_HUGHES_MSQL_H
#include "/usr/lib/Hughes/include/msql.h"
#endif
#endif

#ifdef USE_SQLITE
#ifdef INCL_WIN32_SQLITE_H
#include "../SQLite/include/sqlite3.h"
#endif
#endif

#ifdef USE_MYSQL
//#define MUDOS_MYSQL_VERSION   50
#define MUDOS_MYSQL_VERSION   80

#ifdef INCL_WIN32_MYSQL_H
#if 50 == MUDOS_MYSQL_VERSION
#include "../mysql/50/include/mysql.h"
#elif 80 == MUDOS_MYSQL_VERSION
#include "../mysql/80/include/mysql.h"
#endif
#endif
#ifdef INCL_LOCAL_MYSQL_H
#include "/usr/local/include/mysql.h"
#endif
#ifdef INCL_LOCAL_INCLUDE_MYSQL_MYSQL_H
#include "/usr/local/include/mysql/mysql.h"
#endif
#ifdef INCL_LOCAL_MYSQL_MYSQL_H
#include "/usr/local/mysql/include/mysql.h"
#endif
#ifdef INCL_MYSQL_MYSQL_H
#include "/usr/include/mysql/mysql.h"
#endif
#endif

typedef union dbconn_u {
#ifdef USE_SQLITE
      struct tmp_sqlite3 {
        struct sqlite3 *handle;
        struct sqlite3_stmt *results;
        int nrows;
        int ncolumns;
        int last_row;
        int step_res;
        char errormsg[256];
      } SQLite3;
#endif
#ifdef USE_MYSQL
    struct tmp_mysql {
	char errormsg[256];
	MYSQL *handle;
	MYSQL_RES *results;
    } mysql;
#endif
} dbconn_t;

/*
 * Structure so we can have a lookup table for the specific database
 */
typedef struct db_defn_s {
    char *name;
    int (*connect)(dbconn_t *, char *, char *, char *, char *);
    int (*close)(dbconn_t *);
    int (*execute)(dbconn_t *, char *);
    array_t * (*fetch)(dbconn_t *, int);
    int (*commit)(dbconn_t *);
    int (*rollback)(dbconn_t *);
    void (*cleanup)(dbconn_t *);
    void (*status)(dbconn_t *, outbuffer_t *);
    char * (*error)(dbconn_t *);
    int (*affected)(dbconn_t *);
} db_defn_t;

#define DB_FLAG_EMPTY	0x1

typedef struct _db {
    int flags;
    db_defn_t *type;
    dbconn_t c;
} db_t;

void db_cleanup PROT((void));

#endif	/* PACKAGES_DB */

#endif	/* PACKAGES_DB_H */
