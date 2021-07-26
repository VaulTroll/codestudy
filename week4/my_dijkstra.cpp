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


void dijkstra(int start, vector<vector<int> > graph, int n, int d[]){
    priority_queue<pair<int,int>, vector<pair<int,int> >,greater<pair<int,int> > > pq; //거리, 노드

    //노드의 수만큼 최단 경로를 저장할 배열 생성 
    pq.push({0,start}); //시작 노드의 최단 경로는 0
    d[start] = 0;

    while(!pq.empty()){
        int dist = pq.top().first; //현재 노드까지 가중치 합
        int node = pq.top().second; //현재 노드 
        pq.pop();

        if(d[node] < dist){
            continue;
        }
        for (int i=0; i<graph[node].size();i++){ //해당 노드와 연결된 노드들의 수 만큼 
            int weight = dist + graph[node][i]; //시작 노드부터 현재 노드까지의 거리합 계산
            if(weight < d[i]){ //만약 최소거리가 존재한다면 갱신 
                d[i] = weight; 
                pq.push(make_pair(weight, i)); //우선순위 큐에 삽입 
            }
        }
    }
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
    int n;
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
            }
            count++;
        }
        graph[dota][dotb] = weight;
    }
    rFile.close();


    n = v.size(); //총 노드의 수
    int d[n];    //노드의 수만큼 최단 경로를 저장할 배열 생성
    fill(d,d+n,9999); //초기값은 9999로 설정

    dijkstra(0, graph, n, d);

    for(int i=0; i<n;i++){
        cout<<(char)(i+65)<<","<<d[i]<<endl;
    }

}




