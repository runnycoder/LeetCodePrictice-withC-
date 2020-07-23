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

/*
两个列表的最小索引总和
假设Andy和Doris想在晚餐时选择一家餐厅，并且他们都有一个表示最喜爱餐厅的列表，每个餐厅的名字用字符串表示。

你需要帮助他们用最少的索引和找出他们共同喜爱的餐厅。 如果答案不止一个，则输出所有答案并且不考虑顺序。 你可以假设总是存在一个答案。

示例 1:

输入:
["Shogun", "Tapioca Express", "Burger King", "KFC"]
["Piatti", "The Grill at Torrey Pines", "Hungry Hunter Steakhouse", "Shogun"]
输出: ["Shogun"]
解释: 他们唯一共同喜爱的餐厅是“Shogun”。
*/
vector<string> findRestaurant(vector<string>& list1, vector<string>& list2) {
     std::hash<string> hash_str;
    vector<string> res;
    unordered_set<long long> hashset;
    unordered_map<long long,int> hashmap;
    long long hash_key;
    int MIN_INDEX = 99999;
    for (int i = 0; i < list1.size(); i++)
    {
        /* code */
        hash_key = hash_str(list1[i]);
        hashmap[hash_key]=i;
    }
    for (int i = 0; i < list2.size(); i++)
    {
        /* code */
        hash_key = hash_str(list2[i]);
        
        if(hashmap.count(hash_key)>0){
            int hash_value = hashmap[hash_key];
            if(hash_value+i<MIN_INDEX){
                res.clear();
                MIN_INDEX=hash_value+i;
                res.push_back(list2[i]);
            }else if(hash_value+i==MIN_INDEX){
                res.push_back(list2[i]);
            }
        }
    }
    return res;
}

/*
字符串中的第一个唯一字符
给定一个字符串，找到它的第一个不重复的字符，并返回它的索引。如果不存在，则返回 -1。
示例：

s = "leetcode"
返回 0

s = "loveleetcode"
返回 2
*/

int firstUniqChar(string s) {
    int len = s.size();
    if(0==len){
        return -1;
    }else if(1==len){
        return 0;
    }else{
        unordered_map<char,int> hashmap;
        for (auto ch : s)
        {   
            if(hashmap.count(ch)<=0){
                hashmap[ch]=1;
            }else{
                hashmap[ch]+=+1;
            }
            
        }

        for (int i = 0; i < len; i++)
        {
            /* code */
            char ch = s[i];
            if(hashmap.count(ch)>0&&hashmap[ch]==1){
                return i;
            }
        }
        return -1;
    }
}

/*
两个数组的交集 II
给定两个数组，编写一个函数来计算它们的交集。

 

示例 1：

输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2,2]
示例 2:

输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[4,9]

说明：

输出结果中每个元素出现的次数，应与元素在两个数组中出现次数的最小值一致。
我们可以不考虑输出结果的顺序。
进阶：

如果给定的数组已经排好序呢？你将如何优化你的算法？
如果 nums1 的大小比 nums2 小很多，哪种方法更优？
如果 nums2 的元素存储在磁盘上，磁盘内存是有限的，并且你不能一次加载所有的元素到内存中，你该怎么办
*/

vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    if(nums1.size()>nums2.size()){
        return intersect(nums2,nums1);
    }
    unordered_map<int,int> hashmap;
    vector<int> res;
    for (auto num : nums1)
    {
        if(hashmap.count(num)>0){
            ++hashmap[num];
        }else{
            hashmap[num]=1;
        }
    }

    for (auto num : nums2)
    {
        if(hashmap.count(num)>0){
            --hashmap[num];
            res.push_back(num);
            if(hashmap[num]==0){//个数减到0 说明集合2相交的元素个数和集合1中相同了 再多同样的元素会被舍弃
                hashmap.erase(num);
            }
        }
    }

    return res;
}

/*
    存在重复元素 II
    给定一个整数数组和一个整数 k，判断数组中是否存在两个不同的索引 i 和 j，使得 nums [i] = nums [j]，并且 i 和 j 的差的 绝对值 至多为 k。

    

    示例 1:

    输入: nums = [1,2,3,1], k = 3
    输出: true
    示例 2:

    输入: nums = [1,0,1,1], k = 1
    输出: true
    示例 3:

    输入: nums = [1,2,3,1,2,3], k = 2
    输出: false
*/

 bool containsNearbyDuplicate(vector<int>& nums, int k) {
     int len = nums.size();
    unordered_map<int,int> hashmap;
    for (int i = 0; i < len; i++)
    {
        /* code */
        int num = nums[i];
        if(hashmap.count(num)>0){//如果已经存在num
            if(i-hashmap[num]<=k){
                return true;
            }else{
                hashmap[num]=i;
            }
        }else{
            hashmap[num]=i;
        }
    }
    return false;
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

    //同构字符串判定测试
    // string s = "abcdef";
    // string t = "dcefgf";
    // bool flag =  subIsIsomorphic(s,t)&&subIsIsomorphic(t,s);
    // cout<<flag<<endl; 

    //["Shogun","Tapioca Express","Burger King","KFC"]
// ["KFC","Shogun","Burger King"]
    // vector<string> s ;
    // s.push_back("Shogun");
    // s.push_back("Tapioca Express");
    // s.push_back("Burger King");
    // s.push_back("KFC");
    // vector<string> t;
    // t.push_back("KFC");
    // t.push_back("Shogun");
    // t.push_back("Burger King");
    // vector<string> res = findRestaurant(s,t);
    // for (auto string: res)
    // {
    //     /* code */
    //     cout<<string<<endl;
    // }
    // string s = "leetcode";
    // int index = firstUniqChar(s);
    // cout<<index<<endl;

    vector<int> s;
    int k =1;
    s.push_back(1);
    s.push_back(0);
    s.push_back(1);
    s.push_back(1);
    bool flag = containsNearbyDuplicate(s,k);
    cout<<flag<<endl;
    return 0;
}

