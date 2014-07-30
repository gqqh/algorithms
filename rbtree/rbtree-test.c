#include "rbtree.h" 
#include <time.h>
//#include <math.h>
  
//八、测试用例  
//主函数
//层序遍历打印树，空节点为-1，颜色为黑：格式为node->key(node->color)
int pow2(int n){
    int ret = 1;
    while(n-- > 0){
        ret *= 2;
    }
    return ret;
}
void print(rb_node_t* root){
    rb_node_t* queue[100];
    rb_node_t* node;
    int head, tail;
    head = 0; 
    tail = 0;
    int depth = 1, count = 0;
    queue[tail] = root;
    tail = (tail ++) % 100;
    while(head != tail){    //队列不为空就输出
        node = queue[head];
        head = (head ++) % 100;
        if(node != NULL){
            queue[tail] = node->left;
            tail = (tail ++) % 100;
            queue[tail] = node->right;
            tail = (tail ++) % 100;
            printf("%d(%c) ", node->key, node->color ? 'B' : 'R');
            count ++;
            if(count == pow2(depth) - 1){
                depth++;
                printf("\n");
            }
        }else{
            printf("%d(%c) ", -1, 'B');
            count ++;
            if(count == pow2(depth) - 1){
                depth++;
                printf("\n");
            }
        }
    }
}

int main()  
{  
    int i, count = 100;  
    key_t key;  
    rb_node_t* root = NULL, *node = NULL;
    int test[100] = {0};
      
    srand(time(NULL));
    //测试插入和查找  
    for(i = 1; i < count; ++i){  
        key = rand() % count;  
        test[i] = key;
        if((root = rb_insert(key, i, root)) != NULL){  
            printf("[i = %d] insert key %d success!\n", i, key);  
        }else{  
            printf("[i = %d] insert key %d error!\n", i, key);  
            exit(-1);  
        }  
    
        if((node = rb_search(key, root)) != NULL){  
            printf("[i = %d] search key %d success!\n", i, node->key);  
        }else{  
            printf("[i = %d] search key %d error!\n", i, key);  
            exit(-1);  
        }
    } 
    //测试删除
    for(i = 0; i < 30; i++){ //删除20个数
        int t = rand() % count;  
        while(test[t] == -1){
                t = rand() % count;
        } 
        printf("\n key=%d\n", test[t]);

        if((root = rb_erase(test[t], root)) != NULL){
            print(root); 
            printf("\n"); 
            printf("[i = %d] erase key %d success\n", i, test[t]);  
        }else{
            print(root); 
            printf("\n"); 
            printf("[i = %d] erase key %d error\n", i, test[i]);  
        }
        test[t] = -1;
    }
    printf("rbtree as fallow:\n");
    print(root);
    printf("\n");
    
    return 0;  
}  
