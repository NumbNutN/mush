## MUSH - Mini Micro Shell

Mush是一个简陋的shell，其需要基于别的shell运行
Mush用于应付一次大学操作系统课程作业

### 依赖

mush从源代码构建依赖两个语法处理工具和项目构建工具

```
flex
bison
cmake
make
```

请从官网构建源代码或获取您的Linux发行版提供的二进制分发文件



### 构建

```
mkdir ./build
mkdir ./bin
cd ./build
cmake ..
make
```



### 执行程序

```
./bin/mush
```



### 支持的指令

##### 执行ELF文件

```
ExecutableFile [args]
```

进程的标准输入将被设置为"/dev/stdin"

标准输出将被设置为"/dev/stdout"



##### 输入重定向

```
ExecutableFile [args] < File
```

这会将进程的文件描述符0替换为File



##### 输出重定向

```
ExecutableFile [args] > File
```

这会将进程的文件描述符1替换为File



##### 管道

```
ExecutableFile1 [args] | ExecutableFile2 [args]
```

这会在/tmp创建一个命名管道 mush_pipe

并将其作为前者的标准输出和后者的标准输入



### 文件路径

##### 绝对路径

```
/bin/xx
```

从'/'根目录开始的绝对路径



##### 当前目录

```
./FileName
```

为mush工作路径或上文路径前缀的当前目录，当前工作路径会提示在mush中



##### 上一级目录

```
../FileName
```

为mush工作路径或上文路径前缀的上一级目录，当前工作路径会提示在mush中



##### 子目录

```
[suffix]/subDirectory/FileName
```

为上文路径前缀的下一级目录，mush不检查该路径是否存在



##### 组合使用

```
/bin/.././bin/cat
```



##### 路径缺省情况

对文件路径的缺省是允许的，如调用：

```
ls
```

不论在cd指令、执行ELF文件还是读写重定向至另一个文本文件，缺省视为其处于默认的bin目录/bin

这与bash的行为不太一致，如果想表示当前路径，请使用

```
./ELFFile > ./output
```



### 工作路径

当前工作路径cwd会标注在mush中

```
(mush)[CWD]
```

该路径决定了装载并运行的所有子进程的工作路径

您可以通过mush内置的cd指令随时切换到其他路径

```
cd NEWPATH
```

### 项目云端仓库
https://github.com/NumbNutN/mush