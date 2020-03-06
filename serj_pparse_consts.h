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
        {"uchar", pparse_uchar_s},
        {"char", pparse_schar_s},
        {"ushort", pparse_ushort_s},
        {"short", pparse_sshort_s},
        {"uint", pparse_uint_s},
        {"int", pparse_sint_s},
        {"ulong", pparse_ulong_s},
        {"long", pparse_slong_s},
        {"udlong", pparse_udlong_s},
        {"dlong", pparse_sdlong_s},
        {"float", pparse_float_s},
        {"double", pparse_double_s},
    });
}

}

//#undef pparse_uchar_s
//#undef pparse_schar_s
//#undef pparse_ushort_s
//#undef pparse_sshort_s
//#undef pparse_uint_s
//#undef pparse_sint_s
//#undef pparse_ulong_s
//#undef pparse_slong_s
//#undef pparse_udlong_s
//#undef pparse_sdlong_s
//#undef pparse_float_s
//#undef pparse_double_s

#endif /* SERJ_PPARSE_CONSTS_H */

