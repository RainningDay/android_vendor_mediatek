#undef cosh
#define cosh __clc_cosh

#define __CLC_BODY <clc/math/unary_decl.inc>
#define __CLC_FUNCTION __clc_cosh

#include <clc/math/gentype.inc>

#undef __CLC_BODY
#undef __CLC_FUNCTION

