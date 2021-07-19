#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<algorithm>
#include"json/json.h"


using namespace std;


int my_dist(string str1, string str2){
    int check =0;
    int result=0;
    int str1_l = str1.length();
    int str2_l = str2.length();
    int dist[str1_l+1][str2_l+1];

    for(int i=0; i<=str1_l; i++){
        dist[i][0] = i;  
    }
    for(int j=0; j<=str2_l; j++){
        dist[0][j] = j;
    }

    for(int i =1; i<=str1_l; i++){
        for(int j=1; j<=str2_l; j++){
            if(str1[i] != str2[j]){ 
                //서로 다르면 수정[i-1][j-1], 삭제[i][j-1], 추가[i-1][j]한 편집거리 중 최소값 가져온 뒤 + 1
                check = min(min(dist[i-1][j-1], dist[i][j-1]), dist[i-1][j]);
                dist[i][j] = check + 1;
                
            }
            else if(str1[i] == str2[j]){ //문자열이 같다면 이전 편집거리를 그대로 유지
                dist[i][j] = dist[i-1][j-1];
            }
        }
    }

    result = dist[str1_l][str2_l];

    return result;

}


int main(){
    vector<pair<string,string> > str;

    vector<int> dist;
    vector<int> mydist;
    int result;
    
    
    Json::Value root;
    Json::Reader reader;

    ifstream json("strings.json", ifstream::binary);
    reader.parse(json,root);
    for(auto& value:root){
        str.push_back(pair<string,string>(value["str1"].asString(), value["str2"].asString()));
        dist.push_back(value["dist"].asInt());
    }
    for(auto& it:str){
        mydist.push_back(my_dist(it.first, it.second));
    }

    for(size_t i =0; i<mydist.size(); i++)
        cout<< "result dist: "<<mydist[i]<<", label: "<<dist[i]<<endl;



}
