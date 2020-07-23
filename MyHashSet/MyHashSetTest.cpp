#include<iostream>
#include<unordered_set>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;
int getNext(int num);

//using hashset to find duplicates
template <class Type>
bool findDuplicates(vector<Type>& keys){
    unordered_set<Type> hashset;
    for (Type key : keys)
    {
        if(hashset.count(key)>0){
            return true;
        }
        hashset.insert(key);
    }
    return false;
}
//寻找一个数组里唯一不重复的元素
int singleNumber(vector<int>& nums) {
    unordered_set<int> hashset;
    int singleNum = -1;
    for (auto num : nums)
    {
        if(hashset.count(num)<=0){
            hashset.insert(num);
        }else{
            hashset.erase(num);
        }
    }
    if(hashset.size()==1){
        auto it = hashset.begin();
        return (*it);
    }else{
        return -1;
    }
}

//求两个数组的交集
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> hashset;
    vector<int> res;
    for (auto num : nums1)
    {
        hashset.insert(num);
    }

    for (auto num : nums2)
    {
        if(hashset.count(num)>0){
            res.push_back(num);
        }
    }
    hashset.clear();
    for (auto num : res)
    {
        hashset.insert(num);
    }
    res.clear();

    for(auto it = hashset.begin();it!=hashset.end();it++){
        res.push_back(*it);
    }
    return res;
}

/*快乐数计算
输入：19
输出：true
解释：
1^2 + 9^2 = 82
8^2 + 2^2 = 68
6^2 + 8^2 = 100
1^2 + 0^2 + 0^2 = 1
*/
int getNext(int n){//获取下一个数字
    int sum =0;
    while(n>0){
        int d = n%10;
        n/=10;
        sum+=d*d;
    }
    return sum;
}

bool isHappy(int n) {
    unordered_set<int> hashset;
    while(n!=1&&hashset.count(n)<=0){//如果发现是快乐数或者 发现一个结点重复出现则跳出
        hashset.insert(n);
        n = getNext(n);
    }
    return n==1;
}

bool isHappyByPointer(int n){
    int slowPointer = n;
    int fastPointer = getNext(n);
    while(slowPointer!=fastPointer){
        slowPointer = getNext(slowPointer);
        fastPointer = getNext(fastPointer);
    }
    return slowPointer==1;
}
/*给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
    你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。
    给定 nums = [2, 7, 11, 15], target = 9
    因为 nums[0] + nums[1] = 2 + 7 = 9
    所以返回 [0, 1]
    */
vector<int> twoSum(vector<int>& nums, int target) {
    unordered_set<int> resHashSet;
    vector<int> res;

    
    for (int i = 0; i < nums.size(); i++)
    {
        /* code */
        int another_num = target-nums[i];
        for (int j = 0; j < nums.size(); j++)
            {
                /* code */
                if(nums[j]==another_num&&i!=j){
                    resHashSet.insert(j);
                    resHashSet.insert(i);
                }
        }
    }
    
    
    for (auto it = resHashSet.begin(); it != resHashSet.end(); it++)
    {
        /* code */
        res.push_back(*it);
    }
    
    
    return res;
}

/*
同构字符串
给定两个字符串 s 和 t，判断它们是否是同构的。

如果 s 中的字符可以被替换得到 t ，那么这两个字符串是同构的。

所有出现的字符都必须用另一个字符替换，同时保留字符的顺序。两个字符不能映射到同一个字符上，但字符可以映射自己本身。

示例 1:

输入: s = "egg", t = "add"
输出: true
示例 2:

输入: s = "foo", t = "bar"
输出: false
示例 3:

输入: s = "paper", t = "title"
输出: true
说明:
你可以假设 s 和 t 具有相同的长度。
abdca
cefgc
构建两个映射 初始化value=0 
每个映射中为字符==index+1
同样的字符映射值相同
*/
bool isIsomorphic(string s, string t) {
    int slen = s.length();
    int tlen = t.length();
    int* smap = new int[128];
    int* tmap = new int[128];
    if(slen!=tlen){
        return false;
    }else{
        for (int i = 0; i < slen; i++)
        {
            /* code */
            char c_s=s[i];
            char c_t=t[i];
            int sValue = smap[c_s];
            int tValue = smap[c_t];
            if(sValue!=tValue){
                return false;
            }else{
                if(sValue==0){//如果未修改过 则赋值映射
                    smap[c_s]=i+1;
                    tmap[c_t]=i+1;
                }
            }
           
        }
        return true;
        
    }

}
//return subIsIsomorphic(s,t)&&subIsIsomorphic(t,s);
bool subIsIsomorphic(string s, string t) {
    int slen = s.length();
    int tlen = t.length();
    unordered_map<char,char> hashmap;
    
    if(slen!=tlen){
        return false;
    }else{
        for (int i = 0; i < slen; i++)
        {
           char c_s=s[i];
           char c_t=t[i];
           if(hashmap.count(c_s)>0){
               if(hashmap[c_s]!=c_t){
                   return false;
               }
           }else{
               hashmap[c_s]=c_t;
           }
           
        }
        return true;
        
    }

}

int main(){
    // cout<<"git merge dev_test branch to master branch"<<endl;
    // //initialize a has set
    // unordered_set<int> hashset;
    // //insert a new key
    // hashset.insert(3);
    // hashset.insert(2);
    // hashset.insert(1);
    // //delete a key
    // hashset.erase(2);
    // //check if the key is in the hashset
    // if(hashset.count(2)<=0){
    //     cout<<"key 2 is not in the hashset."<<endl;
    // }
    // //get the size of hashset
    // cout<<"this hashset size is "<<hashset.size()<<endl;

    // for (auto it = hashset.begin(); it != hashset.end(); it++)
    // {
    //     /* code */
    //     cout<<(*it)<<" ";
    // }
    // cout<<"are int the hashset"<<endl;

    // hashset.clear();
    // if(hashset.empty()){
    //     cout<<"hashset is empty"<<endl;
    // }
    // int sum = getNext(1234);
    // cout<<sum<<endl;
    string s = "ab";
    string t = "aa";
    bool flag =  isIsomorphicT(s,t)&&isIsomorphicT(t,s);
    cout<<flag<<endl;
    return 0;
}

