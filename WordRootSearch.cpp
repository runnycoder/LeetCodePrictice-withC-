#include<iostream>
#include<string>
#include<vector>
using namespace std;
class Trie{
    public:
        bool isWord;
        Trie* children[26];
        Trie(){
            isWord=false;
            for (int i = 0; i < 26; i++)
            {
                /* code */
                this->children[i]=NULL;
            }
        }
        ~Trie(){
            for (Trie* child : children)
            {
                /* code */
                if(child){
                    delete(child);
                }
            }
            
        }
   
};

class Solution{
    private:
        Trie* rootTrie;
        void addWord(string& word){
            Trie* root = rootTrie;
            for (int i = 0; i < word.size(); i++)
            {
                /* code */
                int cindex = word[i]-'a';
                if(root->children[cindex]==NULL){
                    root->children[cindex]=new Trie();
                }
                root = root->children[cindex];
            }
            root->isWord=true;//添加完毕 在最后结点标记单词结束
        }

        //返回word最短词根的下标 如果不存在返回-1
        int searchRoot(string& word){
            Trie* root = rootTrie;
            int wordSize = word.size();
            for (int i = 0; i < wordSize; i++)
            {
                /* code */
                int cindex = word[i]-'a';
                if(root==NULL||root->children[cindex]==NULL){
                    //字符匹配中断
                    return -1;
                }
                root = root->children[cindex];
                if(root->isWord==true){
                    return i;
                }
            }
            return -1;
            
        }

    public:
        Solution(){

        }
        //将sentence字符串以ch进行分割
        void split(vector<string> &words,string &sentence,char ch){
            int sentenceSize = sentence.size();
            int index=0;
            while (index<sentenceSize)
            {
                /* code */
                string tempStr = "";
                //截取每个单词
                while (index<sentenceSize&&sentence[index]!=ch)
                {
                    /* code */
                    tempStr+=sentence[index++];
                }
                words.push_back(tempStr);
                index++;
                
            }
        }

        string replaceWords(vector<string>& dict, string sentence){
            string resStr="";
            rootTrie = new Trie();
            vector<string> words;

            //将句子分割成单词
            split(words,sentence,' ');
            //对字典单词建立前缀树
            for(auto &rootStr :dict){
                addWord(rootStr); 
            }
            
            for(auto &word:words){
                int rootIndex = searchRoot(word);
                if(rootIndex==-1){//没有找到词根
                    resStr += word+" ";
                }else{
                    resStr+=word.substr(0,rootIndex+1)+" ";
                }
            }

            //去除最后的空格
            if(resStr.size()>0){
                resStr.resize(resStr.size()-1);
            }
            return resStr;

        }

};

int main(){
    Solution s;
    Solution* solution = new Solution();
    vector<string> dict ;
    dict.push_back("cat");
    dict.push_back("bat");
    dict.push_back("rat");

    string sentence = "the cattle was rattled by the battery";
    string res;
    res = solution->replaceWords(dict,sentence);
    res = s.replaceWords(dict,sentence);
    cout<<res<<endl;
    return 0;
}