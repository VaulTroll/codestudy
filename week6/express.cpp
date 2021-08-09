#include<iostream>
#include<queue>

using namespace std;

string prefix(string express){
    queue<char> q;
    string result="";
    int n=express.length();
    for(int i=0; i<express.length()-1; i++){
        if(express[i] == ' '){
            continue;
        }
        else if(express[i] == '*'){
            result = result + " *" + ' ' + q.front() + ' '+ express[i+2]; //공백이 한칸씩 있어서 +2
            q.pop();
            i+=2;
        }else if(express[i] == '+'){
            result = result + " +"; 
        }else if(express[i] == '-'){
            result = result + " -";
        }else{ //오퍼랜드
            q.push(express[i]);
            if(q.size() == 2){
                result = result +' ' + q.front();
                q.pop();
            }
        }
    }
    while(!q.empty()){
        result = result + ' '+q.front();
        q.pop();
    }
    return result;
}


string postfix(string express){
    queue<char> q;
    string result="";
    for(int i=0; i<express.length(); i++){
        if(express[i] == ' '){
            continue;
        }
        else if(express[i] == '*'){
            result = result + ' ' + express[i+2] + " *"; //공백이 한칸씩 있어서 +2
            i+=2;
        }else if(express[i] == '+' || express[i] == '-'){
            q.push(express[i]);
            if(q.size() == 2){
                result = result + ' '+q.front();
                q.pop();
            }
        }else{
            result = result + ' '+express[i];
        }
    }
    while(!q.empty()){
        result = result + ' '+q.front();
        q.pop();
    }
    return result;
}

int main(){
    string express = "a + b * c - 1 + d * 5";
    string express2 = "a * b + c * d";
    string express3 = "a + b * c + d";
    string express4 = "a + b + c + d";

    string result = prefix(express);

    cout<<"prefix:  "<<result <<endl;

    string result2 = postfix(express);
    cout<<"postfix: "<<result2<<endl;
    result2 = postfix(express2);
    cout<<"postfix: "<<result2<<endl;
    result2 = postfix(express3);
    cout<<"postfix: "<<result2<<endl;
    result2 = postfix(express4);
    cout<<"postfix: "<<result2<<endl;
    

}
