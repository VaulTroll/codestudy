#include<iostream>
#include<time.h>
#include<ctime>

using namespace std;

long long dp[100]={0,}; //동적프로그래밍을 위한 배열 

long long fibo(long long n){
    if (n<=1){
        return n;
    }
    return fibo(n-1) + fibo(n-2);
}
    
long long ite_fibo(long long n){
    long long current, n_1=1, n_2=0; //현재값, n-1값,n-2값
    if(n<=1)
        return n;
    for(int i=2; i<=n; i++){
        current = n_1 + n_2; //현재값 = (n-1) + (n-2)
        n_2 = n_1;
        n_1 = current;
    }
    return current;
}

long long dp_fibo(long long n){
    if(n<=2){
        return 1;
    }
    if(dp[n] != 0){ //만약 미리 계산된 값이 있다면 바로 리턴 
        return dp[n];
    }
    dp[n] = dp_fibo(n-1) + dp_fibo(n-2);
    return dp[n];
}

long long tail_fibo(long long n, long long n_1, long long n_2){
    long long current;
    if(n<=1)
        return n * n_1; //n-1에 이전에 계산된 피보나치 값이 저장되어 있음
    current = n_1 + n_2;
    n_2 = n_1;
    n_1 = current;

    return tail_fibo(n-1, n_1, n_2);

}

int main(){
    long long result;
    double t;
    clock_t start, end;

    
    start = clock();
    //result = fibo(50);
    //result = ite_fibo(100);
    //result = dp_fibo(100);
    result = tail_fibo(100, 1, 0);
    end = clock();
    t = (double)(end-start);

    cout<<"time: "<<(double)(t/CLOCKS_PER_SEC)<<endl;
    cout<<"result: "<<result<<endl;

    return 0;
}
