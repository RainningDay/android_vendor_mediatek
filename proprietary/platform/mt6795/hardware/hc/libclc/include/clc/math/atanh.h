#undef atanh
#define atanh __clc_atanh

#define __CLC_BODY <clc/math/unary_decl.inc>
#define __CLC_FUNCTION __clc_atanh

#include <clc/math/gentype.inc>

#undef __CLC_BODY
#undef __CLC_FUNCTION

