#undef fma
#define fma __clc_fma

#define __CLC_BODY <clc/math/ternary_decl.inc>
#define __CLC_FUNCTION __clc_fma

#include <clc/math/gentype.inc>

#undef __CLC_BODY
#undef __CLC_FUNCTION

