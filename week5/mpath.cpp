#include<iostream>

using namespace std;

//기본 재귀
int mpath(int arr[][20], int i, int j){
    if(i==0 && j==0){
        return arr[0][0];
    }
    else if(i==0){
        return (arr[0][j] + mpath(arr, 0, j-1)); //만약 맨 왼쪽 줄이라면 현재값 + 위쪽값(왼쪽에서 올 수는 없기에)
    }
    else if(j==0){
        return (arr[i][0] + mpath(arr, i-1, 0)); //만약 맨 윗줄이라면 현재값 + 왼쪽값(위에서 내려올 수는 없기에) 
    }
    else{ //위 혹은 왼쪽 중에서 더 큰 값을 가져와 현재 값을 더해줌
        return (arr[i][j] + max(mpath(arr, i-1, j), mpath(arr, i, j-1)));
    }
}

//
int mmpath(int arr[][20], int i, int j, int L[][20]){
    if(L[i][j] != 0){
        return L[i][j]; //미리 구해져 있는 값
    }
    if(i==0 && j==0){
        L[0][0] = arr[0][0];
    }
    else if(i==0){
        L[0][j] = (arr[0][j] + mmpath(arr, 0, j-1, L)); 
    }
    else if(j==0){
        L[i][0] = (arr[i][0] + mmpath(arr, i-1, 0, L)); 
    }
    else{ 
        L[i][j] = (arr[i][j] + max(mmpath(arr, i-1, j, L), mmpath(arr, i, j-1, L)));
    }
    return L[i][j];
}

//
int dmpath(int arr[][20], int n, int L[][20]){ //L은 누적행렬
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i ==0 && j==0){
                L[0][0] = arr[0][0];
            }
            else if(i == 0){
                L[0][j] = L[0][j-1] + arr[0][j];
            }
            else if(j == 0){
                L[i][0] = L[i-1][0] + arr[i][0];
            }
            else{
                L[i][j] = max(L[i][j-1], L[i-1][j]) + arr[i][j]; 
            }
        }
    } 
    return L[n-1][n-1];
}

int main(){
    int count = 0;
    const int n = 20;

    int my_arr[n][n];
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            my_arr[i][j] = rand()%20 +1;
        }
    }
    /*
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout<<my_arr[i][j]<<", ";
        }
        cout<<endl;
    }*/

    int L_arr[n][n];    
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            L_arr[i][j] = 0;
        }
    }

    //count = mpath(my_arr, n-1, n-1);
    //cout<< count << endl;

    count = mmpath(my_arr,n-1,n-1, L_arr);
    cout<< count << endl;

    count = dmpath(my_arr, n, L_arr);
    cout<< count << endl;


}
