#include<iostream>
#include<cstring>
using namespace std;
class Trie{
    public:
        /*Initialize your data structure*/
        Trie(){
             isWord = false;
             for (int i = 0; i < 26; i++)
             {
                 /* code */
                 this->children[i]=NULL;
             }
             
        }

        /* Inserts a word int trie*/
        void insert(string word){
            Trie* root = this;
            for (int i = 0; i < word.size(); i++)
            {
                /* code */
                int cindex = word[i]-'a';
                if(root->children[cindex]==NULL){//word[i]-'a'表示当前字符 在数组结点中应该存储的位置
                    root->children[cindex]=new Trie();
                }
                root = root->children[cindex];
            }
            root->isWord=true;
        }
        
        /* Search if the word is in the trie*/
        bool search(string word){
            Trie* root = this;//根结点为调用函数的
            for (int i = 0; i < word.size(); i++)
            {
                /* code */
                int cindex = word[i]-'a';
                if(root->children[cindex]==NULL){//word[i]-'a'表示当前字符 在数组结点中应该存储的位置
                    return false; 
                }
                root = root->children[cindex];
            }
            return root->isWord;
        }

        /* Return if there is any word int the trie that startwith the given prefix*/
        bool startWith(string prefix){
            Trie* root = this;
            for (int i = 0; i < prefix.size(); i++)
            {
                /* code */
                int cindex = prefix[i]-'a';
                if(root->children[cindex]==NULL){
                    return false;
                }
                root=root->children[cindex];
            }
            return true;
        }
        public:
            Trie* children[26];
            bool isWord;
};

int main(){
    string key1="abc";
    string key2="abcd";
    string key3="bcd";
    string key4="cde";

    // Trie* root=new Trie();
    // root->insert(key1);
    // root->insert(key2);
    // root->insert(key3);
    // root->insert(key4);

    //  root->insert(key1);
    // root->insert(key2);
    // root->insert(key3);
    // root->insert(key4);
    //  cout<<root->startWith("cd")<<endl;

    Trie root;
    root.insert(key1);
    root.insert(key2);
    root.insert(key3);
    root.insert(key4);
    cout<<root.startWith("cd")<<endl;
    
    
    
    
}