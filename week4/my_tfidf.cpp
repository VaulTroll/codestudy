#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<string.h>
#include<algorithm>
#include<regex>
#include<vector>
#include<set>
#include<map>
#include<math.h>
#include<queue>
#include"json/json.h"


using namespace std;

bool cmp(const pair<string,int>& a, const pair<string,int>& b ){
        return a.second > b.second;
}

void tfidf(vector<string> re_str){
    map<string, int> global_bow;
    vector< map<string, int> > t_bow;
    
    int tf;
    double df, idf, tfidf_;

    ///////////////////////////////////////////
    //전체 문서를 각각 map형태의 bow로 만들어 global vector에 저장한다. 
    for(const auto &it: re_str){
        vector<string> token;
        map<string, int> bow;
        string tokenize;

        regex re("[^\\w_-]");
        tokenize = regex_replace(it, re, " ");
        
        stringstream ss(tokenize);
        string temp;
        while(getline(ss, temp, ' ')){
            if(bow.find(temp)==bow.end()){
                bow.insert(make_pair(temp,1));
            }
            else{
                bow[temp]+=1;
            }
        }
        t_bow.push_back(bow);
    }

    //////////////////////////////////////////////
    //tfidf 값을 구하기 위해 각 문서의 단어의 tfidf값을 구하기 위해 글로벌 bow를 체크한다
    string key;
    
    for(int i=0; i<t_bow.size(); i++){
        priority_queue<pair<double, string> > pq; //tfidf , 단어 의 형태로 우선순위 큐를 만든다

        for(const auto& it: t_bow[i]){
            key = it.first;
            tf = it.second;
            df = 0.0;
            for(int k=0; k<t_bow.size(); k++){
                if(t_bow[k].find(key) != t_bow[k].end()){ //3000개 문서에서 해당 단어가 존재하는지 체크 
                    df++;
                }
            }
            //해당 단어에 대한 df계산끝
            idf = log((double)t_bow.size()/(df + 1.0));

            tfidf_ = (double)tf * idf;
            pq.push(make_pair(tfidf_, key)); //계산된 값을 우선순위 큐에 넣는다 

        }
        //해당 벡터의 단어들에 대한 tfidf pair 생성됨
        //이제 정렬을 한 뒤에 상위3개만 뽑아서 글로벌 벡터에 넣음
        for(int z =0; z<3; z++){
            cout<<i<<"번째 문서   ";
            cout<<pq.top().first<<" , "<<pq.top().second<<" ... ";        
            if(global_bow.find(pq.top().second)==global_bow.end()){
                global_bow.insert(make_pair(pq.top().second,1));
            }
            else{
                global_bow[pq.top().second]+=1;
            }
            pq.pop();
        }
        cout<<endl;
    }


    vector< pair<string,int> > sort_g(global_bow.begin(), global_bow.end());
    sort(sort_g.begin(),sort_g.end(),cmp);
    //전체 이슈 중 주제어 빈도 수 측정 위한 정렬

    for(int i=0;i<4;i++){
        cout<<endl;
        cout<<"결과"<<sort_g[i].first<<", "<<sort_g[i].second<<endl;
    }
}


int main(){
    vector<string> re_str;
    int result;
    
    Json::Value root;
    Json::Reader reader;

    ifstream json("issues.json", ifstream::binary);
    reader.parse(json,root);
    for(auto& value:root){
        re_str.push_back(value["body"].asString());
    }
    tfidf(re_str);


}
