
#define __CLC_DECLARE_ATOMIC_XCHG(ADDRSPACE, TYPE) \
	_CLC_OVERLOAD _CLC_DECL TYPE __CLC_FUNCTION (volatile ADDRSPACE TYPE *, TYPE);

#define __CLC_DECLARE_ATOMIC_XCHG_ADDRSPACE(TYPE) \
	__CLC_DECLARE_ATOMIC_XCHG(global, TYPE); \
	__CLC_DECLARE_ATOMIC_XCHG(local, TYPE);

__CLC_DECLARE_ATOMIC_XCHG_ADDRSPACE(int);
__CLC_DECLARE_ATOMIC_XCHG_ADDRSPACE(uint);
__CLC_DECLARE_ATOMIC_XCHG_ADDRSPACE(float);
