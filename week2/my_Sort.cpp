#include<iostream>
#include<string>

using namespace std;

void swap(int &a, int &b){
    int tmp;
    tmp =a;
    a =b;
    b =tmp;
}

void printArr(int *arr, int n){
    for(int i=0; i<n; i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}

void selectSort(int *arr, int n){
    for(int i=0; i<n-1; i++){
        int min_index=i;
        for(int j=i+1; j<n; j++){
            //i보다 큰 인덱스 중 현재 최소값보다 작은 값이 있다면 위치저장
            if(arr[min_index]>arr[j]){
                min_index = j;
            }
        }
        swap(arr[i],arr[min_index]);
    }
}

void bubbleSort(int *arr, int n){
    for(int i=0; i<n-1; i++){
        // 나중에 남는 1개는 자동 정렬되어있으므로 n-1
        for(int j=0; j<n-1-i; j++){
            // j와j+1을 비교하므로 j<n-1-i -1이 없으면 오버플로우
            if (arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
            }
        }
    }
}

void insertSort(int *arr, int n){
    for(int i=1; i<n; i++){
        //맨 처음은 제외하고 시작하므로 1, 끝까지 비교하므로 n
        int tmp = arr[i];
        //현재 비교할 값 저장
        for(int j=i-1; j>=0; j--){
            //비교되는 값들은 key인덱스의 바로 전부터 0번 인덱스까지
            if(tmp<arr[j]){
                swap(arr[j],arr[j+1]);
                //key값보다 큰 값이 보이면 key값과 해당 값 swap
                //여기서 항상 j+1은 key값이 들어있게 됨
            }else{
                break;
                //하나라도 key보다 작은값을 만나면 다음 key값을 비교
            }
        }
    }
}

int main(){
    int arr1[11] ={2,4,8,1,3,10,15,75,5,80,11};
    int n = sizeof(arr1)/sizeof(int);
    //selectSort(arr1,n);
    //bubbleSort(arr1,n);
    insertSort(arr1, n);
    printArr(arr1,n);

}
