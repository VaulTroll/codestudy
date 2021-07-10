#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<vector>


using namespace std;


class Node{
private:
    string data; //데이터
    int level; //트리의 깊이
    int degree =0; //노드의 차수
    vector<Node*> childNodes; //자식 노드는 동적 배열

public:

    Node(string key){
        data =key;
        level =1;
    }

    void setData(string ch){
        data =ch;
    }
    string getData(){
        return data;
    }
    void setDegree(int key){
        degree =key;
    }
    int getDegree(){
        return degree;
    }
    void setLevel(int key){
        level =key;
    }
    int getLevel(){
        return level;
    }

    void addChild(Node* node){
        //자식노드 생성
        childNodes.push_back(node);//새 노드 동적할당
        setDegree(childNodes.size());//차원 할당

    }

    vector<Node*> getChildNodes(){
        //자식 노드 조회
        return childNodes;
    }

    bool printTree(Node* node, int num){
        if (num==0){
            cout <<getData();
            num++;
        }
        vector<Node*> childNodes = node->getChildNodes();
        if(childNodes.size()==0)
            return false;
        if(childNodes.size()>0){
            cout<<"(";
            for(int i=0; i<childNodes.size();i++){
                cout <<childNodes[i]->getData()<<",";
                printTree(childNodes[i],num);
            }
        }
        cout <<")";
        return false;
    }

    Node* getNode(Node* node, string key){
        vector<Node*> v = node->getChildNodes();

        if(v.size()==0){
            return 0;
        }
        for (int i=0; i<v.size();i++){
            if(v[i]->getData()==key){
                return v[i];
            }
            else{
                Node* tn = getNode(v[i],key);
                if(NULL !=tn)
                    return tn;
            }
        }
        return NULL;
    }



    void printChildNodes(){
        cout<<getData()<<": ";
        for(int i=0; i<childNodes.size();i++){
            cout<<childNodes[i]->getData()<<", ";
        }
        cout << ")";
    }
};

int main(){

    cout<<endl;

    string str_buf;
    fstream fs;

    Node* root = new Node("root");


    fs.open("tree.csv",ios::in);

    while(!fs.eof()){
        getline(fs, str_buf);
        int count =0;
        string p;
        string c;
        istringstream ss(str_buf);

        while(getline(ss,c,',')){
            if (count ==0)
                p=c;
            if(count ==1){
                root->getNode(root,p)->addChild(new Node(c));
            }
            count++;
        }
    }
    fs.close();

    root->printTree(root,0);

}

