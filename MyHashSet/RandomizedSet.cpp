#include<iostream>
#include<vector>
#include<unordered_map>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
    常数时间插入、删除和获取随机元素
设计一个支持在平均 时间复杂度 O(1) 下，执行以下操作的数据结构。

insert(val)：当元素 val 不存在时，向集合中插入该项。
remove(val)：元素 val 存在时，从集合中移除该项。
getRandom：随机返回现有集合中的一项。每个元素应该有相同的概率被返回。
示例 :

// 初始化一个空的集合。
RandomizedSet randomSet = new RandomizedSet();

// 向集合中插入 1 。返回 true 表示 1 被成功地插入。
randomSet.insert(1);

// 返回 false ，表示集合中不存在 2 。
randomSet.remove(2);

// 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
randomSet.insert(2);

// getRandom 应随机返回 1 或 2 。
randomSet.getRandom();

// 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
randomSet.remove(1);

// 2 已在集合中，所以返回 false 。
randomSet.insert(2);

// 由于 2 是集合中唯一的数字，getRandom 总是返回 2 。
randomSet.getRandom();
*/

/*
    思路：O(1)级别的插入删除肯定要用哈希表 问题在于随机返回一个元素
    哈希表属于无序容器 无序容器的迭代器不支持随机访问 随机访问一定要用到支持随机访问的迭代器
    支持随机访问的迭代器必须是管理连续内存的容器 常见的有 vector deque C-staying array
    所以解决方案是两者都用 vector存储插入的元素 hashmap存储 元素和元素对应下标的映射 
    插入可以做到O(1) 问题是删除 删除只能从尾部删除 将被删除的元素换到尾部然后再删除 并更新原队尾元素的下标即可
*/
class RandomizedSet {
public:
    /** Initialize your data structure here. */
    vector<int> arrays;
    unordered_map<int,int> hashmap;
    RandomizedSet() {

    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if(hashmap.count(val)>0){
            return false;
        }else{
            arrays.push_back(val);
            hashmap[val]=arrays.size()-1;
            return true;
        } 
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if(hashmap.count(val)>0){
            int index = hashmap[val];
            int rear_index = arrays.size()-1;
            hashmap[arrays[rear_index]]=index;//更新原队尾元素的映射
            swap(arrays[index],arrays[rear_index]);//和队尾元素交换位置
            arrays.pop_back();//删除队尾元素
            hashmap.erase(val);//删除队尾元素字典的映射
            return true;
        }else{
            return false;
        }
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        // srand((int)time(0));
        int index = arrays.empty()?0:rand()%arrays.size();
        return  arrays[index];
    }
};

int main(){
    return 0;
}
