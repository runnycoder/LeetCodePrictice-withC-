#include<iostream>
#include<sstream>
#include<queue>
#include<string>
// #include<string.h>
#include<vector>
// #include<stdio.h>
using namespace std;

class Node{
    public:
        int val;
        Node* left;
        Node* right;
        Node* next;
        Node(): val(0),left(NULL),right(NULL),next(NULL) {}
        Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
        Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

/*
    填充每个节点的下一个右侧节点指针
给定一个完美二叉树，其所有叶子节点都在同一层，每个父节点都有两个子节点。二叉树定义如下：

struct Node {
  int val;
  Node *left;
  Node *right;
  Node *next;
}
填充它的每个 next 指针，让这个指针指向其下一个右侧节点。如果找不到下一个右侧节点，则将 next 指针设置为 NULL。

初始状态下，所有 next 指针都被设置为 NULL。

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/data-structure-binary-tree/xoo0ts/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
Node* connect(Node* root) {
      if(root==NULL){
          return NULL;
      }
      Node* leftmost = root;
      while(leftmost->left!=NULL){
          Node* head = leftmost;
          while (head!=NULL)
          {
              /* code */
              head->left->next = head->right;
              if(head->next!=NULL){
                  head->right->next = head->next->left;
              }
              head = head->next;
          }
          leftmost = leftmost->left;
      }
      return root;
}

//使用队列实现
Node* connectByQueue(Node* root) {
      if(root==NULL){
          return NULL;
      }
      queue<Node*> Q;
      Q.push(root);
      while (!Q.empty())
      {
          /* code */
          int q_size = Q.size();
          for (int i = 0; i < q_size; i++)//队列中已经存储的都是同一层的结点
          {
              /* code */
              Node* temp = Q.front();
              Q.pop();
              if(i<q_size-1){//如果不是最右侧结点 则将next指向相邻的右侧结点
                  temp->next = Q.front();
              }
              //将当前结点的左右结点添加到下一层
              if(temp->left){
                  Q.push(temp->left);
              }
              if(temp->right){
                  Q.push(temp->right);
              }
          }
      }
      return root;
}

/*
    二叉树的最近公共祖先
给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

百度百科中最近公共祖先的定义为：“对于有根树 T 的两个结点 p、q，最近公共祖先表示为一个结点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（一个节点也可以是它自己的祖先）。”

输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
输出: 3
解释: 节点 5 和节点 1 的最近公共祖先是节点 3。

输入: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
输出: 5
解释: 节点 5 和节点 4 的最近公共祖先是节点 5。因为根据定义最近公共祖先节点可以为节点本身。

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/data-structure-binary-tree/xopaih/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};
//递归方式实现
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if(root->val<p->val&&root->val<q->val){
             return lowestCommonAncestor(root->right,p,q);
        }
        if(root->val>p->val&&root->val>q->val){
             return lowestCommonAncestor(root->left,p,q);
        }
        return root;
}

//迭代的方式实现
TreeNode* lowestCommonAncestorForWhile(TreeNode* root, TreeNode* p, TreeNode* q) {
        while(root!=NULL){
            if(root->val<p->val&&root->val<q->val){
                root = root->right;
            }
            if(root->val>p->val&&root->val>q->val){
                root = root->left;
            }
            break;
        }
        return root;
}

/*
    二叉树的序列化与反序列化
    序列化是将一个数据结构或者对象转换为连续的比特位的操作，进而可以将转换后的数据存储在一个文件或者内存中，同时也可以通过网络传输到另一个计算机环境，采取相反方式重构得到原数据。

    请设计一个算法来实现二叉树的序列化与反序列化。这里不限定你的序列 / 反序列化算法执行逻辑，你只需要保证一个二叉树可以被序列化为一个字符串并且将这个字符串反序列化为原始的树结构。

    作者：力扣 (LeetCode)
    链接：https://leetcode-cn.com/leetbook/read/data-structure-binary-tree/xomr73/
    来源：力扣（LeetCode）
    著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/
// Encodes a tree to a single string.


//先序遍历序列化
void pre_serialize(TreeNode* root,string& str){
    if(root==NULL){
        str.append("#,");
    }else{
        str.append(to_string(root->val)).append(",");
        pre_serialize(root->left,str);
        pre_serialize(root->right,str);
    }
}

//后序遍历序列化
void post_serialize(TreeNode* root,string& str){
    if(root==NULL){
        str.append("#,");
    }else{
        post_serialize(root->left,str);
        post_serialize(root->right,str);
        str.append(to_string(root->val)).append(",");
    }
}
//层序遍历序列化
void level_serialize(TreeNode* root,string& str){
    if(root==NULL){
        str.append("#");
        return;
    }
    queue<TreeNode*> Q;
    Q.push(root);
    while(!Q.empty()){
        TreeNode* front = Q.front();
        Q.pop();
        if(front==NULL){
            str.append("#,");
        }else{
            str.append(to_string(front->val)).append(",");
            Q.push(front->left);
            Q.push(front->right);
        }
    }
}


string serialize(TreeNode* root) {
    string result = "";
    // post_serialize(root,result);
    level_serialize(root,result);
    return result;
}

string serialize_ll(TreeNode* root) {
        if (!root) return "X";
        auto l = "(" + serialize_ll(root->left) + ")";
        auto r = "(" + serialize_ll(root->right) + ")";
        return  l + to_string(root->val) + r;
}



//辅助函数
void split(const string& s,vector<string>& sv,const char flag){
     sv.clear();
     istringstream str_stream(s);
     string temp;
     while(getline(str_stream,temp,flag)){
         sv.push_back(temp);
     }
     return;
}

TreeNode* rdeserialize(vector<string>& slist){
    if(slist[0]=="#"){
        slist.erase(slist.begin());
        return NULL;
    }
    TreeNode* root = new TreeNode(stoi(slist[0]));
    slist.erase(slist.begin());
    root->left = rdeserialize(slist);
    root->right = rdeserialize(slist);
    return root;

}
//先序序列反序列化
TreeNode* pre_deserialize(const string& data,int& position){
    if(data[position]=='#'){
        position+=2;//中间有,间隔 所以移动到下一个字符需要两位
        return NULL;
    }
    int next = position;
    while (data[next]!=',')//由于数字可能是两位数以上的 所以一直移动到下一个,的位置
    {
        /* code */
        next++;
    }
    int val = stoi(data.substr(position,next-position));
    position=next+1;//移动到下一个字符
    TreeNode* root = new TreeNode(val);

    root->left=pre_deserialize(data,position);
    root->right=pre_deserialize(data,position);
    return root;
}

//后序序列反序列化
TreeNode* post_deserialize(const string& data,int& position){
    if(data[position]=='#'){
        position-=2;//中间有,间隔 所以移动到下一个字符需要两位
        return NULL;
    }
    int next = position;
    while (data[next]!=',')//由于数字可能是两位数以上的 所以一直移动到下一个,的位置
    {
        /* code */
        next--;
    }
    int val = stoi(data.substr(next+1,position-next));
    position=next-1;//移动到下一个字符
    TreeNode* root = new TreeNode(val);

    root->right=post_deserialize(data,position);
    root->left=post_deserialize(data,position);
    return root;
}
//层序反序列化
TreeNode* level_deserialize(const string& data,int& position){
    if(data[position]=='#'){
        return NULL;
    }
    
    int next = position;
    while (data[next]!=',')//由于数字可能是两位数以上的 所以一直移动到下一个,的位置
    {
        /* code */
        next++;
    }
    int val = stoi(data.substr(position,position-next));
    position = next+1;

    queue<TreeNode*> Q;
    TreeNode *root = new TreeNode(val);
    Q.push(root);
    while (!Q.empty())
    {
        /* code */
        TreeNode* front = Q.front();
        Q.pop();
        if(data[position]!='#'){
            next = position;
            //获取下一个元素的值
            while (data[next]!=',')//由于数字可能是两位数以上的 所以一直移动到下一个,的位置
            {
                /* code */
                next++;
            }
            val = stoi(data.substr(position,position-next));
            position = next+1;
            front->left = new TreeNode(val);
            Q.push(front->left);
        }else{
            position+=2;
            next = position;
        }

        if(data[position]!='#'){
            //获取下一个元素的值
            next = position;
            while (data[next]!=',')//由于数字可能是两位数以上的 所以一直移动到下一个,的位置
            {
                /* code */
                next++;
            }
            val = stoi(data.substr(position,position-next));
            position = next+1;
            front->right = new TreeNode(val);
            Q.push(front->right);
        }else{
            position+=2;
            next = position;
        }
    }
    
    return root;
    
}




// Decodes your encoded data to tree.
TreeNode* deserialize(string data) {
    // vector<string> sv ;
    // split(data,sv,',');
    // return rdeserialize(sv);
    // int position = data.size()-2;//最后一个字符是","舍弃
    // return post_deserialize(data,position);

    int position = 0;
    return level_deserialize(data,position);
    
}



int main(){
    string s = "a,b,c,";
    vector<string> sv;
    split(s,sv,',');
    for (auto s : sv)
    {
        cout<<s<<endl;
    }
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);

    root->right->left = new TreeNode(4);
    root->right->right = new TreeNode(5);
    string result;
    // result =  serialize(root);
    // cout<<result<<endl;

    // TreeNode *returnRoot = deserialize(result);
    // result =  serialize(returnRoot);
    // cout<<result<<endl;

    result = serialize_ll(root);
    cout<<result<<endl;

    // TreeNode* temp;
    // temp = deserialize(result);
    // string s = "abc";
    // cout<<s[0]<<endl;
    // cout<<s[1]<<endl;
    // cout<<s[2]<<endl;
    
    return 0;
}