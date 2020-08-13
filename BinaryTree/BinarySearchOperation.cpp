#include<iostream>
#include<vector>
using namespace std;
/*
验证二叉搜索树
给定一个二叉树，判断其是否是一个有效的二叉搜索树。

假设一个二叉搜索树具有如下特征：

节点的左子树只包含小于当前节点的数。
节点的右子树只包含大于当前节点的数。
所有左子树和右子树自身必须也是二叉搜索树。

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/introduction-to-data-structure-binary-search-tree/xpkc6i/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};
/*
    思路：二叉搜索树 按照中序遍历得到的是一个递增的有序数列
*/
bool isValidBST(TreeNode* root) {
    vector<int> list;
    in_orderVisit(list,root);
    if(list.size()==0){//空数也符合条件
        return true;
    }
    return isSorted(list);
}
void in_orderVisit(vector<int>& list,TreeNode* root){
    if(!root){
        return;
    }
    in_orderVisit(list,root->left);
    list.push_back(root->val);
    in_orderVisit(list,root->right);
}
bool isSorted(const vector<int>& list){
    for (int i = 0; i < list.size()-1; i++)
    {
        /* code */
        if(list[i]>=list[i+1]){//等于也不算
            return false;
        }
    }
    return true;
}

int main(){
    return 0;
}
