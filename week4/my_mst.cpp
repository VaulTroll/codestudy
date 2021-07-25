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

void mst(vector<string> result,int start, vector<vector<int> > graph, set<int> set_c){
    vector<int> visit;
    vector<int> unvisit;
    pair<int,int> test;
    int n = set_c.size();
    int count =0;
    //int min = 9999;

    visit.push_back(0);

    set_c.erase(0);
    for(auto &m: set_c){
        unvisit.push_back(m);
    }

    for(int i=1; i< n; i++){
        int min = 9999;
        int min_index =0;
        for(int j=0; j<i; j++){
            for(int k=0; k<n-i; k++){
                if(graph[visit[j]][unvisit[k]] > 0 && min > graph[visit[j]][unvisit[k]]){
                    min = graph[visit[j]][unvisit[k]];
                    min_index = k;
                                        //test.push_back(make_pair(j,k));
                    cout<< "min: "<< min<<"  ";
                    cout<<"index: "<<k<<"  ";
                    cout<<"count: "<<count <<endl;

                }

            }

        }
        visit.push_back(unvisit[min_index]);
        unvisit.erase(unvisit.begin() + min_index);
        if(min!=9999){
            count +=min;
        } 
    }
    
    /*for(auto &i: test){
        cout<<i.first<<": "<<i.second<<", "<<endl;
    }*/
    cout<< count <<endl;






}


int main(){
    fstream rFile;
    string line;
    rFile.open("graph.txt");

    vector< vector<int> > graph(15, vector<int>(15, 9999));
    vector<string> result;
    set<int> v;
    int dota, dotb, weight;
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
                        //cout<<dota<<": "<<one<<"  ";
                    }else{
                        dotb = k-65;
                        //cout<<dotb<<": "<<one<<"  ";
                        v.insert(dotb);
                    }
                    count_d++;
                }

            }else{
                weight=stoi(w);
                //cout<<weight<<": w"<<endl;
                v.insert(weight);
            }
            count++;
        }
        graph[dota][dotb] = weight;
        graph[dotb][dota] = weight;
    }
    rFile.close();


    for(int i=0; i<graph[i].size()-1; i++){
       for(auto &j: graph[i]){
            cout<<j<<", ";
       }
       cout<<endl;
    }

    mst(result, 0, graph, v);




}




