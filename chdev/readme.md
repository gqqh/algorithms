```
http://blog.sina.com.cn/s/blog_69ef92d60100l8ab.html
编写步骤：
 1. 申请设备编号
 2. 定义struct file_operations结构体
 3. 定义struct cdev结构体
 4. 绑定cdev、fie_operation和设备号，注册字符设备
 5. 注销字符设备

编译安装模块：
 1. [Makefile](Makefile)
 2. make
 3. sudo insmod hello.ko
 4. dmesg
 5. lsmod | grep hello

测试驱动模块：
  创建结点：mknod  /dev/gehu c 250 10 [250,10是根据上面dmesg看到的]
  执行程序：./main
  运行结果如下：
  file /dev/hello is opening……successfully!
  Its fd is 3

  执行dmesg命令,显示：
  file open in hello_dev_open……finished!
```
