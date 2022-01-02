#include "mc_ilist.h"
#include "mc_list.h"
#include "mc_stl_defxxx.h"

#define list_node_create	LS_FL##list_node_create

INLINE int list_node_create(int offs,pTData* retData){
	pTData rData = NULL;
	if(retData == NULL){
		printf("Func list_node_create ptr err: %d\n",-1);
		return -1;
	}
	if(offs <= 0){
		printf("func list_node_create ptr err: %d",-2);
		return -2;
	}
	rData = (pTData)mc_pMalloc(sizeof(iList_node) + __Byte * offs);
	if(rData == NULL){
		printf("func list_node_create alloc err: %d",-3);
		*retData = NULL;
		return -3;		
	}
	*retData = rData;
	return 0;
}

typedef struct real_list real_list;

struct real_list{
	iList header;
	void* null;
	int size;
	size_t offs;
};

static ls_technique ls_technique_base = {
	list_size,
	list_pushBack,
	list_popBack,
	list_front,
	list_back,
	list_at,
	list_insert,
	list_erase,
	list_iterator,
	list_iter_techinique,
	list_iter_begin,
	list_iter_end,
	list_index,
	NULL,NULL,NULL,NULL	
};

int list_create(list* pls,size_t type){
	real_list* pRls = NULL;
	if(pls == NULL){
		printf("Func list_create ptr err: %d\n",-1);
		return -1;
	}
	if(type <= 0){
		printf("Func list_create type err: %d\n",-2);
		return -2;
	}
	pRls = (real_list*)mc_pMalloc(sizeof(real_list));
	if(pRls == NULL){
		printf("Func list_create alloc err: %d\n",-3);
		return -3;
	}
	iList_header(&pRls->header);
	pRls->size = 0;
	pRls->offs = type;
	pls->hdle = pRls;
	return 0;
}

int list_ls_technique(ls_technique* plstq){
	if(plstq == NULL){
		printf("Func list_ls_technique ptr err: %d\n",-1);
		return -1;		
	}
	*plstq = ls_technique_base;
	return 0;
}

int list_destroy(list* pls,ls_technique* plstq){
	real_list* pRls = NULL;
	iList_node* current = NULL;
	iList_node* iLnext = NULL; 
	iList_node* iLend = NULL;
	if(pls == NULL || pls->hdle == NULL){
		printf("Func list_destroy ptr err: %d\n",-1);
		return -1;
	}
	pRls = (real_list*)pls->hdle;
	iLend = (iList_node*)pRls;
	if(plstq != NULL && plstq->dess != NULL){
		void (*dess)(pTData ) = plstq->dess;
		for(current = pRls->header.next;current != iLend;current = iLnext){
			iLnext = current->next;
			dess((mcbyte*)current + sizeof(iList_node));
			mc_pFree(current);
		}
	}
	else{
		for(current = pRls->header.next;current != iLend;current = iLnext){
			iLnext = current->next;
			mc_pFree(current);
		}
	}
	iList_header((iList*)pRls);
	pRls->size = 0;
	pRls->offs = 0;
	mc_pFree(pRls);
	pls->hdle = NULL;
	return 0;
}

int 	 	list_size(c_list ls){
	real_list* pRls = NULL;
	if(ls.hdle == NULL){
		printf("func list_size ptr err: %d\n",-1);
		return -1;
	}
	pRls = (real_list*)ls.hdle;
	return pRls->size;
}

int		 	list_pushBack(c_list ls,c_pTData pdata,ls_technique* plstq){
	real_list* pRls = NULL;
	iList_node* header = NULL;
	iList_node* rData = NULL;
	int ret = 0;
	if(ls.hdle == NULL){
		printf("func list_pushBack ptr err: %d\n",-1);
		return -1;
	}
	pRls = (real_list*)ls.hdle;
	header = &pRls->header;
	ret = list_node_create(pRls->offs,(void**)&rData);
	if(rData == NULL){
		return ret;
	}
	iList_tAdd(header,rData);
	if(plstq != NULL && plstq->copyCons != NULL){
		plstq->copyCons((mcbyte*)rData + sizeof(iList_node),pdata);
	}
	else{
		memcpy((mcbyte*)rData + sizeof(iList_node),pdata,pRls->offs);
	}
	pRls->size ++;
	return 0;
}

int	 		list_popBack(c_list ls,ls_technique* plstq){
	real_list* pRls = NULL;
	iList_node* node = NULL;
	if(ls.hdle == NULL){
		printf("func list_popBack ptr err: %d\n",-1);
		return -1;
	}
	pRls = (real_list*)ls.hdle;
	node = pRls->header.prev;
	iList_del(node);
	if(plstq != NULL && plstq->dess != NULL){
		plstq->dess(node);
	}
	mc_pFree(node);
	pRls->size --;
	return 0;
}

pTData 		list_front(c_list ls){
	real_list* pRls = NULL;
	iList_node* node = NULL;
	if(ls.hdle == NULL){
		printf("func list_front ptr err: %d\n",-1);
		return NULL;
	}
	pRls = (real_list*)ls.hdle;
	node = pRls->header.next;
	return (mcbyte*)node + sizeof(iList_node);
}

pTData 		list_back(c_list ls){
	real_list* pRls = NULL;
	iList_node* node = NULL;
	if(ls.hdle == NULL){
		printf("func list_back ptr err: %d\n",-1);
		return NULL;
	}
	pRls = (real_list*)ls.hdle;
	node = pRls->header.prev;
	return (mcbyte*)node + sizeof(iList_node);	
}

pTData 		list_at(c_list ls,int pos,int *err){
	real_list* pRls = NULL;
	iList_node* current = NULL;
	iList_node* iLend = NULL;
	int i = 0;
	if(ls.hdle == NULL){
		printf("func list_at ptr err: %d\n",-1);
		err && (*err = -1);
		return NULL;
	}
	pRls = (real_list*)ls.hdle;
	iLend = &pRls->header;
	if(pos < 0 || pos >= pRls->size){
		printf("func list_at pos err: %d\n",-3);
		err && (*err = -3);
		return NULL;
	}
	if(pos - 0 < pRls->size - pos){
		current = iLend;
		for(i = 0;i < pos; ++i){
			current = current->next;
		}
		return (mcbyte*)current->next + sizeof(iList_node);
	}
	else{
		current = iLend;
		for(i = pRls->size - 1;i > pos; --i){
			current = current->prev;
		}
		return (mcbyte*)current->prev + sizeof(iList_node);		
	}
}

DITOR		list_insert(c_list ls,DITOR dit,c_pTData pdata,ls_technique* plstq){
	real_list* pRls = NULL;
	iList_node* header = NULL;
	iList_node* rData = NULL;
	if(ls.hdle == NULL){
		printf("func list_insert ptr err: %d\n",-1);
		return dit;
	}
	pRls = (real_list*)ls.hdle;
	header = (iList_node*)((mcbyte*)dit - sizeof(iList_node));
	list_node_create(pRls->offs,(void**)&rData);
	if(rData == NULL){
		return dit;
	}
	iList_tAdd(header,rData);
	if(plstq != NULL && plstq->copyCons != NULL){
		plstq->copyCons((mcbyte*)rData + sizeof(iList_node),pdata);
	}
	else{
		memcpy((mcbyte*)rData + sizeof(iList_node),pdata,pRls->offs);
	}
	pRls->size ++;
	return (mcbyte*)rData + sizeof(iList_node);	
}

DITOR		list_erase(c_list ls,DITOR dit,ls_technique* plstq){
	real_list* pRls = NULL;
	iList_node* node = NULL;
	iList_node* next = NULL;
	if(ls.hdle == NULL){
		printf("func list_erase ptr err: %d\n",-1);
		return dit;
	}
	pRls = (real_list*)ls.hdle;
	node = (iList_node*)((mcbyte*)dit - sizeof(iList_node));
	next = node->next;
	iList_del(node);
	if(plstq != NULL && plstq->dess != NULL){
		plstq->dess(node);
	}
	mc_pFree(node);
	pRls->size --;
	return (mcbyte*)next + sizeof(iList_node);	
}

DITOR		list_index(c_list ls,int pos){
	real_list* pRls = NULL;
	iList_node* current = NULL;
	iList_node* iLend = NULL;
	int i = 0;
	if(ls.hdle == NULL){
		printf("func list_index ptr err: %d\n",-1);
		return NULL;
	}
	pRls = (real_list*)ls.hdle;
	iLend = &pRls->header;
	if(pos < 0 || pos >= pRls->size){
		printf("func list_index pos err: %d\n",-3);
		return NULL;
	}
	if(pos - 0 < pRls->size - pos){
		current = iLend;
		for(i = 0;i < pos; ++i){
			current = current->next;
		}
		return (mcbyte*)current->next + sizeof(iList_node);
	}
	else{
		current = iLend;
		for(i = pRls->size - 1;i > pos; --i){
			current = current->prev;
		}
		return (mcbyte*)current->prev + sizeof(iList_node);		
	}
}

int 		list_iterator(c_list ls,iterator it){
	real_iterator* pRit = NULL;
	real_list*	pRls = NULL;
	if(ls.hdle == NULL || it == NULL){
		printf("func list_iterator ptr err: %d\n",-1);
		return -1;
	}
	pRit = (real_iterator*)it;
	pRls = (real_list*)ls.hdle;
	pRit->offs = pRls->offs;
	*it = list_iter_begin(ls);
	pRit->begin = *it;
	pRit->curEnd = list_iter_end(ls);
	pRit->reaEnd = (void**)&pRls->size;
	return 0;
}

int 		list_iter_techinique(iter_technique* pittq,ls_technique* plstq){
	iterator_technique(pittq);
	pittq->prev 	= list_iter_prev;
	pittq->next 	= list_iter_next;
	pittq->index 	= list_iter_index;
	pittq->hasPrev  = list_iter_hasPrev;
	pittq->hasNext  = list_iter_hasNext;
	pittq->insert	= list_iter_insert;
	pittq->erase	= list_iter_erase;
	pittq->copyCons = plstq->copyCons;
	pittq->cons		= plstq->cons;
	pittq->dess		= plstq->dess;
	pittq->cmp		= plstq->cmp;	
}

DITOR		list_iter_begin(c_list ls){
	real_list* pRls = NULL;
	if(ls.hdle == NULL){
		printf("func list_iter_begin ptr err: %d\n",-1);
		return NULL;
	}
	pRls = (real_list*)ls.hdle;
	return (mcbyte*)pRls->header.next + sizeof(iList_node);
}

DITOR		list_iter_end(c_list ls){
	real_list* pRls = NULL;
	if(ls.hdle == NULL){
		printf("func list_iter_end ptr err: %d\n",-1);
		return NULL;
	}
	pRls = (real_list*)ls.hdle;
	return (mcbyte*)&pRls->header + sizeof(iList_node);	
}

DITOR		list_iter_index(ITOR it,int pos){
	real_iterator* pRit = NULL;
	iList_node* current = NULL;
	iList_node* iLend = NULL;
	if(it == NULL){
		printf("func list_iter_index ptr err: %d\n",-1);
		return NULL;
	}
	pRit = (real_iterator*)it;
	iLend = (iList_node*)((mcbyte*)pRit->begin - sizeof(iList_node));
	current = iLend;
	for(int i = 0;i < pos; ++i){
		current = current->next;
	}
	return (mcbyte*)current->next + sizeof(iList_node);
}

DITOR 		list_iter_prev(ITOR it){
	iList_node* current = NULL;
	if(it == NULL){
		printf("func list_iter_prev ptr err: %d\n",-1);
		return NULL;
	}
	current = (iList_node*)((mcbyte*)*(void**)it - sizeof(iList_node));
	return (mcbyte*)current->prev + sizeof(iList_node);	
}

DITOR 		list_iter_next(ITOR it){
	iList_node* current = NULL;
	if(it == NULL){
		printf("func list_iter_next ptr err: %d\n",-1);
		return NULL;
	}
	current = (iList_node*)((mcbyte*)*(void**)it - sizeof(iList_node));
	return (mcbyte*)current->next + sizeof(iList_node);
}

mcbool		list_iter_hasPrev(ITOR it){
	real_iterator* pRit = NULL;
	if(it == NULL){
		printf("func list_iter_hasPrev ptr err: %d",-1);
		return 0;
	}
	pRit = (real_iterator*)it;
	return *(void**)it != pRit->curEnd ? 1 : 0 ;
}

mcbool		list_iter_hasNext(ITOR it){
	real_iterator* pRit = NULL;
	if(it == NULL){
		printf("func list_iter_hasNext ptr err: %d",-1);
		return 0;
	}
	pRit = (real_iterator*)it;
	return *(void**)it != pRit->curEnd ? 1 : 0 ;	
}

int 		list_iter_insert(ITOR it,c_pTData pdata,iter_technique* pittq){
	real_iterator* pRit = NULL;
	iList_node* header = NULL;
	iList_node* rData = NULL;
	if(it == NULL || pdata == NULL){
		printf("func list_iter_insert ptr err: %d",-1);
		return -1;
	}
	pRit = (real_iterator*)it;
	header = (iList_node*)((mcbyte*)pRit->cur - sizeof(iList_node));
	list_node_create(pRit->offs,(void**)&rData);
	if(rData == NULL){
		return -3;
	}
	iList_tAdd(header,rData);
	if(pittq != NULL && pittq->copyCons != NULL){
		pittq->copyCons((mcbyte*)rData + sizeof(iList_node),pdata);
	}
	else{
		memcpy((mcbyte*)rData + sizeof(iList_node),pdata,pRit->offs);
	}
	(*(int*)pRit->reaEnd) ++;
	*(void**)it = (mcbyte*)rData + sizeof(iList_node);
	return 0;
}

int			list_iter_erase(ITOR it,iter_technique* pittq){
	real_iterator* pRit = NULL;
	iList_node* node = NULL;
	iList_node* next = NULL;
	if(it == NULL){
		printf("func list_iter_erase ptr err: %d\n",-1);
		return -1;
	}
	pRit = (real_iterator*)it;
	node = (iList_node*)((mcbyte*)it - sizeof(iList_node));
	next = node->next;
	iList_del(node);
	if(pittq != NULL && pittq->dess != NULL){
		pittq->dess(node);
	}
	mc_pFree(node);
	*(pRit->reaEnd) --;
	it = (mcbyte*)next + sizeof(iList_node);
	return 0;		
}
