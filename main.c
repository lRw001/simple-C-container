#include "mc_stl_defxxx.h"
#include "mc_vector.h"
#include "mc_list.h"

void vec_demo01();

void vec_demo02(int m,int n);
void vecCopyCons(pTData ,pTData );
void vecDess(pTData );

void lis_demo01();
void lis_demo02();
void lisCopyCons(pTData ,pTData );
void lisDess(pTData );

int main(){
	//vec_demo01();
	//vec_demo02(20,25);
	//lis_demo01();
	lis_demo02(20,25);
	return 0;
}

void vec_demo02(int m,int n){
	vector v;
	vec_technique vec;
	iterator it,it1;
	iter_technique itor;
	vector_create(&v,sizeof(vector));
	vector_vec_technique(&vec);
	vec.copyCons = vecCopyCons;
	vec.dess = vecDess;
	vec.ittq(&itor,&vec);
	for(int i = 0;i < m;++i){
		vector tmpv;
		vec.push_back(v,&tmpv,&vec);
	}
	vec.resize(v,m);
	vec.iter(v,it);
	for(*it = vec.begin(v);*it != vec.end(v);*it = itor.next(it)){
		for(int i = 0;i < n; ++i){
			vec.push_back(itTod(vector,it),&i,NULL);
		}
		vec.resize(itTod(vector,it),n); 
	}
	for(*it = vec.begin(v);*it != vec.end(v);*it = itor.next(it)){
		vec.iter(itTod(vector,it),it1);
		for(*it1 = vec.begin(itTod(vector,it));*it1 != vec.end(itTod(vector,it));*it1 = itor.next(it1)){
			printf("%d ",itTod(int,it1));
		}
		puts("");
	}
	vector_destroy(&v,&vec);
}

void vecCopyCons(pTData pv,pTData v){
	vector_create(pv,sizeof(int));
}

void vecDess(pTData pv){
	vector_destroy(pv,NULL);
}

void vec_demo01(){
	int x = 0;
	vector v1;
	iterator it;
	iter_technique itor;
	vec_technique vec;
	vector_create(&v1,sizeof(int));
	vector_vec_technique(&vec);
	vec.ittq(&itor,&vec);
	for(int i = 0;i < 20; ++i){
		vec.push_back(v1,&i,&vec);
	}
	vec.iter(v1,it);
	for(*it = vec.begin(v1);itor.hasNext(it);*it = itor.next(it)){
		printf("%d\n",itTod(int,it));
	}
	printf("size = %d\n",vec.size(v1));
	*it = itor.index(it,19);
	printf("%d\n",itTod(int,it));
	vec.erase(v1,vec.index(v1,19),&vec);
	for(*it = vec.begin(v1);*it != vec.end(v1);*it = itor.next(it)){
		printf("%d\n",itTod(int,it));
	}
	printf("size = %d\n",vec.size(v1));
	x = 100; 
	vec.insert(v1,vec.index(v1,10),&x,&vec);
	vec.iter(v1,it);
	for(*it = vec.begin(v1);*it != vec.end(v1);*it = itor.next(it)){
		printf("%d\n",itTod(int,it));
	}
	printf("size = %d\n",vec.size(v1));
	*it = itor.index(it,10);
	itor.erase(it,&itor);
	vec.iter(v1,it);
	for(*it = vec.begin(v1);*it != vec.end(v1);*it = itor.next(it)){
		printf("%d\n",itTod(int,it));
	}
	printf("size = %d\n",vec.size(v1));
	x = 99;
	*it = itor.index(it,6);
	itor.insert(it,&x,&itor);	
	vec.iter(v1,it);
	for(*it = vec.begin(v1);*it != vec.end(v1);*it = itor.next(it)){
		printf("%d\n",itTod(int,it));
	}
	printf("size = %d\n",vec.size(v1));
	while(vec.size(v1) != 0){
		vec.pop_back(v1,&vec);
	}
	printf("size = %d\n",vec.size(v1));
	vector_destroy(&v1,&vec);
} 

void lis_demo01(){
	list ls;
	iterator it;
	ls_technique lis;
	iter_technique itor;
	list_create(&ls,sizeof(int));
	list_ls_technique(&lis);
	lis.ittq(&itor,&lis);
	for(int i = 0;i < 10;++i){
		lis.push_back(ls,&i,NULL);
	}
	printf("%d\n",*(int*)lis.index(ls,8));
	printf("size = %d\n",lis.size(ls));
	int x = 100;
	lis.insert(ls,lis.index(ls,8),&x,NULL);
	lis.erase(ls,lis.index(ls,8),NULL);
	printf("%d\n",*(int*)lis.index(ls,8));
	lis.iter(ls,it);
	for(*it = lis.begin(ls);itor.hasNext(it);*it = itor.next(it)){
		printf("%d\n",itTod(int,it));
	}
	list_destroy(&ls,NULL);	
}

void lis_demo02(int m,int n){
	list ls;
	iterator it;
	iterator it1;
	iter_technique itor;
	ls_technique lis;
	list_ls_technique(&lis);
	lis.copyCons = lisCopyCons;
	lis.dess = lisDess;
	lis.ittq(&itor,&lis);
	list_create(&ls,sizeof(list));
	for(int i = 0;i < m; ++i){
		list tmpls;
		lis.push_back(ls,&tmpls,&lis);
	}
	lis.iter(ls,it);
	for(*it = lis.begin(ls);*it != lis.end(ls); *it = itor.next(it)){
		for(int i = 0;i < n; ++i){
			lis.push_back(itTod(list,it),&i,NULL);
		}
	}
	lis.iter(ls,it);
	for(*it = lis.begin(ls);*it != lis.end(ls); *it = itor.next(it)){
		lis.iter(itTod(list,it),it1);
		for(*it1 = lis.begin(itTod(list,it));*it1 != lis.end(itTod(list,it));*it1 = itor.next(it1)){
			printf("%d ",itTod(int,it1));
		}
		puts("");
	}
	list_destroy(&ls,&lis);
}

void lisCopyCons(pTData pl,pTData l){
	list_create(pl,sizeof(int));
}

void lisDess(pTData pl){
	list_destroy(pl,NULL);
}
