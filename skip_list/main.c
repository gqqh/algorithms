//测试skip list
#include "skip_list.h"

#define sample_size 60000

//测试
int main() {
  list lst;
  int i,k;
  key_t keys[sample_size];
  value_t values[sample_size];
  value_t v;
  lst = new_list();

  for(k = 0; k < sample_size; k++){
    keys[k] = random();
    values[k] = keys[k];
    if(!insert(lst, keys[k], values[k])){
     	printf("insert (#%d, %d) error\n", keys[k], values[k]);
    }
  };
  printf("insert %d mumbers over...\n", sample_size);
  printer(lst);

  for(i = 0; i < 4; i++){
  	printf("test round %d:\n", i);
  	for(k = 0; k < sample_size; k++){
  		if(!search(lst, keys[k], &v))
  			printf("error in search #%d,#%d\n", keys[k], values[k]);
	    if(v != values[k])
	    	printf("search returned wrong value\n");
	    else 
	    	printf("search (#%d, %d) ok\n", keys[k], v);
    };

    for(k = 0; k < sample_size; k++){
    	if(!delete(lst, keys[k]))
    		printf("error in delete\n");
    	else
    		printf("delete (#%d, %d) ok\n", keys[k], values[k]);
      values[k] = random();
 	    if(!insert(lst, keys[k], values[k])){
 	    	printf("insert (#%d, %d) error\n", keys[k], values[k]);
 	    }else{
 	    	printf("insert (#%d, %d) ok\n", keys[k], values[k]);
 	    }
    };
    
  	printer(lst);
  };

  free_list(lst);

  return 0;
};
