#ifndef __MYC_STL_DEFXXX_H__
#define __MYC_STL_DEFXXX_H__

//include
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mc_type.h"
#include "mc_iterator.h"

//data

//pool 
inline void* mc_pMalloc(int size){
	return malloc(size);
} 

inline void mc_pFree(void* ptr){
	free(ptr);
	return;
}

inline void* mc_pRealloc(void* ptr,int size){
	void* temp = NULL;
	temp = realloc(ptr,size);
	return temp;
}

#endif
