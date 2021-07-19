#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include"json/json.h"


using namespace std;


string my_lcs(string str1, string str2){
    string result ="";


    int check =0; //앞에서부터 가장 최장 문자열 길이 카운트
    int count[2] = {0}; //최장 문자열 위치 카운트 
    int str1_l = str1.length();
    int str2_l = str2.length();

    int lcs[str1_l+1][str2_l+1];

    for(int i =0; i<=str1_l; i++){
        lcs[i][0] = 0;
    }
    for(int j=0; j<=str2_l; j++){
        lcs[0][j] = 0;
    }
//문자열은 0부터 시작하지만 배열은 1부터 문자가 들어있으므로 str[i-1], str[j-1]
    for(int i =1; i<=str1_l; i++){
        for(int j=1; j<=str2_l; j++){
            if(str1[i-1] != str2[j-1]){ //같지 않다면 0
                lcs[i][j]=0;
            }
            else if(str1[i-1] == str2[j-1]){ //문자열이 같다면 이전까지 연속된 문자열의 수 +1
                lcs[i][j] = lcs[i-1][j-1] +1;
                if(lcs[i][j]>check){
                    check = lcs[i][j];
                    count[0] = i;
                    count[1] = j;
                }
            }
        }
    }
    result.clear();
    //substr을 통해 현재 가장 큰 카운트를 가진 연속 문자열을 가져온다
    result = str1.substr(count[0]-check, check);
    
    return result;

}


int main(){
    vector<pair<string,string> > str;

    vector<string> lcs;
    vector<string> my_result;
    
    Json::Value root;
    Json::Reader reader;

    ifstream json("strings.json", ifstream::binary);
    reader.parse(json,root);
    for(auto& value:root){
        str.push_back(pair<string,string>(value["str1"].asString(), value["str2"].asString()));
        lcs.push_back(value["lcs"][0].asString());
    }
    
    for(auto& it:str){
        my_result.push_back(my_lcs(it.first, it.second));
    }

    
    for(size_t i =0; i<my_result.size(); i++){
        cout<< "result lcs: "<<my_result[i]<<", label: "<<lcs[i]<<endl;
    }
    




}
