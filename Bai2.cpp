#include<iostream>
#include<conio.h>
#include<string.h>
using namespace std;
struct nut
{
	char nd[80]; //noi dung khai bao
	nut*sau,*truoc; //2 con tro
};

typedef nut Node;
Node*dau;
Node*dau1;
int i,dem,j,n,m,k,l,h;
void Tao(Node *&dau)//khoi tao
{
	dau = NULL;
}
/*=------------------------------------------------------------*/
void Nhap(Node *&dau)//Nhap van ban
{
	char tam[80];
	Node*q,*p;
	do
	{
		cout<<"Nhap vao dong van ban, Enter dung: ";
		fflush(stdin);
		gets(tam);
		if(strcmp(tam,"\0")!=0)
		{
			p=new Node;
			strcpy(p->nd,tam);
			p->sau=NULL;
			p->truoc=NULL;
			if(dau==NULL)
				dau=p;
			else
				{
					q->sau=p;
					p->truoc=q;
				}
			q=p;
		}
	}
	while(strcmp(tam,"\0")!=0);
}
/*=------------------------------------------------------------*/
void Duyet(Node*dau)
{
	if(dau!=NULL)
		{
			cout<<dau->nd<<endl;
			Duyet(dau->sau);
		}
}

void Inij(Node *dau, int i, int j) 
{  	
	int dem;  
	Node *p,*q;  
	if(j>=i)  
	{
		// tim i   
		dem=1;   
		p=dau;   
		while(p!=NULL&&dem!=i)   
		{   
			 p=p->sau;   
			 dem=dem+1;   
		}   
		if(p!=NULL)   
		{
			// tim j   
			q=p;    
			while(q!=NULL&&dem!=j)    
			{     
				q=q->sau;     
				dem=dem+1;    
			} 
			// in ra dong i den dong j.    
			if(q!=NULL)    
			while(p!=q->sau)    
			{     
				cout<<p->nd<<endl;     
				p=p->sau;    
			}    
		}     
	} 
} 
/*=------------------------------------------------------------*/
void ChenDongCuoi(nut *&dau)
{
	nut *p, *q;
	char tam[80];
	p = new Node;
	fflush(stdin);
	cout << "Nhap van ban muon chen vao cuoi: ";
	gets(tam);
	strcpy(p -> nd, tam);
	p -> sau = NULL;
	p -> truoc = NULL;
	q = dau;
	while(q -> sau != NULL)
	{
		q = q -> sau;
	}
	q -> sau = p;
	p -> truoc = q;
}
/*=------------------------------------------------------------*/
void Xoadong(Node *&dau, int i)
{
	Node *p,*t,*s;
	int k=1;
	p=dau;
	while((p!=NULL)&&(k!=i))
	{
		p=p->sau;
		k+=1;
	}
	if(p!=NULL)
	{
		if(p==dau)//p nut dau
		{
			dau=dau->sau;
			dau->truoc=NULL;
		}
		else 
			if(p->sau==NULL)//truong hop p la nut cuoi
			{
				t=p->truoc;
				t->sau=NULL;
			}
		else 
			if((p!=dau)&&(p->sau!=NULL))
			{
				t=p->truoc;
				s=p->sau;
				t->sau=s;
				s->truoc=t;
			}
			delete p;
	}
	//1.p==dau thi xoa nut dau
	//2.p khac NULL
	//3.p->sau=NULL
}
/*=------------------------------------------------------------*/
void Xoadongij(nut *&dau, int i, int j)
{
	int k;
	for(k=i;k<=j;k++)
		Xoadong(dau,i);
}
/*=------------------------------------------------------------*/
void Chepij(Node *dau, int i, int j, Node *&dau1)
{
	int dem;
	Node *p,*q,*t,*n;
	if(j>=i)
	{
		// tim i
		dem=1;
		p=dau;
		while(p!=NULL&&dem!=i)
		{
			p=p->sau;
			dem=dem+1;
		}
		if(p!=NULL)
		{
			// tim j
			q=p;
			while(q!=NULL&&dem!=j)
			{
				q=q->sau;
				dem=dem+1;
			}
			// in ra dong i den dong j.
			if(q!=NULL)
			while(p!=q->sau)
			{

				t=new Node;
				strcpy(t->nd,p->nd);
				t->sau=NULL;t->truoc=NULL;
				if (dau1==NULL)
					dau1=t;
				else
				{
					n->sau=t;
					t->truoc=n;
				}
				n=t;
				p=p->sau;
			}
		}
	}
}
//--------------------------------------------------------------------------------
void Chendongij(Node *&dau,int i, int j, int k)
{
	int m;
	Node *v,*u,*w;
	v=dau;
	m=1;
	Chepij(dau,i,j,dau1);
	while(v!=NULL&&m!=k)
	{
		v=v->sau;
		m=m+1;
	}
	if(v!=NULL)
	{ 
		// v tro den dong k
		u=dau1;
		while(u->sau!=NULL)
		u=u->sau;
		// u la dong cuoi cua ds dau1
		w=v->sau; // dong sau dong k
		v->sau=dau1;
		dau1->truoc=v;
		u->sau=w;
		w->truoc=u;
	}
}
/*=------------------------------------------------------------*/
int main()
{
	Nhap(dau);
	Duyet(dau);
	cout<<"\nChon van ban muon xuat ra man hinh tu dong thu: ";
	cin>>i;
	cout<<"den dong thu: ";
	cin>>j;
	cout<<"\n-------------------------------------------------\n";
	Inij(dau,i,j);
	ChenDongCuoi(dau);
	fflush(stdin);
	Duyet(dau);
	cout<<"\n---------------------------------------------\n";
	cout<<"\n Xoa van ban tu dong thu ";cin>>n; cout<<"den dong: "; cin>>m;
	Xoadongij(dau,n,m);
	Duyet(dau);
	cout<<"\n----------------------------------------------\n";
	cout<<"\n Chep van ban tu dong thu ";cin>>k; cout<<"den dong thu "; cin>>l; cout<<"dua vao sau dong thu: "; cin>>h;
	Chendongij(dau,k,l,h);
	Duyet(dau);
}
