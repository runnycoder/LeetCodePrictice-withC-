#include<iostream>
using namespace std;
/*
    红黑树 是平衡二叉树的一种 相比于AVL树在插入和删除方面 需要调整的结点比较少
    效率会高一点 红黑树是根据2-3树演化过来的 可以参考这边文章 https://zhuanlan.zhihu.com/p/95892351
    介绍的比较详细了
*/

enum RBTColor{RED,BLACK};
template <class T>
class RBTNode{
    public:
        RBTColor color;//颜色
        T key;//键值
        RBTNode* left;//左孩子
        RBTNode* right;//右孩子
        RBTNode* parent;//父结点
        RBTNode(T value,RBTColor c,RBTNode *p,RBTNode* l,RBTNode* r):
        key(value),color(c),parent(p),left(l),right(r){}
};

template<class T>
class RBTree{
    private:
        RBTNode<T>* mroot;//根结点
    public:
        RBTree();
        ~RBTree();
        //key值查找
        RBTNode<T>* search(T key);
        //寻找最大结点k值
        T findMaximum();
        //寻找最小结点k值
        T findMinimum();
        //查找指定结点的后继
        RBTNode<T>* successor(RBTNode<T>* x);
        //查找指定结点的前驱
        RBTNode<T>* predecessor(RBTNode<T>* x);
        
        void insert(T key);

        void remove(T key);

        void print();

        void destroy();

        bool isRed(RBTNode<T>* x);

        bool isBlack(RBTNode<T>* x);
    private:
        //查找红黑树x中键值为key的结点
        RBTNode<T>* search(RBTNode<T>* x,T key) const;
        //寻找以x为根结点红黑树的最大结点
        RBTNode<T>* findMaximum(RBTNode<T>* x);
        //寻找以x为根结点红黑树的最小结点
        RBTNode<T>* findMinimum(RBTNode<T>* x);
        //左旋
        void leftRotate(RBTNode<T>* &root,RBTNode<T>* x);
        //右旋
        void rightRotate(RBTNode<T>* &root,RBTNode<T>* x);
        //插入新结点
        void insert(RBTNode<T>* &root,RBTNode<T>* node);
        //插入后平衡调整
        void insertFixUp(RBTNode<T>* &root,RBTNode<T>* node);
        //删除指定结点
        void remove(RBTNode<T>* &root,RBTNode<T>* node);
        //删除后平衡调整
        void removeFixUp(RBTNode<T>* &root,RBTNode<T>* node);

        void destroy(RBTree<T>* &tree);

        void print(RBTree<T>* tree,T key,int direction);
};
//constructor define start
template<class T>
RBTree<T>::RBTree():mroot(NULL){
    mroot = NULL;
}

template<class T>
RBTree<T>::~RBTree(){
    destroy();
}
//constructor define end

//search define start
template<class T>
RBTNode<T>* RBTree<T>::search(RBTNode<T>* x,T key) const{
    if(x==NULL||x->key==key)
        return x;
    if(key<x->key)
        return search(x->left,key);
    else
        return search(x->right,key);
}

template<class T>
RBTNode<T>* RBTree<T>::search(T key){
    return search(mroot,key);
}
//search define end

//find min,max node define start
template<class T>
RBTNode<T>* RBTree<T>::findMaximum(RBTNode<T>* tree){
    if(tree==NULL){
        return NULL;
    }
    while (tree->right)
    {
        /* code */
        tree = tree->right;
    }
    return tree;
}
template<class T>
T RBTree<T>::findMaximum(){
    RBTNode<T>* tree = findMaximum(mroot);
    if(tree){
        return tree->key;
    }
    return NULL;
}

template<class T>
RBTNode<T>* RBTree<T>::findMinimum(RBTNode<T>* tree){
    if(tree==NULL){
        return NULL;
    }
    while(tree->left){
        tree = tree->left;
    }
    return tree;
}
template<class T>
T RBTree<T>::findMinimum(){
    RBTNode<T>* tree = findMinimum(mroot);
    if(tree){
        return tree->key;
    }
    return NULL;
}
//find min,max node define end

//find successor node define start
template<class T>
RBTNode<T>* RBTree<T>::successor(RBTNode<T>* x){
    if(x==NULL){
        return NULL;
    }else if(x->right!=NULL){//有右结点 返回右子树的最小结点
        return findMinimum(x->right);
    }else{
        /*无右结点 如果当前结点是父结点的左结点 则后继为父结点  若为右结点 需要向上回朔直到 p->left=ch 
              p1
            /
            p2
           /  \  
       left    ch1
                  \
                   ch2
                      \
                       ch3
        left结点的后继是 p2
        ch3结点的后继是 p1
        */
        RBTNode<T>* p = x->parent;
        RBTNode<T>* ch = x;
        while (p&&p->right==ch)
        {   
            ch = p;
            p = p->parent;
        }
        return p;
    }
}
//find successor node define end

//find predeccessor node define start
template<class T>
RBTNode<T>* RBTree<T>::predecessor(RBTNode<T>* x){
    if(x==NULL){
        return NULL;
    }else if(x->left){//如果有左结点 返回左子树的最大值
        return findMaximum(x);
    }else{
        /*
            无左结点 如果当前结点ch是父结点的右结点 则父结点p即为前驱结点 若为左结点 则需要向上回朔 直到p->right=ch
            p1
              \
              p2
            /   \
          l1     right1
         /
       l2
      /
    l3
        right1 predcessor is p2
        l3 predecessor is l3
        */
        RBTNode<T>* p = x->parent;
        RBTNode<T>* ch = x;
        while (p&&p->left==ch)
        {
            ch = p;
            p = p->parent;
        }
        return p;
    }
}
//find predeccessor node define end

//color judgment start
template<class T>
bool RBTree<T>::isRed(RBTNode<T>* x){
    if(x!=NULL&&x->color==RED){
        return true;
    }
    return false;
}

template<class T>
bool RBTree<T>::isBlack(RBTNode<T>* x){
     if(x==NULL||x->color==BLACK){
        return true;
    }
    return false;
}
//color judgment end

//leftrotate a subtree start
template<class T>
void RBTree<T>::leftRotate(RBTNode<T>* &root,RBTNode<T>* x){
    RBTNode<T>* rchild = x->right;
    x->right = rchild->left;
    if(rchild->left!=NULL){
        rchild->left->parent = x;
    }
    rchild->parent = x->parent;
    if(x->parent==NULL){
        root = rchild;
    }else if(x->parent->left==x){
        rchild->parent->left=rchild;
    }else{
        rchild->parent->right=rchild;
    }
    rchild->left=x;
    x->parent=rchild;
}
//leftrotate a subtree end

//rightrotate a subtree start
template<class T>
void RBTree<T>::rightRotate(RBTNode<T>* &root,RBTNode<T>* x){
    RBTNode<T>* lchild = x->left;
    x->left = lchild->right;
    if(x->left!=NULL){
        lchild->right->parent = x;
    }
    lchild->parent = x->parent;
    if(x->parent==NULL){
        root = lchild;
    }else if (x->parent->left==x)
    {
        lchild->parent->left=lchild;
    }else{
        lchild->parent->right=lchild;
    }
    lchild->right = x;
    x->parent = lchild;
}
//rightrotate a subtree end

//insert and fix start
template<class T>
void RBTree<T>::insertFixUp(RBTNode<T>* &root,RBTNode<T>* node){
   
    while(node!=NULL&&node!=root&&node->parent->color==RED){
        RBTNode<T>* t_parent = node->parent;
        RBTNode<T>* t_grandpa = t_parent->parent;
        RBTNode<T>* t_uncle;
        if(t_parent == t_grandpa->left){//父结点是祖父结点的左孩子
            t_uncle = t_grandpa->right;
            if(isRed(t_uncle)){//叔叔结点也是红色的 进行颜色反转
                t_parent->color=BLACK;
                t_uncle->color=BLACK;
                t_grandpa->color=RED;
                node=t_grandpa;
                continue; //递归向上判断 祖父结点变为红色是否会造成不平衡
            }else{//叔叔结点是黑色的
                if(node == t_parent->right){//如果当前结点是右孩子 则先进行一个左旋
                    RBTNode<T>* temp;
                    leftRotate(root,t_parent);
                    temp = t_parent;
                    t_parent = node;
                    node =temp;
                }
                t_parent->color=BLACK;
                t_grandpa->color=RED;
                rightRotate(root,t_grandpa);
            }
        }else{//父结点是祖父结点的右孩子 和上面的操作相反
            t_uncle = t_grandpa->left;
            if(isRed(t_uncle)){//叔叔结点为RED
                t_parent->color=BLACK;
                t_uncle->color=BLACK;
                t_grandpa->color=RED;
                node = t_grandpa;
                continue;
            }else{//叔叔结点为黑
                if(node == t_parent->left){//如果当前结点为左孩子 需要先进行一个右旋
                    RBTNode<T>* temp;
                    rightRotate(root,t_parent);
                    temp = t_parent;
                    t_parent = node;
                    node = temp;

                }
                t_parent->color=BLACK;
                t_grandpa->color = RED;
                leftRotate(root,t_grandpa);
            }
        }
    }
    root->color = BLACK;
}

template<class T>
void RBTree<T>::insert(RBTNode<T>* &root,RBTNode<T>* node){
    
    RBTNode<T>* troot = root;
    RBTNode<T>* parent = NULL;
    while (troot!=NULL)
    {
        parent=troot;
        if(node->key<troot->key){
            troot = troot->left;
        }else if(node->key>troot->key){
            troot = troot->right;
        }else{
            troot->key = node->key;
            return;
        }
    }
    node->parent = parent;
    if(parent!=NULL){
        if(node->key<parent->key){
            parent->left=node;
        }else if(node->key>parent->key){
            parent->right=node;
        }
    }else{
        root = node;
    }
    node->color = RED;
    insertFixUp(root,node);
};

template<class T>
void RBTree<T>::insert(T key){
    RBTNode<T>* newNode = new RBTNode<T>(key,RED,nullptr,nullptr,nullptr);
    insert(RBTree<T>::mroot,newNode);
}

template<class T>
void RBTree<T>::removeFixUp(RBTNode<T>* &root,RBTNode<T>* node){
    while(node!=root && node->color==BLACK){
        if(node==node->parent->left){//node为左子结点
            RBTNode<T>* sib = node->parent->right;//寻找兄弟结点sib
            if(sib->color==RED){//兄弟结点为空 node为黑 说明父结点p一定为黑 交换 sib和parent的颜色 然后左旋
                sib->color=BLACK;
                node->parent->color=RED;
                leftRotate(root,node->parent);
                sib = node->parent->right; //node新的兄弟结点为 sib(原)->left必为黑
            }
            //经过上面的调整 下面都是兄弟结点为黑这种情况了
            //兄弟为黑 兄弟左右孩子同时为黑 这种直接将sib置为红 然后node指向parent 递归向上进行处理
            if(sib->left->color==BLACK&&
                sib->right->color==BLACK){
                    sib->color=RED;
                    node=node->parent;
            }else{
                if(sib->left->color==RED){//sib为黑 sib左结点为红
                    //交换sib与左结点的颜色 以sib为中心进行右旋
                    sib->left->color=BLACK;
                    sib->color=RED;
                    rightRotate(root,sib);
                    sib=node->parent->right;//旋转之后新的sib结点 应该是sib(old)->left结点
                    //这样就变成了下面sib为黑 sib的右结点为红这种情况
                }//sib为黑 sib-right-color=red 这样我们左子树可以通过旋转 从兄弟子树借一个黑色结点 
                //同时把sib->right->color置为黑色 保持右子树黑色结点不变 parent结点颜色也不变
                sib->color=node->parent->color;
                node->parent->color=BLACK;
                sib->right->color=BLACK;
                leftRotate(root,node->parent);//调整完毕之后就平衡了
                node = root;//这个应该是为了跳出循环？
            }

        }else{//下面就是镜像处理了
            RBTNode<T>* sib = node->parent->left;
            if(sib->color==RED){
                sib->color=BLACK;
                node->parent->color=RED;
                rightRotate(root,node->parent);
                sib = node->parent->left;
            }
            if(sib->right->color==BLACK&&
                sib->left->color==BLACK){
                sib->color=RED;
                node=node->parent;
            }else{
                if(sib->left->color==BLACK){
                    sib->right->color=BLACK;
                    sib->color=RED;
                    rightRotate(root,node->parent);
                    sib = node->parent->left;
                }
                sib->color=node->parent->color;
                node->parent->color=BLACK;
                sib->left->color=BLACK;
                rightRotate(node->parent);
                node =root;
            }
        }
    }
    node->color=BLACK;
}

template<class T>
void RBTree<T>::remove(RBTNode<T>* &root,RBTNode<T>* node){
    RBTNode<T>* child,parent;
    if(node->left!=NULL&&node->right!=NULL){//双结点一定存在后继结点
         RBTNode<T>* s_node = successor(node);
         node->key = s_node->key;//删除结点node 变成删除结点的后继结点s_node
         node = s_node;
    }
    /*
        如果node有两个子结点 那么使用后继结点替换之后
        1 node(new)只有一个子结点
        2 node(new)没有子结点
        对于第1种情况 由于红黑树的性质分析node和子结点应该是什么颜色的
            (1)假设node->color=red node->left=null
            此时node->right一定是黑色结点 此时node右子树一定会比左子树多出至少一个黑色结点 不满足平衡条件
            (2)假设node->color=black node->left=null
                (2-1)node->right=black与(1)情况相同不满足平衡条件
                (2-2)node->right=red 当node->right的子结点都是null的时候满足平衡条件 否则依然是不平衡的
            同理可以推断出node->right=null的情况 综上所述node只有一个子孩子的时候  必须满足node->color=black
            node->child->color=red
        此时只需将node结点删除 node->child->color=black 然后连接node->child和node->parent即可完成平衡
        所以我们的删除后平衡处理主要针对第二种情况 第二种情况比较复杂 但也有迹可循 原理可以参考 
        https://www.jianshu.com/p/84416644c080 这篇文件 下面的代码实现根据的是java TreeMap的源码
    */
    RBTNode<T>* replacement = node->left==NULL?node->right:node->left;
    if(replacement!=NULL){
        replacement->parent=node->parent;
        if(node->parent==NULL){
            root = replacement;
        }else if(node==node->parent->left){
            node->parent->left = replacement;
        }else{
            node->parent->right = replacement;
        }
        node->left=node->right=node->parent=NULL;
        cout<<"删除结点node的颜色为"<<node->color<<endl;

        //这个是java TreeMap这样实现的 我觉得这一步其实没有必要 直接把replacement颜色变黑就已经完成平衡了
        //还没想明白 什么情况下 才会出现node为红而且只有一个非空子结点
        if(node->color==BLACK){
            removeFixUp(root,replacement);
        }

        // replacement->color=BLACK;
    }else if(node->parent==NULL){//没有左右结点且父结点为空 说明此时只有这一个结点
        root = NULL;
    }else{//没有子结点
        //此处node作为一个占位结点 不会影响后续平衡调整 因为就算先删除node node原来的位置也是null(黑色结点)
        //可以等调整完成再进行删除
        if(node->color==BLACK){
            removeFixUp(root,node);
        }
        if(node->parent!=NULL){
            if(node==node->parent->left){
                node->parent->left=NULL;
            }else{
                node->parent->right=NULL;
            }
            node->parent=NULL;
        }
    }


}

// struct TreeNode{
//     int val;
//     TreeNode* left;
//     TreeNode* right;
//     TreeNode* parent;
//     TreeNode(int x,TreeNode* l,TreeNode* r,TreeNode* p):
//     val(x),left{l},right(r),parent(p){}
// };

//insert and fix end
int main(){
    RBTree<int>* tree = new RBTree<int>();
    tree->insert(3);
    tree->insert(4);
    tree->insert(5);
    tree->insert(6);
    tree->insert(7);
    return 0;
}