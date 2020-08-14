#include<iostream>
#include<vector>
#include<queue>
using namespace std;
/*
数据流中的第K大元素
设计一个找到数据流中第K大元素的类（class）。注意是排序后的第K大元素，不是第K个不同的元素。

你的 KthLargest 类需要一个同时接收整数 k 和整数数组nums 的构造器，它包含数据流中的初始元素。每次调用 KthLargest.add，返回当前数据流中第K大的元素。

示例:

int k = 3;
int[] arr = [4,5,8,2];
KthLargest kthLargest = new KthLargest(3, arr);
kthLargest.add(3);   // returns 4
kthLargest.add(5);   // returns 5
kthLargest.add(10);  // returns 5
kthLargest.add(9);   // returns 8
kthLargest.add(4);   // returns 8

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/introduction-to-data-structure-binary-search-tree/xpjovh/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
class KthLargest{
    struct TreeNode{
        int val;
        int count;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x):val(x),count(1),left(NULL),right(NULL){}
    };
public:
    int K;
    TreeNode* root;
  
    TreeNode* addNode(TreeNode* root,int val){
        if(root==NULL){
            return new TreeNode(val);
        }
        if(val<=root->val){
            root->count+=1;
            root->left = addNode(root->left,val);
        }else if(val>root->val){
            root->count+=1;
            root->right = addNode(root->right,val);
        }
        return root;
    }
    //迭代方式实现添加
    TreeNode* addNodeByItr(TreeNode* root,int val){
        if(root==NULL){
            return new TreeNode(val);
        }
        TreeNode* res = root;
        while (true)
        {
            /* code */
            if(val>res->val){
                res->count+=1;
                if(res->right){
                    res=res->right;
                }else{
                    res->right = new TreeNode(val);
                    break;
                }
            }else{
                res->count+=1;
                if(res->left){
                    res=res->left;
                }else{
                    res->left = new TreeNode(val);
                    break;
                }
            }
          
        }
        return root;
        
    }

    int findKthNum(TreeNode* treeRoot,int k){
        int m = 1;
        if(treeRoot->right){
            m +=treeRoot->right->count;
        }
        if(m==k){//如果m=k 说明当前结点就是第k大的元素
            return treeRoot->val;
        }else if (m>k)//如果m>k说明 第k大的元素在右子树
        {
            return findKthNum(treeRoot->right,k);
        }else{//如果m<k说明 第k大的元素在左子树 而且往左子树搜索的时候 还要排除 右子树结点数目+1(根结点数目)
            return findKthNum(treeRoot->left,k-m);
        }
    }

    KthLargest(int k,vector<int>& nums):K(k),root(NULL){
        for (auto &&i : nums)
        {
            root = addNode(root,i);
        }
    }
    int add(int val){
        root = addNode(root,val);
        return findKthNum(root,K);
    }
};

class KthLargest2 {
    int K;
    priority_queue<int, vector<int>, greater<int>> pq;
public:
    KthLargest2(int k, vector<int>& nums) {
        for (int n : nums) {
            pq.push(n);
            if (pq.size() > k) pq.pop();//构造最小堆 保留前K个最大的值 top元素即为第k个最大值
        }       
        K = k;
    }
    
    int add(int val) {
        pq.push(val);
        if (pq.size() > K) pq.pop();
        return pq.top();
    }
};



int main(){
    priority_queue<int,vector<int>,greater<int> > q1;
    priority_queue<int> q2;
    for (int i = 0; i < 10; i++)
    {
        /* code */
        q1.push(i);
        q2.push(i);
    }
    while (!q1.empty())
    {
        /* code */
        cout<<q1.top()<<" ";
        q1.pop();
    }
    cout<<endl;

     while (!q2.empty())
    {
        /* code */
        cout<<q2.top()<<" ";
        q2.pop();
    }
    cout<<endl;
    
    
    return 0;
}