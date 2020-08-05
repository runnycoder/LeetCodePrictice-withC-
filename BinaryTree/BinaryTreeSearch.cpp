#include<iostream>
#include<vector>
#include<queue>
#include<stack>
#include<algorithm>
#include<unordered_map>
using namespace std;

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x),left(NULL),right(NULL){}
};

void preorderTraversal(TreeNode* root, vector<int>& res){
    if(root==NULL){
        return;
    }
    res.push_back(root->val);
    preorderTraversal(root->left,res);
    preorderTraversal(root->right,res);
}

//先序遍历递归方式实现
vector<int> preorderTraversal(TreeNode* root){
    vector<int> res;
    preorderTraversal(root,res);
    return res;
} 

//先序遍历迭代方式实现
vector<int> preorderTraversalByStack(TreeNode* root){
        vector<int> res;
        // preorderTraversal(root,res);
        stack<TreeNode*> s;
        s.push(root);
        while (!s.empty()&&s.top()!=NULL)
        {
            /* code */
            TreeNode* current_node = s.top();//访问栈顶部元素
            s.pop();//弹出栈顶元素
            res.push_back(current_node->val);
            if(current_node->right){
                s.push(current_node->right);
            }
            if(current_node->left){
                s.push(current_node->left);
            }
        }
    
    return res;
}


void inorderTraversal(TreeNode* root, vector<int>& res){
    if(root==NULL){
        return;
    }
    inorderTraversal(root->left,res);
    res.push_back(root->val);
    inorderTraversal(root->right,res);
}

//中序遍历二叉树递归方式实现
vector<int> inorderTraversal(TreeNode* root){
    vector<int> res;
    inorderTraversal(root,res);
    return res;
}

//中序遍历二叉树迭代方式实现
vector<int> inorderTraversalByStack(TreeNode* root){
    vector<int> res;
    stack<TreeNode*> s;
    while (root!=NULL || !s.empty())
    {
        /* code */
        while(root!=NULL){
            s.push(root);
            root=root->left;
        }
        if(!s.empty()){
             root = s.top();
             res.push_back(root->val);
             s.pop();
             root = root->right;
        }

    }
    return res;
}




void postorderTraversal(TreeNode* root, vector<int>& res){
    if(root==NULL){
        return;
    }
    postorderTraversal(root->left,res);
    postorderTraversal(root->right,res);
    res.push_back(root->val);

}

//后续遍历二叉树递归方式实现
vector<int> postorderTraversal(TreeNode* root){
    vector<int> res;
    postorderTraversal(root,res);
    return res;
}

//后续遍历二叉树迭代方式实现
vector<int> postorderTraversalByStack(TreeNode* root){
    vector<int> res;
    stack<TreeNode*> s;
    s.push(root);
    if(root==NULL){
        return res;
    }
    while(!s.empty()){
        TreeNode *position = s.top();
        res.push_back(position->val);
        s.pop();
        if(position->left){
            s.push(position->left);
        }
        if(position->right){
            s.push(position->right);
        }
    }
    reverse(res.begin(),res.end());
    return res;
}

//二叉树的层序遍历
vector<vector<int>> levelOrder(TreeNode* root) {


    vector<vector<int> > res;
    if(root==NULL){
        return res;
    }

    queue<TreeNode*> q;
    q.push(root);
    int level = q.size();
    while(!q.empty()){
        vector<int> level_set;
        for (int i = 0; i < level; i++)
        {
            /* code */
            TreeNode *position = q.front();
            q.pop();
            level_set.push_back(position->val);
            if(position->left){
                q.push(position->left);
            }
            if(position->right){
                q.push(position->right);
            }
        }
        res.push_back(level_set);
        level = q.size();
    }
    return res;
}

//求数的最大深度
int max_depth;
void maximum_depth(TreeNode* root,int depth){
    if(root==NULL){
        return;
    }
    if(!root->left&&!root->right){
       max_depth = max(max_depth,depth);
    }
    maximum_depth(root->left,depth+1);
    maximum_depth(root->right,depth+1);
}

int maxDepth(TreeNode* root) {
    if(root==NULL){
        return 0;
    } 
    int max_left = maxDepth(root->left);
    int max_right = maxDepth(root->right);
    return max(max_left,max_right)+1;
}

//检查一颗二叉树是否是对称的
/*
    两棵树 A B 什么时候互为镜像 首先根结点相同
    A->left = B->right 
    A->right = B->left
    判断一棵树是否是镜像对称 使用递归的思想
     p q指针一开始指向根结点 p往左移动的时候 q往右移动
*/
bool check(TreeNode* p,TreeNode* q){
    if(!p&&!q) return true; //p q = NULL
    if(!p||!q) return false;// p = NULL or q=NULL

    //p q ! = NULL
    return p->val==q->val&&check(p->left,q->right)&&check(p->right,q->left);
}
bool isSymmetric(TreeNode* root) {
   return check(root,root);
}

//迭代方式实现
bool checkByItor(TreeNode* p,TreeNode* q){
    queue<TreeNode*> que;
    que.push(p);
    que.push(q);
    while(!que.empty()){
        p = que.front();
        que.pop();
        q = que.front();
        que.pop();
        if(!p&&!q) continue; //p and q is NULL
        if((!p||!q)||p->val!=q->val) return false;
        que.push(p->left);
        que.push(q->right);

        que.push(p->right);
        que.push(q->left);
    }
    return true;
}

bool checkByStack(TreeNode* p,TreeNode* q){
    stack<TreeNode*> S;
    S.push(p);
    S.push(q);
    while(!S.empty()){
        p = S.top();
        S.pop();
        q = S.top();
        S.pop();
        if(!p&&!q) continue; //p and q is NULL
        if((!p||!q)||p->val!=q->val) return false;
        S.push(p->left);
        S.push(q->right);

        S.push(p->right);
        S.push(q->left);
    }
    return true;
}

/*
路径总和
给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，这条路径上所有节点值相加等于目标和。

说明: 叶子节点是指没有子节点的节点。

示例: 
给定如下二叉树，以及目标和 sum = 22，
*/
bool pathSum(TreeNode* root,int parentNum,int sum){
    if(root==NULL){
        return parentNum==sum;
    }
    int current_num = parentNum + root->val;
    bool left = pathSum(root->left,current_num,sum);
    bool right = pathSum(root->right,current_num,sum);
    return left||right;
}
bool hasPathSum(TreeNode* root, int sum) {
   return pathSum(root,0,sum);
}


//使用队列层序遍历 查找符合条件的叶结点
bool hasPathSumByQueue(TreeNode* root,int sum){
    if(root==NULL){
        return false;
    }
    queue<TreeNode*> q_node;
    queue<int> q_val;
    q_node.push(root);
    q_val.push(root->val);
    while (!q_node.empty())
    {
        /* code */
        root = q_node.front();
        q_node.pop();
        int current_sum = q_val.front();
        q_val.pop();
        if(root->left==root->right){//左右结点只有在等于NULL的时候才会相等 也就是当前结点为叶结点
            if(current_sum==sum){
                return true;
            }
        }
        if(root->left){
            q_node.push(root->left);
            q_val.push(current_sum+root->left->val);
        }
        if(root->right){
            q_node.push(root->right);
            q_val.push(current_sum+root->right->val);
        }
    }
    return false;
    
}

/*
    从中序与后序遍历序列构造二叉树
根据一棵树的中序遍历与后序遍历构造二叉树。

注意:
你可以假设树中没有重复的元素。

例如，给出
前序列遍历 preorder = [3,9,20,15,7]
中序遍历 inorder = [9,3,15,20,7]
后序遍历 postorder = [9,15,7,20,3]

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/data-structure-binary-tree/xo98qt/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int post_index;
TreeNode* helper(vector<int>& inorder,vector<int>& postorder,unordered_map<int,int>& index_map,int in_left,int in_right){
    if(in_left>in_right){
        return NULL;
    }
    //pick up post_index element as root
    int root_val = postorder[post_index];
    TreeNode* root = new TreeNode(root_val);

    int index = index_map[root_val];

    post_index--;
    root->right = helper(inorder,postorder,index_map,index+1,in_right);
    root->left =  helper(inorder,postorder,index_map,in_left,index-1);
    return root;
}

TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    unordered_map<int,int> index_map;
    for (int i = 0; i < inorder.size(); i++)
    {
        /* code */
        index_map[inorder[i]]=i;
    }
    post_index = postorder.size()-1;
    int in_left = 0;
    int in_right = inorder.size()-1;
    return helper(inorder,postorder,index_map,in_left,in_right);  
}

/*
    从前序与中序遍历序列构造二叉树
    根据一棵树的前序遍历与中序遍历构造二叉树。

    注意:
    你可以假设树中没有重复的元素。

    例如，给出

    前序遍历 preorder = [3,9,20,15,7]
    中序遍历 inorder = [9,3,15,20,7]

    作者：力扣 (LeetCode)
    链接：https://leetcode-cn.com/leetbook/read/data-structure-binary-tree/xoei3r/
    来源：力扣（LeetCode）
    著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
int pre_index;

TreeNode* preHelper(vector<int>& preorder,vector<int>& inorder,unordered_map<int,int>& index_map,int in_left,int in_right){
    if(in_left>in_right){
        return NULL;
    }
    int root_val = preorder[pre_index];
    TreeNode* root = new TreeNode(root_val);

    pre_index++;
    int index = index_map[root_val];
    root->left=preHelper(preorder,inorder,index_map,in_left,index-1);
    root->right=preHelper(preorder,inorder,index_map,index+1,in_right);
    return root;
}

TreeNode* buildTreeFromPre(vector<int>& preorder, vector<int>& inorder) {
    pre_index = 0;
    unordered_map<int,int> index_map;
    for (int i = 0; i < inorder.size(); i++)
    {
        /* code */
        index_map[inorder[i]]=i;
    }
    int in_left = 0;
    int in_right = inorder.size()-1;
    return preHelper(preorder,inorder,index_map,in_left,in_right);
    
}




int main(){
    // TreeNode* root;
    // root->val =2;
    // root->left = new TreeNode(3);
    // root->left->left = new TreeNode(1);
    // preorderTraversalit(root);

    vector<int> in_order = {9,3,15,20,7};
    vector<int> post_order = {9,15,7,20,3};
    TreeNode* root = buildTree(in_order,post_order);
    return 0;
}


