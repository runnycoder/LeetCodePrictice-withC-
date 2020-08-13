#include<iostream>
#include<stack>

using namespace std;
/*
    二叉搜索树迭代器
    实现一个二叉搜索树迭代器。你将使用二叉搜索树的根节点初始化迭代器。
    调用 next() 将返回二叉搜索树中的下一个最小的数。

    next() 和 hasNext() 操作的时间复杂度是 O(1)，并使用 O(h) 内存，其中 h 是树的高度。
    你可以假设 next() 调用总是有效的，也就是说，当调用 next() 时，BST 中至少存在一个下一个最小的数。

    作者：力扣 (LeetCode)
    链接：https://leetcode-cn.com/leetbook/read/introduction-to-data-structure-binary-search-tree/xpg4qe/
    来源：力扣（LeetCode）
    著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

struct TreeNode{
    int val;
    TreeNode *left;
    TreeNode * right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};
class BSTIterator{
public:
    stack<TreeNode*> myStack;
    BSTIterator (TreeNode* root){
        leftMostInorder(root);
    }


    /** @return the next smallest number 使用堆栈模拟中序遍历 */
    int next() {
        TreeNode* top_node = myStack.top();
        myStack.pop();
        if(top_node->right){
            leftMostInorder(top_node->right);//压入下一步的访问序列
        }
        return top_node->val;
    }
    
    /** @return whether we have a next smallest number */
    bool hasNext() {
        return !myStack.empty();
    }
private:
    //将根结点一直查找左结点 全部压入栈中
    void leftMostInorder(TreeNode* root){
        while (!root)
        {
            myStack.push(root);
            root=root->left;
        }
    }
    /**
 * Your BSTIterator object will be instantiated and called as such:
 * BSTIterator* obj = new BSTIterator(root);
 * int param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */
};
