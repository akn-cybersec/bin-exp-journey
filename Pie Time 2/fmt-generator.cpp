#include<iostream>
using namespace std;

int main(){
    int start, end;
    cout<<"Enter the start: ";
    cin>>start;
    cout<<"Enter the end: ";
    cin>>end;
    for (int i = start; i<=end; i++){
        cout<<"|"<<i<<"=%"<<i<<"$p";
    }
    return 0;
}