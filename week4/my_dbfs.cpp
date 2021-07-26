#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>

using namespace std;


void dfs(vector<string> &result, string s, multimap<string,string> mm, map<string,bool> check){

    check.find(s)->second = true;
    result.push_back(s);
 
    for(auto i = mm.lower_bound(s); i !=mm.upper_bound(s); i++){
        string k = i->second;
        if(!check.find(k)->second){
            //이미 방문했다면 빠져나가고 방문하지 않았다면 재귀 호출 
            dfs(result, k, mm, check);
        }
    }

}

void bfs(vector<string> &result, string s, multimap<string, string> mm, map<string,bool> check){

    queue<string> q;

    q.push(s);
    check.find(s)->second = true;
    result.push_back(s);
    while(!q.empty()){
        string tmp= q.front();
        q.pop();

        for(auto i = mm.lower_bound(tmp); i != mm.upper_bound(tmp); i++){
            string k = i->second;
            result.push_back(k);
            //아직 방문하지 않았다면 큐에 넣어줌
            if(check.find(k)->second == false){
                q.push(k);
                check.find(k)->second = true;

            }
        }
    }
}

int main(){
    fstream rFile;
    string line;
    rFile.open("tree.txt");

    multimap<string,string> mm;    
    map<string, bool> m;
    vector<string> result;

    while(getline(rFile, line)){
        string buff, k_buff;
        stringstream ss(line);
        int c =0;
        while(getline(ss, buff, '-')){
            if(c==0){
                k_buff = buff;
            }
            else{
                mm.insert(pair<string, string>(k_buff,buff));     
            }
            c++;
        }
    }
    rFile.close();


    for(auto &i: mm){
        m.insert(make_pair(i.first, false));
    }

    string start = "";
    start = mm.begin()->first;

    //dfs(result, start, mm, m);
    bfs(result, start, mm, m);
    for(auto &i:result){
        cout<<i<<",";
    }


}




