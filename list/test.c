//test.c 测试list.h
#include "list.h"
#include <stdlib.h>

typedef struct {
	char *name; //name
	char sex;	//sex 'm', 'f'
	int age;
	struct list_head list;
} student;

int main(){
	LIST_HEAD(students); 	//初始化一个队列
	student *studentA;
	studentA = malloc(sizeof(student));
	studentA->name = "gehu";
	studentA->sex = 'm';
	studentA->age = 25;
	list_add_head(&studentA->list, &students);
	
	student *B;
	B = malloc(sizeof(student));
	B->name = "gehu1";
	B->sex = 'm';
	B->age = 23;
	list_add_head(&B->list, &students);

	student *C;
	C = malloc(sizeof(student));
	C->name = "gehu2";
	C->sex = 'm';
	C->age = 23;
	list_add_tail(&C->list, &students);

	struct list_head *p = students.next;
	student *s;
	s = container_of(p, student, list);
	printf("name:%s\n sex:%c\n age:%d\n", s->name, s->sex, s->age);
	for(p = p->next; p != &students; p = p->next){
		s = container_of(p, student, list);
		printf("name:%s\n sex:%c\n age:%d\n", s->name, s->sex, s->age);
	}
	return 0;
}