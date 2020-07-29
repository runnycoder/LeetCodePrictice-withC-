#include<iostream>
#include<vector>
#include<queue>
#include<stack>
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


int main(){
    TreeNode* root;
    root->val =2;
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(1);
    // preorderTraversalit(root);
    return 0;
}


