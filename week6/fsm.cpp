#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
#include<queue>

using namespace std;


map<string,int> mapt;


class Node{
private:
    string data;
    vector<Node*> child;

public:
    Node(string key){
        data=key;
    }


    void setData(string str){
        data = str;
    }

    string getData(){
        return data;
    }

    void addChild(Node* node){
        child.push_back(node);
    }

    vector<Node*> getChild(){
        return child;
    }

    
    void print(){
        cout<<getData()<<":(";
        for(int i=0;i<child.size();i++){
            cout<<child[i]->getData()<<", ";
        }
        cout<<")";
    }

    Node* getNode(Node* node, string key){
        vector<Node*> v = node->getChild();
        if(node->getData()==key){
            return node;
        }
        if(v.size()==0){
            return NULL;
        }
        for(int i=0; i<v.size();i++){
            if(v[i]->getData() == key){
                return v[i];
            }
            else{
                Node* t = getNode(v[i], key);
                if(NULL!=t){
                    return t;
                }
            }
        }
        return NULL;
    }


    bool printTree(Node* node, int num) {
        if (num == 0) {
            cout << getData();     
            num++;
        }
        vector<Node*> child = node->getChild();
        if (child.size() == 0)
            return false;
        if (child.size() > 0) {
            cout << "( ";

            for (int i = 0; i < child.size(); i++) {
                cout << child[i]->getData() << ", ";
                printTree(child[i], num);
            }
        }
        cout << ") ";
        return false;
    }

};

void bfs(Node* node, map<string,int> &map){
    queue<string> q;
    string subtree="";
    int check=0;
    q.push(node->getData());

    while(!q.empty()){
        string now = q.front();
        if(now!="root"){
            subtree+=now+",";
        }
        check++;
        //cout<<now<<" ->  ";
        if(check>3){
            //map(make_pair(subtree);
            if(map.find(subtree)!=map.end()){
                map.find(subtree)->second++;
            }else{
                map.insert(make_pair(subtree,1));
            }
            //cout<<subtree<<" ------ ";
        }
        //cout<<now<<" ->  ";
        q.pop();
        vector<Node*> child = node->getNode(node,now)->getChild();
        for(int i=0; i<child.size();i++){
            string n_str=child[i]->getData();
            q.push(n_str);
        } 
    }
    cout<<endl;
}

void subt(Node* node, map<string,int> &map){
    queue<string> q;
    string subtree="";
    q.push(node->getData());

    while(!q.empty()){
        string now = q.front();
        q.pop();
        vector<Node*> child = node->getNode(node,now)->getChild();

        if(now!="root"){
            if(child.size()>1){
                for(int i=0; i<child.size()-1;i++){
                    subtree = now+","+child[i]->getData()+","+child[i+1]->getData(); //????????????, ????????????,???????????????
                    if(map.find(subtree)!=map.end()){ //????????? ?????? ???????????? ?????????
                        map.find(subtree)->second++;
                    }else{ //????????? ?????? ??????
                        map.insert(make_pair(subtree,1)); 
                        //cout<<subtree<<",  ";
                    }           
                }
            }
        }
        for(int i=0; i<child.size();i++){
            string n_str=child[i]->getData();
            q.push(n_str);
        } 
    }

}

bool cmp(const pair<string, int>&a, const pair<string, int>&b){
    if(a.second == b.second) return a.first < b.first;
    return a.second > b.second;
}

int main(){

    map<string,int> n_map;
    map<string,int> s_map;

    fstream rFile;
    string line;
    rFile.open("orders.txt");

    char cht[1];

    //??? ?????? ????????? ?????? ?????? ??????, ?????? ?????? ???????????? ???????????? ??????
    while(getline(rFile, line)){
        stringstream ss(line);
        string w,th, one, two;
        int check=0;
        Node* root = new Node("root");
        while(getline(ss,w,'|')){
            stringstream so(w);
            int count=0;
            while(getline(so, one,',')){
                if(count==0){
                    int count_d=0;
                    stringstream oo(one);
                    while(getline(oo, two,'-')){
                        if(count_d==0){
                            //?????? ????????? ??? ???
                            th=two;
                            if(check==0){
                                root->addChild(new Node(th));
                                check++;
                            }
                        }
                        else{
                            //?????? ????????? ??? ???
                            root->getNode(root,th)->addChild(new Node(two));
                        }
                        count_d++;
                    }                
                }else{
                    //????????? ?????? ?????? map????????? ??????                         
                    int weight_ = atoi(one.c_str());
                    s_map.insert(make_pair(th+","+two , weight_));
                }
                count++;
            }
        }
        //bfs(root, n_map); bfs??? ???????????? ???????
        subt(root, n_map); //3????????? ???????????? ???????
        //cout<<"?????? ?????? ???, ??????????????? ?????? ??????"<<endl;
           
    }
    rFile.close();

    //map?????? ??? value?????? ???????????? ??????
    vector<pair<string, int> > vec(n_map.begin(), n_map.end());
    sort(vec.begin(), vec.end(), cmp);

    
    //?????????????????? ????????? ??? ?????? 5??? ????????? ?????? ??? ???????????? ????????? 
    int reslut=0;
    for(int i=0; i<5; i++){
        string fir = vec[i].first;
        int sec = vec[i].second;
        cout<<fir<<" (??????, ??????, ?????????): ?????? ?????? -> "<<sec<<endl;

        stringstream fss(fir);
        string m, t;
        int m_ch=0;
        int nleft, nright;
        while(getline(fss, m,',')){
            if(m_ch==0){
                t=m;
                m_ch++;
            }else if(m_ch==1){
                string z = t+","+m;
                nleft = s_map.find(z)->second;
                m_ch++;
            }else if(m_ch==2){
                string z = t+","+m;
                nright = s_map.find(z)->second;
                m_ch++;
            }
        }
        int save = (nleft + nright)/2 * sec;
        reslut+=save;
        cout<<i+1<<"?????? ????????? ?????? ??????: "<<save<<endl;
    }

    cout<<"\n?????? ?????? ??????: "<<reslut<<endl;
}
