/*container_of宏定义在[include/linux/kernel.h]中:
 *container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

//offsetof宏定义在[include/linux/stddef.h]中：

#define offsetof(type, member) ((size_t) &((type *)0)->member)
/*
下面用一个测试程序test.c来说明
*/
#include<stdio.h>

struct student{
    char name[20];  
    char sex;
    int age;
}stu={"zhangsan",'m', 20};

int main()
{
    struct student *stu_ptr;    //存储container_of宏的返回值
    int offset;            	//存储offsetof宏的返回值
//下面三行代码等同于 container_of（＆stu.sex,struct student, sex ）参数带入的情形
/*
    const typeof(((struct student*)0)->sex) *_mptr = &stu.sex;
//首先定义一个 _mptr指针，类型为struct student结构体中sex成员的类型
//typeof 为获取（（（struct student＊）0）->sex)的类型，此处此类型为char
//（（struct student＊）0）在offsetof处讲解

    offset = (int)(&((struct student *)0)->sex);
（（struct student＊）0）为把0地址强制转化为指向student结构体类型的指针
该指针从地址 0 开始的 21个字节用来存放name 与 sex（char name〔20〕与 char sex共21字节）
sex存放在第20个字节出（从0字节开始）
&((struct student *)0)->sex 取出sex地址(此处即为20) 并强制转化为整形
所以offset为20，后面的printf结果将证明这一点

    stu_ptr = (struct student *)((char*)_mptr - offset);
（（char＊）_mptr - offset）此处先把_mptr指针转化为字符形指针
（为什么这么做呢？ 如果_mptr为整形指针 _mptr - offset 相当于减去 sizeof（int）＊offset个字节）
减去 offset值 相当于 得到_mptr所在结构体的首地址（即stu的地址）
然后我们把 该地址 强制转化为 struct student类型即可正常使用了
*/
    printf("sizeof(struct student):%lu\n", sizeof(struct student));
    printf("offsetof stu.sex = %d\n",(int)offsetof(struct student, sex));  
    //offset = (int)(&((struct student *)0)->name);
    printf("offsetof stu.name = %d\n",(int)offsetof(struct student, name));
    printf("offsetof stu.age = %d\n",(int)offsetof(struct student, age));
    stu_ptr = container_of(&stu.sex, struct student, sex);
    printf("stu_ptr->name:%s\nstu_ptr->sex:%c\nstu_ptr->age:%d\n", 
        stu_ptr->name, stu_ptr->sex, stu_ptr->age);
    stu_ptr = container_of(&stu.age, struct student, age);
    printf("stu_ptr->name:%s\nstu_ptr->sex:%c\nstu_ptr->age:%d\n", 
        stu_ptr->name, stu_ptr->sex, stu_ptr->age);
    stu_ptr = container_of(&stu.name, struct student, name);
    printf("stu_ptr->name:%s\nstu_ptr->sex:%c\nstu_ptr->age:%d\n", 
        stu_ptr->name, stu_ptr->sex, stu_ptr->age);
    return 0;
}
