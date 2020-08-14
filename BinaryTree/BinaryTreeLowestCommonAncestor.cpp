#include<iostream>
using namespace std;

/*
    二叉搜索树的最近公共祖先
    给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。

    百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

    作者：力扣 (LeetCode)
    链接：https://leetcode-cn.com/leetbook/read/introduction-to-data-structure-binary-search-tree/xpf523/
    来源：力扣（LeetCode）
    著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    int root_val = root->val;
    int p_val = p->val;
    int q_val = q->val;
    if(p_val<root_val&&q_val<root_val){//递归搜索其左子树
        return lowestCommonAncestor(root->left,p,q);
    }else if(p_val>root_val&&q_val>root_val){
        return lowestCommonAncestor(root->right,p,q);
    }else{
        return root;
    }
}

int main(){
    return 0;
}