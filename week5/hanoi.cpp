#include<iostream>
using namespace std;

int countr=0;

void hanoi(int n, int start, int by, int to){     
    if(n==1){ //남은 원판이 하나일 때 목적지로 바로 옮긴다
        countr++; 
    }
    else{
        //hanoi (남은 원판 수, 출발, 경유, 목적)
        hanoi(n-1, start, to, by); //기둥1의 n-1개 원판을 기둥2로
        countr++; //기둥1의 1개 원판을 기둥3으로 
        hanoi(n-1, by, start, to); //기둥2의 원판을 기둥3으로 
        
    }
}

int main(){
    int num = 4;
    hanoi(num, 1,2,3); //1번 기둥에서 2번기둥을 거쳐 3번 기둥으로 가는 하노이탑
    cout<< (1<<num)-1 <<endl; //답은 2^n -1
    cout<<countr<<endl;
}
