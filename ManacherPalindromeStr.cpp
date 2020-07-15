#include<iostream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

//字符串预处理 用#填充字符串空隙 以#开头和结尾 #字符的数目为 n-1+2 总长度为2n+1
string preProcess(string sentence){
    int length = sentence.size();
    if(!length){
        return "";
    }
    char end = '#';
    string newStr;
    for(int i=0;i<length;i++){
        newStr.push_back('#');
        newStr.push_back(sentence[i]);
    }
    newStr.push_back(end);
    return newStr;
}
//中心扩展的方式计算 以center为中心的回文字符串 左右两侧的扩展长度
int centerSpread(string sentence,int center){
    int len = sentence.size();
    int i = center-1;
    int j = center+1;
    int spread = 0;
    while(i>=0&&j<len&&sentence[i]==sentence[j]){
        i--;
        j++;
        spread++;
    }
    return spread;
}
//计算给定字符串中最长的回文子串 利用回文字符串的对称性质 遍历每一个字符i 
//以i为中心向两边扩散计算最大的扩散距离spread
string normalPalindromeCalculate(string sentence){
    int length = sentence.size();
    if(length<2){
        return sentence;
    }
    string fixStr = preProcess(sentence);//预处理原始字符串
    int fixStrLen=2*length+1;//处理后的字符串长度
    int maxLen = 1;//回文字符串最大
    int start = 0;//回文字符串开头索引
    for(int i =0;i<fixStrLen;i++){
        int spreadLen = centerSpread(fixStr,i);
        if(spreadLen>maxLen){
            maxLen = spreadLen;
            start = (i-spreadLen)/2;//i-spreadLen为fixStr的回文字符串开始索引 /2才是原始字符串的开始索引
        }
    }
    cout<<"maxLen="<<maxLen<<endl;
    return sentence.substr(start,start+maxLen);//substr 包含头也包含尾
}


/*
Manacher最大回文子串算法实现
*/
class Solution{
    public:
        //字符串预处理 用#填充字符串空隙 以#开头和结尾 #字符的数目为 n-1+2 总长度为2n+1
        string preProcess(string sentence){
            int length = sentence.size();
            if(!length){
                return "";
            }
            char end = '#';
            string newStr;
            for(int i=0;i<length;i++){
                newStr.push_back('#');
                newStr.push_back(sentence[i]);
            }
            newStr.push_back(end);
            return newStr;
        }
        //Manacher最大回文字串计算
        string manacherPalindromeCalculate(string sentense){
            int len = sentense.size();
            if(len<2){
                return sentense;
            }
            string fixStr = preProcess(sentense);//获取预处理之后的字符串
            int fixLen = 2*len+1;

            //数组p[]记录扫描过的回文子串信息 p[i]代表以i为中心的最大扩散距离 
            //也就是原始字符串中以i为中心回文字串的长度
            vector<int> p(fixLen,0);//初始化为0
            int maxRight = 0;//扫描过程中 回文子串右侧可扩展的最大索引
            int center = 0;//扫描过程中 回文子串中心对称索引值

            //当前最大扩散步数 其值等于原始字符串最大回文子串长度
            int maxLen =1;
            //原始最大回文字串 开始索引
            int start =0;
            for(int i=0;i<fixLen;i++){
                if(i<maxRight){
                    int mirror = 2*center-i;//i 关于center堆成的索引mirror
                    p[i] = min(maxRight-1,p[mirror]);//Manacher算法的关键
                }
                //下一次扩散的左右起点，能扩散的步数直接加到p[i]中
                int left = i -(p[i]+1);
                int right = i+(p[i]+1);

                while(left>=0&&right<fixLen&&fixStr[left]==fixStr[right]){
                    p[i]++;
                    left--;
                    right++;
                }

                //maxRight是遍历过i的i+p[i]的最大者
                // 如果 maxRight 的值越大，进入上面 i < maxRight 的判断的可能性就越大，这样就可以重复利用之前判断过的回文信息了
                if(i+p[i] > maxRight){
                    maxRight = i+p[i];
                    center = i;
                }

                if(p[i]>maxLen){
                    maxLen=p[i];
                    start = (i-maxLen)/2;
                }
            }
            cout<<"maxLen="<<maxLen<<endl;
            return sentense.substr(start,start+maxLen);
        }
};
 

int main(){
    string s = "baab";
    // s = "ababa";
    // s = s.substr(0,3);
    // s = preProcess(s);
    // cout<<s<<endl;
    // s = normalPalindromeCalculate(s);
    Solution solve;
    s = solve.manacherPalindromeCalculate(s);
    cout<<s<<endl;
    return 0;
}