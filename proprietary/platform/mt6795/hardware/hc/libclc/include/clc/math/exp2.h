#undef exp2
#define exp2 __clc_exp2

#define __CLC_BODY <clc/math/unary_decl.inc>
#define __CLC_FUNCTION __clc_exp2

#include <clc/math/gentype.inc>

#undef __CLC_BODY
#undef __CLC_FUNCTION

