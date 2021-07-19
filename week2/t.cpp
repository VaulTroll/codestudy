#include<iostream>

using namespace std;

void swap(int &a, int &b){
    int temp;
    temp=a;
    a=b;
    b=temp;
}

void quick(int *arr, int left, int right){
    int pivot=left;
    int start = left+1;
    int end = right;
    int arr1[right]={};
    while(start!=end){
        while(arr[start]<arr[pivot]){ arr1[]
        }
        
        

    }
    arr1[start]=pivot;



}
int main(){

    int array[5]={1,5,4,2,3};
    insert(array,5);
    int n=5;
    for(int k=0; k<n;k++){
        cout<<array[k]<<",";
    }
    



}
