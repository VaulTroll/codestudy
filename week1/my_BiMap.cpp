#include<iostream>
#include<string.h>
#include<fstream>
#include<sstream>
#include<set>
#include<map>
#include<list>

using namespace std;


int main(){

    string str_buf;
    fstream fs;

    multimap<string, string> mapA;
    multimap<string, string> mapB;

    fs.open("data.csv",ios::in);

    while(!fs.eof()){
        getline(fs, str_buf);
        int count = 0;
        string k;
        string buff;
        istringstream ss(str_buf);

        while(getline(ss,buff,',')){
            if(count ==1)
                k = buff;
            if(count==2){
                mapA.insert(pair<string, string>(k,buff));
                mapB.insert(pair<string, string>(buff,k));
            }
            count++;
        }
    }
    fs.close();

///////////////////////////////////////////////////////////////

    auto it = mapA.find("redis");
    if(it == mapA.end()){
        cout<<"not found";
    }
    else{
        cout << "이름이 '" << it->first <<"'인 저장소의 언어는?  "<< it->second << endl;
    }

//////////////////////////////////////////////////////////////

    cout << "언어가 'Ruby'인 저장소의 개수는? "<<mapB.count("Ruby") << endl;

///////////////////////////////////////////////////////////////

    multimap<string, string>::iterator ita = mapA.begin();
    int p_count = 0;
    for(; ita !=mapA.end(); ita++){
        if(ita->first.front()=='i'){
            if(ita->second.compare("Python") == 0){
                //cout << ita->first << " "<<ita->second <<endl;
                p_count++;
            }
        }
    }; 
    cout<< "이름이 'i'로 시작하는 저장소 중 언어가 'Python'인 저장소의 개수는? "<<p_count<<"개 "<<endl;
/////////////////////////////////////////////////////////////////


    multimap<string, string>::iterator itb = mapB.begin();
    int c_count =0;
    for(; itb !=mapB.end(); itb++){
        if(itb->first == "C"){
            if(itb->second.size()>=20){
                //cout<<itb->first <<"  "<< itb->second <<endl;
                c_count++;
            }
        }
    }

    cout<<"언어가 'C'인 저장소 중 이름의 길이가 20자 이상인 저장소의 개수는? "<<c_count<<"개 "<<endl;

}
