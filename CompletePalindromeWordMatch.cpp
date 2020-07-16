#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<math.h>
using namespace std;

/*
回文对
给定一组唯一的单词， 找出所有不同 的索引对(i, j)，使得列表中的两个单词， words[i] + words[j] ，可拼接成回文串。

示例 1:

输入: ["abcd","dcba","lls","s","sssll"]
输出: [[0,1],[1,0],[3,2],[2,4]] 
解释: 可拼接成的回文串为 ["dcbaabcd","abcddcba","slls","llssssll"]
示例 2:

输入: ["bat","tab","cat"]
输出: [[0,1],[1,0]] 
解释: 可拼接成的回文串为 ["battab","tabbat"]
*/

/*
思路 什么样的两个字符串可以构成新的回文字符串呢 两个字符串a b只能进行拼接 ab或者ba这样的形式
1 当a.length=b.length a=b的逆序 abcd + dcba
2 当a.length<b.length 此时新构成的回文中心一定是在b中 所以b的前缀是回文字符串 剩下的后缀字符串是a的逆序
3 当a.length>b.length 此时构成的新的回文中心一定在a中 所以a的后缀是回文字符串 剩下的前缀字符串是b的逆序
*/

class Solution{
    public:

        bool isPalindromeStr(string str){//空字符串也算是回文
            int start = 0;
            int end = str.size()-1;
            while(start<end){
                if(str[start++]!=str[end--]){
                    return false;
                }
            }
            return true;
        }

        //获取字符串word所有的后缀为回文字符串的 前缀
        vector<string> allValidPrefixs(string word){
            vector<string> res;
            for (int i = 0; i < word.size(); i++)
            {
                /* code */
                string subStr = word.substr(i,word.size());
                string prefix = word.substr(0,i);
                if(isPalindromeStr(subStr)){
                    res.insert(res.end(),prefix);
                }
            }
            return res;
        }

        //获取字符串word所有的前缀为回文字符串的后缀
        vector<string> allValidSuffixs(string word){
            vector<string> res;
            for (int i = 0; i < word.size(); i++)
            {
                /* code */
                string subStr = word.substr(0,i+1);
                string suffix = word.substr(i+1,word.size());
                if(isPalindromeStr(subStr)){
                    res.insert(res.end(),suffix);
                }
            }
            return res;
        }

        vector<vector<int> > palindromePairs(vector<string> words){
            unordered_map<string,int> wordsIndexMap;//key为word value是与word可以构成回文字符串的单词索引index
            for (int i = 0; i < words.size(); i++)//初始化 word与自身可以构成回文
            {
                /* code */
                wordsIndexMap.insert(make_pair(words[i],i));
            }

            vector<vector<int> > solution;

            for (int i = 0; i < words.size(); i++)
            {
                /* code */
                string word = words[i];
                string reverseWord = "";
                reverseWord.assign(word.rbegin(),word.rend());

                unordered_map<string,int>::const_iterator got = wordsIndexMap.find(word);
                int currentWordIndex = got->second;//获取当前索引
                unordered_map<string,int>::const_iterator map_end  = wordsIndexMap.end();
                //第一种情况查找
                if(wordsIndexMap.count(reverseWord)&&
                wordsIndexMap[reverseWord]!=currentWordIndex){
                    vector<int> temp;
                    temp.push_back(currentWordIndex);
                    temp.push_back(wordsIndexMap[reverseWord]);
                    solution.push_back(temp);
                }

                for(string prefix: allValidPrefixs(word)){
                    string reversePrefix = "";
                    reversePrefix.assign(prefix.rbegin(),prefix.rend());
                    if(wordsIndexMap.count(reversePrefix)){
                        vector<int> temp;
                        temp.push_back(currentWordIndex);
                        temp.push_back(wordsIndexMap[reversePrefix]);
                        solution.push_back(temp);
                    }
                }

                for(string suffix: allValidSuffixs(word)){
                    string reverseSuffix = "";
                    reverseSuffix.assign(suffix.rbegin(),suffix.rend());
                    if(wordsIndexMap.count(reverseSuffix)){
                        vector<int> temp;
                        temp.push_back(wordsIndexMap[reverseSuffix]);
                        temp.push_back(currentWordIndex);
                        solution.push_back(temp);
                    }
                }

            }
            return solution;
            
        }

};

// class Solution2 {
// public:
//     bool isPalin(string& str)
//     {
//         for(int i = 0; i < str.size()/2; i++)
//             if(str[i] != str[str.size()-i-1]) return false;
//         return true;
//     }
    
//     vector<vector<int>> palindromePairs(vector<string>& words) {
//         unordered_map<string, int> hash;
//         vector<vector<int>> result;
//         for(int i =0; i< words.size(); i++) hash[words[i]] = i;
//         for(int i =0; i< words.size(); i++)
//         {
//             reverse(words[i].begin(), words[i].end());
//             int len = words[i].size();
//             for(int j = 0; j<= len; j++)
//             {
//                 string left =words[i].substr(0, j), right = words[i].substr(j);
//                 if(hash.count(left) &&isPalin(right) &&hash[left]!=i)
//                     result.push_back(vector<int>{hash[left], i});
//                 if(hash.count(right) &&isPalin(left) &&hash[right]!=i && j > 0)
//                     result.push_back(vector<int>{i, hash[right]});
//             }
//         }
//         return result;
//     }

// };

int main(){
    // string s = "ab";

    // string word = "abcd";
    //             string reverseWord = "";
    //             reverseWord.assign(word.rbegin(),word.rend());
    // cout<<reverseWord<<endl;
    Solution s;
    vector<string> words(5,"");
    words[0]="abcd";
    words[1]="dcba";
    words[2]="lls";
    words[3]="s";
    words[4]="sssll";
    vector<vector<int> > res = s.palindromePairs(words);
    for (int i = 0; i < res.size(); i++)
    {
        /* code */
        vector<int> temp = res[i];
        cout<<temp[0]<<":"<<temp[1]<<endl;
    }
    
    return 0;
}