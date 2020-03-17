#ifndef SERJ_PPARSE_H
#define SERJ_PPARSE_H
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include "serj_pparse_llist.h"
#include "serj_pparse_consts.h"
using namespace std;

#define PPARSE_ERR_HEAD "[PPARSE ERROR]: "
#define PPARSE_LOG_ERR(x) std::cerr << PPARSE_ERR_HEAD << x
#define PPARSE_LOG_OBJ_ERR(x, y) std::cerr << PPARSE_ERR_HEAD << " obj:  '" << x << "'\n\t\t" << y
#define PPARSE_LOG_HEAD "[PPARSE LOG]: "
#define PPARSE_LOG(x) std::cout << PPARSE_LOG_HEAD << x << std::endl

//cast last uncasted object to an object type
#define cast_pparsed_object(type) *static_cast<type*>(last_uncst_obj->object_data)

namespace serj{

//prepare pparse for usage
void pparse_init(){
    init_uncasted_objects();
    init_datasizes();
}

//exit pparse
void pparse_exit(){
    destroy_uncasted_objects();
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

//parse file data to usable objects
void pparse_object(string data, string label = "No Label"){
    if(data[0] != '$'){
        PPARSE_LOG_OBJ_ERR(data, "Invalid object initial character.\n");
        return;
    }
    
    //get architecture of object
    vector<string> bsizedefstr = split(uncase(data, '<', '>'), ',');
    vector<string> bsizedef;

    int bsize = 0;
    for(int i = 0; i < bsizedefstr.size(); i++){
        if(isalpha(bsizedefstr[i][0])){
            vector<string> bsdfp = split(bsizedefstr[i], '_');
            int ss = 1;
            if(bsdfp.size() > 1) ss = stoi(bsdfp[1]);
            bsize += pparse_type_bytesizes[bsdfp[0]] * ss;
            bsizedef.insert(bsizedef.end(), ss, bsdfp[0]);
        }else{
            bsize += stoi(bsizedefstr[i]);
        }
    }
//    cout << "bsize: " << bsize << endl;
    
    create_uncasted_object(bsize);
    last_uncst_obj->object_string = data;
    last_uncst_obj->object_label = label;
//    cout << data << " " << label << endl;
    char* objdata = static_cast<char*>(last_uncst_obj->object_data);
    
    //strip outermost braces
    data = uncase(data, '{', '}');
    vector<string> datas = split(data, ',');
    
    void* v = new char;
    int s, rep, di = 0;
    string sdfstr;
    
    for(int i = 0; i < bsizedef.size(); di++){
        delete static_cast<char*>(v);
        sdfstr = bsizedef[i];
        
        vector<string> dtsp = split(datas[di], '_');
        string dato = dtsp[0];
        
        if(dtsp.size() > 1){
            rep = stoi(dtsp[1]);
        }else{
            rep = 1;
        }

        s = pparse_type_bytesizes[sdfstr];
        v = new char[s];
        //actual data parse
        pparse_typefuncs[sdfstr](dato, v);
        for(int rr = 0; rr < rep; rr++){
            for(int j = 0; j < s; j++){
                *objdata = static_cast<char*>(v)[j];
                objdata++;
            }
        }
        
        i += rep;
    }
    
    delete static_cast<char*>(v);
}

void pparse_file(string path){
    ifstream ist(path);
    string label = "No Label";
    string comment;
    
    ostringstream obj("");
    
    char c;
    int lb = 0;
    bool objective = false;
    string strb;

    map<string, string> tdefs;
    vector<string> keys;
    
    while(ist >> c){
        if(c == '$'){
            objective = true;
            obj << c;
            getline(ist, strb, '{');
            obj << strb;
            obj << '{';
            lb = 0;
            continue;
        }else if(c == ' ' || c == '\n' || c == '\t'){
            continue;
        }else if(c == '?'){
            getline(ist, label);
            continue;
        }else if(c == '#'){
            getline(ist, comment);
            PPARSE_LOG("File comment: '" << comment << "'");
            continue;
        }else if(c == '!'){
            ist >> strb;
            string def;
            ist.ignore(1);
            getline(ist, def);
            keys.push_back(strb);
            tdefs.insert({strb, def});
            PPARSE_LOG("File text macro: " << strb << " -> " << def);
        }
        
        if(objective){
            if(c == '{'){
                lb++;
            }else if(c == '}'){
                lb--;
            }
            
            obj << c;
            if(lb == -1){
                objective = false;
                strb = obj.str();
                
                for(int i = 0; i < keys.size(); i++){
                    string dd = tdefs[keys[i]];
                    while(replace(strb, keys[i], dd)){}
                }
                
                pparse_object(strb, label);
                label = "No Label";
                obj = ostringstream("");
            }
        }
    }
    
    ist.close();
}

}

#endif /* SERJ_PPARSE_H */

