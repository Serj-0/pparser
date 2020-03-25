#ifndef SERJ_PPARSE_STRING_H
#define SERJ_PPARSE_STRING_H
#include <sstream>
using namespace std;

//get string from within braces\n
//e.g. "{content}" -> "content"
string uncase(string str, char lbrace, char rbrace){
    int fst = str.find_first_of(lbrace);
    int lbrc = 0;
    for(int i = fst + 1; i < str.size(); i++){
        lbrc += (str[i] == lbrace) - (str[i] == rbrace);
        if(lbrc < 0 && str[i] == rbrace){
            return str.substr(fst + 1, i - fst - 1);
        }
    }
    return str;
}

//split string by delimiter
vector<string> split(string str, char delim){
    istringstream ist(str);
    string elem;
    vector<string> splits;
    while(getline(ist, elem, delim)){
        splits.push_back(elem);
    }
    return splits;
}

//cut first and last character from string
string trimcase(string str){
    return str.substr(1, str.size() - 2);
}

bool replace(string& target, string remove, string replace){
    int spos = -1, ccount = 0, rsize = remove.size();
    
    for(int i = 0; i < target.size(); i++){
        if(spos == -1 && target[i] == remove[0]){
            spos = i;
            ccount++;
            continue;
        }
        
        if(spos > -1){
            if(target[i] == remove[ccount]){
                ccount++;
            }else{
                spos = -1;
                ccount = 0;
                continue;
            }
        }
        
        if(ccount == rsize){
            target.replace(spos, rsize, replace);
            return true;
        }
    }
    return false;
}

#endif /* SERJ_PPARSE_STRING_H */

