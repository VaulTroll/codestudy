#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<set>
#include<map>

using namespace std;


int main(){

    cout<<endl;

    string str_buf;
    fstream fs;

    map<string, int> mapT; 

    fs.open("data.csv",ios::in);

    while(!fs.eof()){
        getline(fs, str_buf);
        int count = 0;
        string k;
        string buff;
        istringstream ss(str_buf);

        while(getline(ss,buff,',')){
            if(count == 2){   //언어만 골라낸다. 
                auto it = mapT.find(buff); 
                if(it == mapT.end()){ //만약 key값이 없다면 처음 보는 언어
                    mapT.insert(make_pair(buff,0)); //insert
                }
                else{
                    it->second ++;//만약 key값이 중복이라면 카운트를 올려준다.
                }
            }
            count++;
            
        }
    }
    fs.close();

//////////////////////////////////////////////////////////////

    auto ith = mapT.find("HTML");
    if(ith == mapT.end()){
        cout<<"언어 'HTML'을 찾을 수 없음 "<<endl;
    }
    else{
        cout << "언어 'HTML'의 개수는? "<< int(ith->second)+1 <<endl;
    }
    
    
///////////////////////////////////////////////////////////////
    map<string, int>::iterator ita = mapT.begin();
    int e_count = 0;
    for(; ita !=mapT.end(); ita++){
        e_count += (int)ita->second+1; //0부터 카운트되기 때문에 1을 더해줌
    }; 

    cout<<"저장된 총 원소의 개수는? " << e_count<<"개"<<endl;
///////////////////////////////////////////////////////////////////////

    cout << "저장된 언어의 종류는 몇 가지인가? "<< mapT.size() << endl;

/////////////////////////////////////////////////////////////////

    ita = mapT.begin();
    int s_count =0;
    for(; ita !=mapT.end(); ita++){
        if(ita->first.find("Script")!=string::npos){//string의 find함수 이용, 없으면 npos 반환
            //cout<<ita->first<<endl;
            s_count++;
        }
    }

    cout<<"이름에 Script가 포함된 언어의 원소 개수는? " << s_count<<"개"<<endl;

}
