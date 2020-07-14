#include<iostream>
#include<string>
#include<vector>
using namespace std;
/*
数组中两个数的最大异或值
给定一个非空数组，数组中元素为 a0, a1, a2, … , an-1，其中 0 ≤ ai < 231 。

找到 ai 和aj 最大的异或 (XOR) 运算结果，其中0 ≤ i,  j < n 。

你能在O(n)的时间解决这个问题吗？
输入: [3, 10, 5, 25, 2, 8]

输出: 28

解释: 最大的结果是 5 ^ 25 = 28.
*/

class Trie{
    public:
        int passed;//记录经过这个结点的字符串有几个
        int ends;//记录多少个字符串以这个结点结尾
        Trie* next[2];
        Trie(){
            passed=0;
            ends=0;
            next[0]=NULL;
            next[1]=NULL;
        }
        
        //word都已经被转换成 二进制表示的字符串
        void insert(string word){
            Trie* p = this;
            for(int i=0;i<word.size();i++){
                int cindex=word[i]-'0'; 
                if(p->next[cindex]==NULL){//不存在新建结点
                    p->next[cindex]=new Trie();
                }
                ++p->passed;
                p=p->next[cindex];
            };
            ++p->ends;
        }

        int solve(string word){
            int ret=0;
            int mask = (1<<30);

            Trie* p = this;
            for(int i=0;i<word.size();i++){
                int key = word[i]-'0';
                if(p->next[!key]!=NULL){//寻找与当前位相反的进行与运算
                    ret|=mask;//与掩码做|运算 相当于保留最高位 存在相反的此位为1
                    key = !key;
                }
                mask>>=1;
                p=p->next[key];
            }
            return ret;
        }

};

class Solution{
    public:
        int findMaximumXOR(vector<int>& nums){
            Trie trie = Trie();
            vector<string> bits;
            int ans = -1;
            int N =nums.size();
            for(int i=0;i<N;++i){//将数字转换成32位的二进制数存储
                bits.push_back(bitset<31>(nums[i]).to_string());
                trie.insert(bits[i]);
            }

            for(int i=0;i<N;++i){
                ans = max(ans,trie.solve(bits[i]));
            }
            return ans;
        }
};




//按二进制输出整数
void Binarycout(int n) 
{ 
 for (int i=31;i>=0;i--) //一次取最高位。。。到最低位的数值
 { 
 cout<<((n>>i)&1); //与1相与相当于取二进制的最末位
 } 
 cout<<endl; 
}

int main(){
    int i = 16;
    cout<<hex<<i<<endl;//16进制输出
    cout<<oct<<i<<endl;//8进制输出
    return 0;
}