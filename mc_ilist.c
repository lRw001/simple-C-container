#include "mc_ilist.h"

static inline void __iList_Add(iList_node* prev,iList_node* next,iList_node* node){
	node->next = next;	next->prev = node;
	node->prev = prev;	prev->next = node; 
} 

static inline void __iList_Del(iList_node* prev,iList_node* next){
	next->prev = prev;	prev->next = next;
}

void iList_header(iList* pHeader){
	pHeader->prev = pHeader;
	pHeader->next = pHeader;
}

/*
	iList_hAdd(iList* pHeader,iList_node* pNode)
	头插
	无返回值 
*/
void iList_hAdd(iList* pHeader,iList_node* pNode){	 
	__iList_Add(pHeader,pHeader->next,pNode);
}
 
/*
	iList_tAdd(iList* pHeader,iList_node* pNode)
	尾插
	无返回值 
*/ 
void iList_tAdd(iList* pHeader,iList_node* pNode){
	__iList_Add(pHeader->prev,pHeader,pNode);
} 

/*
	iList_del(iList_node* pNode);
	删除
	无返回值 
*/ 
void iList_del(iList_node* pNode){
	__iList_Del(pNode->prev,pNode->next);
}
