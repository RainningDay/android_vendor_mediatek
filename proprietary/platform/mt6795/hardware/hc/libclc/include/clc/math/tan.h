#undef tan
#define tan __clc_tan

#define __CLC_BODY <clc/math/unary_decl.inc>
#define __CLC_FUNCTION __clc_tan

#include <clc/math/gentype.inc>

#undef __CLC_BODY
#undef __CLC_FUNCTION

