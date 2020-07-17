#include<iostream>
using namespace std;

class A{
     private:
        int a;
        int b;
     public:
        A(){
          cout<<"A is initialize"<<endl;
        }
        ~A(){
          cout<<"A is destroy"<<endl; 
        }
        void printf(){
                cout<<"a="<<a<<";b="<<b<<endl;
        }
};

int main(){
        A * list = new A[20];
        list[2].printf();
        delete list;
        return 0;
}