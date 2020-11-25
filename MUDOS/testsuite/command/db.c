#include <globals.h>

int
main(string type)
{
    int dbhandle = db_connect("127.0.0.1", "mudos", "dbuser", 1);
    write("connect " + dbhandle + "\n");
    write("type " + type + "\n");
    if ( 1 > dbhandle ) return 0;

    if ( "0" == type )
    {
        db_exec(dbhandle, "DROP TABLE IF EXISTS `users`");
        db_commit(dbhandle);
        db_exec(dbhandle, "CREATE TABLE `users` (`id` varchar(10) NOT NULL DEFAULT '', `name` varchar(10) NOT NULL DEFAULT '', `password` varchar(50) NOT NULL DEFAULT '')");
        db_commit(dbhandle);
    }
    else if ( "1" == type )
    {
        db_exec(dbhandle, "INSERT INTO `users` VALUES ('test', '123456', 'abcdefg')");
        db_commit(dbhandle);
    }
    else if ( "2" == type )
    {
        int rows = db_exec(dbhandle, "SELECT name from users");
        int currow;

        if ( !rows )
        {
            write("No rows returned.\n");
        }
        else if ( stringp(rows) )
        {
            write(rows + "\n");
        }
        else
        {
            for ( currow = 1; currow <= rows; currow++ )
            {
                mixed res = db_fetch(dbhandle, currow);
                write(res[0] + "\n");
            }
        }
    }

    db_close(dbhandle);

    return 1;
}

