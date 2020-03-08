#ifndef SERJ_PPARSE_H
#define SERJ_PPARSE_H
#include <string>
#include <sstream>
#include <vector>
#include "serj_pparse_llist.h"
#include "serj_pparse_consts.h"

#define PPARSE_ERR_HEAD "[PPARSE ERROR]: "
#define PPARSE_LOG_ERR(x) std::cerr << PPARSE_ERR_HEAD << x
#define PPARSE_LOG_OBJ_ERR(x, y) std::cerr << PPARSE_ERR_HEAD << " obj: '" << x << "'\n\t\t" << y
#define pparse_object_to(str, type, var) pparse_object(str); var = *static_cast<type*>(last_unprs_obj->object_data);
using namespace std;

namespace serj{

//prepare pparse for usage
void pparse_init(){
    init_unparsed_objects();
    init_datasizes();
}

//exit pparse
void pparse_exit(){
    destroy_unparsed_objects();
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

//cut first and last character from string
string trimcase(string str){
    return str.substr(1, str.size() - 1);
}

//parse file data to usable object
void pparse_object(string data){
    if(data[0] != '$'){
        PPARSE_LOG_OBJ_ERR(data, " Invalid object initial character.\n");
        return;
    }
    
    //get architecture of object
//    vector<string> bsizedef = split(data.substr(2, data.length() - data.find_first_of(">", 2, data.length())), ',');
    vector<string> bsizedef = split(uncase(data, '<', '>'), ',');

    int bsize = 0;
    for(int i = 0; i < bsizedef.size(); i++){
        if(isalpha(bsizedef[i][0])){
            bsize += pparse_type_bytesizes[bsizedef[i]];
        }else{
            bsize += stoi(bsizedef[i]);
        }
    }
    cout << "bsize: " << bsize << endl;
    
//    char* objdata = static_cast<char*>(create_unparsed_object(bsize)->object_data);
    create_unparsed_object(bsize);
    char* objdata = static_cast<char*>(last_unprs_obj->object_data);
    
    //strip outermost braces
    data = uncase(data, '{', '}');
    vector<string> datas = split(data, ',');
    
    void* v = new char;
    int s;
    string sdfstr;
    
    for(int i = 0; i < bsizedef.size(); i++){
        cout << "PARSING '" << datas[i] << "'\n";
        delete static_cast<char*>(v);
        sdfstr = bsizedef[i];
        s = pparse_type_bytesizes[sdfstr];
        cout << sdfstr << " DATA POINT s:" << s << "\n";
        v = new char[s];
        pparse_typefuncs[sdfstr](datas[i], v);
        cout << *static_cast<float*>(v) << endl;
        for(int j = 0; j < s; j++){
            cout << "\tByte " << j << " : " << static_cast<unsigned char*>(v)[j] + 0 << "\n";
            *objdata = static_cast<char*>(v)[j];
            objdata++;
        }
    }
    
    delete static_cast<char*>(v);
}

}

#endif /* SERJ_PPARSE_H */

