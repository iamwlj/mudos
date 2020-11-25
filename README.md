1、此版本来源：http://www.revivalworld.org/static/downloads/driver/MudOS/v22.2b14.tar.gz  
我没有改什么具体逻辑和功能，只是做了几件事：  
修改为VS2010/2019本地化，傻瓜式一键编译  
增加自动测试功能  
增加64位大数据支持，编译x64版本即可开启  
增加数据库支持，兼容32位MySQL 5、32位MySQL 8、32位SQLite 3、64位MySQL 5、64位MySQL 8、64位SQLite 3  
增加部分ntos的efun，可以直接启动NT3的lib  
  
2、进入根目录，双击Mudos.sln，选择VS2019/2010打开，如下图（参考“不看说明别怪我.doc”）：  

四个项目说明如下：  
bison--这个是yacc的本地编译版本，不用管它，编译mudos的时候会自动依赖的。  
editsource--用于生成一些编译需要的文件，不用管它，编译mudos的时候会自动依赖的。  
mudos--主项目，点击鼠标右键，点击重新生成，即可全自动编译生成mudos.exe。  
testmud--测试项目，点击鼠标右键，点击重新生成，会重新编译mudos.exe，并且自动使用最新生成的mudos.exe来启动xyj 4.50的lib  
https://gitee.com/andersgong/xyj450  
这个lib也是我用来测试这个版本mudos的，目前基本上运行正常，报错都解决了，还加入了rzr自动测试，以及db指令测试数据库，供大家参考。具体可以在项目上点击鼠标右键，选择属性，进入“调试”标签页查看。  
  
3、鼠标右键mudos，重新生成，如下图表示编译成功：  
  
编译warning我已经全部解决了。  
  
4、mudos项目编译完成后，可以直接按F5看看效果，这个版本自带了一个testsuite最小测试lib，我已经设置好，mudos项目编译完成后，会自动将mudos.exe复制到testsuite下面，config文件在testsuite\etc\config.test，端口5555，第一次运行mudos.exe之前，需要设置管理员权限和xp模式。如下图：  
  
5、按下F5后mudos正常启动，zmud连接5555端口，如下图：  
  
6、数据库方面的测试方法，根据你options.h里的设置，首先开启MySQL 5或者8的服务，然后用客户端连接，创建用户dbuser，密码dbpassword，如果你有自己的用户密码，可以修改对应的文件：  
testsuite\command\db.c  
testsuite\single\master.c的valid_database函数  
  
7、手动创建一个名为mudos的数据库  
  
8、回到zmud，分别执行三条命令：  
db 0  
  
此时会在mudos库里创建数据表users  
  
db 1  
会在users表里插入数据  
  
  
db 2  
自动查询users表里的name字段  
  
关于数据库选项的配置，请看options.h  
  
以及PACKAGES\db.h  
  
50表示MySQL 5，80表示MySQL 8，如果直接使用sqlite3则无此烦恼，会自动在lib根目录生成mudos.db数据库文件（参考/cmds/adm/db.c或者testsuite\command\db.c指令），用客户端打开就能看到数据了。  
  
补充说明：如果需要使用数据库功能的话，请将libcrypto-1_1.dll、libssl-1_1.dll、sqlite3.dll三个文件和mudos.exe放在一起。32位和64位版本的dll分别放在MUDOS\testsuite\win32和MUDOS\testsuite\x64下面。  
  
再补充说明：此版本同时兼容32位MySQL 5、32位MySQL 8、32位SQLite 3、64位MySQL 5、64位MySQL 
8、64位SQLite 3，代码内部已经处理好了所有的依赖关系。  
  
9、支持64位大数据，如下图，x64版本默认开启大数据支持，轻松超过21亿上限。  
  
10、最新支持NT3的lib，https://gitee.com/andersgong/nitan3  
增加了部分ntos的efun，开关如下：  
  
源代码在mudos\PACKAGES\ntos.c  
  
11、如果想要修改编译参数，自己改options.h。Enjoy it!