#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>

using namespace std;

/*
    设计一个支持在平均 时间复杂度 O(1) 下， 执行以下操作的数据结构。

    注意: 允许出现重复元素。

    insert(val)：向集合中插入元素 val。
    remove(val)：当 val 存在时，从集合中移除一个 val。
    getRandom：从现有集合中随机获取一个元素。每个元素被返回的概率应该与其在集合中的数量呈线性相关。
    示例:

    来源：力扣（LeetCode）
    链接：https://leetcode-cn.com/problems/insert-delete-getrandom-o1-duplicates-allowed
    著作权归领扣网络所有。商业转载请联系官方授权，非商业转载请注明出处。
*/
class RandomizedCollection{
public:
    vector<int> arrays;
    unordered_map<int,unordered_set<int> > dict;//使用unordered_set是因为vector不支持删除指定元素 只能通过索引删除
    /** Initialize your data structure here. */
    RandomizedCollection() {

    }

    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        arrays.push_back(val);
        dict[val].insert(arrays.size()-1);//将插入val index放入映射的集合中
        return dict[val].size()==1;
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if(dict.count(val)>0&&dict[val].size()>0){
            int val_set_size = dict[val].size();//val 对应的索引集合元素个数
            int arrays_rear_index = arrays.size()-1;//尾元素存储的index
            int rear_num = arrays[arrays_rear_index];//arrays尾元素的值
            if(rear_num==val){
                dict[rear_num].erase(arrays_rear_index);
                arrays.pop_back();
            }else {
                int val_index = *dict[val].begin();//要删除元素的索引
                dict[rear_num].erase(arrays_rear_index);//更新尾部元素的索引集合
                dict[rear_num].insert(val_index);
                swap(arrays[val_index],arrays[arrays_rear_index]);
                arrays.pop_back();//删除元素
                dict[val].erase(val_index);//更新删除元素的索引集合
            }

            if(dict[val].empty()){
                dict.erase(val);
            }
            // if(arrays[val_index]!=arrays[rear_num]){//要交换的不是同一个元素
            //     dict[arrays[arrays_rear_index]].push_back(val_index);//更新交换后元素的索引集合
            //     swap(arrays[val_index],arrays[arrays_rear_index]);//交换删除元素到尾部
            // }
            // arrays.pop_back();//删除元素
            // dict[val].pop_back();//删除val元素 在字典映射集合的index

            return true;
        }else{
            return false;
        }
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        int pos = arrays.empty()?0:rand()%arrays.size();
        return arrays[pos];
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

int main(){
    RandomizedCollection randomizedCollection;
    // randomizedCollection.insert(10);
    // randomizedCollection.insert(10);
    // randomizedCollection.insert(20);
    // randomizedCollection.insert(20);
    // randomizedCollection.insert(30);
    // randomizedCollection.insert(30);

    // randomizedCollection.remove(10);
    // randomizedCollection.remove(20);
    // randomizedCollection.remove(20);
    // randomizedCollection.remove(10);
    // randomizedCollection.remove(30);

    // randomizedCollection.insert(40);
    // randomizedCollection.remove(30);
    // randomizedCollection.remove(30);

    randomizedCollection.insert(9);
    randomizedCollection.insert(9);
    randomizedCollection.insert(1);
    randomizedCollection.insert(1);
    randomizedCollection.insert(2);
    randomizedCollection.insert(1);
    randomizedCollection.insert(1);

    randomizedCollection.remove(2);
    randomizedCollection.remove(1);
    randomizedCollection.remove(1);
    randomizedCollection.insert(9);
    randomizedCollection.remove(1);

    // randomizedCollection.insert(40);
    // randomizedCollection.remove(30);
    // randomizedCollection.remove(30);
    return 0;
}