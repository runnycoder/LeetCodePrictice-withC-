#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;
class Node{
public:
    int val;
    vector<Node*> children;
    Node(){}
    Node(int _val){val=_val;}
    Node(int _val,vector<Node*> _children){
        val = _val;
        children = _children;
    }
};

void preorder(Node* root,vector<int>& list) {
    if(root==NULL){
        return;
    }
    list.push_back(root->val);
    vector<Node*> children = root->children;
    for (int i = 0; i < root->children.size(); i++)
    {
        /* code */
        Node* child = root->children[i];
        preorder(child,list);
    }
    return;
}

vector<int> preorder(Node* root) {
    vector<int> list;
    preorder(root,list);
    return list;
}

void postorder(Node* root,vector<int>& list) {
    if(root==NULL){
        return;
    }
    vector<Node*> children = root->children;
    for (int i = 0; i < root->children.size(); i++)
    {
        /* code */
        Node* child = root->children[i];
        postorder(child,list);
    }
    list.push_back(root->val);
    return;
}

vector<int> postorder(Node* root) {
    vector<int> list;
    postorder(root,list);
    return list;   
}
//迭代的方式实现后序遍历
vector<int> postorder_by_iter(Node* root) {
    vector<int> list;
    vector<int> result;
    if(!root){
        return list;
    }
    stack<Node*> node_stack;
    node_stack.push(root);
    while (!node_stack.empty())
    {
        /* code */
        Node* node = node_stack.top();
        node_stack.pop();
        list.push_back(node->val);
        for (auto &&child : node->children)
        {   if(child!=NULL){
                node_stack.push(child);
            }
        }
    }

    vector<int>::reverse_iterator riter;
    for (riter = list.rbegin(); riter!=list.rend(); riter++)
    {
        /* code */
        result.push_back(*riter);
    }

    return result;   
}

//中序遍历的实现
vector<vector<int> > levelOrder(Node* root) {
    vector<vector<int> > result;
    if(!root){
        return result;
    }
    queue<Node*> node_queue;
    node_queue.push(root);
    while (!node_queue.empty())
    {
        /* code */
        vector<int> level;
        int level_size = node_queue.size();
        for (int i = 0; i < level_size; i++)
        {
            /* code */
            Node* node = node_queue.front();
            node_queue.pop();
            level.push_back(node->val);

            for (auto &&child : node->children)
            {   if(child!=NULL){
                    node_queue.push(child);
                }
            }
        }
        result.push_back(level);
    }
    return result;       
}

/*
    N 叉树的最大深度
给定一个 N 叉树，找到其最大深度。

最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。
*/
int maxDepth(Node* root) {
     int child_max_level = -1;
     if(root==NULL){
         return 0;
     }else if (root->children.empty())
     {
         return 1;
     }else{
        vector<Node*> children = root->children;
        
        for (Node* child : children)
        {
            int dep = maxDepth(child);
            if(dep>child_max_level){
                child_max_level = dep;
            }
        }
     }
     return child_max_level+1;  
}



int main(){
    return 0;
}