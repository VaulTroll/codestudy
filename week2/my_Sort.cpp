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

void quickSort(int *arr, int left, int right){
    if (left>=right) return;
    int l = left+1;
    int r = right;
    int pivot = left; //피봇은 맨 왼쪽으로 설정
    while(l<=r){
        while(arr[l]<=arr[pivot] && l <= right){ 
            //l값이 피봇보다 작거나 같으면 통과, 맨 오른쪽 인덱스를 초과하지 않게비교 
            l++;
        }
        while(arr[r]>=arr[pivot] && r > left){  //left는 피봇이므로 비교하지 않음
            //r값이 피봇보다 크거나 같으면 통과
            r--;
        }
        if(l <= r){ // l과 r이 아직 교차하지 않았다면 둘을 스왑
            swap(arr[l],arr[r]);
        }else{ // r과 l이 교차했다면 피봇의 위치 정렬, r에 피봇보다 작은 값이 있음
            //그래서 피봇과 그 피봇보다 작은 값을 스왑해야 정렬이 됨
            swap(arr[pivot],arr[r]); 
        }
        
    }
    quickSort(arr,left, r-1); //현재 r은 피봇과 스왑되어 r에 피봇값이 들어있음
    quickSort(arr,l, right); //현재 l은 피봇+1의 인덱스임
}



void quickSelection(int *arr, int left, int right, int k){
    //퀵 정렬 후 pivot이 k라면 해당 정수, k보다 크다면 left -> pivot-1로 다시 파티션
    //k보다 작다면 pivot+1 -> right로 다시 파티션
    int l = left+1;
    int r = right;
    int pivot = left;
    while(l<=r){
        while(arr[l]<=arr[pivot] && l <= right){
            l++;
        }
        while(arr[r]>=arr[pivot] && r > left){
            r--;
        }
        if(l <= r){
            swap(arr[l],arr[r]);
        }else{
            swap(arr[pivot],arr[r]);
            pivot = r;
        }
    }
    if (pivot == k-1){ //k는 1부터 세지만 배열의 index는 0부터 시작하므로 k-1로 비교
        cout << k <<"번째 작은 정수는 " <<arr[pivot] << endl;
    }else if(pivot > k-1){
        quickSelection(arr, left, pivot-1,k);
    }else if(pivot < k-1){
        quickSelection(arr, pivot+1, right,k);
    }
}

int main(){
    int arr1[11] ={2,4,8,1,3,10,15,75,5,80,11};
    int n = sizeof(arr1)/sizeof(int);
    printArr(arr1,n);
    //selectSort(arr1,n);
    //bubbleSort(arr1,n);
    //insertSort(arr1, n);
    quickSort(arr1, 0, n-1);
    //
    cout<<"최소값, 최대값: "<< arr1[0]<<", "<<arr1[n-1]<<endl;

    //quickSelection(arr1, 0, n-1, 7);
    
    //
    //
    //printArr(arr1,n);

}
