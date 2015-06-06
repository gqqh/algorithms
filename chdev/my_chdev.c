#include <linux/init.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/cdev.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("GEHU");
 

static int count = 10;
static char *init_mesg = "hello.\n";
static char *exit_mesg = "goodbye...\n";

//字符设备号
static int major;
static int minor;
dev_t devnum;

//open
int static hello_dev_open(struct inode *inode, struct file *file)
{
	printk("file open in hello_dev_open......finished!\n");
	return 0;
}
//release
int static hello_dev_release(struct inode *inode, struct file *file)
{
	printk("file release in hello_dev_release......finished!\n");
	return 0;
}

//定义cdev结构体变量
static struct cdev hello_dev;
//定义file_operation结构体变量
static struct file_operations fops ={
	.owner = THIS_MODULE,
	.open  = hello_dev_open,
	.release = hello_dev_release,
};

//设备初始化
static int __init hello_init(void)
{
	int i;
	int ret;
	//加载模块，打印信息
	for(i = 0; i < count; i++)
		printk(init_mesg);
	//ret = register_chrdev_region(MKDEV(major,minor), 1, "hello_dev");
	//申请设备编号
	ret = alloc_chrdev_region(&devnum, 10, 1, "hello_dev");
	if(!ret){
		major = MAJOR(devnum);
		minor = MINOR(devnum);
		printk("major = %d; minor = %d\n", major, minor);
	}
	//绑定
	cdev_init(&hello_dev, &fops);
	//注册字符设备
	ret = cdev_add(&hello_dev, devnum, 1);

	return ret;
}
//卸载模块
void hello_exit(void)
{
	printk(exit_mesg);
	//注销字符设备
	cdev_del(&hello_dev);
	//释放设备号
	unregister_chrdev_region(MKDEV(major, minor),1);

	return;
}

void hello(void)
{
	printk("good mornig1\n");
}

module_param(count, int, S_IRUGO);
module_param(init_mesg, charp, S_IRUGO);
module_param(exit_mesg, charp, S_IRUGO);

EXPORT_SYMBOL_GPL(hello);
module_init(hello_init);
module_exit(hello_exit);
