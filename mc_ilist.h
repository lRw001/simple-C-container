#ifndef __ILIST_H__
#define __ILIST_H__

/*
	基类双向循环链表
	用于构造线性数据链式存储关系 
*/ 
typedef struct iList_node iList_node,iList;
struct iList_node{
	iList_node *prev,*next;
};

/*
	iList_offs( _type, _member)
	返回元素偏移量 
*/ 
#define iList_offs( _type, _member)\
	((unsigned int)&((_type*)0)->member)

/*
	iList_cont( _ptr, _type, _member)
	返回_type类型节点首地址
	无类型要求可以嵌套使用 
*/
#define iList_cont( _ptr, _type, _member)\
	(_type*)((char*)_ptr - ilist_offs(_type,_member))

void iList_header(iList* pHeader);

/*
	iList_hAdd(iList* pHeader,iList_node* pNode)
	头插
	无返回值 
*/
void iList_hAdd(iList* pHeader,iList_node* pNode);

/*
	iList_tAdd(iList* pHeader,iList_node* pNode)
	尾插
	无返回值 
*/ 
void iList_tAdd(iList* pHeader,iList_node* pNode);

/*
	iList_del(iList_node* pNode);
	删除
	无返回值 
*/ 
void iList_del(iList_node* pNode);

#endif
