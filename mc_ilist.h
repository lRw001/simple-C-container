#ifndef __ILIST_H__
#define __ILIST_H__

/*
	����˫��ѭ������
	���ڹ�������������ʽ�洢��ϵ 
*/ 
typedef struct iList_node iList_node,iList;
struct iList_node{
	iList_node *prev,*next;
};

/*
	iList_offs( _type, _member)
	����Ԫ��ƫ���� 
*/ 
#define iList_offs( _type, _member)\
	((unsigned int)&((_type*)0)->member)

/*
	iList_cont( _ptr, _type, _member)
	����_type���ͽڵ��׵�ַ
	������Ҫ�����Ƕ��ʹ�� 
*/
#define iList_cont( _ptr, _type, _member)\
	(_type*)((char*)_ptr - ilist_offs(_type,_member))

void iList_header(iList* pHeader);

/*
	iList_hAdd(iList* pHeader,iList_node* pNode)
	ͷ��
	�޷���ֵ 
*/
void iList_hAdd(iList* pHeader,iList_node* pNode);

/*
	iList_tAdd(iList* pHeader,iList_node* pNode)
	β��
	�޷���ֵ 
*/ 
void iList_tAdd(iList* pHeader,iList_node* pNode);

/*
	iList_del(iList_node* pNode);
	ɾ��
	�޷���ֵ 
*/ 
void iList_del(iList_node* pNode);

#endif
