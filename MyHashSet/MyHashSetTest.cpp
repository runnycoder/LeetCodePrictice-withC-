#include<iostream>
#include<unordered_set>
#include<vector>
using namespace std;
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