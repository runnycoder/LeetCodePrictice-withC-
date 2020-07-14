#include<iostream>
#include<string>

using namespace std;
/*
search(word) 可以搜索文字或正则表达式字符串，字符串只包含字母 . 或 a-z 。 . 可以表示任何一个字母。
addWord("bad")
addWord("dad")
addWord("mad")
search("pad") -> false
search("bad") -> true
search(".ad") -> true
search("b..") -> true
*/
class Trie{
    public:
        bool isWord;
        Trie* children[26];
        Trie(){
            isWord=false;
            for (int i = 0; i <26; i++)
            {
                /* code */
                children[i]=NULL;
            }
        }
        ~Trie(){
            for(Trie* child : children){
                if(child){
                    delete(child);
                }
            }
        }

};
class WordDictionary{
    private:
        Trie* root;
    public:
        WordDictionary(){
            root = new Trie();
        }
        void addWord(string word){
            Trie* p = root;
            for(int i=0;i<word.size();i++){
                int cindex = word[i]-'a';
                if(p->children[cindex]==NULL){
                    p->children[cindex]=new Trie();
                }
                p=p->children[cindex];
            }
            p->isWord=true;
        }

        bool search(string word){
            return dfs(word,root,0);
        }

        bool dfs(string &word,Trie* p,int i){
            if(i==word.size()){
                return p->isWord;
            }

            //如果是.则要搜索全部的子结点
            if(word[i]=='.'){
                for(auto &a:p->children){
                    if(a&&dfs(word,a,i+1)){
                        return true;
                    }
                }
            }else{
                int cindex = word[i]-'a';
                return p->children[cindex]&&dfs(word,p->children[cindex],i+1);
            }
            return false;
        }
// 0000 0101
// 0001 1001
// 0001 1100
// 16+8+4=28
};


int main(){
    WordDictionary dictionary;
    dictionary.addWord("abc");
    dictionary.addWord("bcd");
    dictionary.addWord("dab");
    cout<<dictionary.search("abc")<<endl;
    cout<<dictionary.search(".bc")<<endl;
    cout<<dictionary.search("..c")<<endl;
    cout<<dictionary.search("a.c")<<endl;
    return 0;
}