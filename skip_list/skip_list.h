/**
 * 跳表的C源代码：
 * 1、跳表是一个或许可以替代平衡树的方法，由William Pugh在1987年设计的。
 * 2、思想很简单，就是在一个有序的链表上面随机加索引，规定每个节点多可以有k个向后的不同高度的链接，高层的索引一次跨越的数据更多，
 *   第0层的forward指针就是普通单链表的next指针，如果k=0，那么就是普通的单链表了。
 *   1）查找：每次遍历的时候，从表头开始，从最高层索引开始比较，因为NIL的key值是最大值，所以可以每次比较key值，小于给定的key则继续往后，
 *           否则，向当前节点的下一层k进行比较。直到k=0，此时后一个节点就是找到的节点，再判断key是否等于给定的key。
 *   2）插入：先按照查找的方法找到插入位置，在查找的时候要同时记录，每一个查找时的拐点，记录在update[MAX_NUMBER_OF_LEVEL]中，
 *           直到0，然后随机生成一个要插入的节点及其节点的层数tmp_t，如果层数tmp_t > 最高层level，则level++，
 *           当前节点设为最高层数，同时把update[level]填入表头。update记录的是插入节点后，可能会被该节点挡到的节点，
 *           也就是update[0-tmp_t]这些节点的对应层的forward都要指向要插入的节点。同时把要插入的节点的forward[0-tmp_t]都要改成
 *           update对应节点的forward指针。
 *   3）删除：类似与插入，也是在找要删除的节点时记录拐点，然后找到要删除的节点后，更新update对应层的指针为要删的节点的对应层的forward指针。
 * 3、注意：
 *       1）每一个节点并不知道自己有几层，除表头为MAX_LEVEL层，表尾为1层，外均不知道自己有多少个forward指针。
 *       2）表头和表尾均为为空节点，表头key和value都是最小值，表尾key和value都是最大值。
 *       3）要注意插入一个节点可能总的高度增加了，删除一个节点可能总的高度减少了
 *       4）     
 */

#include <stdio.h>
#include <stdlib.h>

#define INT_MAX 0x7fffffff
#define INT_MIN 0x80000000
#define false 0
#define true 1
typedef char boolean;

#define MAX_NUMBER_OF_LEVELS 16
#define MAX_LEVEL (MAX_NUMBER_OF_LEVELS - 1)

//分配节点
#define new_node_of_level(n) (struct node_struct *)malloc(sizeof(struct node_struct) + (n) * sizeof(struct node_struct **))

//key和value的类型
typedef int key_t;
typedef int value_t;

//节点指针及其数据结构
typedef struct node_struct * node; 
struct node_struct{
    key_t key;      //key
    value_t value;  //value
    node forward[1];//默认只有一个forward指针
};

//跳表指针及其数据结构
typedef struct list_struct * list;
struct list_struct{
   int level; //结构中最大的层数+1
   int len;   //元素个数
   struct node_struct * header;   //表头
 };

//代表空节点，其层数为0，key值和value值均为最大值，forward为NULL
node NIL;
/**初始化跳表lst，初始化表头节点为最大层数，且所有forward都为空，返回跳表指针
 */
list new_list(){
  list lst; //跳表指针
  lst = (list)malloc(sizeof(struct list_struct));
  lst->level = 0; //该链表的层数0，从0开始
  lst->len = 0;
    
  //初始化表尾节点
  NIL = new_node_of_level(0); 
  NIL->key = INT_MAX;
  NIL->value = INT_MAX;
  NIL->forward[0] = NULL;

  //初始化表头节点
  int i;
  //跳表表头节点，初始化为最大的层数，每一个forward指针都为空
  lst->header = new_node_of_level(MAX_LEVEL); //注意表头是一个空表头，层数为1+MAX_LEVEL
  lst->header->key = INT_MIN;
  lst->header->value = INT_MIN;
  for(i = 0; i < MAX_NUMBER_OF_LEVELS; i++)
    lst->header->forward[i] = NIL;
  
  return lst;
}; 

/**释放跳表空间，使用forward[0]进行遍历，依次释放
 */
void free_list(list lst){
  node p, q;  //p为表头，q为临时指针
  p = lst->header;
  do{
    q = p->forward[0];
    free(p);
    p = q;
  }while(p != NIL);

  free(lst);
};

/**求一个插入节点的随机高度，使用的是random函数生成的对最大层数+1取余
 * @return 节点的随机值高度
 */
int random_level(){
  int level;
  level = random() % MAX_NUMBER_OF_LEVELS; //使用random()也本身就有挺好的随机性

  return level;
};

/**插入键值对，首先找到要插入的位置，在找位置的同时拐点的位置
 *     然后是插入节点，注意如果链表中已经有了这个值，那么更新value值，并返回false，否则插入并返回true
 * @param  lst   skip list
 * @param  key   插入节点key值
 * @param  value 插入的节点的value值
 * @return       成功返回1，否则返回0
 */
boolean insert(list lst, key_t key, value_t value){
  int k;
  node update[MAX_NUMBER_OF_LEVELS]; //update数组
  node p,q;

  //从表头的最高层数往后或者往下遍历
  p = lst->header;
  k = lst->level;
  for(; k >=0; --k){
    while(q = p->forward[k], q->key < key){
      p = q;
    }
    update[k] = p; //记录从最高层到第0层的所有拐点指针
  }
  
  //key已经存在，则更新value并返回false
  if(q->key == key){
    q->value = value;
    return false;
  }
  // 找到了插入位置，随机生成一个层数，并且进行插入及调整
  k = random_level();
  //随机生成的层数高于了最高层数，要把最高层数+1，同时把最高层的拐点填上表头
  if(k > lst->level){ 
    lst->level ++; 
		k = lst->level; 
		update[k] = lst->header;
	};
	//插入值节点，更新挡住的指针，也就是记录的update的拐点指针中<=k层的
  q = new_node_of_level(k);
  lst->len ++;
  q->key = key;
  q->value = value;
  //p用来遍历update数组从q挡住的第一个节点往后遍历直到q前一个节点，k为p能挡住的最高层数
  for(; k >= 0; --k){
		p = update[k]; 
		q->forward[k] = p->forward[k]; 
		p->forward[k] = q;    
  }

  return true;
}

/**删除键值对，根据给定的键值删除元素，也是首先找到要删除的元素，同时要记录所有拐点，便于更新forward指针。
 *      如果key值不存在，则返回false，否则删除并返回true。
 * @param  lst skip list
 * @param  key 被删除节点的key值
 * @return     成功则返回1，失败返回0
 */
boolean delete(list lst, key_t key){
  int k,m;
  node update[MAX_NUMBER_OF_LEVELS]; //记录找到该节点路过的所有拐点
  node p,q;

  //找要删的节点，同时记录拐点
  p = lst->header;
  k = lst->level;
  m = lst->level; //备份k
  for(; k >= 0; --k){
    while(q = p->forward[k], q->key < key){
      p = q;
    }
    update[k] = p; //记录所有拐点
  }
  //找到节点判断是否是key值，然后依次更新前后的forward指针并释放空间
  if(q->key == key){
    k = 0;
    p = update[k];
    while(k <= m && p->forward[k] == q){
      p->forward[k] = q->forward[k];
      k++;
      p = update[k];
    }
		free(q);
		
    //有可能删了一个节点之后，总的最大层数减少了
   	while( lst->header->forward[m] == NIL && m > 0 )
	     m--;
		lst->level = m;
    lst->len --;
    return true;
  }else{ //没有key
    return false;
  }//end if-else 
}

/**跳表查询，根据key值，如果找到则返回true和value，否则返回true
 * @param  lst          跳表指针
 * @param  key          要找的键值
 * @param  value_p      返回的value值
 * @return              找到返回true，否则返回false
 */
boolean search(list lst, key_t key, value_t *value_p){
  int k;
  node p,q;
  *value_p = INT_MAX; //找不到时的返回值
  p = lst->header;
  k = lst->level;
  //从表头的最高层往下遍历
  for(; k >= 0; --k){
    while(q = p->forward[k], q->key < key){
      p = q;
    }
  }
  //找到之后，判断是否是要找的值
  if(q->key != key) 
    return false;
  
  *value_p = q->value;
  return true;
};
/**打印显示所有元素。
 * @param lst 跳表指针
 */
void printer(list lst){
  if(lst == NULL) 
    return;
  node p = lst->header; //表头是空的
  int len = lst->len;
  printf("There are %d members in the list:\n", len);
  while(p = p->forward[0], len-- > 0){
    printf("(#%d, %d)\n", p->key, p->value);
  }
}
