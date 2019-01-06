#include<iostream>
#include<fstream>
using namespace std;

fstream fi;

struct PhanSo
{
	int tu;
	int mau;
}PS;
PhanSo a[20];

void DocFile(int &n, int &p, int &q) //doc file 
{
	fi.open("FRACTIONS.INP.txt", ios::in); //mo file de doc
	fi >> n >> p >> q;
	fi.close();
	
}

void SapXep(PhanSo a[20], int n)//sap xep phan so theo thu tu tang dan
{
	for(int i = 0; i < n - 1; i++)
	{
		for(int j = i+1; j < n; j++)
		{
			if((float)a[i].tu / a[i].mau > (float)a[j].tu / a[j].mau)//neu phan so i lon hon phan so j thi doi 2 vi tri cho nhau
				swap(a[i], a[j]);
		}
	}
}

void LuuFile(PhanSo a[20], int n)//luu phan so sau khi sap xep vao file
{	
	SapXep(a,n);
	fi.open("FRACTIONS.OUT.txt", ios::out);//mo file de ghi
	for(int i = 0; i < n; i++)
	{
		fi << a[i].tu << "/" << a[i].mau << endl;
	}
	fi.close();
}


void KiemTra(int n, int p, int q) //kiem tra theo dieu kien cua de
{
	PhanSo a[(n / 2) - 1];
	int v = 0; //vi tri
	//phan doi day n ra de khong kiem tra trung lai
	for (float i = n / 2; i < n; i++) 
	{
		for(float j = 1; j < n / 2; j++)
		{
			if(j/i > (float)1/p && j/i < (float)1/q) //kiem tra dieu kien (1/p) < f < (1/q)
			{
				a[v].tu = j;
				a[v].mau = i;
				v++;
			}
		}
	}
	LuuFile(a, (n / 2) - 1); 
	cout << "Ghi thanh cong! Mo File FRACTION.OUT de xem!";
}

int main()
{
	int n, p, q;
	DocFile(n,p,q);
	KiemTra(n,p,q);
}
