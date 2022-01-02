#ifndef __MC_ITERATOR_H__
#define __MC_ITERATOR_H__

#include "mc_type.h" 

#define ITOR_FL __FILE__##__LINE__

#define iterator 			ITOR_FL##iterator
#define reverse_iterator 	ITOR_FL##reverse_iterator
#define ITOR 				ITOR_FL##ITOR
#define DITOR 				ITOR_FL##DITOR
#define c_ITOR				ITOR_FL##c_ITOR
#define real_iterator		ITOR_FL##real_iterator
#define iterator_begin		ITOR_FL##iterator_begin
#define iterator_end		ITOR_FL##iterator_end
#define iterator_technique	ITOR_FL##iterator_technique
#define iterator_copy		ITOR_FL##iterator_copy

#define itTod( type, it)\
	(*(type*)*(it))

#define itTop( type, it)\
	((type*)*(it))

typedef void* iterator[5];//是元素的二级指针//解决强制类型转换问题 
typedef iterator reverse_iterator;
typedef struct real_iterator real_iterator;//真正的iterator iterator用real_iterator的方式赋值
typedef struct iter_technique iter_technique;
typedef void *ITOR,*DITOR;//iterator第一个元素
typedef const ITOR c_ITOR;

struct real_iterator{
	pTData cur;
	pTData* begin;
	pTData* curEnd;
	pTData* reaEnd;
	size_t offs;
};

struct iter_technique{
	DITOR 		(*begin)(ITOR it);
	DITOR 		(*end)(ITOR it);
	int   		(*copy)(ITOR it,c_ITOR base_it);
	
	DITOR 		(*prev)(ITOR it);
	DITOR 		(*next)(ITOR it);
	DITOR 		(*index)(ITOR it,int pos);
	mcbool 		(*hasPrev)(ITOR it);
	mcbool 		(*hasNext)(ITOR it);
	int 		(*insert)(ITOR it,c_pTData pdata,iter_technique* pittq);
	int			(*erase)(ITOR it,iter_technique* pittq);
	
	void 		(*copyCons)(pTData ,pTData );
	void 		(*cons)(pTData );
	void 		(*dess)(pTData );
	int 		(*cmp)(pTData ,pTData ); 
};

int     iterator_technique(iter_technique* pittq);

DITOR   iterator_begin(ITOR it);
DITOR   iterator_end(ITOR it);
int 	iterator_copy(ITOR it,c_ITOR base_it);

#endif
