#include<iostream>
#include<unordered_set>
#include<vector>
using namespace std;
int getNext(int num);
int main(){
    cout<<"git merge dev_test branch to master branch"<<endl;
    //initialize a has set
    unordered_set<int> hashset;
    //insert a new key
    hashset.insert(3);
    hashset.insert(2);
    hashset.insert(1);
    //delete a key
    hashset.erase(2);
    //check if the key is in the hashset
    if(hashset.count(2)<=0){
        cout<<"key 2 is not in the hashset."<<endl;
    }
    //get the size of hashset
    cout<<"this hashset size is "<<hashset.size()<<endl;

    for (auto it = hashset.begin(); it != hashset.end(); it++)
    {
        /* code */
        cout<<(*it)<<" ";
    }
    cout<<"are int the hashset"<<endl;

    hashset.clear();
    if(hashset.empty()){
        cout<<"hashset is empty"<<endl;
    }
    int sum = getNext(1234);
    cout<<sum<<endl;
    return 0;
}

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



