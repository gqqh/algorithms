//rbtree.h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


//新建节点时，只初始化key值和data值
rb_node_t* rb_new_node(key_t key, data_t data){
    rb_node_t *node = (rb_node_t *)malloc(sizeof(rb_node_t));
    if(!node){
        perror("malloc error!\n");
        exit(-1);
    }
    node->key = key;
    node->data = data;
    //另外四个参数，先不固定。

    return node;
}

//一、左旋代码分析  
/*----------------------------------------------------------- 
|--->(X)        左旋          (Y) 
|   /   \     =======>       /   \ 
|  a    (Y)            --->(X)    c
|      /   \              /   \     
|     b     c  a         a     b          --->表示当前节点
|
|
| LEFT-ROTATE(T, x)
| 1  y ← right[x]            //Set y.
| 2  right[x] ← left[y]      //开始变化，y的左孩子成为x的右孩子
| 3  if left[y] != nil[T]
| 4  then p[left[y]] <- x                
| 5  p[y] <- p[x]                       //y成为x的父结点
| 6  if p[x] = nil[T]
| 7     then root[T] <- y
| 8     else if x = left[p[x]]
| 9             then left[p[x]] ← y
|10             else right[p[x]] ← y
|11  left[y] ← x             //x成为y的左孩子
|12  p[x] ← y
|左旋和右旋都不改变当前节点
-----------------------------------------------------------*/  
rb_node_t* rb_rotate_left(rb_node_t* node, rb_node_t* root){  
    rb_node_t *y = node->right;
    //(X)--b
    if((node->right = y->left) != NULL){
        y->left->parent = node;
    }
    //parent[y] = parent[x]
    if((y->parent = node->parent) != NULL){
        if(node == node->parent->right){
            node->parent->right = y;
        }else{
            node->parent->left = y;
        }
    }else{
        root = y;
    }
    //(Y)--(X)
    y->left = node;
    node->parent = y;

    return root;
}  
  
  
//二、右旋   
/*----------------------------------------------------------- 
|    (X)        右旋       --->(Y) 
|   /   \     <=======       /   \ 
|  a -->(Y)                (X)    c
|      /   \              /   \     
|     b     c  a         a     b          --->表示当前节点
|
|
| RIGHT-ROTATE(T, y)
| 1  x ← left[y]            //Set x.
| 2  left[y] ← right[x]      //开始变化，x的右孩子成为y的左孩子
| 3  if right[x] != nil[T]
| 4  then p[right[x]] <- y                
| 5  p[x] <- p[y]                       //x成为y的父结点
| 6  if p[x] = nil[T]
| 7     then root[T] <- x
| 8     else if y = left[p[y]]
| 9             then left[p[y]] ← x
|10             else right[p[y]] ← x
|11  right[x] ← y             //x成为y的左孩子
|12  p[y] ← x
-----------------------------------------------------------*/ 
rb_node_t* rb_rotate_right(rb_node_t* node, rb_node_t* root){  
    rb_node_t* x = node->left;  

    //(Y)---b
    if((node->left = x->right) != NULL){
        x->right->parent = node;
    }
    //parent[x] = parent[y]
    if((x->parent = node->parent) != NULL){
        if(node == node->parent->left){
            node->parent->left = x;
        }else{
            node->parent->right = x;
        }
    }else{
        root = x;
    }
    //(x)---(Y) 
    x->right = node;
    node->parent = x;

    return root;
}  
  
  
//三、红黑树的查找  
//---------------------------------------------------  
//rb_node_t* rb_search_parent：查找节点，并且找到其父节点，如果没有找到节点，则父节点指针保持不变。
//rb_node_t* rb_search：返回找到的结点  
//----------------------------------------------------  
rb_node_t* rb_search_parent(key_t key, rb_node_t* root, rb_node_t **parent){
    rb_node_t *node = root, *p = NULL;  
    key_t delt; 
    
    while(node != NULL){
        delt = key - node->key;
        p = node;           //记录node节点的父节点，插入时也可以用到。
        if(delt == 0){      //找到key则返回node
            return node; 
        }else if(delt > 0){
            node = node->right;
        }else{
            node = node->left;
        }
    }
    if(parent != NULL){     //parent传进来不是空
        *parent = p;        //则返回应当插入节点的父节点
    }

    return NULL;
}

rb_node_t* rb_search(key_t key, rb_node_t* root){
    return rb_search_parent(key, root, NULL); //最后一个参数为NULL,则不记录父节点
}

//四、红黑树的插入  
/*---------------------------------------------------------  
|RB_INSERT(T, z)
| 1 y = nil[T]
| 2 x = root[T]
| 3 while x != nil[T]
| 4   y = x
| 5   if key[z] < key[x]
| 6     x = left[x]
| 7   else x = right[x]
| 8 p[z] = y
| 9 if y == nil[T]
|10   root[T] = x
|11 else if key[z] < key[y]
|12   left[y] = z
|13 else right[y] = z
|14 left[z] = nil[T]
|15 right[z] = nil[T]
|16 color[z] = RED
|17 RB_INSERT_FIXUP(T, z)
|---------------------------------------------------------*/
//红黑树的插入结点  
rb_node_t* rb_insert(key_t key, data_t data, rb_node_t* root){  
    rb_node_t *parent = NULL, *node;  
    //调用rb_search_parent找到插入结点的地方,如果有这个节点，则返回，表示key值不包含重复项。
    if((node = rb_search_parent(key, root, &parent)) != NULL){  
        return root;  
    }  
   
    //插入节点
    node = rb_new_node(key, data);      //分配结点  
    node->parent = parent;     
    node->left = node->right = NULL;    //叶子节点，左右孩子为空   
    node->color = RED;                  //插入红色
    if(parent != NULL){          //parent传给rb_search_parent时不为空，则返回如果为空，则node为根节点。
        if(parent->key > key){  
            parent->left = node;  
        }else{  
            parent->right = node;  
        }  
    }else{  
        root = node;  
    }  
   
    //插入结点后，调用rb_insert_rebalance修复红黑树的性质  
    return rb_insert_fixup(node, root);   
}  
  
//五、红黑树的3种插入修改情况  
/*---------------------------------------------------------------
|接下来，咱们重点分析针对红黑树插入的3种情况，而进行的修复工作。  
|总结一下：
|1）叔红，则叔父双黑，祖红，跳到祖
|2）叔黑父左己右，则跳到父左旋
|3）叔黑父左己左，则父黑祖红以祖右旋
|4）叔黑父右己左，则跳到父右旋
|5）叔黑父右己右，则父黑祖红以祖左旋
|
|插入看叔，左旋右旋，没有指明都是以当前节点为参数，指明以祖右旋则以祖节点为参数。
|用z表示当前结点，p[z]表示父母、p[p[z]]表示祖父、y表示叔叔。  
--------------------------------------------------------------*/  
rb_node_t* rb_insert_fixup(rb_node_t *node, rb_node_t *root){  
    rb_node_t *parent, *gparent, *uncle, *tmp;      //父母p[z]、祖父p[p[z]]、叔叔y、临时结点*tmp  
   
    while ((parent = node->parent) && parent->color == RED){        //parent为node的父母，且当父母的颜色为红时  
        gparent = parent->parent;                                   //gparent为祖父      
        //当祖父的左孩子即为父母时,其实上述几行语句，无非就是理顺孩子、父母、祖父的关系.
        if (parent == gparent->left){//父为左        
            uncle = gparent->right;              //定义叔叔的概念，叔叔y就是父母的右孩子。  
            if (uncle && uncle->color == RED){   //情况1：概括为：<<叔红，则叔父双黑，祖红，跳到祖>>    
                uncle->color = BLACK;   
                parent->color = BLACK;  
                gparent->color = RED;    
                node = gparent;                  //跳到祖节点，继续下一次循环。
            }else{                
                if(parent->right == node){       //情况2：<<叔黑父左己右，则跳到父左旋>>
                    node = parent;  //跳到父
                    root = rb_rotate_left(node, root);      //左旋
                    parent = node->parent;       //因为情形2变化之后必然变成情形3，所以，此处更新一下父节点，进入情形3.
                }                                //情况3：<<叔黑父左己左，则父黑祖红以祖右旋>>                
                parent->color = BLACK;   
                gparent->color = RED;    
                root = rb_rotate_right(gparent, root); //以祖右旋，当前节点不动  
            }
        }else{//父为右       
            uncle = gparent->left;
            if(uncle && uncle->color == RED){    //情况1：<<叔红，则叔父双黑，祖红，跳到祖>> ，当叔为红时，就不用考虑自己和父节点的左右了。
                uncle->color = BLACK;  
                parent->color = BLACK;  
                gparent->color = RED;  
                node = gparent;                 //跳到祖
            }else{//叔黑                            
                if(parent->left == node){       //情况2：<<叔黑父右己左，跳到父右旋>>  
                    node = parent;
                    root = rb_rotate_right(node, root);  //以结点parent、root右旋  
                    parent = node->parent;      //同样，经过情形2必然变成情形3，同步更新父节点。
                }                               //情况3：<<叔黑父右己右，则父黑祖红以祖左旋>>  
                parent->color = BLACK;  
                gparent->color = RED;  
                root = rb_rotate_left(gparent, root);   //以祖左旋，当前节点不动。 
            }  
        }  
    }  
   
    root->color = BLACK; //根结点，不论怎样，都得置为黑色。  
    return root;      //返回根结点。  
}  
  
  
//六、红黑树的删除  
/*---------------------------------------------------------  
|RB_DELETE(T, z)
| 1 if left[z] == nil or right[z] == nil
| 2     y = z
| 3 else  y = TREE-SUCCESSOR(z)
| 4 if left[y] != nil
| 5     x = left[y]
| 6 else x = right[y]
| 7 p[x] = p[y]
| 8 if p[y] == nil
| 9     root = x
|10 else if y == left[p[y]]
|11         left[p[y]] = x
|12      else right[p[y]] = x
|13 else right[y] = z
|14 if y != z
|15     key[z] = key[y], copy y's satelite data into z
|16 if color[y] = BLACK
|17     RB_DELETE_FIXUP(T, x)
|18 return y
---------------------------------------------------------*/  
/* 删除节点是在二叉查找树的基础上修改，
 * 二叉查找树的删除节点分三种情况：
 * 1)被删节点无子女：则直接删除，父节点对应孩子为空
 * 2)被删结点只有一个子女：则将非空子女传递给其父亲之后再删除
 * 3)被删节点有两个子女：则取出其后继节点作为顶替当前节点，然后删除后继节点（此时后继节点只有可能是有一个右孩子或者没有孩子）
 * 修改就是，在上述删除之后调用rb_erase_fixup调整。
 */


rb_node_t* rb_erase(key_t key, rb_node_t *root){  
    rb_node_t *child, *parent, *old, *left, *node;  
    color_t color;  
   
    if((node = rb_search_parent(key, root, NULL)) == NULL){  //调用rb_search_auxiliary查找要删除的结点 
        printf("key %d is not exist!\n", key);
        return root;  
    }  
   
    old = node;     //记录要删的节点
    if(node->left != NULL && node->right != NULL){  //两个节点都非空  
        node = node->right;  //找到右子树的最小值，作为后继节点
        while((left = node->left) != NULL){  
            node = left;  
        }  
        child = node->right;    //后继节点是最左节点，故取其右孩子为child
        parent = node->parent;  //parent指向后继节点的父节点
        color = node->color;    //后继节点的颜色，因为这个颜色才是被抛弃的颜色
    
        //把后继节点的孩子连上其父节点
        if(child != NULL){ 
            child->parent = parent;  
        }  
        if(parent != NULL){  
            if(parent->left == node){  
                parent->left = child;  
            }else{  
                parent->right = child;  
            }  
        }else{  //node为根节点，则孩子直接为根节点  
            root = child;  
        }  
    
        if(node->parent == old){    //如果后继节点恰好是被删节点的右孩子
            parent = node;          //则令parent节点指向后继节点，此时child为node右孩子
        }  
    
        //node替代掉old节点：继承其链接关系和颜色，注意所有关系均为双向的
        node->parent = old->parent;  
        node->color = old->color;  
        node->right = old->right;  
        node->left = old->left;
        //old与父节点的联系转给node  
        if(old->parent != NULL){  
            if(old->parent->left == old){  
                old->parent->left = node;  
            }else{  
                old->parent->right = node;  
            }  
        }else{  
            root = node;  
        }
        //old的孩子关系转给node  
        old->left->parent = node;  
        if(old->right != NULL){     //old右孩子可能为空，因为修改过node->parent的左孩子和右孩子，右孩子为空时，可能恰好old->right为空
            old->right->parent = node;  
        }  
    }else{  //左右孩子至少有一个为空
        if(node->left == NULL){         //左孩子为空  
            child = node->right;  
        }else if(node->right == NULL){  //左孩子不空，且右孩子为空
            child = node->left;  
        }  
        parent = node->parent;          //记录被删节点的父节点
        color = node->color;            //记录被删节点的颜色
        
        if(child != NULL){              //  
            child->parent = parent;  
        }  
        if(parent != NULL){  
            if(parent->left == node){  
                parent->left = child;  
            }else{  
                parent->right = child;  
            }  
        }else{  //父节点为空，则被删结点为根，独子为根  
            root = child;  
        }  
    }  
   
    if(color == BLACK){     //真正被删的节点为黑色，则修正
        //child:可能是1）后继节点的右孩子，如果后继节点恰好为被删节点的右孩子
        //     2）被删节点至少有一个孩子为空时，则为其左孩子或右孩子或空
        //parent：为child父节点，child可能为左孩子也可能为右孩子，还可能为空
        root = rb_erase_fixup(child, parent, root); //注意parent可能不是child的父节点  
    }  
   
    return root;  
}  
   
  
//七、红黑树的4种删除情况  
/*----------------------------------------------------------------  
|红黑树修复删除的4种情况，node节点一定非空
|前提是：己为空或为黑，且不为根
|1）己左兄红，则兄黑父红，以父左旋
|2）己左兄黑两子黑，则兄红跳到父（此时不分左右） 
|3）己左兄黑左子红，则兄红两子黑，以兄右旋
|4）己左兄黑右子红，则双子黑，兄同父，父变黑，以父左旋
|5）己右兄红，则兄黑父红，以父右旋
|6）己右兄黑右子红，则兄红双子黑，以兄左旋
|7）己右兄黑左子红，则双子黑，兄同父，父变黑，以父右旋
|注意：插入时修复是看叔节点，删除时修复是看兄弟节点。 
|----------------------------------------------------------------  */
rb_node_t* rb_erase_fixup(rb_node_t *node, rb_node_t *parent, rb_node_t *root){  
    rb_node_t *brother;   //x的兄弟*brother
    while ((node == NULL || node->color == BLACK) && node != root){    //调整节点为空或者为黑色， 且非根 
        if(parent->left == node){   //当前节点为父节点的左孩子
            brother = parent->right;  //兄弟为右
            if(brother->color == RED){                   //情况1：<<兄红己左，则兄黑父红，以父左旋>>
                brother->color = BLACK;    
                parent->color = RED;   
                root = rb_rotate_left(parent, root);       //以父左旋，不跳  
                brother = parent->right;  //更新其右兄弟  
            }

            if((brother->left == NULL || brother->left->color == BLACK) &&  
                    (brother->right == NULL || brother->right->color == BLACK)){
                                                        //情况2：<<兄两子黑，则兄红跳到父>>  
                brother->color = RED; 
                node = parent; 
                parent = node->parent;  //更新父  
            }else{                       //兄弟为黑  
                if(!brother->right || brother->right->color == BLACK){    //情况3：<<兄左子红，则兄红两子黑，以兄右旋>>  
                    if(brother->left != NULL){
                        brother->left->color = BLACK;   
                    }

                    brother->color = RED;           
                    root = rb_rotate_right(brother, root);  //以兄右旋  
                    brother = parent->right;        //更新兄弟  
                }//旋转之后必然变成情况4                      
                brother->color = parent->color;                           //情况4：<<兄右子红，则变双黑，兄同父，父变黑，以父左旋>>  
                parent->color = BLACK;  
                if(brother->right != NULL){      //且w的右孩子是红 
                    brother->right->color = BLACK;  //兄弟节点w右孩子染成黑色  
                }  
                root = rb_rotate_left(parent, root);  //以父左旋  
                node = root;   //并把x置为根。  
                break;  
            }  
        }else{  //当前节点为父节点的右孩子
            brother = parent->left;  
            if(brother->color == RED){                 //情况5：<<兄红己右，则兄黑父红，以父右旋>> 
                brother->color = BLACK;  
                parent->color = RED;  
                root = rb_rotate_right(parent, root);  //以父右旋，不跳
                brother = parent->left;  
            }  
            if((brother->left == NULL || brother->left->color == BLACK) &&  
                (brother->right == NULL || brother->right->color == BLACK)){   //情况2：<<兄两子黑，则兄红跳到父>>  
                brother->color = RED;  
                node = parent;  
                parent = node->parent;  
            }else{  //兄黑，两子不全黑    
                if(brother->left == NULL || brother->left->color == BLACK){    //情况6：<<兄黑右子红，则兄红双子黑，以兄左旋>>  
                    if(brother->right != NULL){  
                        brother->right->color = BLACK;  
                    }  
                    brother->color = RED;  
                    root = rb_rotate_left(brother, root);   //以兄左旋，不跳
                    brother = parent->left;  
                }                                                       //情况7：<<兄黑左子红，则双子黑，兄同父，父变黑，以父右旋>>
                brother->color = parent->color;  
                parent->color = BLACK;  
                if(brother->left){  
                    brother->left->color = BLACK;  
                }  
                root = rb_rotate_right(parent, root);  
                node = root;    
                break;  
            }  
        }  
    }  
   
    if(node != NULL){  
        node->color = BLACK;  //最后将node[上述步骤置为了根结点]，改为黑色。  
    }    
    return root;  //返回root  
}  
