#undef tanpi
#define tanpi __clc_tanpi

#define __CLC_BODY <clc/math/unary_decl.inc>
#define __CLC_FUNCTION __clc_tanpi

#include <clc/math/gentype.inc>

#undef __CLC_BODY
#undef __CLC_FUNCTION

