#include<iostream>
#include<vector>
#include<unordered_set>
#include<unordered_map>
using namespace std;
/*
    给定一棵二叉树，返回所有重复的子树。对于同一类的重复子树，你只需要返回其中任意一棵的根结点即可。

    两棵树重复是指它们具有相同的结构以及相同的结点值。

    https://leetcode-cn.com/explore/learn/card/hash-table/206/practical-application-design-the-key/823/
*/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */



class Solution {
public:
    struct TreeNode
    {
        /* data */
        int val;
        TreeNode  *left;
        TreeNode  *right;
        TreeNode() : val(0),left(nullptr),right(nullptr) {}
        TreeNode(int x) : val(x),left(nullptr),right(nullptr) {}
        TreeNode(int x,TreeNode *left,TreeNode *right) : val(x), left(left), right(right){}
    };

    unordered_map<string,int> count_map;
    vector<TreeNode*> res;
    
    /*
        思路：首先对给定的二叉树进行序列化（先序遍历） 用#填充子树 使得每个结点都有左右子树 每棵不同子树的序列化结果都是唯一的
        使用深度优先搜索 递归函数返回当前根结点子树的序列化结果
    */
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        collect(root);
        return res;
    }

    string collect(TreeNode* node){
        if(node==NULL){
            return "#";
        }
        string val_str =to_string(node->val);
        string serialize_str = val_str +","+collect(node->left)+","+collect(node->right);
        
        count_map[serialize_str] +=1;

        if(count_map[serialize_str]==2){
            res.push_back(node);
        }
        return serialize_str;
        
    }
};

int main(){
    return 0;
}