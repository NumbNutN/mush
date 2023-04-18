### 构建

```
mkdir ./build
mkdir ./bin
cd ./build
cmake ..
make

//执行程序
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



#### 文件路径

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
.../subDirectory/FileName
```

为上文路径前缀的下一级目录，mush不检查该路径是否存在



##### 组合使用

```
/bin/.././bin/cat
```

