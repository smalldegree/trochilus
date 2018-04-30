Welcome to trochilus.

Trochilus aims to implement common structures and algorithms.

[Build Cunit]
+ aclocal
+ autoconf
+ autoheader
+ libtoolize --automake --copy --debug --force
+ automake --add-missing
+ sh configure
+ make


[Header Structures]
stdlib.h stdarg.h ......  sys/socket.h arpa/inet.h ......
   |        |       |        |            |          |
   |        |       |        |            |          |
   ---- trls_base.h -        -------- trls_sys.h -----
            |                             |
            |                             |
trls_queue.h trls_str.h trls_hash.h trls_rbtree.h ......
     |            |          |           |          |
     |            |          |           |          |
     (---------------- trls_config.h ---------------)
                             |
                             |
                           users

Enjoy trochilus!
