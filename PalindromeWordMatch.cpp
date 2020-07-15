#include<iostream>
#include<string>
#include<vector>
using namespace std;
/*
在输入的字符串数组当中寻找互文的 一组单词
["abcd","dcba","lls","s","sssll"]

字符串:abcd存在回文字符串!
[0,1]
字符串:dcba存在回文字符串!
[1,0]
*/
class Trie{
    private:
        bool isWord;
        int  index;
        Trie* children[26];
    public:
        Trie(){
            isWord = false;
            for(int i=0;i<26;i++){
                children[i] = NULL;
            }
        }

        void reverseOrderInsert(string word,int index){
            Trie* root = this;
            for (int i = word.size() - 1; i >= 0; i--)
            {
                /* code */
                int cindex = word[i]-'a';
                if(root->children[cindex]==NULL){//如果字符位置为空 则新建结点填充
                    root->children[cindex] = new Trie();
                }
                root = root->children[cindex];//指向下一个结点
            }
            root->isWord = true; //插入完毕之后在最后的字符结点 标记为单词
            root->index = index;//记录当前字典 在单词集合中的位置
        }

        int search(string word){//正序查找字典树
            Trie* root = this;
            for(int i=0; i<word.size(); i++){
                int cindex = word[i]-'a';
                if(root->children[cindex]==NULL){
                    return false;
                }
                root = root->children[cindex];
            }
            return root->index;
        }

};


int main(){
    vector<string> words ;
    words.push_back("abcd");
    words.push_back("dcba");
    words.push_back("lls");
    words.push_back("s");
    words.push_back("sssll");

    Trie trie;
    for(int i=0;i<words.size();i++){
        trie.reverseOrderInsert(words[i],i+1);
    }

    for(int i=0;i<words.size();i++){
        int flag =  trie.search(words[i]);
        // bool rflag = trie.reverseSearch(words[i]);
        // cout<<"flag="<<flag<<";rflag="<<rflag<<endl;
        if(flag&&(flag-1)!=i){
            cout<<"字符串:"<<words[i]<<"存在回文字符串!"<<endl;
            cout<<"["<<i<<","<<(flag-1)<<"]"<<endl;
        }
    }


    return 0;
}