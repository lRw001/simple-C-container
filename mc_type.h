#ifndef __MC_TYPE_H__
#define __MC_TYPE_H__

#define TYPE_FL __FILE__##__LINE__

#define HDLE 		TYPE_FL##HDLE
#define pTData		TYPE_FL##pTData
#define c_pTData	TYPE_FL##c_pTData
#define mcbool		TYPE_FL##mcbool

#define INLINE		static inline

typedef void* HDLE;
typedef void* pTData;
typedef void* cont;
typedef const pTData c_pTData;
typedef unsigned size_t; 
typedef unsigned char mcbool;
typedef unsigned char mcbyte;

#define __Byte sizeof(mcbyte)

#endif
