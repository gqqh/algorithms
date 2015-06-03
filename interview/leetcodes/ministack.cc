#include <iostream>
using namespace std;

/**
 * 最小栈，如果多次pop之后最小值可能会改变哦。。。
 */
class MinStack {
public:
    size_t size = 10;
    size_t min_size = 10;
    size_t len = 0;
    size_t min_len = 0;
    int * stack = (int *)malloc(sizeof(int) * size);
    int * min_stack = (int *)malloc(sizeof(int) * min_size);

    void push(int x) {
        //push stack
        if(len >= size){
            size *= 2;
            stack = (int *)realloc(stack, sizeof(int) * size);
        }
        stack[len++] = x;
        //push min_stack
        if(min_len == 0 || x <= min_stack[min_len-1]){ //插入最小值
            if(min_len >= min_size){
                min_size += 10;
                min_stack = (int *)realloc(min_stack, sizeof(int) * min_size);
            }
            min_stack[min_len++] = x;
        }
    }

    void pop() {
        if(len > 0){
            if(min_len > 0 && stack[len-1] == min_stack[min_len-1])
                min_len--;
            len--;
        }
        //栈为空未说明
    }

    int top() {
        if(len > 0)
            return stack[len-1];
        else 
            return -1; //栈为空未说明
    }

    int getMin() {
        if(min_len > 0)
            return min_stack[min_len-1];
        //栈为空未说明
        return -1;
    }
};

int main(int argc, char const *argv[])
{
    MinStack min;
    int j = -10000;
    for(int i = 0; i < 70000; ++i){
        min.push(j + i);
        printf("%d ", j+i);
    }
    printf("\nlen:%ld, min_len:%ld\n", min.len, min.min_len);
    printf("min:%d\n", min.getMin());
    printf("top:%d\n", min.top());

    j = 10000;
    for(int i = 20000; i > 0; --i){
        min.push(j - i);
        printf("%d ", j-i);
    }
    printf("\nlen:%ld, min_len:%ld\n", min.len, min.min_len);
    printf("min:%d\n", min.getMin());
    printf("top:%d\n", min.top());

    for(int i = 0; i < 10000; i++){
        min.getMin();
        min.pop();
    }
    printf("len:%ld, min_len:%ld\n", min.len, min.min_len);
    printf("min:%d\n", min.getMin());
    printf("top:%d\n", min.top());
    

    return 0;
}