#include<iostream>
#include<fstream>
#include<string>
#include<string.h>
#include<algorithm>
#include<regex>
#include<vector>
#include<set>
#include<map>
#include"json/json.h"


using namespace std;

int re1(multimap<string,int> re_map){
    int check=0;
    regex re("#\\d+"); //#으로 시작하고 뒤에 숫자가 1개 보다 많이 존재하면
    for(const auto &it : re_map){
        if(regex_search(it.first, re)){
            check += it.second;
        }
    }

    return check;
}

int re2(vector<string> str){
    set<string> num; //중복 제거를 위한 set
    smatch match;

    //regex re("\\[(\\w+[ -]?\\w*?[ -]?\\w*?)\\]");
    regex re("\\[([a-zA-Z]+[ -]?\\w*?[ -]?\\w*?)\\]");
    for(const auto &it: str){
        if(regex_search(it, match, re)){
            num.insert(match.str());
        }
    }

    return num.size();
}

void re3(vector<string> str){
    vector<string> save_str; 
    string save;
    smatch match;

    regex re("\\[([a-zA-Z]+[ -]?\\w*?[ -]?\\w*?)\\]");
    for(const auto &it: str){
        if(regex_search(it, match, re)){
            save = regex_replace(it, re, "(($1)) ");
            save_str.push_back(save);
        }
    }

    ofstream fout;
    fout.open("my_issue_converted.txt");
    for(auto& it:save_str)
        fout<< it << "\n";
    fout << endl;
    fout.close();

}


int main(){

    vector<string> re_str;
    multimap<string, int> re_map;
    int result;
    
    
    Json::Value root;
    Json::Reader reader;

    ifstream json("issues.json", ifstream::binary);
    reader.parse(json,root);
    for(auto& value:root){
        re_str.push_back(value["title"].asString());
        re_map.insert({value["title"].asString(),value["comments"].asInt()});
    }


    result = re1(re_map);
    cout<<result<<endl;

    result = re2(re_str);
    cout<<result<<endl;  

    re3(re_str);


}
