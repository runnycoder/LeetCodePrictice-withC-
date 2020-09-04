#include<iostream>
#include<cmath>
using namespace std;
/*
    平衡为叉树的基础是在二叉搜索树 在插入或删除新结点的时候 要检查是否破坏了树的平衡性
    若是则找出最小的不平衡子树 在保持二叉搜索树的特性的前提下 调整最小不平衡子树中各个结点
    的链接关系 使之成为新的平衡子树
*/
class AVLNode{
public:
    int data;
    int height;//结点高度 叶结点高度为1
    AVLNode* left;
    AVLNode* right;
    AVLNode(int data):data(data),height(1),left(NULL),right(NULL){}
};

class AVLTree{
public:
    AVLNode* root;
    AVLTree(){
        root=nullptr;
    }
    ~AVLTree(){
        delete root;
        root = NULL;
    }
    int height(AVLNode* root){
        if(root){
            return root->height;
        }
        return 0;
    }
    AVLNode* findMaxNode(AVLNode* root){//以root为根结点 查找最大结点
        if(root){
            while (root->right)
            {
                root=root->right;
            }
        }
        return root;
    }
    AVLNode* findMinNode(AVLNode* root){//以root为根结点 查找最小结点
        if(root){
            while (root->left)
            {
                root=root->left;
            }
        }
        return root;
    }

    /*
        mark:AVL树左旋右旋右不同的定义规则 我这里采用 以根结点p为中心
        p位置从右到左 认为是左旋 ll
        p位置从左到右 认为是右旋 rr
        以p的左孩子为中心 先进行左旋 然后再以p为中心进行右旋 认为是左右旋转
        以p的右孩子为中心 先进行右旋 然后在以p为中心进行左旋 认为是右左旋转
    */

    //以p为根结点进行右旋 返回新的根结点 新的根结点为p->left
    AVLNode* rrRotate(AVLNode* p){
        AVLNode* pleft = p->left;
        p->left = pleft->right;
        pleft->right = p;
        p->height = max(height(p->left),height(p->right))+1;
        pleft->height = max(height(pleft->left),height(pleft->right))+1;
        return pleft;
    }

    //以p为根结点进行左旋 返回新的根结点 新的根结点为p->right
    AVLNode* llRotate(AVLNode* p){
        AVLNode* pright = p->right;
        p->right = pright->left;
        pright->left = p;
        p->height = max(height(p->left),height(p->right))+1;
        pright->height = max(height(pright->left),height(pright->right))+1;
       
        return pright;
    }

    //进行lr旋转 先以p->right进行左旋转 再以p结点进行右旋转
    AVLNode* lrRotate(AVLNode* p){
        p->left = llRotate(p->left);
        return rrRotate(p);
    }

    //进行rl旋转 先以p->left进行右旋 再以p结点进行左旋转
    AVLNode* rlRotate(AVLNode* p){
        p->right = rrRotate(p->right);
        return llRotate(p);
    }
    //插入新结点 并保持平衡
    AVLNode* insert(int data,AVLNode* root){
        if(root==NULL){
            root = new AVLNode(data);
        }else{
            if(data<root->data){//递归左子树
                root->left = insert(data,root->left);
                if(height(root->left)-height(root->right)==2){//如果插入之后破坏了平衡性
                    if(data<root->left->data){//如果插入结点在左子树的左子树
                        root = rrRotate(root);//右旋
                    }else{//如果插入结点在左子树的右子树
                        root = lrRotate(root);// 先左旋 后右旋
                    }
                }
            }else if (data>root->data)//递归右子树
            {
                root->right = insert(data,root->right);
                if(height(root->right)-height(root->left)==2){//如果插入之后破坏了平衡性
                    if(data>root->right->data){//插入结点在右子树的右子树
                        root = llRotate(root);//左旋
                    }else{//插入结点在右子树的左子树
                        root = rlRotate(root);//先右旋 再左旋
                    }
                }
            }else{
                cout<<"AVL树中已经存在该值"<<data<<endl;
            }
        }
        root->height = max(height(root->left),height(root->right))+1;
        return root;
    }

    //插入新结点 并保持平衡
    void insertNode(int data,AVLNode* root){
        if(root==NULL){
            root = new AVLNode(data);
        }else{
            if(data<root->data){//递归左子树
                insertNode(data,root->left);
                if(height(root->left)-height(root->right)==2){//如果插入之后破坏了平衡性
                    if(data<root->left->data){//如果插入结点在左子树的左子树
                        root = rrRotate(root);//右旋
                    }else{//如果插入结点在左子树的右子树
                        root = lrRotate(root);// 先左旋 后右旋
                    }
                }
            }else if (data>root->data)//递归右子树
            {
                insertNode(data,root->right);
                if(height(root->right)-height(root->left)==2){//如果插入之后破坏了平衡性
                    if(data>root->right->data){//插入结点在右子树的右子树
                        root = llRotate(root);//左旋
                    }else{//插入结点在右子树的左子树
                        root = rlRotate(root);//先右旋 再左旋
                    }
                }
            }else{
                cout<<"AVL树中已经存在该值"<<data<<endl;
            }
        }
        root->height = max(height(root->left),height(root->right))+1;
    }

    //删除结点 并保持平衡
    void deleteNode(int data,AVLNode*& root){
        if(root==NULL){
            cout<<"AVL树中不存在该值:"<<data<<endl;
        }else{
            if(data<root->data){
                deleteNode(data,root->left);
                //判断删除之后是否平衡
                if(height(root->right)-height(root->left)==2){
                    AVLNode* rnode =  root->right;//判断右子树的高度
                    if(height(rnode->left)<height(rnode->right)){//右子树的右子树高
                        root = llRotate(root);//左旋
                    }else{
                        root = rlRotate(root);//右左旋转
                    }
                }
            }else if(data>root->data){
                deleteNode(data,root->right);
                //判断是否平衡
                if(height(root->left)-height(root->right)==2){
                    AVLNode* lnode = root->left;
                    if(height(lnode->left)>height(lnode->right)){//左子树的左子树高
                        root = rrRotate(root);//右旋
                    }else{
                        root = lrRotate(root);//左右旋转
                    }
                }
            }else{//当前结点即是要删除的结点
                if(root->left&&root->right){//左右子结点不为空
                    //根据左右子树的高度判断交换那一边的结点 这样的好处是删除之后仍然是平衡的
                    if(height(root->left)>height(root->right)){//如果左子树比右子树高 则从左子树删除
                        AVLNode* maxNode = findMaxNode(root->left);
                        root->data = maxNode->data;
                        deleteNode(root->data,root->left);
                    }else{
                        AVLNode* minNode = findMinNode(root->right);
                        root->data = minNode->data;
                        deleteNode(root->data,root->right);
                    }

                }else if(root->left){//左结点不为空
                    AVLNode* maxNode = findMaxNode(root->left);
                    root->data = maxNode->data;
                    deleteNode(root->data,root->left);
                }else if(root->right){//右结点不为空
                    AVLNode* minNode = findMinNode(root->right);
                    root->data = minNode->data;
                    deleteNode(root->data,root->right);
                }else{//左右结点都为空
                    root = nullptr;
                }
            }
        }
    }

    void inOrder(AVLNode* root){
        if(root){
            inOrder(root->left);
            cout<<root->data<<endl;
            inOrder(root->right);
        }
    }
};

int main(){
    AVLTree avl;
    // AVLNode* root = new AVLNode(3);

    // root = avl.insert(2,root);
    // root = avl.insert(1,root);
    // root = avl.insert(4,root);
    // root = avl.insert(5,root);
    // root = avl.insert(6,root);
    // root = avl.insert(7,root);
    // root = avl.insert(10,root);
    // root = avl.insert(9,root);
    // root = avl.insert(8,root);
    //  avl.inOrder(root);


    avl.insertNode(3,avl.root);
    avl.insertNode(2,avl.root);
    avl.insertNode(1,avl.root);
    avl.insertNode(4,avl.root);
    avl.insertNode(5,avl.root);
    avl.insertNode(6,avl.root);
    avl.insertNode(7,avl.root);
    avl.insertNode(10,avl.root);
    avl.insertNode(9,avl.root);
    avl.insertNode(8,avl.root);

    avl.inOrder(avl.root);
    cout<<"================"<<endl;
    avl.deleteNode(5,avl.root);
    avl.inOrder(avl.root);
    cout<<"================"<<endl;
    avl.deleteNode(4,avl.root);
    avl.inOrder(avl.root);
    return 0;
}