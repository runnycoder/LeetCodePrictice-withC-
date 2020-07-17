#include<iostream>
#include<math.h>
using namespace std;

//HashTable的建立一个是桶数据的确定 桶数必须是一个素数 最大程度让元素均匀的分布到桶中
//另一个是hash计算冲突的处理 这里使用单开链的方式 将hash值相同的 键值对 存入同一个桶中
//HashTable里面 最经常的就是元素的插入 删除 查找操作 如果使用链表 查询的效率比较低 但是又不能使用数组
//数组的插入删除复杂度为O(n) 综合考虑 我们使用二叉搜索树作为桶 这样插入 查询 和搜索的平均时间复杂度都是logn
template<typename Key,typename Value>
class TreeNode{
    public:
        Key key;
        Value value;
        TreeNode* left;
        TreeNode* right;
    TreeNode(){

    }
    TreeNode(Key key,Value value){
        this->key = key;
        this->value = value;
        this->left=this->right=NULL;
    }
};
template<typename Key,typename Value>
class BSTree{
    private:
        TreeNode<Key,Value>* root ;
        int count;
    public:
        BSTree (){
            root = NULL;
            count = 0;
        }
        ~ BSTree(){
            cout<<"Current BSTree is deleting..."<<endl;
            destory(root);
        }

        int size(){
            return count;
        }

        bool isEmpty(){
            return count==0;
        }

        void insert(Key key,Value value){
            root = insert(root,key,value);
        }

        Value* search(Key key){
            return search(root,key);
        }

        bool contains(Key key){
            return contains(root,key);
        }

        void  deleteNode(Key key){
            root = deleteNode(root,key);
        }

        

        void destory(){
            destory(root);
        }
    private:
        TreeNode<Key,Value>* insert(TreeNode<Key,Value>* TNode,Key key,Value value){
            if(TNode==NULL){
                count++;
                return new TreeNode<Key,Value>(key,value);
            }
            if(key==TNode->key){
                TNode->value = value;
            }else if(key<TNode->key){
                TNode->left = insert(TNode->left,key,value);
            }else {
                TNode->right = insert(TNode->right,key,value);
            }
            return TNode;
        }

        Value* search(TreeNode<Key,Value>* TNode,Key key){
            if(TNode==NULL){
                return NULL;
            }
            if(key==TNode->key){
                return &(TNode->value);
            }else if(key<TNode->key){
                return search(TNode->left,key);
            }else {
                return search(TNode->right,key);
            }
        }

        bool contains(TreeNode<Key,Value>* TNode,Key key){
            return search(TNode,key)==NULL?false:true;
        }

        //寻找以TNode为树根的最小值结点
        TreeNode<Key,Value>*  findMinNode(TreeNode<Key,Value>* TNode){
            if(TNode==NULL){
                return NULL;
            }else if (TNode->left!=NULL)
            {
                return findMinNode(TNode->left);
            }else
            {
                return TNode;
            }
            
            
        }
        //返回删除结点后的二叉树的树根
        TreeNode<Key,Value>*  deleteNode(TreeNode<Key,Value>* TNode,Key key){
            if(TNode==NULL){
                return NULL;
            }
            if(key<TNode->key){
                TNode->left = deleteNode(TNode->left,key);
                return TNode;
            }else if (key>TNode->key)
            {   TNode->right = deleteNode(TNode->right,key);
                return TNode;
            }else{
               
               if(TNode->left==NULL){
                   TreeNode<Key,Value>* temp = TNode->right;
                   delete TNode;
                   count--;
                   return temp;
               }
               if(TNode->right==NULL){
                   TreeNode<Key,Value>* temp = TNode->left;
                   delete TNode;
                   count--;
                   return temp;
               }
               //左右结点都不为空 寻找右子树值最小的结点
               TreeNode<Key,Value>* RMinNode =  findMinNode(TNode->right);
               TNode->key = RMinNode->key;
               TNode->value = RMinNode->value;
               return deleteNode(TNode->right,RMinNode->key);
            }
            
        }



        void destory(TreeNode<Key,Value>* TNode){
            if(NULL!=TNode){
                destory(TNode->left);
                destory(TNode->right);
                delete(TNode);
                count--;
            }
        }
};
template<typename Key,typename Value>
class Bucket{
    private:
        BSTree<Key,Value> Tree;
    public:
        Bucket(){

        }
        // Bucket(const Bucket<Key,Value>& bucket){
        //     Tree = bucket.Tree;
        // }
        void bucketInsert(Key key,Value value){
            Tree.insert(key,value);
        }

        void bucketDelete(Key key){
            Tree.deleteNode(key);
        }

        bool bucketContains(Key key){
            return Tree.contains(key);
        }
};

template<typename Key,typename Value,typename T>
class MyHashSet {

    private:
    static const int MAX_TABLE_SIZE = 10000;
    T* buket;
    int  buketNum;
    int nextPrime(int n){//取大于n的下一个素数
        int prime = n%2==0?n+1:n+2;//取大于n的第一个奇数
        int i;
        while(prime<MAX_TABLE_SIZE){
            for (i = (int)sqrt(prime); i >= 2; i--)
            {
                /* code */
                if(prime%i==0) break;
            }
            if(i==2){//说明循环完毕 prime是素数
                return prime;
            }else{//否则试探下一个素数
                prime+=2;
            }
        }
        return prime;
    }

    int hash(int number){
        return number%buketNum;
    }
    public:
    /** Initialize your data structure here. */
    MyHashSet() {
        buketNum = nextPrime(1000);
        buket = new T[buketNum];
        // for (int i = 0; i < buketNum; i++)
        // {
        //     /* code */
        //     buket[i] = ;
        // }
        

    }
    ~MyHashSet(){
        delete [] buket;
    }
       
    
    
    void add(Key key,Value value) {
        int index = hash(key);
        T indexBuket = buket[index];
        if(&(indexBuket)==NULL){
            buket[index]= T();
        }else{
            buket[index].bucketInsert(key,value);
        }
    }
    
    void remove(Key key) {
        int index = hash(key);
        T indexBuket = buket[index];
        if(&(indexBuket)==NULL){
            cout<<"this key is not in HashSet delete error";
        }else{
            indexBuket.bucketDelete(key);
        }
    }
    
    /** Returns true if this set contains the specified element */
    bool contains(Key key) {
        int index = hash(key);
        T indexBuket = buket[index];
        if((&indexBuket)==NULL){
            return false;
        }else{
            return indexBuket.bucketContains(key);
        }
    }

    
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */
int main(){
    // BSTree<int,int> BT;

    // BT.insert(10,11);
    // int* p= BT.search(10);
    // cout<<(*p)<<endl;
    // BT.insert(10,12);
    // int* a= BT.search(10);
    // cout<<(*a)<<endl;

    // BT.deleteNode(10);
    // cout<<BT.contains(10)<<endl;

    // MyHashSet<int,int> HashSet;
    // HashSet.add(11,12);
    // cout<<HashSet.contains(11)<<endl;

    // MyHashSet<int,int,Bucket<int,int> > HashSet;
    // HashSet.add(11,12);
    // cout<<HashSet.contains(11)<<endl;
    // Bucket<int,int> bucket;
    // bucket.bucketInsert(11,12);
    // cout<<bucket.bucketContains(11)<<endl;


    return 0;
}