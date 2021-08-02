#include<iostream>
#include<string>
#include<string.h>

using namespace std;

int lcs(string str1, string str2, int s1_l, int s2_l){
    if(s1_l == 0 || s2_l == 0) //둘 중 하나라도 끝이면 0
        return 0;
    else if(str1[s1_l -1] == str2[s2_l -1]){ //서로 같은 경우 대각선 + 1
        return lcs(str1, str2, s1_l -1, s2_l -1) + 1;
    }else{ //서로 다른 경우 왼 or 위 중에서 더 큰값 
        return max(lcs(str1, str2, s1_l, s2_l-1), lcs(str1, str2, s1_l -1, s2_l));
    }
}


int main(){
    string str1 = "ABCDEFGH";
    string str2 = "XBCYEZGAH";
    
    int result = lcs(str1, str2, str1.length(), str2.length());
    cout<<result<<endl;
    





}
