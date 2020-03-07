#ifndef SERJ_PPARSE_CONSTS_H
#define SERJ_PPARSE_CONSTS_H
#include <utility>
#include <map>

#define pparse_uchar_s sizeof(unsigned char)
#define pparse_schar_s sizeof(signed char)
#define pparse_ushort_s sizeof(unsigned short)
#define pparse_sshort_s sizeof(signed short)
#define pparse_uint_s sizeof(unsigned int)
#define pparse_sint_s sizeof(signed int)
#define pparse_ulong_s sizeof(unsigned long)
#define pparse_slong_s sizeof(signed long)
#define pparse_udlong_s sizeof(unsigned long long)
#define pparse_sdlong_s sizeof(signed long long)
#define pparse_float_s sizeof(float)
#define pparse_double_s sizeof(double)
using namespace std;

namespace serj{

map<string, int> pparse_type_bytesizes;

//initalize a map of type names and their byte sizes
void init_datasizes(){
    pair<string, int> a = {"str", 1};
    pparse_type_bytesizes.insert({
        {"char", pparse_schar_s},
        {"short", pparse_sshort_s},
        {"int", pparse_sint_s},
        {"long", pparse_slong_s},
        {"dlong", pparse_sdlong_s},
        {"float", pparse_float_s},
        {"double", pparse_double_s},
    });
}

}

#endif /* SERJ_PPARSE_CONSTS_H */

