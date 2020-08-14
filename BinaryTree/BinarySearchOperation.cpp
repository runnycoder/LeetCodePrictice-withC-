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
bool isValidBST(TreeNode* root) {
    vector<int> list;
    in_orderVisit(list,root);
    if(list.size()==0){//空数也符合条件
        return true;
    }
    return isSorted(list);
}


TreeNode* searchBST(TreeNode* root, int val) {
    if(root==NULL){
        return NULL;
    }
    if(root->val==val){
        return root;
    }else if(val<root->val){
        return searchBST(root->left,val);
    }else{
        return searchBST(root->right,val);
    }
}

TreeNode* insertIntoBST(TreeNode* root, int val) {
        if(root==NULL){
            return new TreeNode(val);
        }
        if(root->val==val){
            return root;
        }else if(val<root->val){
            root->left = insertIntoBST(root->left,val);
        }else{
            root->right = insertIntoBST(root->right,val);
        }
        return root;
}

/*
删除要比我们前面提到过的两种操作复杂许多。有许多不同的删除节点的方法，这篇文章中，我们只讨论一种使整体操作变化最小的方法。我们的方案是用一个合适的子节点来替换要删除的目标节点。根据其子节点的个数，我们需考虑以下三种情况：

1. 如果目标节点没有子节点，我们可以直接移除该目标节点。
2. 如果目标节只有一个子节点，我们可以用其子节点作为替换。
3. 如果目标节点有两个子节点，我们需要用其中序后继节点或者前驱节点来替换，再删除该目标节点。

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/introduction-to-data-structure-binary-search-tree/xpyd7r/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

/*思路 二叉查找树的重要性质 结点左子树的所有结点都比自己小 结点右子树的结点值都比自己大
 中序遍历可以得到一个递增的序列
*/
//获取当前结点中序遍历的后继结点 右子树的最左
int successor(TreeNode* root){
    root = root->right;
    while(root->left!=NULL){
        root = root->left;
    }
    return root->val;
}

int preSuccessor(TreeNode* root){
    root = root->left;
    while(root->right!=NULL){
        root = root->right;
    }
    return root->val;
}



TreeNode* deleteNode(TreeNode* root, int key) {
    if(root==NULL){
        return NULL;
    }
    if(key<root->val){
        root->left=deleteNode(root->left,key);
    }else if(key>root->val){
        root->right=deleteNode(root->right,key);
    }else{//找到要删除的结点了
        if(root->left&&root->right){//有左右子结点 可以选择左或者右子树进行操作
            //和右子树的后继结点互换位置
           root->val = successor(root);
            //对右子树进行删除操作
           root->right = deleteNode(root->right, root->val);
        }else if (root->left){//只有左结点
            //和左子树的前驱结点互换位置
           root->val = preSuccessor(root);
            //对左子树进行删除操作
           root->left = deleteNode(root->left, root->val);

        }else if (root->right)//只有右结点
        {
            //和右子树的后继结点互换位置
           root->val = successor(root);
            //对右子树进行删除操作
           root->right = deleteNode(root->right, root->val);
           
        }else{//为叶子结点
            root = NULL;
        }
    }
    return root;
}

int main(){
    TreeNode* root = new TreeNode(5);
    root->left = new TreeNode(3);
    root->left->left = new TreeNode(2);
    root->left->right = new TreeNode(4);
    root->right = new TreeNode(6);
    root->right->right = new TreeNode(7);
    
    deleteNode(root,3);
    return 0;
}
