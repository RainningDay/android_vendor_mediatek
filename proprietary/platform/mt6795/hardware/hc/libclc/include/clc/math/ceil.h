#undef ceil
#define ceil __clc_ceil

//#define __CLC_FUNCTION __clc_ceil
//#define __CLC_INTRINSIC "llvm.ceil"
//#include <clc/math/unary_intrin.inc>

#define __CLC_BODY <clc/math/unary_decl.inc>
#define __CLC_FUNCTION __clc_ceil

#include <clc/math/gentype.inc>

#undef __CLC_BODY
#undef __CLC_FUNCTION
