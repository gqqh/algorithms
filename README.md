###Algorithms study
##1、[container_of](container_of/)  
`container_of`是一个宏，定义在[`kernel.h`]中：

```C
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
```

功能是：根据ptr和member返回该ptr所在的结构体的指针地址。
详解：
* `const typeof( ((type *)0)->member ) *__mptr = (ptr);` typeof是gcc的C语言扩展保留字，用于变量声明；  
   `(type *)0` 是把0强制转换成type型的指针;   
   `((type *)0)->member` 指向type的成员变量;   
   `typeof( ((type *)0)->member )` 是声明这种变量;     
   `const typeof(((type *)0)->member) *__mptr = (ptr);`是声明一个常量指针__mptr，并且初始化为ptr.  
* `(type *)( (char *)__mptr - offsetof(type,member) )`;   
  `offsetof`是一个宏定义在[stddef.h]中：  
    `#define offsetof(type, member) ((size_t) &((type *)0)->member)` //就是求成员变量相对于结构体的偏移量  
  `(char *)__mptr - offsetof(type,member)` 就是把指向该成员变量的指针向前后退该成员变量的偏移量，就可以指向该结构体的起始地址，然后再强制转换一下，就ok了。
  
##2、[list](list/)
使用container_of实现一个双向循环队列。

##3、[rbtree](rbtree/)
 红黑树的实现与测试：
+ 1)文件rbtree.h是红黑树的定义与实现的文件
其中节点格式为：

```C
typedef int key_t;      //key类型
typedef int data_t;     //数据类型
typedef enum color_t{   //rb数color
    RED = 0,
    BLACK = 1
} color_t;

//节点定义
typedef struct rb_node_t{
    struct rb_node_t *left, *right, *parent; //三个指针
    key_t key;      //key
    data_t data;    //value
    color_t color;  //locor
} rb_node_t;
//文件中包含了函数：
//函数声明：
static rb_node_t* rb_new_node(key_t key, data_t data);                 //新建节点
static rb_node_t* rb_rotate_left(rb_node_t* node, rb_node_t* root);    //左旋
static rb_node_t* rb_rotate_right(rb_node_t* node, rb_node_t* root);   //右旋
static rb_node_t* rb_search_parent(key_t key, rb_node_t* root, rb_node_t **parent);    //协助搜索节点
rb_node_t* rb_search(key_t key, rb_node_t* root);               //搜索节点
rb_node_t* rb_insert(key_t key, data_t data, rb_node_t* root);  //插入节点
static rb_node_t* rb_insert_fixup(rb_node_t *node, rb_node_t *root);   //插入节点后修正
rb_node_t* rb_erase(key_t key, rb_node_t *root);                //删除节点
static rb_node_t* rb_erase_fixup(rb_node_t *child, rb_node_t *parent, rb_node_t *root);//删除节点后修正
```

+ 2)文件rbtree-test.h是测试程序
先随即生成100个节点，然后插入并查询，再随即删除30个节点。

##4、[字符串匹配](substring_search/) [*more*](http://www-igm.univ-mlv.fr/~lecroq/string/node1.html)
* 蛮力方法 [brute_force.c](substring_search/brute_force.c) [*参考*](http://www-igm.univ-mlv.fr/~lecroq/string/node3.html#SECTION0030)
* kmp算法 [kmpsearch.c](substring_search/kmpsearch.c) [*参考*](http://www-igm.univ-mlv.fr/~lecroq/string/node8.html#SECTION0080)
* sunday算法 [sunday_search.c](substring_search/sunday_search.c)
