#include "mc_stl_defxxx.h"
#include "mc_iterator.h"

static iter_technique iter_techinique_base = {
	iterator_begin,
	iterator_end,
	iterator_copy,
};

int iterator_technique(iter_technique* pittq){
	if(pittq == NULL){
		printf("Func iterator_begin ptr err: %d\n",-1);
		return -1;
	}
	*pittq = iter_techinique_base;
	return 0;
}

DITOR iterator_begin(ITOR it){
	real_iterator* pRit = NULL;
	if(it == NULL){
		printf("Func iterator_begin ptr err: %d\n",-1);
		return NULL;
	}
	pRit = (real_iterator*)it;
	return *(pRit->begin);
}

DITOR iterator_end(ITOR it){
	real_iterator* pRit = NULL;
	if(it == NULL){
		printf("Func iterator_end ptr err: %d\n",-1);
		return NULL;
	}
	pRit = (real_iterator*)it;
	return *(pRit->curEnd);	
} 

int 	iterator_copy(ITOR it,c_ITOR base_it){
	if(it == NULL || base_it == NULL){
		printf("Func iterator_copy ptr err: %d\n",-1);
		return -1;
	}
	*(real_iterator*)it = *(real_iterator*)base_it;
	return 0;
}
