#include<iostream>
#include<stdlib.h>
using namespace std;

struct AVLNODE
{
     int key; //truong key cua du lieu
	 int bal;//thuoc tinh cho biet gia tri can bang,0:can bang, 1:lech trai, 2:lech phai
     AVLNODE* pLeft, *pRight; //con trai va con phai
};
typedef AVLNODE *Tree;  //cay
AVLNODE *root;

void KhoiTao(AVLNODE *&root)
{
	root = NULL;
}

void mocNut(AVLNODE *&root, int x)
{  
	if(root == NULL)  
	{   
		root = new AVLNODE;   
		root->key = x;   
		root->pLeft = NULL;   
		root->pRight = NULL;  
	}  
	else  
	{   
		if(root->key >= x)    
			mocNut(root->pLeft,x);  
		else    
			mocNut(root->pRight,x);  
	} 
} 
 
void taoCay(AVLNODE *&root) 
{  
	int tmp;  
	do  
	{   
		cout<<"Nhap so nguyen, 0 de dung: ";   
		cin>>tmp;   
		if(tmp != 0)    
		mocNut(root,tmp);  
	}
	while(tmp != 0); 
} 


void LeftRotate(AVLNODE* &P)//xoay trai
{
	AVLNODE *Q;
	Q = P->pRight;
	P->pRight = Q->pLeft;
	Q->pLeft = P;
	P = Q;
}
void RightRotate(AVLNODE* &P)//xoay phai
{
	AVLNODE *Q;
	Q = P->pLeft;
	P->pLeft = Q->pRight;
	Q->pRight = P;
	P = Q;
}

void LeftBalance(AVLNODE* &P)//can bang trai
{
	switch(P->pLeft->bal)
	{
		case 1: //mat can bang trai trai
		RightRotate(P);
		P->bal = 0;
		P->pRight->bal = 0;
		break;
		case 2: //mat can bang phai trai
		LeftRotate(P->pLeft);
		
		RightRotate(P);
		switch(P->bal)
		{
			case 0:
			P->pLeft->bal= 0;
			P->pRight->bal= 0;
			break;
			case 1:
			P->pLeft->bal= 0;
			P->pRight->bal= 2;
			break;
			case 2:
			P->pLeft->bal= 1;
			P->pRight->bal= 0;
			break;
		}
		P->bal = 0;
		break;
	}
}


void RightBalance(AVLNODE* &P)//can bang phai
{
	switch(P->pRight->bal)
	{
		case 1: //mat can bang trai phai
		RightRotate(P->pRight);
		LeftRotate(P);
		switch(P->bal)
		{
			case 0:
			P->pLeft->bal= 0;
			P->pRight->bal= 0;
			break;
			case 1:
			P->pLeft->bal= 1;
			P->pRight->bal= 0;
			break;
			case 2:
			P->pLeft->bal= 0;
			P->pRight->bal= 2;
			break;
		}
		P->bal = 0;
		break;
		case 2: //mat can bang phai phai
		LeftRotate(P);
		P->bal = 0;
		P->pLeft->bal = 0;
		break;
	}
}

AVLNODE* CreateNode(int Data)
 {  
 	AVLNODE* pNode; 
 	 pNode = new AVLNODE;

     if (pNode == NULL)
	 {   
		return NULL; 
	 }  
	pNode->key = Data;
	pNode->pLeft = NULL; 
	pNode->pRight = NULL; 
	pNode->bal = 0; 
	return pNode; 
}

int InsertNode(AVLNODE* &root, int x)
{
	int res;
	if(root == NULL)
  { //neu cay  null thi tao moi  
  	 root = CreateNode(x);
      if(root == NULL)
	  {    return -1;
	   //them khong thanh cong vi thieu bo nho
	     }  
	    return 2;
		//them thanh cong va lam tang chieu cao
		  } 
	 else
	  {  
		if(root->key==x)
		{
			return 0;
		}
		else if(root->key > x)
		{
			res = InsertNode(root->pLeft,x);
			if(res < 2) 
			{
				return res;
			}
			switch(root->bal)
			{ 
				case 0:
				root->bal = 1;
				return 2;
				case 1:
				LeftBalance(root);
				return 1;
				case 2:
				root->bal = 0;
				return 1;
			}
		}
		else
		{
			res = InsertNode(root->pRight,x);
			if(res<2)
			{
				return res;
			}
			switch(root->bal)
			{
				case 0:
				root->bal=2;
				return 2;
				case 1:
				root->bal = 0;
				return 1;
				case 2:
				RightBalance(root);
				return 1;
			}
		}
	}
}


int delKey(Tree &T, int x)     // xoa nut co key x
{
    if (T==NULL) return 0;
    else if (T->key > x) return delKey(T->pLeft, x);
    else if (T->key < x) return delKey(T->pRight, x);
    else // T->key == x
    {
        AVLNODE *P = T;
        if (T->pLeft == NULL) T = T->pRight;    // Node chi co cay con phai
        else if (T->pRight == NULL) T = T->pLeft;   // Node chi co cay con trai
        else // Node co ca 2 con
        {
            AVLNODE *S = T, *Q = S->pLeft;
            // S la cha cua Q, Q la Node phai nhat cua cay con trai cua P
            while (Q->pRight != NULL)
            {
                S = Q;
                Q = Q->pRight;
            }
            P->key = Q->key;
            S->pRight = Q->pLeft;
            delete Q;
        }
    }
    return 1;
}

void Traverse(AVLNODE* t)//can bang
{
	if(t!=NULL)
	{
		Traverse(t->pLeft);
		cout<<"\nKhoa: "<<t->key <<" can bang: "<<t->bal;
		Traverse(t->pRight);
	}
}

void LNR(Tree T) //duyet cay
{
     if(T!=NULL)
     {
      LNR(T->pLeft);
      cout<<T->key<<"\t";
      LNR(T->pRight);
     }
}

int KiemTraCayAVL(AVLNODE *root)
{
	if(root == NULL)
		return 1;
	if((root -> pLeft == NULL) && (root -> pRight == NULL))
		return 1;
	else
		if(root -> pLeft == NULL)
			KiemTraCayAVL(root -> pRight);
		else
			if(root -> pRight == NULL)
				KiemTraCayAVL(root -> pLeft);
			else
			    if((root -> pLeft -> key > root -> key) || (root -> pRight -> key < root -> key))
					return 0;
}
int main()
{
	int Data,x;
	taoCay(root);
	cout<<"Duyet LNR"<<endl;
	LNR(root);
	cout<<"\n-------------------------------------------------------\n";
	Traverse(root);
	if(KiemTraCayAVL(root))
		cout<<"\nDay la cay AVL";
	else
		cout<<"\nKhong phai cay AVL";
	cout<<"\n-------------------------------------------------------";	
	cout<<"\nNhap nut muon xoa: ";
	cin>>x;
	if(delKey(root,x))
		cout<<"Nut da duoc xoa !";
	else
		cout<<"Khong co nut can xoa trong cay !";
	cout<<"\n-------------------------------------------------------";
	cout<<"\nDuyet lai cay theo LNR:"<<endl;
	LNR(root);
	cout<<endl<<InsertNode(root,x);
	Traverse(root);
}
