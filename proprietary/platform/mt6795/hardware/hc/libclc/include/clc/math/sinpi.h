#undef sinpi
#define sinpi __clc_sinpi

#define __CLC_BODY <clc/math/unary_decl.inc>
#define __CLC_FUNCTION __clc_sinpi

#include <clc/math/gentype.inc>

#undef __CLC_BODY
#undef __CLC_FUNCTION

