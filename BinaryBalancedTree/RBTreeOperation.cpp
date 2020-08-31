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
        RBTNode(T value,RBTColor c,RBTColor *p,RBTNode* l,RBTNode* r):
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
        void removeFixUp(RBTNode<T>* &root,RBTNode<T>* node,RBTNode<T> *parent);

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
    RBTNode<T>* t_parent = node->parent;
    RBTNode<T>* t_grandpa = t_parent->parent;
    RBTNode<T>* t_uncle;
    while(node!=NULL&&node!=root&&t_parent->color==RED){
        if(t_parent == t_grandpa->left){//父结点是祖父结点的左孩子
            t_uncle = t_grandpa->right;
            if(t_uncle->color==RED){//叔叔结点也是红色的 进行颜色反转
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
            if(t_uncle->color==RED){//叔叔结点为RED
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
}

template<class T>
void RBTree<T>::insert(RBTNode<T>* &root,RBTNode<T>* node){
    RBTNode<T>* troot = root;
    RBTNode<T>* parent = root->parent;
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


//insert and fix end
int main(){

    return 0;
}