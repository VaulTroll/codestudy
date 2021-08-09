#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<set>
#include<queue>


using namespace std;

int dijk(int start, int cost[][30], int n){
    priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> > > pq; //거리, 노드
    int ret=0;

    int d[n];
    fill(d, d+n, 999);

    pq.push({0, start});
    d[start]=0;
    while(!pq.empty()){
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();

        if(d[node]< dist){
            continue;
        }
        for(int i=0; i<n; i++){
            int weight = dist + cost[node][i];
            if(weight <d[i]){
                d[i] = weight;
                pq.push(make_pair(weight, i));
            }
        }
    }
    for(int i=0; i<n; i++){
        ret += d[i];
    }
    return ret;
}


int main(){
    fstream rFile;
    string line;
    int d, h;
    rFile.open("cost.txt");

    int cost[30][30];
    fill(&cost[0][0], &cost[30-1][30], 999);
    char cht[1];
    int pos, result = 9999;
    int check;
    set<int> s;

    while(getline(rFile, line)){
        stringstream ss(line);
        string w, one, two;
        int weight;
        int count =0;
        while(getline(ss, w, ',')){
            if(count ==0){
                stringstream so(w);
                int count_d =0;
                while(getline(so, one, '-')){
                    int k;
                    if(count_d ==0){
                        strcpy(cht, one.c_str());
                        k = (int)cht[0];
                        d = k-65;
                        s.insert(d);
                    }else{
                        two = one[1];
                        strcpy(cht, two.c_str());
                        k= (int)cht[0];
                        h = k-65;
                        s.insert(h);
                    }
                    count_d++;
                }    
            }else{
                weight = stoi(w);
            }
            count++;
        }
        //cout<< d<< "->"<<h<<", "<<weight<<endl;
        cost[d][h] = weight;
    }
    rFile.close();



    int n = s.size();
    for(int i=0; i<n; i++){
        check = dijk(i, cost, n);
        cout<<(char)(i+65)<<"의 최소비용 "<< check<<endl;
        if(check < result){
            result = check;
            pos = i;
        }
    }
    cout<<endl;
    cout<< "최적 위치: "<<(char)(pos+65)<<", 비용의 총 합:  "<<result<<endl;
}
