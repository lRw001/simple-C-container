#include "mc_stl_defxxx.h"
#include "mc_vector.h"

#define __vector_realloc	VEC_FL##__vector_realloc

typedef struct real_vector real_vector;
struct real_vector{
	pTData slider;
	pTData begin;
	pTData end;
	size_t offs;
};

enum{default_size = 12};

INLINE int __vector_realloc(int offs,pTData* pslider,pTData* pbegin,pTData* pend,int size){
	pTData tbegin = NULL;
	if(pslider == NULL || pbegin == NULL || pbegin == NULL || pend == NULL){
		printf("Func vector_realloc ptr err: %d\n",-1);
		return -1;
	}
	if(offs <= 0){
		printf("Func vector_realloc type err: %d\n",-2);
		return -2;		
	}
	tbegin = mc_pRealloc(*pbegin,__Byte * size * offs);
	if(tbegin == NULL){
		printf("Func vector_realloc alloc err: %d\n",-3);
		return -3;
	}
	if(*pbegin != tbegin){
		*pslider = (mcbyte*)tbegin + ((int)*pslider - (int)*pbegin);
		*pbegin = tbegin;
	}
	*pend = (mcbyte*)tbegin + __Byte * size * offs;
	return 0;
}

static vec_technique vec_technique_base = {
	vector_size,
	vector_capacity,
	vector_pushBack,
	vector_popBack,
	vector_front,
	vector_back,
	vector_at,
	vector_insert,
	vector_erase,
	vector_iterator,
	vector_iter_techinique,
	vector_iter_begin,
	vector_iter_end,
	vector_index,
	vector_resize,
	NULL,NULL,NULL,NULL	
};

int		 	vector_create(vector* pvec,size_t type){
	real_vector* pRvec = NULL;
	pvec->hdle = NULL;
	if(pvec == NULL){
		printf("Func vector_create ptr err: %d\n",-1);
		return -1;	
	}
	if((int)type <= 0){
		printf("Func vector_create type err: %d\n",-2);
		return -2;
	}
	pRvec = (real_vector*)mc_pMalloc(sizeof(real_vector));
	if(pRvec == NULL){
		printf("Func vector_create alloc err: %d\n",-3);
		return -3;
	}
	pRvec->offs = type;
	pRvec->begin = mc_pMalloc(__Byte * type * default_size);
	if(pRvec->begin == NULL){
		printf("Func vector_create alloc err: %d\n",-3);
		free(pRvec);
		return -3;
	}
	pRvec->slider = pRvec->begin;
	pRvec->end = (mcbyte*)pRvec->begin + __Byte * type * default_size;
	pvec->hdle = pRvec;
	return 0;
}

int 		vector_vec_technique(vec_technique* vectq){//给予基本的方法赋值 
	if(vectq == NULL){
		printf("Func vector_vec_technique err: %d\n",-1);
		return -1;
	}
	*vectq = vec_technique_base;
	return 0;
}
 
int 		vector_destroy(vector* pvec,vec_technique* pvectq){
	real_vector* pRvec = NULL;
	if(pvec == NULL){
		printf("Func vector_destroy ptr err: %d\n",-1);
		return -1;
	}
	pRvec = (real_vector*)pvec->hdle;
	if(pRvec == NULL){
		printf("Func vector_destroy ptr err: %d\n",-1);
		return -1;
	}
	if(pvectq != NULL && pvectq->dess != NULL){//需要析构
		iterator it;
		iter_technique ittq;
		vector_iterator(*pvec,it);
		vector_iter_techinique(&ittq,pvectq);
		for(*it = vector_iter_begin(*pvec);*it != vector_iter_end(*pvec); *it = vector_iter_next(it)){
			pvectq->dess(*it);
		}
	}
	mc_pFree(pRvec->begin);
	mc_pFree(pRvec);
	pvec->hdle = NULL;
	return 0;
}

int 	 	vector_size(c_vector vec){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_size ptr err: %d\n",-1);
		return -1;
	}
	pRvec = (real_vector*)vec.hdle;
	return ((int)pRvec->slider - (int)pRvec->begin) / pRvec->offs;
}

int 	 	vector_capacity(c_vector vec){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_capcity ptr err: %d\n",-1);
		return -1;
	}
	pRvec = (real_vector*)vec.hdle;
	return ((int)pRvec->end - (int)pRvec->begin) / pRvec->offs;	
}

int		 	vector_pushBack(c_vector vec,c_pTData pdata,vec_technique* pvectq){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL || pdata == NULL){
		printf("Func vector_pushBack ptr err: %d\n",-1);
		return -1;
	}
	pRvec = (real_vector*)vec.hdle;
	if(vector_size(vec) / 2 * 3 >= vector_capacity(vec)){
		__vector_realloc(pRvec->offs,&pRvec->slider,&pRvec->begin,&pRvec->end,vector_capacity(vec) / 2 * 3);
	}
	if(pvectq != NULL && pvectq->copyCons != NULL){
		pvectq->copyCons(pRvec->slider,pdata);
	}
	else{
		memcpy(pRvec->slider,pdata,pRvec->offs);
	}
	pRvec->slider = (mcbyte*)pRvec->slider + pRvec->offs; 
	return 0;
}

int	 		vector_popBack(c_vector vec,vec_technique* pvectq){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_pushBack ptr err: %d\n",-1);
		return -1;
	}
	pRvec = (real_vector*)vec.hdle;
	pRvec->slider = (mcbyte*)pRvec->slider - pRvec->offs;
	if(pvectq != NULL && pvectq->dess != NULL){
		pvectq->dess(pRvec->slider);
	}
	return 0;
}

pTData 		vector_front(c_vector vec){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_front ptr err: %d\n",-1);		
		return NULL;
	}
	pRvec = (real_vector*)vec.hdle;
	return pRvec->begin;
}

pTData 		vector_back(c_vector vec){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_front ptr err: %d\n",-1);		
		return NULL;
	}
	pRvec = (real_vector*)vec.hdle;
	return (mcbyte*)pRvec->slider - pRvec->offs;
}

pTData 		vector_at(c_vector vec,int pos,int *err){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_at ptr err: %d\n",-1);
		if(err != NULL){
			*err = -1;
		}
		return NULL;		
	}
	if(pos < 0 || pos >= vector_size(vec)){
		printf("Func vector_at size err: %d\n",-4);
		if(err != NULL){
			*err = -4;
		}
		return NULL;
	}
	pRvec = (real_vector*)vec.hdle;
	if(err != NULL){
		*err = 0;
	}
	return (mcbyte*)pRvec->begin + pos * pRvec->offs;
}

int			vector_insert(c_vector vec,DITOR dit,c_pTData pdata,vec_technique* pvectq){
	real_vector* pRvec = NULL;
	pTData current = NULL;
	int offs = 0;
	if(vec.hdle == NULL || pdata == NULL || dit == NULL){
		printf("Func vector_insert ptr err: %d\n",-1);
		return -1;
	}
	pRvec = (real_vector*)vec.hdle;
	offs = pRvec->offs;
	if(((int)dit - (int)pRvec->begin) / offs > vector_size(vec)){
		printf("Func vector_insert itor err: %d\n",-1);
		return -5;		
	}
	pRvec->slider = (mcbyte*)pRvec->slider + offs;
	if(vector_size(vec) / 2 * 3 >= vector_capacity(vec)){
		__vector_realloc(offs,&pRvec->slider,&pRvec->begin,&pRvec->end,vector_capacity(vec) / 2 * 3);
	}	
	for(current = pRvec->slider;current != dit;current = (mcbyte*)current - offs){
		memcpy(current,(mcbyte*)current - offs,offs);
	}
	if(pvectq != NULL && pvectq->copyCons != NULL){
		pvectq->copyCons(dit,pdata);
	}
	else{
		memcpy(dit,pdata,offs);
	}
	return 0;
}

int			vector_erase(c_vector vec,DITOR dit,vec_technique* pvectq){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL || dit == NULL){
		printf("Func vector_insert ptr err: %d\n",-1);
		return -1;
	}
	pRvec = (real_vector*)vec.hdle;
	if(((int)dit - (int)pRvec->begin) / pRvec->offs >= vector_size(vec)){
		printf("Func vector_insert itor err: %d\n",-1);
		return -5;		
	}
	if(pvectq != NULL && pvectq->dess != NULL){
		pvectq->dess(dit);
	}
	memcpy(dit,(mcbyte*)dit + pRvec->offs,((int)pRvec->slider - (int)dit));
	pRvec->slider = (mcbyte*)pRvec->slider - pRvec->offs;
	return 0;
}

int 		vector_resize(c_vector vec,int size){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_resize ptr err: %d\n",-1);
		return -1;
	}
	if(size < vector_size(vec)){
		printf("Func vector_resize size err: %d\n",-1);
		return -4;
	}
	pRvec = (real_vector*)vec.hdle;
	__vector_realloc(pRvec->offs,&pRvec->slider,&pRvec->begin,&pRvec->end,size);
	return 0;
}

int 		vector_iterator(c_vector vec,iterator it){
	real_iterator* rit = NULL;
	real_vector* pRvec = NULL;
	if(it == NULL || vec.hdle == NULL){
		printf("Func vector_iterator ptr err: %d\n",-1);
		return -1;
	}
	pRvec = (real_vector*)vec.hdle;
	rit = (real_iterator*)it;
	rit->cur = pRvec->begin;
	rit->begin = &pRvec->begin;
	rit->curEnd = &pRvec->slider;
	rit->reaEnd = &pRvec->end;
	rit->offs = pRvec->offs;
	return 0;
}

int 		vector_iter_techinique(iter_technique* pittq,vec_technique* pvectq){
	iterator_technique(pittq);
	pittq->prev 	= vector_iter_prev;
	pittq->next 	= vector_iter_next;
	pittq->index 	= vector_iter_index;
	pittq->hasPrev  = vector_iter_hasPrev;
	pittq->hasNext  = vector_iter_hasNext;
	pittq->insert	= vector_iter_insert;
	pittq->erase	= vector_iter_erase;
	pittq->copyCons = pvectq->copyCons;
	pittq->cons		= pvectq->cons;
	pittq->dess		= pvectq->dess;
	pittq->cmp		= pvectq->cmp;
	
}

DITOR		vector_iter_begin(c_vector vec){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_iter_begin ptr err: %d\n",-1);		
		return NULL;
	}
	pRvec = (real_vector*)vec.hdle;
	return pRvec->begin;
}

DITOR		vector_iter_end(c_vector vec){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_iter_end ptr err: %d\n",-1);		
		return NULL;
	}
	pRvec = (real_vector*)vec.hdle;
	return pRvec->slider;	
}

DITOR		vector_index(c_vector vec,int pos){
	real_vector* pRvec = NULL;
	if(vec.hdle == NULL){
		printf("Func vector_index ptr err: %d\n",-1);
		return NULL;		
	}
	if(pos < 0 || pos > vector_size(vec)){
		printf("Func vector_index pos err: %d\n",-1);
		return NULL;
	}
	pRvec = (real_vector*)vec.hdle;
	return (mcbyte*)pRvec->begin + pos * pRvec->offs;
}

DITOR		vector_iter_index(ITOR it,int pos){
	real_iterator* pRit = NULL;
	DITOR tmp = NULL;
	if(it == NULL){
		printf("Func vector_iter_index ptr err: %d\n",-1);
		return NULL;
	}
	if(pos < 0){
		printf("Func vector_iter_index pos err: %d\n",-1);		
		return NULL;
	}
	pRit = (real_iterator*)it;
	tmp = (DITOR)((mcbyte*)*(pRit->begin) + pos * pRit->offs);
	if((int)tmp >= (int)*(pRit->curEnd)){
		printf("Func vector_iter_index pos err: %d\n",-1);
		return NULL;
	}
	return  tmp;
}

DITOR		vector_iter_prev(ITOR it){
	real_iterator* pRit = NULL;
	if(it == NULL){
		printf("Func vector_iter_prev ptr err: %d\n",-1);
		return NULL;
	}
	pRit = (real_iterator*)it;
	if(pRit->cur == (mcbyte*)*(pRit->begin) - pRit->offs){
		return pRit->cur;
	}
	return (mcbyte*)pRit->cur - pRit->offs;
}

DITOR 		vector_iter_next(ITOR it){
	real_iterator* pRit = NULL;
	if(it == NULL){
		printf("Func vector_iter_next ptr err: %d\n",-1);
		return NULL;
	}
	pRit = (real_iterator*)it;
	if(pRit->cur == *(pRit->curEnd)){
		return pRit->cur;
	}
	return (mcbyte*)pRit->cur + pRit->offs;
}

mcbool		vector_iter_hasPrev(ITOR it){
	return *(void**)it && *(void**)it != vector_iter_prev(it) ? 1 : 0;
}

mcbool		vector_iter_hasNext(ITOR it){
	return *(void**)it && *(void**)it != vector_iter_next(it) ? 1 : 0;
}

int 		vector_iter_insert(ITOR it,c_pTData pdata,iter_technique* pittq){
	real_iterator* pRit = NULL;
	pTData current = NULL;
	int offs = 0;
	if(it == NULL || pdata == NULL || *(void**)it == NULL){
		printf("Func vector_iter_insert ptr err: %d\n",-1);
		return -1;
	}
	pRit = (real_iterator*)it;
	offs = pRit->offs;
	if(((int)*(void**)it - (int)*(pRit->begin)) / offs > (int)*(pRit->curEnd) - (int)*(pRit->begin)){
		printf("Func vector_iter_insert itor err: %d\n",-1);
		return -5;		
	}
	*(pRit->curEnd) = (mcbyte*)*(pRit->curEnd) + offs;
	if(((int)*(pRit->curEnd) - (int)*(pRit->begin)) / 2 * 3 >= (int)*(pRit->reaEnd) - (int)*(pRit->begin)){
		__vector_realloc(offs,pRit->curEnd,pRit->begin,pRit->reaEnd,((int)*(pRit->reaEnd) - (int)*(pRit->begin)) / 2 * 3);
	}	
	for(current = *(pRit->curEnd);current != *(void**)it;current = (mcbyte*)current - offs){
		memcpy(current,(mcbyte*)current - offs,offs);
	}
	if(pittq != NULL && pittq->copyCons != NULL){
		pittq->copyCons(*(void**)it,pdata);
	}
	else{
		memcpy(*(void**)it,pdata,offs);
	}
	return 0;	
}

int			vector_iter_erase(ITOR it,iter_technique* pittq){
	real_iterator* pRit = NULL;
	if(it == NULL || *(void**)it == NULL){
		printf("Func vector_iter_erase ptr err: %d\n",-1);
		return -1;
	}
	pRit = (real_iterator*)it;
	if(((int)*(void**)it - (int)*(pRit->begin)) / pRit->offs >= ((int)*(pRit->curEnd) - (int)*(pRit->begin))){
		printf("Func vector_iter_erase itor err: %d\n",-1);
		return -5;		
	}
	if(pittq != NULL && pittq->dess != NULL){
		pittq->dess(*(void**)it);
	}
	memcpy(*(void**)it,(mcbyte*)*(void**)it + pRit->offs,((int)*(pRit->curEnd) - (int)*(void**)it));
	*(pRit->curEnd) = (mcbyte*)*(pRit->curEnd) - pRit->offs;
	return 0;	
}
