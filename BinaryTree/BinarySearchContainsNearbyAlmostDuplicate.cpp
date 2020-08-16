#include<iostream>
#include<vector>
#include<cmath>
#include<set>
#include<unordered_map>
using namespace std;

/*存在重复元素 III
在整数数组 nums 中，是否存在两个下标 i 和 j，使得 nums [i] 和 nums [j] 的差的绝对值小于等于 t ，且满足 i 和 j 的差的绝对值也小于等于 ķ 。

如果存在则返回 true，不存在返回 false。

 

示例 1:

输入: nums = [1,2,3,1], k = 3, t = 0
输出: true
示例 2:

输入: nums = [1,0,1,1], k = 1, t = 2
输出: true
示例 3:

输入: nums = [1,5,9,1,5,9], k = 2, t = 3
输出: false

作者：力扣 (LeetCode)
链接：https://leetcode-cn.com/leetbook/read/introduction-to-data-structure-binary-search-tree/xpffam/
来源：力扣（LeetCode）
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/
//思路 在|i-j|<k的约束下 寻找满足|nums[i]-nums[j]|<t的对 滑动窗口
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    for (int i = 0; i < nums.size(); i++)
    {
        /* code */
        for (int j = max((i-k),0) ; j < i; j++)
        {
            /* code */
            if(abs(nums[j]-nums[i])<t){
                return true;
            }
        }
        
    }
    return false;
}

// bool containsNearbyAlmostDuplicate2(vector<int>& nums, int k, int t) {
//     set<int> treeSet;
//     for (int i = 0; i < nums.size(); i++)
//     {
//         /* code */
//         //取i的后继值
//         set<int>::iterator successor_it = treeSet.upper_bound(i);


//         int successor = *treeSet.upper_bound(i);
//         if(nums[i]!=successor&&successor-nums[i]<=t){
//             return true;
//         }
//         int preSuccessor = *(treeSet.lower_bound(i)--);
//         if(preSuccessor<30000&& nums[i]!=preSuccessor&&nums[i]-preSuccessor<=t){
//             return true;
//         }
//         treeSet.insert(nums[i]);
//         if(treeSet.size()>k){
//             treeSet.erase(nums[i-k]);
//         }
//     }
//     return false;
// }
long getBucketId(long x,long w){
    return x<0?(x+1)/w-1:x/w;
}

bool containsNearbyAlmostDuplicate2(vector<int>& nums, int k, int t) {
    if(t<0) return false;
    unordered_map<long,long> map;
    long width = (long)t+1;
    for (int i = 0; i < nums.size(); i++)
    {
        /* code */
        long number = getBucketId(nums[i],width);
        if(map.count(number)>0){
            return true;
        }
        if(map.count(number-1)>0 && abs(nums[i]-map[number-1])<=t){
            return true;
        }
        if(map.count(number+1)>0 && abs(nums[i]-map[number+1])<=t){
            return true;
        }
        map[number] = (long)nums[i];
        if(i>=k){
            map.erase(getBucketId(nums[i-k],width));
        }
    }
    
    return false;
}



int main(){
    // set<int> s;
    // for (int i = 0; i < 10; i++)
    // {
    //     /* code */
    //     s.insert(i);
    // }
    // cout<<*s.upper_bound(4)<<endl;
    // cout<<*s.lower_bound(4)<<endl;

    // s.erase(3);
    // set<int>::iterator it;
    // for ( it = s.begin(); it != s.end(); it++)
    // {
    //     /* code */
    //     cout<<*it<<endl;
    // }

    vector<int> nums;
    nums.push_back(2);
    nums.push_back(1);
    // nums.push_back(3);
    // nums.push_back(1);
    bool flag = containsNearbyAlmostDuplicate2(nums,1,1);
    cout<<flag<<endl;
    // bool flag = containsNearbyAlmostDuplicate2(nums,3,0);
    // cout<<flag<<endl;

    return 0;
}