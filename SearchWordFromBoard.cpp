#include<vector>
#include<iostream>
#include<string>
#include<set>

using namespace std;
/*
给定一个二维网格 board 和一个字典中的单词列表 words，找出所有同时在二维网格和字典中出现的单词。

单词必须按照字母顺序，通过相邻的单元格内的字母构成，其中“相邻”单元格是那些水平相邻或垂直相邻的单元格。同一个单元格内的字母在一个单词中不允许被重复使用。

示例:

输入: 
words = ["oath","pea","eat","rain"] and board =
[
  ['o','a','a','n'],
  ['e','t','a','e'],
  ['i','h','k','r'],
  ['i','f','l','v']
]

输出: ["eat","oath"]
*/
class Trie{
    private:
        bool isWord;
        Trie* children[26];
    public:
        Trie(){
            isWord=false;
            for(int i=0;i<26;i++){
                children[i]=NULL;
            }
        }
        void insert(string word){
            Trie* root=this;
            for(int i=0;i<word.size();i++){
                int cindex = word[i]-'a';
                if(root->children[cindex]==NULL){
                    root->children[cindex] = new Trie();
                }
                root = root->children[cindex];
            }
            root->isWord = true;
        }

        bool search(string word){
            Trie* root = this;
            for(int i=0;i<word.size();i++){
                int cindex = word[i]-'a';
                if(root->children[cindex]==NULL){
                    return false;
                }
                 root = root->children[cindex];
            }
            return root->isWord;
        }

        bool searchPrefix(string word){
            Trie* root = this;
            for(int i=0;i<word.size();i++){
                int cindex = word[i]-'a';
                if(root->children[cindex]==NULL){
                    return false;
                }
                 root = root->children[cindex];
            }
            return true;
        }
};

class Solution{
    public:
        set<string> res;
        Trie trie;
        // Solution(){
        //     trie = new Trie();
        // }

        vector<string> findWords(vector<vector<char> >& board, vector<string>& words ){
            vector<string> vs;
            int m = board.size();
            if(m==0) return vs;
            int n = board[0].size();
            if(n==0) return vs;

            //定义是否被访问过矩阵
            vector<vector<int> > visited(m,vector<int>(n,0));
 
            // vector<vector<int>> visited(m,vector(n,0));
            //为单词建立字典树
            for(string word: words){
                trie.insert(word);
            }
            for(int i=0;i<m;i++){
                for(int j=0;j<n;j++){
                    dfs(board,i,j,"",visited);
                }
            }

            for(auto s : res){
                vs.push_back(s);
            }
            return vs;
        }

        void dfs(vector<vector<char> >& board,int x,int y,string str,vector<vector<int> >& visited ){
            int m = board.size();
            int n = board[0].size();
            if(x<0||x>=m||y<0||y>=n){//递归基础 不能大于等于边界
                return;
            }
            str+=board[x][y];
            if(!trie.searchPrefix(str)){//如果字典中没有以str为前缀的单词直接返回
                return;
            }
            if(trie.search(str)){//如果在字典树找到和str匹配的单词 放入res集合中
                res.insert(str);
            }
            visited[x][y]=1;//设置当前位置以访问
            //访问当前字符的上下左右位置
            dfs(board,x,y+1,str,visited);//上
            dfs(board,x,y-1,str,visited);//下
            dfs(board,x-1,y,str,visited);//左
            dfs(board,x+1,y,str,visited);//右
            visited[x][y]=0;//清除访问标记继续下次循环
        }

};

int main(){
    Solution* s = new Solution();
    vector<string> words;
    words.push_back("oath");
    words.push_back("pea");
    words.push_back("eat");
    words.push_back("rain");

    vector< vector<char> > board;
    vector<char> board1;
    vector<char> board2;
    vector<char> board3;
    vector<char> board4;
    board1.push_back('o');
    board1.push_back('a');
    board1.push_back('a');
    board1.push_back('n');

    board2.push_back('e');
    board2.push_back('t');
    board2.push_back('a');
    board2.push_back('e');

    board3.push_back('i');
    board3.push_back('h');
    board3.push_back('k');
    board3.push_back('r');

    board4.push_back('i');
    board4.push_back('f');
    board4.push_back('l');
    board4.push_back('v');

    board.push_back(board1);
    board.push_back(board2);
    board.push_back(board3);
    board.push_back(board4);
    vector<string> resvector = s->findWords(board,words);
    for(string word : resvector){
        cout<<word<<endl;
    }
    // Trie trie;
    // trie.insert("abc");
    // trie.insert("bcd");

    // cout<<trie.search("abc")<<endl;
    // cout<<trie.searchPrefix("a")<<endl;
}