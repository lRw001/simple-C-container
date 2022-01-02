#ifndef __MC_VECTOR_H__
#define __MC_VECTOR_H__

#include "mc_type.h"
#include "mc_iterator.h"

#define VEC_FL __FILE__##__LINE__

#define vector						VEC_FL##vector
#define c_vector					VEC_FL##c_vector
#define vec_technique 				VEC_FL##vec_technique

#define vector_create 				VEC_FL##vector_create
#define vector_vec_technique		VEC_FL##vector_vec_technique
#define vector_destroy	 			VEC_FL##vector_destroy

#define vector_size 				VEC_FL##vector_size
#define vector_capacity 			VEC_FL##vector_capacity
#define vector_pushBack				VEC_FL##vector_pushBack
#define vector_popBack				VEC_FL##vector_popBack
#define vector_back					VEC_FL##vector_back
#define vector_front				VEC_FL##vector_front
#define vector_at					VEC_FL##vector_at
#define vector_insert				VEC_FL##vector_insert
#define vector_erase				VEC_FL##vector_earse
#define vector_index				VEC_FL##vector_index
#define vector_resize				VEC_FL##vector_resize

#define vector_iterator				VEC_FL##vector_iterator
#define vector_iter_techinique		VEC_FL##vector_iter_techinique
#define vector_iter_begin			VEC_FL##vector_iter_begin
#define vector_iter_end				VEC_FL##vector_iter_end
#define vector_iter_index			VEC_FL##vector_iter_index
#define vector_iter_prev			VEC_FL##vector_iter_prev
#define vector_iter_next			VEC_FL##vector_iter_next
#define vector_iter_hasPrev			VEC_FL##vector_iter_hasPrev
#define vector_iter_hasNext			VEC_FL##vector_iter_hasNext
#define vector_iter_insert			VEC_FL##vector_iter_insert
#define vector_iter_erase			VEC_FL##vector_iter_erase

typedef struct vector vector;
typedef const vector c_vector;
typedef struct vec_technique vec_technique;

struct vector{
	HDLE hdle;
};

struct vec_technique{
	int 		(*size) (c_vector vec);
	int 		(*capacity)(c_vector vec);
	int 		(*push_back) (c_vector vec,c_pTData pdata,vec_technique* pvectq);
	int			(*pop_back) (c_vector vec,vec_technique* pvectq);
	pTData 		(*front) (c_vector vec);
	pTData 		(*back) (c_vector vec);
	pTData 		(*at) (c_vector vec,int pos,int *err);
	int			(*insert) (c_vector vec,DITOR dit,c_pTData pdata,vec_technique* pvectq);
	int			(*erase) (c_vector vec,DITOR dit,vec_technique* pvectq);
	
	int 		(*iter) (c_vector vec,iterator it);//直接赋值
	int 		(*ittq) (iter_technique* pittq,vec_technique* pvectq);
	DITOR 		(*begin) (c_vector vec);//赋值或者比较时需要将it变为一级指针
	DITOR		(*end) (c_vector vec);//赋值或者比较时需要将it变为一级指针
	DITOR		(*index)(c_vector vec,int pos);
	int 		(*resize)(c_vector vec,int size);
	
	//非基本方法 
	void 		(*copyCons)(pTData ,pTData );
	void 		(*cons)(pTData );
	void 		(*dess)(pTData );
	int 		(*cmp)(pTData ,pTData );//比较函数
};

int		 	vector_create(vector* pvec,size_t type);
int 		vector_vec_technique(vec_technique* pvectq);//给予基本的方法赋值 
int 		vector_destroy(vector* pvec,vec_technique* pvectq);

int 	 	vector_size(c_vector vec);
int 	 	vector_capacity(c_vector vec);
int		 	vector_pushBack(c_vector vec,c_pTData pdata,vec_technique* pvectq);
int	 		vector_popBack(c_vector vec,vec_technique* pvectq);
pTData 		vector_front(c_vector vec);
pTData 		vector_back(c_vector vec);
pTData 		vector_at(c_vector vec,int pos,int *err);
int			vector_insert(c_vector vec,DITOR dit,c_pTData pdata,vec_technique* pvectq);
int			vector_erase(c_vector vec,DITOR dit,vec_technique* pvectq);
DITOR		vector_index(c_vector vec,int pos);
int 		vector_resize(c_vector vec,int size);

int 		vector_iterator(c_vector vec,iterator it);
int 		vector_iter_techinique(iter_technique* pittq,vec_technique* pvectq);
DITOR		vector_iter_begin(c_vector vec);
DITOR		vector_iter_end(c_vector vec);
DITOR		vector_iter_index(ITOR it,int pos);
DITOR 		vector_iter_prev(ITOR it);
DITOR 		vector_iter_next(ITOR it);
mcbool		vector_iter_hasPrev(ITOR it);
mcbool		vector_iter_hasNext(ITOR it);
int 		vector_iter_insert(ITOR it,c_pTData pdata,iter_technique* pittq);
int			vector_iter_erase(ITOR it,iter_technique* pittq);

#endif
