#include<vector>
#include<iostream>
#include<algorithm>
#include<string.h>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;


void interval_s(const vector<vector<pair<int,int> > > &v_i){

    int n = v_i.size(); //v_i size를 하면 맨 뒤 -1 해주어야 함
    //int k = v_i[1].size(); // v_i[n].size() 하면 해당 사이즈가 바로 나옴
    for (int i =0; i<n-1; i++){
        vector<pair<int,int> > p;
        int result =1;
        int earli_end = v_i[i][0].first; //가장 빠른 종료시간을 첫 작업으로 선택
        p.push_back(make_pair(v_i[i][0].second, v_i[i][0].first));
        
        for( int j =1; j<v_i[i].size(); j++ ){
            if(earli_end < v_i[i][j].second){
                //만약 현재 종료시간보다 미래의 시작시간이 존재한다면
                result++;
                earli_end = v_i[i][j].first; //새 작업의 종료시간 업데이트
                p.push_back(make_pair(v_i[i][j].second, v_i[i][j].first));
                //job 저장
            }

        }
        cout<<"result is "<<result<<endl;
        for(auto it=p.begin(); it != p.end(); it++){
            cout<<"["<<it->first<<", "<<it->second<<"] "; 
        }
        cout<<endl;
        cout<<endl;
    }
}


int main(){

    vector<vector<pair<int,int> > > v_i;
    vector<pair<int,int> > v;

    string str_buf;
    fstream fs;
    int ind=0;

    fs.open("tasks.csv",ios::in);
    while(!fs.eof()){
        getline(fs, str_buf);
        string buff;
        istringstream ss(str_buf);
        while(getline(ss,buff,',')){
            int count = 0;
            string task_buf;
            istringstream st(buff);
            while(getline(st,task_buf,':')){
                int st;
                if(count == 0){
                    st = stoi(task_buf);

                }else{
                    //earliest finish를 이용하므로 종료시간, 시작시간 순으로 저장
                    v.push_back(pair<int,int>(stoi(task_buf),st));
                }
                count++;
            }
        }
        v_i.push_back(v);
        v.clear();
    }

    
    //종료시간을 기준으로 오름차순 정렬
    for(int s=0; s < v_i.size()-1; s++){
        sort(v_i[s].begin(), v_i[s].end());
    }

/*
    for(int a=0; a < v_i.size()-1; a++){
        for(int b=0; b< v_i[a].size(); b++){
            cout<< v_i[a][b].first << "," << v_i[a][b].second <<"||";
        }
        cout<<endl;
    }
    */

    interval_s(v_i);
}

