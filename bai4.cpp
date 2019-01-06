#include<iostream>
#include<fstream>
#include<stdio.h>
# define ds	"danhsach.txt" 
# define ds1 "ds1.txt"
# define ds2 "ds2.txt"
using namespace std;

int n, p = 1;//p la so luong phan tu lay ra
FILE *a, *b, *c;

//-------------------------------------------------------------------------------------------------------------------------------------
void TaoMoi()//ham tao moi vao file
{
	
	int	x;
	FILE *a;			
	printf("Nhap vao so phan tu: "); 	
	scanf("%d", &n);
	printf("\n");
	a = fopen("danhsach.txt","wt");//ghi vao file a
	printf("\nNhap vao cac phan tu lan luot: \n");
	for (int i=0; i<n; i++)
	{
		printf(" - ");
		scanf("%d", &x);//nhap phan tu x tu ban phim
		fprintf(a, "%3d", x); //ghi phan tu x vao file 
	}
	fclose(a);//dong file a
}

//-------------------------------------------------------------------------------------------------------------------------------------
void Xuat(FILE *a, const char link[])//dua cac phan tu trong file ra man hinh
{
	
	int	x;
	a = fopen(link,"rt"); 
	printf("\t");
	while  (!feof(a)) //doc file danhsach den khi het file thi dung
	{
		fscanf(a, "%d", &x);
		printf("%3d", x);	
	
	}
	fclose(a);
}

//-------------------------------------------------------------------------------------------------------------------------------------
void Tach(FILE *a, FILE *b, FILE *c, int p)//dung de tach day run tu file a ra 2 file b va c
{
	int dem, x;
	//mo cac file de ghi/doc
	a = fopen("danhsach.txt","rt"); 	
	b = fopen("ds1.txt","wt"); 	
	c = fopen("ds2.txt","wt"); 
	while (!feof(a)) //doc file a den khi het file thi dung
	{
		dem = 0;//gan bien dem ban dau bang 0
		while ((dem<p)and (!feof(a)))//khi bien dem van con nho hon so luong phan tu p va file a van con phan tu
		{
			fscanf(a,"%3d", &x);//doc 1 phan tu tu file a ra x	
			fprintf(b,"%3d", x);//ghi x ra file	a	
			dem++;	//tang bien dem len 1 don vi		
		}		
		dem = 0; //reset lai bien dem
		while ((dem<p)and (!feof(a)))
		{
			
			fscanf(a,"%3d", &x); //doc 1 phan tu tu file a ra x	
			fprintf(c,"%3d", x); //ghi x ra file c	
			dem++;	//tang bien dem len 1 don vi		
		}
	}
	//dong cac file lai
	fclose(a);	 
	fclose(b);		
	fclose(c);
}

//-------------------------------------------------------------------------------------------------------------------------------------
void Tron(FILE *a, FILE *b, FILE *c, int p)//gop day run trong file b va c vao lai file a
{
	//x dung de ghi/doc vao file b
	//y dung de ghi/doc vao file c
	//m  khai bao so phan tu cua b ghi len a
	//n khai bao so phan tu cua c da ghi len a
	int	stop, x, y, m, n;
	//goi ra cac duong dan
	a = fopen("danhsach.txt","wt"); 	
	b = fopen("ds1.txt","rt"); 	
	c = fopen("ds2.txt","rt");
	
	while ((!feof(b))&& (!feof(c)))//khi file b va c con phan tu
	{
		m = 0;
		n = 0;
		fscanf(b, "%3d", &x); //doc 1 phan tu tu file b vao bien x
		fscanf(c, "%3d", &y); //doc 1 phan tu tu file c vao bien y
		stop = 0;//gan bien dung = 0
		while ((m!=p)&& (n!=p)&& (!stop))
		{
			if (x<y)//ghi file b vao
			{
				fprintf(a,"%3d", x);//ghi x ra file	a
				m++;//so phan tu cua b ghi vao a tang len 1
				if ((m<p)&& (!feof(b)))	//so phan tu b van con nho hon so luong p va chua het file b
					fscanf(b, "%3d", &x);//doc phan tu tu b vao bien x
				else //da xong b hoac ket thuc
				{
					fprintf(a,"%3d", y);//ghi y ra file	a
					n++;//so phan tu cua c ghi vao a tang len 1
					if (feof(b))//neu b da ket thuc
						stop = 1;//dung lai
				}
			}
			else //ghi file c vao
			{
				fprintf(a,"%3d", y);//ghi y ra file	a
				n++;//so phan tu cua c ghi vao c tang len 1
				
				if ((n<p) && (!feof(c)))//so phan tu b van con nho hon so luong p va chua het file c
					fscanf(c, "%3d", &y);//doc phan tu tu c vao bien x
				else //da xong c hoac ket thuc
				{
					fprintf(a,"%3d", x);//ghi x ra file	a
					m++;//so phan tu cua b ghi vao a tang len 1
					if (feof(c))//neu b da ket thuc
						stop = 1;//dung lai
				}							
			}	
		}
		
		//khi file b da het phan tu nhung file c van con thi ghi p phan tu con lai vao file a
		//ghi tiep phan con lai cua p phan tu tren c vao a
		while ((n<p)&& (!feof(c)))	
		{
			fscanf(c, "%3d", &y);
			fprintf(a,"%3d", y);	
			n++;
		}				
		//khi file c da het phan tu nhung file b van con thi tiep tuc ghi p phan tu vao file a
		while ((m<p)&& (!feof(b)))	
		{
			fscanf(b, "%3d", &x);
			fprintf(a,"%3d", x);	
			m++;
		}
	}
	if(!feof(b))// b con phan tu
	{
		//chep phan con lai cua b len a
			while (!feof(b))
			{	
				fscanf(b, "%3d", &x);
				fprintf(a,"%3d", x);	
			}
	}
	if(!feof(c))// c con phan tu
	{
		//chep phan con lai cua c len a
			while (!feof(c))
			{	
				fscanf(c, "%3d", &y);
				fprintf(a,"%3d", y);	
			}
	}
	//dong cac file lai
	fclose(a);	 
	fclose(b);		
	fclose(c);	
}

int main()
{
	TaoMoi();
	printf("\n==============================================\n");
	Xuat(a,ds);
	printf("\n      -------------------------------          ");
	printf("\n------Thuat toan Straight - Merge Sort --------\n");
	while	(p<n) ///khi chua duyet het danh sach
	{
	
		Tach(a, b, c, p);
		printf("\n Xuat ra tu file 1:\n"); 	
		Xuat(b, ds1);  
		printf("\n Xuat ra file 2:\n");
		Xuat(c, ds2);  
		Tron(a, b, c, p);
		printf("\n Sau khi tron:\n");
		Xuat(a, ds); 
		p = p*2;//tiep tuc gap doi so luong lay ra	
		printf("\n----------------");	
	}
	printf("Ket thuc !");
}

