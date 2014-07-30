/*
 *双向链表头文件
 */

//链表头，支持双向链表
#include <stdio.h>

struct list_head{
	struct list_head * next;
	struct list_head * prev;
};

//求结构体内成员变量相对于结构体的偏移量
#define offsetof(type, member) ((size_t)&(((type *)0)->member))

//求成员变量所在结构体的指针地址。
#define container_of(ptr, type, member) ({	\
	const typeof(((type *)0)->member) *__mptr = (ptr); \
	(type *)((char *)__mptr - offsetof(type, member)); \
})

//返回包含list_head的父类型结构体地址
#define list_entry(ptr, type, member) container_of(ptr, type, member)

#define LIST_HEAD_INIT(name) { &(name), &(name) }

#define LIST_HEAD(name) struct list_head name = LIST_HEAD_INIT(name)
//链表操作
//增加一个节点到节点head后面
void list_add(struct list_head *newn, struct list_head *node){
	newn->next = node->next;
	newn->prev = node;
	node->next = newn;
	newn->next->prev = newn;
}

//增加一个节点到队列头部
void list_add_head(struct list_head *newn, struct list_head *head){
	list_add(newn, head);
}
//增加一个节点到队列尾部
void list_add_tail(struct list_head *newn, struct list_head *head){
	list_add(newn, head->prev);
}

//链表是否为空，为空返回1， 否则返回0
int isEmpty(struct list_head *head){
	return head->next == head;
}
//节点node在链表中返回1，否则返回0
int is_in_list(struct list_head *node, struct list_head *head){
	if(node == head)
		return 1;
	struct list_head *p = head->next;
	for(; p->next != head; p = p->next){
		if(p == node)
			return 1;
	}
	return 0;
}

//从链表删除一个节点
//注意该函数只会从链表中移除entry节点，并不会释放entry和其所在结构体的内存。释放内存需要在外部操作。
void list_del(struct list_head *entry, struct list_head *head){
	if(entry == NULL || ! is_in_list(entry, head)){
		perror("delete error!");
		return;
	}
	entry->next->prev = entry->prev;
	entry->prev->next = entry->next;
}

//head指针移向下一个
void head_move_next(struct list_head *head){
	head = head->next;
}
void head_move_prev(struct list_head *head){
	head = head->prev;
}
