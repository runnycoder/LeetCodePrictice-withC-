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



//Manacher算法计算字符串的最大回文字串

//字符串预处理 将字符串(size = n)处理成 #a#b#c# 的这种形式 以# 开头和结尾 字符中间用#填充
//这样保证的是新字符串字符的个数是奇数个(size = n+ (n-1)+2 = 2n+1)个 方便利用回文字符串的对称性
//还有一条重要的性质 newIndex/2 =oldIndex 即 新字符串char<a>的下标是原始字符串char<a>下标的2倍
string preProcessStr(string sentence){
    int length = sentence.size();
    if(length==0){
        return "";
    }
    string newStr = "";
    for(int i=0;i<length;i++){
        newStr+='#';
        newStr+=sentence[i];
    }
    newStr+='#';
    return newStr;
}
//manacher算法 计算字符串中的最大回文子串
string maxPalindromeCalculateByManacherAlgorithm(string sentence){
    int s_len = sentence.size();
    if(s_len<2){
        return sentence;
    }
    //预处理字符串
    string fix_str = preProcessStr(sentence);
    int fix_len = 2*s_len+1;//预处理之后字符串的长度

    int maxLen = 1;//最大回文子串的长度
    int start = 0;//最大回文子串的开始索引

    vector<int> p(fix_len,0);//定义新字符串索引对应的p数组 p[i]代表 以i为中心向两边扩散的最大扩散长度spread 
    int maxRight = 0;//扫描过程中 最右边能达到的最大索引
    int center = 0; //扫描过程中 回文子串的中心索引

    for (int i = 0; i < fix_len; i++)
    {
        /* code */
        //i<maxRight的时候才可以利用中心对称性质 寻找镜像 i>=maxRight的时候只能进行中心扩展了
        if(i<maxRight){
            int mirror = center*2-i;//mirror是i关于 center的镜像坐标 center-mirror=i-center
            /*由于回文字符串的对称性质 我们可以利用i关于center对称的镜像坐标来求p[i] 因为我们是从左到右扫描的
            maxRight和center也在不断的更新
            1 当p[mirror]<maxRright p[i]=p[mirror]=d
            2 当p[mirror]=maxRright 需要从左侧的 i-p[mirror]-1和maxRright+1 继续向两侧扩散对比寻找 最大扩展长度
            3 当p[mirror]>maxRright 时p[i]=maxRright-i 简单证明
            p[i]>maxRight-i =>关于i对称 S[i-d-1]=S[maxRright+1] 
            =>关于center对称 S[i-d-1]=S[mirror+d+1] =>关于mirror对称 S[mirror+d+1]=S[mirror-d-1]
            => S[maxRight+1]=S[mirror-d-1] 这说明关于center的最大回文长度是可以加1 maxRight=maxRright+1
            这与现在maxRight所在的位置矛盾 所以 p[i]最大值也就是maxRright-i
            */
           p[i]=min(maxRight-i,p[mirror]);//综上所述 我们取p[i]的最小值 然后在这个最小值的基础上向两侧扩展
    
        }
        //定义开始中心扩散的左右端点
        int left = i-p[i]-1;
        int right = i+p[i]+1;
        while(left>=0&&right<fix_len&&fix_str[left]==fix_str[right]){//开始扫描 指针不越界 对称字符相等继续循环
            left--;
            right++;
            p[i]++;
        }

        //maxRight是向右侧扩展最大的索引 更新maxRight center;
        //maxRight越大越容易进入i<maxRight的条件判断 也就是说可以更多的利用已经有的回文字符串信息
        if(i+p[i]>maxRight){
            maxRight = i+p[i];
            center = i;
        }

        //更新最大回文字符串长度
        if(p[i]>maxLen){
            maxLen = p[i];
            start = (i - maxLen)/2;//原始字符串中 最大回文字串的起始坐标 因为字符串是填充过的 原有字符串的坐标翻倍了
        }
    }
    return sentence.substr(start,start+maxLen);//包含头 不包含尾
}




int main () {
    string s = "abababacde";
    string fixStr = maxPalindromeCalculateByManacherAlgorithm(s);
    cout<<fixStr<<endl;
	  return 0;
}