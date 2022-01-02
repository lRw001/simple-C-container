#ifndef __MC_LIST_H__
#define __MC_LIST_H__

#include "mc_type.h"
#include "mc_iterator.h"

#define LS_FL __FILE__##__LINE__

#define list						LS_FL##list
#define c_list						LS_FL##c_list
#define ls_technique 				LS_FL##ls_technique

#define list_create 				LS_FL##list_create
#define list_ls_technique			LS_FL##list_ls_technique
#define list_destroy	 			LS_FL##list_destroy

#define list_size 					LS_FL##list_size
#define list_pushBack				LS_FL##list_pushBack
#define list_popBack				LS_FL##list_popBack
#define list_back					LS_FL##list_back
#define list_front					LS_FL##list_front
#define list_at						LS_FL##list_at
#define list_insert					LS_FL##list_insert
#define list_erase					LS_FL##list_earse
#define list_index					LS_FL##list_index

#define list_iterator				LS_FL##list_iterator
#define list_iter_techinique		LS_FL##list_iter_techinique
#define list_iter_begin				LS_FL##list_iter_begin
#define list_iter_end				LS_FL##list_iter_end
#define list_iter_index				LS_FL##list_iter_index
#define list_iter_prev				LS_FL##list_iter_prev
#define list_iter_next				LS_FL##list_iter_next
#define list_iter_hasPrev			LS_FL##list_iter_hasPrev
#define list_iter_hasNext			LS_FL##list_iter_hasNext
#define list_iter_insert			LS_FL##list_iter_insert
#define list_iter_erase				LS_FL##list_iter_erase 

typedef struct list list;
typedef const list c_list;
typedef struct list_technique ls_technique;

struct list{
	HDLE hdle;	
};

struct list_technique{
	int 		(*size) (c_list ls);
	int 		(*push_back) (c_list ls,c_pTData pdata,ls_technique* plstq);
	int			(*pop_back) (c_list ls,ls_technique* plstq);
	pTData 		(*front) (c_list ls);
	pTData 		(*back) (c_list ls);
	pTData 		(*at) (c_list ls,int pos,int *err);
	DITOR		(*insert) (c_list ls,DITOR dit,c_pTData pdata,ls_technique* plstq);//指针自动后移 //返回插入的位置 
	DITOR		(*erase) (c_list ls,DITOR dit,ls_technique* plstq);//指针自动后移 //返回后移的位置 
	
	int 		(*iter) (c_list ls,iterator it);//直接赋值
	int 		(*ittq) (iter_technique* pittq,ls_technique* plstq);
	DITOR 		(*begin) (c_list ls);//赋值或者比较时需要将it变为一级指针
	DITOR		(*end) (c_list ls);//赋值或者比较时需要将it变为一级指针
	DITOR		(*index)(c_list ls,int pos);
	
	//非基本方法 
	void 		(*copyCons)(pTData ,pTData );//拷贝构造函数 
	void 		(*cons)(pTData );//构造函数
	void 		(*dess)(pTData );//析构函数
	int 		(*cmp)(pTData ,pTData );//比较函数	
};

int list_create(list* pls,size_t type);
int list_ls_technique(ls_technique* plstq);
int list_destroy(list* pls,ls_technique* plstq);

int 	 	list_size(c_list ls);
int		 	list_pushBack(c_list ls,c_pTData pdata,ls_technique* plstq);
int	 		list_popBack(c_list ls,ls_technique* plstq);
pTData 		list_front(c_list ls);
pTData 		list_back(c_list ls);
pTData 		list_at(c_list ls,int pos,int *err);
DITOR		list_insert(c_list ls,DITOR dit,c_pTData pdata,ls_technique* plstq);//指针自动后移 //返回插入的位置
DITOR		list_erase(c_list ls,DITOR dit,ls_technique* plstq);//指针自动后移 //返回后移的位置 
DITOR		list_index(c_list ls,int pos);

int 		list_iterator(c_list ls,iterator it);
int 		list_iter_techinique(iter_technique* pittq,ls_technique* plstq);
DITOR		list_iter_begin(c_list ls);
DITOR		list_iter_end(c_list ls);
DITOR		list_iter_index(ITOR it,int pos);
DITOR 		list_iter_prev(ITOR it);
DITOR 		list_iter_next(ITOR it);
mcbool		list_iter_hasPrev(ITOR it);
mcbool		list_iter_hasNext(ITOR it);
int 		list_iter_insert(ITOR it,c_pTData pdata,iter_technique* pittq);
int			list_iter_erase(ITOR it,iter_technique* pittq);

#endif 
