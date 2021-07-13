#include<vector>
#include<iostream>
#include<fstream>
#include<algorithm>
#include<string.h>
#include<string>
#include<sstream>
#include<list>
#include<queue>
#include<map>
#include<unordered_map>

using namespace std;

struct Node{
    char ascii; //문자
    int freq; //빈도수
    Node *left, *right;
};

struct my_cmp{
    // 빈도수 기준으로 우선순위 정렬
    bool operator()(Node* A, Node* B){
        return A->freq > B->freq;
    }
};


void Make_tree(priority_queue<Node*, vector<Node*>, my_cmp> &pq){
    while(pq.size()>=2){//1개가 남을때까지 트리 생성
        Node* newNode = new Node;
        newNode->ascii = 0;
        newNode->right = pq.top();
        pq.pop();
        newNode->left = pq.top();
        pq.pop();
        newNode->freq = newNode->right->freq + newNode->left->freq;
        //새 노드의 빈도수는 두 노드의 빈도수의 합
        pq.push(newNode);
    }
    return;
}

void Find_tree(Node* p,unordered_map<char, string> &info , string str){
    if(p == nullptr) return;
    //재귀적으로 호출
    Find_tree(p->left, info ,str + '1'); //왼쪽 자식으로 갈때 1을 붙여줌 
    Find_tree(p->right, info ,str + '0');
    info.insert(make_pair(p->ascii,str)); //해당 문자와 인코딩된 허프만 값을 저장함
}

void Make_node(int *freq, priority_queue<Node*, vector<Node*>, my_cmp> &pq){
    for(unsigned char i=0; i<128; i++){ //아스키 코드의 범위만큼 반복
        if(freq[i]!=0){  //한번이라도 빈도수가 쓰인 것만 트리에 넣음 
            Node* newNode = new Node;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->ascii = i;
            newNode->freq = freq[i];
            pq.push(newNode);
        }

    }
    return;
}

string encode(unordered_map<char, string> &info, string filename ,string str){
    unsigned char index ={0};
    FILE* file = fopen(filename.c_str(),"rt");
    while(fscanf(file, "%c", &index)!=EOF){
         auto test = info.find(index); //해당 문자값을 빈도 인코딩 사전에서 찾음
         //cout<< test->second <<endl;
         str+=test->second; //빈도 사전에서 해당 아스키 문자의 인코딩된 값을 얻음
        
    }
    fclose(file);

    return str;
}

string decode(Node* root){
    int i=0;
    Node* j = root;
    string decode, text2;
    ifstream rf;
    rf.open("my_encode.txt");
    while(!rf.eof()){
        getline(rf, decode);
    }
    while(decode[i] != '\0'){ //문자 끝까지
        if(decode[i]=='1') //인코딩값이 1인경우
            j = j->left; //왼쪽 자식 노드로 이동
        else if (decode[i] == '0')
            j = j->right;
        if (j->left == NULL && j->right == NULL){ //잎 노드인 경우
            text2 += j->ascii; //해당 노드의 알파벳 출력
            j = root; 
        }
        i++;
    }
    return text2;
}

int main(){
    unordered_map<char, string> info;
    priority_queue<Node*, vector<Node*>, my_cmp> pq;

    string text, text2;

    string filename = "content.txt";
    int freq[128] = {0}; //아스키코드는 128가지 글자
    unsigned char index ={0};
    FILE* file = fopen(filename.c_str(),"rt");
    while(fscanf(file, "%c", &index)!=EOF){
        //(int)index를 하면 아스키 숫자가 나오는 것을 이용
        freq[index] += 1;
    }
    fclose(file);

    Make_node(freq,pq);
    Make_tree(pq);
    Find_tree(pq.top(),info,""); //root 노드는 큐의 top()


    for(auto iter: info){
        cout<<iter.first <<": "<<iter.second <<endl;
    }

    
    text = encode(info, filename, "");
    ofstream HzWriteFile("my_encode.txt");
    HzWriteFile << text;
    HzWriteFile.close();

    text2 = decode(pq.top());    
    ofstream HdWriteFile("my_decode.txt");
    HdWriteFile << text;
    HdWriteFile.close();



}
