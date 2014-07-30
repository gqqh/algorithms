container_of是一个宏，定义在[kernel.h]中：
/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.结构体的成员变量的指针。
 * @type:	the type of the container struct this is embedded in.结构体类型。
 * @member:	the name of the member within the struct.ptr对应的成员变量在结构体中的名称。
 *
 */
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})

功能是：根据ptr和member返回该ptr所在的结构体的指针地址。
详解：
1）const typeof( ((type *)0)->member ) *__mptr = (ptr);	
typeof是gcc的C语言扩展保留字，用于变量声明；
  (type *)0 是把0强制转换成type型的指针；
  ((type *)0)->member 指向type的成员变量
  typeof( ((type *)0)->member ) 是声明这种变量
  const typeof(((type *)0)->member) *__mptr = (ptr);是声明一个常量指针__mptr，并且初始化为ptr.
2)(type *)( (char *)__mptr - offsetof(type,member) );
  offsetof是一个宏定义在[stddef.h]中：
    #define offsetof(type, member) ((size_t) &((type *)0)->member) //就是求成员变量相对于结构体的偏移量
  (char *)__mptr - offsetof(type,member) 就是把指向该成员变量的指针向前后退该成员变量的偏移量，就
  可以指向该结构体的起始地址，然后再强制转换一下，就ok了。
  

