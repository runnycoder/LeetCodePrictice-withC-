#include<iostream>
using namespace std;


class Node{
        
    public:
        int key;
        int value;
        Node* next;
        Node(){
            next = NULL;
        }
};

class Bucket{
    private:
        Node* head;
    public:
        Bucket(){
            head = new Node();
        }
        int search(int key){
            Node* thead = head->next;
            if(thead==NULL){
                return -1;
            }else{
                while(thead){
                    if(thead->key==key){
                        return thead->value;
                    }
                    thead = thead->next;
                }
                return -1;
            }
        }
        void insert(int key,int value){
            Node* thead = head->next;
            while(thead){//查询结点 如果找到则更新值 没找到则用头插法插入
                if(thead->key==key){
                    thead->value=value;
                    return;
                }
                thead = thead->next;
            }

            Node* temp = new Node();
            temp->key=key;
            temp->value=value;
            temp->next = head->next;
            head->next = temp;
        }

        int deleteKey(int key){
            Node* thead = head->next;
            Node* pre = head;
            if(thead==NULL){
                return -1;
            }else{
                while(thead){
                    if(thead->key==key){
                        int value = thead->value;
                        pre->next = thead->next;
                        delete thead;
                        thead = NULL;
                        return value;
                    }
                    pre = thead;
                    thead = thead->next;
                }
            }
            return -1;
        }
};

class MyHashMap {
private:
    const int bucketNum = 2069;
    Bucket* buckets = new Bucket[bucketNum];

public:
    /** Initialize your data structure here. */
    MyHashMap() {

    }
    
    int hash(int number){
        return number%bucketNum;
    }

    /** value will always be non-negative. */
    void put(int key, int value) {
        int index = hash(key);
        cout<<"put key="<<key<<" hash key="<<index<<endl;
        buckets[index].insert(key,value);

    }
    
    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        int index = hash(key);
        return buckets[index].search(key);
    }
    
    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        int index = hash(key);
        buckets[index].deleteKey(key);
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

int main(){
    // Bucket bucket;
    // bucket.insert(11,11);
    // bucket.insert(12,13);
    // bucket.insert(13,14);
    // cout<<bucket.search(11)<<endl;
    // cout<<bucket.search(12)<<endl;
    // cout<<bucket.search(13)<<endl;

    MyHashMap* map = new MyHashMap();
    for (int i = 1; i <= 10000; i++)
    {
        /* code */
        cout<<i<<endl;
         map->put(i,i);
    }

    for (int j = 1; j <= 10000; j++)
    {
        /* code */
         cout<<"get(i)="<<map->get(j)<<endl;
    }
    
    map->put(1,1);
    map->put(2,2);

    cout<<map->get(1)<<endl;
    cout<<map->get(3)<<endl;
    map->put(2,1);
    cout<<map->get(2)<<endl;
    map->remove(2);
    cout<<map->get(2)<<endl;
    return 0;
}