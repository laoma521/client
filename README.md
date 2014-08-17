我先描述下怎么运行。客户端，服务端都已经上传。是用QT，C++仿QQ的。具体功能，仿了哪些我会在项目文档好好描述。这里我先说下fork之后怎么运行起来。
第一，务必保证pictures文件夹包含于client文件夹。我已经上传了client，理论上./client可以直接运行。如果不可以，执行qmake client.pro.代码是跨平台的，会有一堆警告，不必理会。我当初是用VC6.0，建议还是不要使用了，我下载补丁之后，又有各种问题。总之我现在那个编译器连执行一个hello world都会出错，好像路径出问题了。直接用gcc运行就好了。可能会出现错误是ui_constant.h 6行那里有问题，把那个inputtextedit.h改成inputTextEdit.h就可以了。
如果你想重新编译整个工程，就是client.pro给移除了，没下载，执行命令qmake -project.然后会生成client.pro。然后在执行qmake client.pro。如果出现错误没有QtNetWork 或者没有sql 只是个大概的名字，我也记不太清楚了。你可以直接在client.pro添加 QT += network,QT += sql.就好了，然后执行命令make , QT会自动生成makefile文件的。如果嫌弃.o文件太多，执行命令 make clean即可。切记不要随便删除ui文件。当初在windows环境下是链接到工程里生成的。ubuntu环境下我没有试过连接。随便删除，应该会失败的。server同理。
对了，补充一点，如果觉得乱乱的，不知道从何看起，可以参照client.ts翻译文件。运行成功应该要下载g++,qt的。我之前下载过，没下载能不能编译成功，我也就不清楚了。嘿嘿。
