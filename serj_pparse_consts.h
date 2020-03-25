#ifndef SERJ_PPARSE_CONSTS_H
#define SERJ_PPARSE_CONSTS_H
#include <utility>
#include <map>
#include "serj_pparse_string.h"
using namespace std;

#define pparse_uchar_s sizeof(unsigned char)
#define pparse_schar_s sizeof(signed char)
#define pparse_ushort_s sizeof(unsigned short)
#define pparse_sshort_s sizeof(signed short)
#define pparse_uint_s sizeof(unsigned int)
#define pparse_sint_s sizeof(signed int)
#define pparse_ulong_s sizeof(unsigned long)
#define pparse_slong_s sizeof(signed long)
#define pparse_ullong_s sizeof(unsigned long long)
#define pparse_sllong_s sizeof(signed long long)
#define pparse_float_s sizeof(float)
#define pparse_double_s sizeof(double)
#define pparse_ldouble_s sizeof(long double)
#define pparse_rawchar_s sizeof(char)
#define pparse_stlstring_s sizeof(string)

namespace serj{

void pparse_uchar(string& str, void* ptr){*static_cast<unsigned char*>(ptr) = stoi(str);}
void pparse_ushort(string& str, void* ptr){*static_cast<unsigned short*>(ptr) = stoi(str);}
void pparse_uint(string& str, void* ptr){*static_cast<unsigned int*>(ptr) = stoi(str);}
void pparse_ulong(string& str, void* ptr){*static_cast<unsigned long*>(ptr) = stol(str);}
void pparse_ullong(string& str, void* ptr){*static_cast<unsigned long long*>(ptr) = stoll(str);}
void pparse_schar(string& str, void* ptr){*static_cast<signed char*>(ptr) = stoi(str);}
void pparse_sshort(string& str, void* ptr){*static_cast<signed short*>(ptr) = stoi(str);}
void pparse_sint(string& str, void* ptr){*static_cast<signed int*>(ptr) = stoi(str);}
void pparse_slong(string& str, void* ptr){*static_cast<signed long*>(ptr) = stol(str);}
void pparse_sllong(string& str, void* ptr){*static_cast<signed long long*>(ptr) = stoll(str);}
void pparse_float(string& str, void* ptr){*static_cast<float*>(ptr) = stof(str);}
void pparse_double(string& str, void* ptr){*static_cast<double*>(ptr) = stod(str);}
void pparse_ldouble(string& str, void* ptr){*static_cast<long double*>(ptr) = stold(str);}
void pparse_rawchar(string& str, void* ptr){
    char c;
    if(str[0] == '\\'){
        switch(str[1]){
        case 'n':
            c = '\n';
            break;
        case 't':
            c = '\t';
            break;
        case '0':
            c = '\0';
            break;
        case '\\':
                c = '\\';
            break;
        }
    }else{
        c = str[0];
    }
    *static_cast<char*>(ptr) = c;
}
void pparse_stlstring(string& str, void* ptr){
//    cout << "input string " << str << endl;
    string copy = str;
//    cout << "trimmed string " << trimmed << endl;
    for(int i = 0; i < copy.size(); i++){
//        cout << trimmed[i] << endl;
        if(copy[i] == '\\'){
            switch(copy[i + 1]){
            case 'n':
                copy.replace(i, 2, "\n");
                break;
            case 't':
                copy.replace(i, 2, "\t");
                break;
            case '0':
                copy.replace(i, 2, "\0");
                break;
            case '\\':
                copy.replace(i, 2, "\\");
                break;
            }
        }
    }
    
    *static_cast<string*>(ptr) = copy;
}

map<string, int> pparse_typesizes;
map<string, void(*)(string&, void*)> pparse_typefuncs;

//initalize a map of type names and their byte sizes
void init_datasizes(){
    pparse_typesizes.insert({
        {"uchar", pparse_uchar_s},
        {"ushort", pparse_ushort_s},
        {"uint", pparse_uint_s},
        {"ulong", pparse_ulong_s},
        {"ullong", pparse_ullong_s},
        {"char", pparse_schar_s},
        {"short", pparse_sshort_s},
        {"int", pparse_sint_s},
        {"long", pparse_slong_s},
        {"llong", pparse_sllong_s},
        {"float", pparse_float_s},
        {"double", pparse_double_s},
        {"ldouble", pparse_ldouble_s},
        {"rawchar", pparse_rawchar_s},
        {"string", pparse_stlstring_s},
    });
    
    pparse_typefuncs.insert({
        {"uchar", pparse_uchar},
        {"ushort", pparse_ushort},
        {"uint", pparse_uint},
        {"ulong", pparse_ulong},
        {"ullong", pparse_ullong},
        {"char", pparse_schar},
        {"short", pparse_sshort},
        {"int", pparse_sint},
        {"long", pparse_slong},
        {"llong", pparse_sllong},
        {"float", pparse_float},
        {"double", pparse_double},
        {"ldouble", pparse_ldouble},
        {"rawchar", pparse_rawchar},
        {"string", pparse_stlstring},
    });
}

}

#endif /* SERJ_PPARSE_CONSTS_H */

