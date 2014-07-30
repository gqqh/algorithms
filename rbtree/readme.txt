红黑树的实现与测试：
1) 文件rbtree.h是红黑树的定义与实现的文件
其中节点格式为：
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
文件中包含了函数：
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

2)文件rbtree-test.h是测试程序
先随即生成100个节点，然后插入并查询，再随即删除30个节点。
