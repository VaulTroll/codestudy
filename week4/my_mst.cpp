#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<algorithm>
#include<queue>
#include<map>
#include<set>

using namespace std;

int mst(int start, vector<vector<int> > graph, set<int> set_c){
    vector<int> visit;
    vector<int> unvisit;

    int n = set_c.size();

    int index_j, index_k;
    int count =0;

    visit.push_back(0); //먼저 0부터 방문 

    set_c.erase(0);
    for(auto &m: set_c){ //나머지는 아직 방문하지 않음 
        unvisit.push_back(m);
    }

    for(int i=1; i< n; i++){
        int min = 9999;
        int min_index =0;


        for(int j=0; j<i; j++){ //체크하려는 노드 
            for(int k=0; k<n-i; k++){//현재 노드와 연결되어 있는 노드들을 탐색
                //만약 가중치가 0보다 크고 현재 최소 가중치보다 더 작다면 그것을 최소 가중치로 업뎃
                if(graph[visit[j]][unvisit[k]] > 0 && min > graph[visit[j]][unvisit[k]]){
                    min = graph[visit[j]][unvisit[k]];
                    min_index = k;
                    index_j = visit[j];
                    index_k = unvisit[k];
                }
            }
        }
        //한 점에 있어서 붙어있는 모든 간선의 가중치 중 최소값을 선택함 
        visit.push_back(unvisit[min_index]);
        unvisit.erase(unvisit.begin() + min_index);
        if(min!=9999){
            count +=min;
            cout<<(char)(index_j+65)<<"-"<<(char)(index_k+65)<<","<<min<<endl;
        } 
    }
    return count;
}


int main(){
    fstream rFile;
    string line;
    rFile.open("graph.txt");

    vector< vector<int> > graph(15, vector<int>(15, 9999));
    //2차원 벡터로 각 노드의 간선 가중치 저장, 최소값을 찾으므로 기본값은 9999로 설정 
    set<int> v; //정점을 저장하기 위한 set
    int dota, dotb, weight; //노드1, 노드2, 가중치 저장  
    int result;
    char cht[1];


    while(getline(rFile, line)){
        stringstream ss(line);
        string w, one, two;
        int weight;
        int count = 0;
        while(getline(ss,w,',')){
            if(count ==0){
                stringstream so(w);
                int count_d =0;
                while(getline(so, one,'-')){                    
                    strcpy(cht, one.c_str());
                    int k=(int)cht[0];
                    if(count_d==0){
                        dota = k-65;
                        v.insert(dota);
                    }else{
                        dotb = k-65;
                        v.insert(dotb);
                    }
                    count_d++;
                }
            }else{
                weight=stoi(w);
                v.insert(weight);
            }
            count++;
        }
        graph[dota][dotb] = weight;
        //graph[dotb][dota] = weight; 
        //방향이 없는 노드면 사용해도 괜찮으나 출력 노드의 순서가 뒤바뀌는 경우가 생김
    }
    rFile.close();

    result = mst(0, graph, v);
    cout<< "result: "<<result<<endl;


}




