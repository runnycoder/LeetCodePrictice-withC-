#include<iostream>
#include<unordered_map>

using namespace std;

int main () {
      //unordered_map是使用hash表的形式存储数据  根据键值计算出hash值 hash%bucket_count()=r
      //这个余数就是key对应桶的序号 hash值相同的放在一个桶里 处理冲突的方法是开链法(seperate chaining)
      //每个桶对应一个链表  出现冲突之后键值对以(头插法)插入对应桶中 结点的数据结构 first对应key second对应value 
	  unordered_map<string,string> mymap;
      mymap.insert(make_pair("Australia","Canberra"));
      mymap.insert(make_pair("U.S","Washington"));
      mymap.insert(make_pair("France","Paris"));
      mymap.insert(make_pair("Paris","Paris"));

      mymap.insert(make_pair("Paris1","Paris"));
      mymap.insert(make_pair("Paris2","Paris"));
      mymap.insert(make_pair("Paris3","Paris"));
      mymap.insert(make_pair("Paris4","Paris"));


      //key hash值计算
      hash<string> h;

      size_t Australia = h("Australia")%11;
	  cout<<"Australia = "<< Australia << endl;

      size_t US = h("U.S")%11;
	  cout<<"U.S = "<< US << endl;

      size_t France = h("France")%11;
	  cout<<"France = "<< France << endl;

      size_t Paris = h("Paris")%11;
	  cout<<"Paris = "<< Paris << endl;

	  size_t Paris1 = h("Paris1")%11;
	  cout<<"Paris1 = "<< Paris1 << endl;

      size_t Paris2 = h("Paris2")%11;
	  cout<<"Paris2 = "<< Paris2 << endl;

      size_t Paris3 = h("Paris3")%11;
	  cout<<"Paris3 = "<< Paris3 << endl;

      size_t Paris4 = h("Paris4")%11;
	  cout<<"Paris4 = "<< Paris4 << endl;

      string s = "Paris";
    
      //key hash值计算
	  cout << "mymap contains:"<<endl;
      
      int cnt = 0;
	  for ( auto it = mymap.cbegin(); it != mymap.cend(); ++it ){
           cout <<" "<< it->first << ":" << it->second<<endl;  // cannot modify *it
           cnt++;
      }
      
	     
	  cout << endl;
      cout << cnt <<endl;
      cout<<"桶数量："<<mymap.bucket_count( )<<endl;
      cout<<"负载因子："<<mymap.load_factor( )<<endl;
	  cout << "mymap's buckets contain:\n";
	  for ( unsigned i = 0; i < mymap.bucket_count(); ++i) {
	      cout << "bucket #" << i << " contains:";
	      for ( auto local_it = mymap.cbegin(i); local_it!= mymap.cend(i); ++local_it )
	          cout << " " << local_it->first << ":" << local_it->second;
	      cout << endl;
	  }
    
	  return 0;
}