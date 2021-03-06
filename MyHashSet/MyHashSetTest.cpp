#include<iostream>
#include<unordered_set>
#include<vector>
#include<string>
#include<unordered_map>
#include<queue>
#include<algorithm>
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

 /*
    字母异位词分组
    给定一个字符串数组，将字母异位词组合在一起。字母异位词指字母相同，但排列不同的字符串。

    示例:

    输入: ["eat", "tea", "tan", "ate", "nat", "bat"]
    输出:
    [
    ["ate","eat","tea"],
    ["nat","tan"],
    ["bat"]
    ]
    说明：

    所有输入均为小写字母。
    不考虑答案输出的顺序。

    思路一：对字符串进行排序 排序结果相同的字符串是同一个异位词组
    思路二：统计每个字符串中字符出现的次数 字符出现次数相同的字符串是同一个异位词组
 */

vector<vector<string> > groupAnagrams(vector<string>& strs) {
    //思路二实现
    int strs_size = strs.size();
    vector<vector<string> > res;
    unordered_map<string,vector<string> > hashmap;
    for (int i = 0; i < strs_size; i++)
    {
        /* code */
        string str = strs[i];
        int str_size = str.size();
        int* chars_index = new int[26]();
        for (int t = 0; t < 26; t++)
        {
            /* code */
            chars_index[t]=0;
        }
        
        for (int j = 0; j < str_size; j++)
        {
            /* code */
            char ch = str[j];
            int char_index = ch -'a';
            int char_index_val = chars_index[char_index];
            chars_index[char_index] = char_index_val+1;
        }
        string key;
        for (int k = 0; k < 26; k++)
        {
            /* code */
            key+="#";
            key+=chars_index[k];
        }
        if(hashmap.count(key)){
            hashmap[key].push_back(str);
        }else{
            hashmap[key] = vector<string>{str};
        }
    }

    for (unordered_map<string,vector<string> >::iterator it = hashmap.begin();
         it != hashmap.end(); it++)
    {
        /* code */
        // if(it->second.size()>0){
            res.push_back(it->second);
        // }
    }
    

    return res;
}

/*
    判断一个 9x9 的数独是否有效。只需要根据以下规则，验证已经填入的数字是否有效即可。

    数字 1-9 在每一行只能出现一次。
    数字 1-9 在每一列只能出现一次。
    数字 1-9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。

    数独部分空格内已填入了数字，空白格用 '.' 表示。

示例 1:

输入:
[
  ["5","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
输出: true
示例 2:

输入:
[
  ["8","3",".",".","7",".",".",".","."],
  ["6",".",".","1","9","5",".",".","."],
  [".","9","8",".",".",".",".","6","."],
  ["8",".",".",".","6",".",".",".","3"],
  ["4",".",".","8",".","3",".",".","1"],
  ["7",".",".",".","2",".",".",".","6"],
  [".","6",".",".",".",".","2","8","."],
  [".",".",".","4","1","9",".",".","5"],
  [".",".",".",".","8",".",".","7","9"]
]
    输出: false
    解释: 除了第一行的第一个数字从 5 改为 8 以外，空格内其他数字均与 示例1 相同。
        但由于位于左上角的 3x3 宫内有两个 8 存在, 因此这个数独是无效的。
    说明:

    一个有效的数独（部分已被填充）不一定是可解的。
    只需要根据以上规则，验证已经填入的数字是否有效即可。
    给定数独序列只包含数字 1-9 和字符 '.' 。
    给定数独永远是 9x9 形式的。

    子数独编号：可以使用 box_index = (row / 3) * 3 + columns / 3，其中 / 是整数除法。
    
*/

bool isValidSudoku(vector<vector<char>>& board) {
        int row_size = board.size();
        int col_size = board[0].size();
        vector<unordered_set<char>* > boxes;
        boxes.resize(9);
        for (int i = 0; i < 9; i++)
        {
            /* code */
            boxes[i] = new unordered_set<char>();
        }
        

        for (int i = 0; i < row_size; i++)
        {
            /* code */
            unordered_set<char> row_set;//第i行重复判断
            unordered_set<char> col_set;//第i列重复判断
            for (int j = 0; j < col_size; j++)
            {
                /* code */
                //行列是否有重复值校验
                char row_value = board[i][j];//行值
                char col_value = board[j][i];//列值
                if('.'!=row_value && row_set.count(row_value)){
                    return false;
                }
                if('.'!=col_value && col_set.count(col_value)>0){
                    return false;
                }
                col_set.insert(col_value);
                row_set.insert(row_value);

                //子矩阵是否有重复值校验
                int boxe_num = (i/3)*3+j/3;
                if('.'!=row_value && boxes[boxe_num]->count(row_value)>0){
                    return false;
                }else{
                    boxes[boxe_num]->insert(row_value);
                }
            }
            row_set.clear();
            col_set.clear();
        }
        return true;
}

/*
   宝石与石头
    给定字符串J 代表石头中宝石的类型，和字符串 S代表你拥有的石头。 S 中每个字符代表了一种你拥有的石头的类型，你想知道你拥有的石头中有多少是宝石。

    J 中的字母不重复，J 和 S中的所有字符都是字母。字母区分大小写，因此"a"和"A"是不同类型的石头。

    示例 1:

    输入: J = "aA", S = "aAAbbbb"
    输出: 3
    示例 2:

    输入: J = "z", S = "ZZ"
    输出: 0
    注意:

    S 和 J 最多含有50个字母。
    J 中的字符不重复。 
*/

int numJewelsInStones(string J, string S) {
    unordered_set<char> hashset;
    int count = 0;
    for (auto ch : J)
    { 
        hashset.insert(ch);  
    }

    for (auto ch : S)
    {
        if(hashset.count(ch)>0){
            count++;
        }
    }
    return count;
    
    
}

/*
无重复字符的最长子串
    给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

    示例 1:

    输入: "abcabcbb"
    输出: 3 
    解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
    示例 2:

    输入: "bbbbb"
    输出: 1
    解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。
    示例 3:

    输入: "pwwkew"
    输出: 3
    解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
        请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
    https://leetcode-cn.com/problems/longest-substring-without-repeating-characters/solution/wu-zhong-fu-zi-fu-de-zui-chang-zi-chuan-by-leetc-2/
*/

int lengthOfLongestSubstring(string s) {
    int max_length = 0;
    unordered_set<char> hashset;
    int n = s.size();
    int rk= -1;//右指针的位置
    for (int i = 0; i < n; i++)
    {
        /* code */
        if(i!=0){//如果不是起始位置 
            hashset.erase(s[i-1]);//左指针右移一位 集合删除左指针前一个元素
        }
        while(rk+1<n&&hashset.count(s[rk+1])<=0){//如果rk+1没有超过界限 且rk+1位置的字符不在非重复集合中
            hashset.insert(s[rk+1]);
            rk ++;
        }
        max_length = max(max_length,rk-i+1);
    }
    return max_length;
}


/*
四数相加 II
给定四个包含整数的数组列表 A , B , C , D ,计算有多少个元组 (i, j, k, l) ，使得 A[i] + B[j] + C[k] + D[l] = 0。

为了使问题简单化，所有的 A, B, C, D 具有相同的长度 N，且 0 ≤ N ≤ 500 。所有整数的范围在 -228 到 228 - 1 之间，最终结果不会超过 231 - 1 。

例如:

输入:
A = [ 1, 2]
B = [-2,-1]
C = [-1, 2]
D = [ 0, 2]

输出:
2

解释:
两个元组如下:
1. (0, 0, 0, 1) -> A[0] + B[0] + C[0] + D[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> A[1] + B[1] + C[0] + D[0] = 2 + (-1) + (-1) + 0 = 0
*/

int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D) {
    unordered_map<int,int> hashmap;
    int res_count = 0;
    for (int i = 0; i < A.size(); i++)
    {
        /* code */
        for (int j = 0; j < B.size(); j++)
        {
            /* code */
            int sum_a_b = A[i]+B[j];
            hashmap[sum_a_b]++;
        }
        
    }

     for (int i = 0; i < C.size(); i++)
    {
        /* code */
        for (int j = 0; j < D.size(); j++)
        {
            /* code */
            int sum_c_d_negative = -(C[i]+D[j]);
            if(hashmap.count(sum_c_d_negative)>0){
                res_count+=hashmap[sum_c_d_negative];
            }
        }
        
    }
    return res_count;
}


/*
    前 K 个高频元素
给定一个非空的整数数组，返回其中出现频率前 k 高的元素。

 

示例 1:

输入: nums = [1,1,1,2,2,3], k = 2
输出: [1,2]
示例 2:

输入: nums = [1], k = 1
输出: [1]
 

提示：

你可以假设给定的 k 总是合理的，且 1 ≤ k ≤ 数组中不相同的元素的个数。
你的算法的时间复杂度必须优于 O(n log n) , n 是数组的大小。
题目数据保证答案唯一，换句话说，数组中前 k 个高频元素的集合是唯一的。
你可以按任意顺序返回答案。
*/

vector<int> topKFrequent(vector<int>& nums, int k) {

    vector<int> res;
    unordered_map<int,int> hashmap;
    for (int i = 0; i < nums.size(); i++)
    {
        /* code */
        int key = nums[i];
        hashmap[key]++;
    }
    //最大堆
    priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int> > > max_queue; 
    for (unordered_map<int,int>::iterator it = hashmap.begin(); it != hashmap.end(); it++)
    {
        /* code */
        if(max_queue.size()<k){
            max_queue.push(make_pair(it->second,it->first));
        }else{
            if(it->second>max_queue.top().first){
                max_queue.pop();
                max_queue.push(make_pair(it->second,it->first));
            }
        }
    }
    
    while (!max_queue.empty())
    {
        /* code */
        res.push_back(max_queue.top().second);
        max_queue.pop();
    }
    reverse(res.begin(),res.end());
    return res;
    
    
    
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

    // vector<int> s;
    // int k =1;
    // s.push_back(1);
    // s.push_back(0);
    // s.push_back(1);
    // s.push_back(1);
    // bool flag = containsNearbyDuplicate(s,k);
    // cout<<flag<<endl;

    // vector<string> param;
    // param.push_back("eat");
    // param.push_back("tea");
    // param.push_back("tan");

    // param.push_back("ate");
    // param.push_back("nat");
    // param.push_back("bat");

    // vector<vector<string> > res;
    // res = groupAnagrams(param);
    // for (int i = 0; i < res.size(); i++)
    // {
    //     /* code */
    //     vector<string> temp = res[i];
    //     cout<<"[";
    //     for (int j = 0; j < temp.size(); j++)
    //     {
    //         /* code */
    //         cout<<temp[j]<<",";
    //     }
    //     cout<<"],";
    // }

    int numRows=9,zone=9;//层数，每层需要的空间
    vector<vector<char>> vec(numRows, vector<char>());//初始层数，赋值
    for (int i = 0; i < numRows; i++) {
        vec[i].resize(zone);
    }

    vec[0]={'5','3','.','.','7','.','.','.','.'};
    vec[1]={'6','.','.','1','9','5','.','.','.'};
    vec[2]={'.','9','8','.','.','.','.','6','.'};
    vec[3]={'8','.','.','.','6','.','.','.','3'};
    vec[4]={'4','.','.','8','.','3','.','.','1'};
    vec[5]={'7','.','.','.','2','.','.','.','6'};
    vec[6]={'.','6','.','.','.','.','2','8','.'};
    vec[7]={'.','.','.','4','1','9','.','.','5'};
    vec[8]={'.','.','.','.','8','.','.','7','9'};
    
    bool res = isValidSudoku(vec);
    cout<<res<<endl;
    return 0;
}

