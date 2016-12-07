#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIDTH 256           //节点可以是所有ASCII码
#define MAX_WORD_LEN 128        //一个单词最大的长度

struct trie_node_st{
        int count; //用来标记该孩子节点是否可以形成一个单词，如果可以则非0；标记单词出现的次数
        int pass;  //用来记录该节点有多少个子孙，pass为0则为叶子节点，pass的个数>=child元素的个数
        struct trie_node_st *child[MAX_WIDTH];  //该节点的孩子指针，如果该节点的'a'孩子存在，则child[97]非空。
};
struct trie_node_st tree = {-1, 0, {NULL}};

int insert_node(struct trie_node_st *root, const char *str);  //插入节点
int lookup_node(struct trie_node_st *root, const char *str);  //查询节点
int delete_node(struct trie_node_st *root, const char *str);  //删除节点
int printer(struct trie_node_st *root);  //打印trie树

/*
 *插入节点：
  从首字母往后插入，当前节点有则该孩子节点则pass加1，继续下一趟遍历，如果单词结束则该节点的count加1
  成功则返回1，否则返回0
 */
int insert_node(struct trie_node_st *root, const char *str){
        struct trie_node_st * curr = root;
        int i;
        if(str[0] == '\0'){     //empty str
                return 0;
        }

        for(i = 0; ; i++){ //遍历str
                if(curr->child[ str[i] ] == NULL){      //letter str[i]不存在，则创建
                        struct trie_node_st *newnode = (struct trie_node_st *)malloc(sizeof(struct trie_node_st));
                        newnode->count = 0;
                        newnode->pass = 0;
                        newnode->child = ;
                        curr->child[ str[i] ] = newnode;        //当前节点指向新节点
                }
                curr = curr->child[str[i]];
                if(str[i+1] == '\0'){   //当前字母为最后一个
                        curr->count ++;
                        break;
                }else{          //不是最后一个节点则pass++
                        curr->pass ++;
                }
        }

        return 1;
}

/*
 *查询节点是否存在，存在则返回1，否则返回0
 *从根开始遍历，如果字母不在树中则返回0；如果在树中且str比较结束且count>0则返回1，在树中且比较没结束继续比较
 */
int lookup_node(struct trie_node_st *root, const char *str){
        struct trie_node_st *curr = root;
        int i;
        if(str[0] == '\0'){     //空串算子串
                return 1;
        }
        for(i = 0; ; i++){
                if(curr->child[ str[i] ] == NULL){      //字母str[i]不在树中
                        break;
                }

                if(str[i+1] == '\0'){   //字符串比较结束
                        if(curr->count > 0)     //字符串在树中，且末位字母的count>0才能表明在树中
                                return 1;
                        else
                                break;
                }else{
                        curr = curr->child[ str[i] ];
                }
        }
        return 0;
}

/*
 *删除节点与查询类似， 先查找一遍，如果不在树中，则返回0；如果树中有多个此节点时，只是减少一次。
        否则，从根节点遍历，如果出现某个字母的pass > 1,则--，否则从此节点往后依次删除并free.
 *如果找不到则返回0；否则，返回1
 */
int delete_node(struct trie_node_st *root, const char *str){
        if(lookup_node(root, str) == 0){ //不存在
                return 0;
        }
        struct trie_node_st *curr = root, *tmp;
        int i;
        for(i = 0; ; i++){
                if(curr->child[ str[i] ]->pass > 1 && str[i+1] != '\0'){
                        curr->child[ str[i] ]->pass --;
                        curr = curr->child[ str[i] ];
                }else if(curr->child[ str[i] ]->pass > 1){  //字符串已处理完，count--
                        curr->child[ str[i] ]->count -- ;
                        break;
                }else{
                    
                    
                }
        }
        return 1;
}

int main(void)
{
        char string[MAX_WORD_LEN];
        //test insert_node
        /*
        printf("input a letter:");
        scanf("%s", string);
        while(strcmp(string, "") != 0){
                if(insert_node(tree, string) == 0){
                        printf("insert error!");
                }
                printf("input a letter:");
                scanf("%s", string);
        }
        printf("these words in the trie tree:\n");
        printer();
        */
        //test lookup_node
        /*
        printf("lookup word:");
        scanf("%s", string);
        while(strcmp(string, "") != 0){
                int t = lookup_node(tree, string);
                if(t == 0){
                        printf("%s not exit...", string);
                }else{
                        printf("%s find %d times.", string, t);
                }
                printf("lookup word:");
                scanf("%s", string);
        }
        printf("these words in the trie tree:\n");
        printer();
        */
        //test delete_node
        /*printf("delete word:");
        scanf("%s", string);
        while(strcmp(string, "") != 0){
                if(delete_node(tree, string) == 0){
                        printf("%s not exit...", string);
                }else{
                        printf("%s delete success...", string);
                }
                
                printf("these words in the trie tree:\n");
                printer();
                
                printf("delete word:");
                scanf("%s", string);
        }*/
        printf("exit");
}
