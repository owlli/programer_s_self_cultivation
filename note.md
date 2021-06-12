## 备注

本文中所有"段"指elf文件中的section.elf中的segment在本文皆以英文表示,没有翻译为中文



## binutils

### size

查看elf文件中text,data,bss段的长度

### objdump

> -h	查看目标文件中主要段的基本信息
>
> -s	将所有段中的内容以十六进制和字符形式打印出来
>
> -d	将所有包含指令的段反汇编
>
> -t	显示文件中的符号表
>
> -r	查看elf文件中的重定位表
>
> -R	查看动态库中需要重定位的信息
>
> -T	查看动态库中动态符号表

### readelf

> -h	查看elf文件头信息
>
> -S	显示elf文件中所有段的信息
>
> -s	显示elf文件中的符号表
>
> -l	显示elf文件中的segment信息
>
> -d	显示.dynamic段中的内容
>
> -r	显示文件中重定位表

### nm

查看符号表(只能显示部分,没有objdump -t显示的全)

### ar

> -t	查看静态库包含的目标文件
>
> -x	将静态库中所有目标文件解压到当前目录

### strip

清除elf文件中所有符号(包括调试符号)信息

### addr2line



## gcc选项

以源码hello.c为例来使用gcc

> -E	仅做预处理
>
> ```shell
> gcc -E hello.c -o hello.i
> ```
>
> 也可用cpp预处理工具实现
>
> ```shell
> cpp hello.c > hello.i
> ```
>
> -S	仅编译产生汇编代码
>
> ```shell
> gcc -S hello.i -o hello.s
> #会自动预处理源码
> ```
>
> -c	仅汇编产生目标文件
>
> ```shell
> gcc -c hello.c -o hello.o
> #会自动预处理,编译源码
> ```
>
> 也可用as汇编器实现
>
> ```shell
> as hello.s -o hello.o
> ```
>
> -e 函数名	用于指定入口函数(默认为_start)
>
> -Ipath	指定头文件的目录
>
> -Lpath	指定库的搜索目录
>
> -lname	指定库的路径,库前缀lib,后缀.so,.a不用写
>
> -static	使用静态链接文件
>
> -Bdynamic	编译为动态共享文件(默认方式)
>
> --verbose	将编译链接过程的中间步骤打印出来
>
> -fno-common	把所有未初始化的全局变量不以COMMON块的形式处理
>
> -ffunction-sections	将每个函数分别保存到独立段中
>
> -fdata-sections	将每个变量分别保存到独立段中
>
> -fno-builtin	禁止使用gcc编译器的内置函数优化(比如gcc默认会将只使用一个字符串参数的printf替换成puts)
>
> -fno-stack-protector	编译时取消默认的栈检查(gcc7.3默认使用栈检查,在没有加入某些gcc的库的情况下使用手动链接,会提示栈检查的函数没定义)
>
> -m32	64位系统下强制使用32位abi编译
>
> -shared	产生共享对象
>
> -fPIC	产生地址无关代码(在gcc7.3中貌似是默认的)
>
> -Wl,-soname,my_soname	指定输出共享库的SO-NAME为my_soname
>
> -Wl,-rpath my_path	指定链接产生的目标程序的共享库查找路径
>
> -Wl,-export-dynamec	产生可执行文件时,将所有全局符号导出到动态符号表
>
> -Wl,-s	产生输出文件时消除所有符号信息
>
> -Wl,-S	产生输出文件时消除调试符号信息
>
> -fomit-frame-pointer	取消帧指针ebp
>
> -nostartfiles	在链接时不使用标准的启动文件(crt1.o,crti.o,crtn.o)
>
> -nostdlib	在链接时不使用标准的启动文件和库,它包含了-nostartfiles这个参数



### ld

链接器

> -e foo	将foo作为程序入口,ld链接器的默认程序入口为_start
>
> -o ab	将链接后的输出文件命名为ab
>
> --verbose	打印链接时的详细信息
>
> -T link.lds	指定链接脚本文件link.lds
>
> -m elf_i386	64位系统下强制链接为32位应用
>
> -soname	my_soname	指定输出共享库的SO-NAME为my_soname
>
> -rpath my_path	指定链接产生的目标程序的共享库查找路径
>
> -export-dynamic	产生可执行文件时,将所有全局符号导出到动态符号表
>
> -s	产生输出文件时消除所有符号信息
>
> -S	产生输出文件时消除调试符号信息



### \_\_attribute\_\_

将变量或函数存在指定段

```c
__attribute__((section("FOO"))) int global = 42;
__attribute__((section("BAR"))) void foo()
{
    
}
```

将强符号定义为弱符号

```c
__attribute__((weak)) int weak2 = 2;
```

声明对外部函数的引用为弱引用

```c
__attribute__((weakref)) void foo();
```

声明一个未初始化的全局变量不以COMMON块的形式处理

```c
int global __attribute__((nocommon));
```

指定共享库的构造函数,使其在该共享库加载时执行,如果是使用dlopen()打开共享库,构造函数会在dlopen返回前被执行

```c
void __attribute__((constructor)) init_function(void);
void __attribute__((constructor(5))) init_function(void);//如果有多个构造函数,可以指定函数优先级,数字越小优先级越高,越先执行
```

指定共享库的析构函数,使其在main函数执行完毕或程序exit时执行,如果该共享库是运行时加载的,使用dlclose()卸载共享库时,析构函数会在dlclose返回前被执行

```c
void __attribute__((destructor)) fini_function(void);
void __attribute__((destructor(10))) fini_function(void);//如果有多个析构函数,可以指定函数优先级,数字越大优先级越高,越先执行
```

使用cdecl函数调用惯例,貌似只能用在编译32位应用时

```c
void __attribute__((cdecl)) test();
```

让函数只从栈上取参数,不从寄存器上取参

```c
//大多用在系统调用中,一般使用宏表示
#define asmlinkage __attribute__((regparm(0)))
asmlinkage pid_t sys_fork(void);
```



## 其他和二进制文件相关工具

### ldd

查看二进制文件依赖于哪些共享库

### ldconfig

为共享库目录下的各个共享库创建,删除或更新相应的SO-NAME,把这些共享库的SO-NAME信息手机起来,集中存放到共享库缓存文件/etc/ld.so.cache中



















