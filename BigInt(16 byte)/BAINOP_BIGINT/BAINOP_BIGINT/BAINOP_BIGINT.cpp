/*
So nguyen lon-co dau-dang BU 2
*/
#include <string>
#include <iostream>
#include <conio.h>
using namespace std;
struct bigint		//khoi tao kdl bigint
{
	int a[4];
};
const bigint ZERO={0};
//Khai Bao Ham


int GetBit(bigint x, int i);
void SetBit(bigint &x, int bit, int i);
string TongChuoi(string x, string y);
string Tinh2Mu(int mu);
string Chia2(string x);
string Str_abs(string x);
void Dao_Bit(bigint &a);
void StrToBigint(string x, bigint &a);
void NhapChuoi_CoDieuKien(string &x);
void ScanfBigint(bigint &a);
void PrintfBigint(bigint a);
bool operator==(bigint a, bigint b);
bool operator!=(bigint a, bigint b);
bool SSLonDuong_bigint(bigint a, bigint b);
bool operator>(bigint a, bigint b);
bool operator<(bigint a, bigint b);
bool operator>=(bigint a, bigint b);
bool operator<=(bigint a, bigint b);
void DecToBin(bigint x);
void BinToDec(int x[], bigint &a);
bigint convert(int a);
bigint DichTrai_bigint(bigint a);
bigint operator<<(bigint a, int n);
bigint DichPhai_bigint(bigint a);
bigint operator>>(bigint a, int n);
bigint operator+(bigint a, bigint b);
bigint operator-(bigint a);
bigint operator-(bigint a, bigint b);
bigint NhanKhongDau(bigint a, bigint b);
bigint operator*(bigint a, bigint b);
bigint ChiaKhongDau_Nguyen(bigint a, bigint b);
bigint operator/(bigint a, bigint b);
bigint ChiaKhongDau_Du(bigint a, bigint b);
bigint operator%(bigint a, bigint b);
//Cac Ham Nhap Xuat Va Ho Tro


int GetBit(bigint x, int i)
{
	return (x.a[i/32]>>(31-i%32))&1;
}
void SetBit(bigint &x, int bit, int i)				
{
	int vt=i/32;
	x.a[vt]=x.a[vt]^(bit<<(31-i%32));
}
string TongChuoi(string x, string y)	
{
	if(x.length()<y.length())
	{
		string tam=x;
		x=y;
		y=tam;
	}
	int lenx=x.length();
	int leny=y.length();
	string z="";
	for(int i=0; i<lenx-leny; i++)
		z+="0";
	y=z+y;
	string kq=x;
	int du=0;
	for(int i=lenx-1; i>=0; i--)
	{
		int gtri=x[i]-'0'+y[i]-'0'+du;
		if(gtri>9)
		{
			du=1;
			kq[i]=gtri%10+'0';
		}
		else
		{
			du=0;
			kq[i]=gtri+'0';
		}
	}
	if(du==1)
		kq="1"+kq;
	return kq;
}
string Tinh2Mu(int mu)					
{
	string kq="1";
	if(mu!=0)
		for(int i=0; i<mu; i++)
			kq=TongChuoi(kq, kq);
	return kq;
}
string Chia2(string x)		//chia 2 tren chuoi DUONG; gttv la chuoi
{
	char str[50];
	int j=0;
	int tam, du=0;
	int n=x.length();
	if(x[n-1]=='1') x[n-1]='0';
	int xet=0;				//Dung de xet xem ki tu dau chuoi co la 1 hay khong
	if(x[0]=='1')
	{
		xet=1;
		du=1;
	}
	for(int i=xet; i<n; i++)
	{
		int so=x[i]-'0';
		if(so!=1||du!=0)
		{
			tam=so+10*du;
			str[j++]=tam/2+'0';
			du=tam%2;
		}
		else
		{
			str[j++]='0';
			du=1;
		}
	}
	string kq(str,j); 
	return kq;
}
string Str_abs(string x)
{
	if(x[0]==45)
	{
		char kq[41];
		for(int i=1; i<x.length(); i++)
			kq[i-1]=x[i];
		string t(kq, x.length()-1);
		return t;
	}
	else
		return x;
}
void StrToBigint(string x, bigint &a)
{
	int i=127;
	int flag=0;				//flag=0: so duong, flag=1: so am
	if(x[0]=='-')
	{
		flag=1;
		x=Str_abs(x);		//Ham Chia2 chi xu ly chuoi DUONG
	}
	while(x!="0")
	{
		int du=(x[x.length()-1]-'0')%2; 
		SetBit(a, du, i);
		x=Chia2(x);
		i--;
	}
	if(flag==1)
		a=-a;
}
void NhapChuoi_CoDieuKien(string &x)
{
	cin>>x;
	int len=x.length();
	int vt=-1;
	if(x[0]=='-')
		vt=0;
	int flag=1;
	for(int i=vt+1; i<len; i++)
		if(x[i]!='0')
			flag=0;
	if(flag==1&&x!="-")
	{
		x="0";
		return;
	}
	for(int i=vt+1; x[i]=='0'; i++)
	{
		for(int j=i; j<len; j++)
			x[j]=x[j+1];
		i--;
	}
	int i;
	char *str=new char[x.length()];
	if(vt==0)
		str[vt]='-';
	for(i=vt+1; x[i]>='0'&&x[i]<='9'; i++)
		str[i]=x[i];
	string kq(str, i);
	x=kq;
}
void ScanfBigint(bigint &a)
{
	bigint b=ZERO;
	string x;
	NhapChuoi_CoDieuKien(x);
	StrToBigint(x, b);
	a=b;
}
void PrintfBigint(bigint a)
{
	int flag=0;
	if(GetBit(a, 0)==1)
	{
		flag=1;
		a=-a;
	}
	string kq="0";
	for(int i=127; i>=0; i--)
	{
		int bit=GetBit(a, i);
		if(bit==1)
		{
			string t=Tinh2Mu(128-1-i);
			kq=TongChuoi(kq, t);
		}
	}
	if(flag==1)
		kq="-"+kq;
	cout<<kq<<endl;
}
//Cac Ham So Sanh


bool operator==(bigint a, bigint b)
{
	for(int i=0; i<4; i++)
		if((a.a[i]^b.a[i])!=0)
			return false;
	return true;
}

bool SSLonDuong_Bigint(bigint a, bigint b)
{
	for(int i=0; i<128; i++)
	{
		if(GetBit(a, i)==1&&GetBit(b, i)==0)
			return true;
		if(GetBit(a, i)==0&&GetBit(b, i)==1)
			return false;
	}
	return false;
}
bool operator>(bigint a, bigint b)
{
	if(a==b) return false;
	int a0=GetBit(a, 0);
	int b0=GetBit(b, 0);
	if(a0==1&&b0==0)
		return false;
	if(a0==0&&b0==1)
		return true;
	if((a0&b0)==1)
	{
		if(SSLonDuong_Bigint(-a, -b)==true) return false;
		return true;
	}
	return SSLonDuong_Bigint(a, b);
}
bool operator!=(bigint a, bigint b)
{
	if(a==b)
		return false;
	return true;
}
bool operator<(bigint a, bigint b)
{
	if(a>b||a==b)
		return false;
	return true;
}
bool operator>=(bigint a, bigint b)
{
	if(a==b||a>b)
		return true;
	return false;
}
bool operator<=(bigint a, bigint b)
{
	if(a>b)
		return false;
	return true;
}
//Ham Chuyen Doi


bigint convert(int a)
{
	bigint kq={0};
	int flag=0;
	if(a<0)
	{
		flag=1;
		a=-a;
	}
	kq.a[3]=kq.a[3]^a;
	if(flag==1)
	kq=-kq;
	return kq;
}
void DecToBin(bigint x)
{
	for(int i=0, dem=1; i<128; i++, dem++)
	{
		cout<<GetBit(x, i);
		if(dem==32)
		{
			cout<<"\n";
			dem=0;
		}
	}
}
void BinToDec(int x[], bigint &a)
{
	bigint b=ZERO;
	for(int i=0; i<128; i++)
		SetBit(b, x[i], i);
	a=b;
}
//Ham Xu Li Bit


void Dao_Bit(bigint &a)
{
	for(int i=0; i<4; i++)
		a.a[i]=a.a[i]^(-1);
}
bigint DichTrai_Bigint(bigint a)
{
	bigint b=ZERO;
	for(int i=127; i>=2; i--)
	{
		int bit=GetBit(a, i);
		SetBit(b, bit, i-1);
	}
	SetBit(b, GetBit(a, 0), 0);
	return b;
}
bigint operator<<(bigint a, int n)
{
	if(n>127)
		return ZERO;
	for(int i=0; i<n; i++)
		a=DichTrai_Bigint(a);
	return a;
}
bigint DichPhai_Bigint(bigint a)
{
	bigint b=ZERO;
	for(int i=1; i<127; i++)
	{
		int bit=GetBit(a, i);
		SetBit(b, bit, i+1);
	}
	SetBit(b, GetBit(a, 0), 0);
	return b;
}
bigint operator>>(bigint a, int n)
{
	if(n>127)
		return ZERO;
	for(int i=0; i<n; i++)
		a=DichPhai_Bigint(a);
	return a;
}
//Ham Tinh Toan

bigint operator+(bigint a, bigint b)	
{
	bigint c=ZERO;
	int du=0;
	for(int i=127; i>=0; i--)
	{
		int x=GetBit(a,i);
		int y=GetBit(b,i);
		int bit=(x+y+du)%2;
		du=(x+y+du)/2;
		SetBit(c, bit, i);
	}
	return c;
}

bigint operator-(bigint a)
{
	bigint One={ 0, 0, 0, 1};
	switch(GetBit(a, 0))
	{
	case 0:
		Dao_Bit(a);
		a = a+One;
		return a;
	case 1:
		a = a-One;
		Dao_Bit(a);
		return a;
	}
}
bigint operator-(bigint a, bigint b)
{
	b=-b;
	return a+b;
}

bigint NhanKhongDau(bigint a, bigint b)
{
	bigint c=a;
	for(int i=127; i>=0; i--)
	{
		if(GetBit(a, i)==1)
		{
			bigint d=b<<(127-i);
			c=c+d;
		}
	}
	c=c-a;
	return c;
}
bigint operator*(bigint a, bigint b)
{
	int a0=GetBit(a, 0);
	int b0=GetBit(b, 0);
	if((a0|b0)==0)
		return NhanKhongDau(a, b);
	if((a0&b0)==1)
		return NhanKhongDau(-a, -b);
	if(a0==1)
	{
		bigint temp=a;
		a=b;
		b=temp;
	}
	return -NhanKhongDau(a, -b);
}
bigint ChiaKhongDau_Nguyen(bigint a, bigint b)
{
	bigint c=ZERO;
	int dem=127;
	while(dem!=0)
	{
		bool bit=GetBit(a, 1);
		a=a<<1;
		c=c<<1;
		SetBit(c, bit, 127);
		c=c-b;
		if(c<ZERO)
			c=c+b;
		else
			SetBit(a, 1, 127);
		dem--;
	}
	return a;
}
bigint operator/(bigint a, bigint b)
{
	if(b==ZERO)
		cout<<"div0!"<<endl;
	int a0=GetBit(a, 0);
	int b0=GetBit(b, 0);
	if((a0|b0)==0)
		return ChiaKhongDau_Nguyen(a, b);
	if((a0&b0)==1)
		return ChiaKhongDau_Nguyen(-a, -b);
	if(a0==1)
		return -ChiaKhongDau_Nguyen(-a, b);
	return -ChiaKhongDau_Nguyen(a, -b);
}
bigint ChiaKhongDau_Du(bigint a, bigint b)
{
	bigint c=ZERO;
	int dem=127;
	while(dem!=0)
	{
		bool bit=GetBit(a, 1);
		a=a<<1;
		c=c<<1;
		SetBit(c, bit, 127);
		c=c-b;
		if(c<ZERO)
			c=c+b;
		else
			SetBit(a, 1, 127);
		dem--;
	}
	return c;
}
bigint operator%(bigint a, bigint b)
{
	if(b==ZERO)
		cout<<"mod0!"<<endl;
	int a0=GetBit(a, 0);
	int b0=GetBit(b, 0);
	if(b0==1)
		b=-b;
	if(a0==1)
		return -ChiaKhongDau_Du(-a, b);
	return ChiaKhongDau_Du(a, b);
}

void main()
{
	int n;
	bigint a, b, c;
	cout<<"Nhap bigint a: ";
	ScanfBigint(a);
	cout<<"Nhap bigint b: ";
	ScanfBigint(b);
	cout<<"--------------------Menu---------------------\n";
	cout<<"1. Xuat a va b\n2. Xem day bit a va b\n3. Tong a va b";
	cout<<"\n4. Hieu a va b\n5. Thuong a va b lay nguyen\n6. Tich a va b\n7. Dich trai a\n";
	cout<<"8. Dich phai b\n9. Thuong a va b lay du\n10. DecToBin\n";
	cout<<"---------------------------------------------\n";
	cout<<"Chon: ";
	cin>>n;
	cout<<"Ket qua:\n";
	switch(n)
	{
	case 1:
		cout<<"gia tri a: ";
		PrintfBigint(a);
		cout<<"gia tri b: ";
		PrintfBigint(b);
		break;
	case 2:
		cout<<"Day bit a:\n";
		DecToBin(a);
		cout<<"Day bit b:\n";
		DecToBin(b);
		break;
	case 3:
		c=a+b;
		PrintfBigint(c);
		break;
	case 4:
		c=a-b;
		PrintfBigint(c);
		break;
	case 5:
		c=a/b;
		PrintfBigint(c);
		break;
	case 6:
		c=a*b;
		PrintfBigint(c);
		break;
	case 7:
		c=a<<1;
		PrintfBigint(c);
		break;
	case 8:
		c=b>>1;
		PrintfBigint(c);
		break;
	case 9:
		c=a%b;
		PrintfBigint(c);
		break;
	case 10:
		int x[128];
		bigint a;
		cout<<"Moi ban nhap day bit (tu trai sang phai):\n";
		for(int i=0; i<128; i++)
		{
			cout<<"bit "<<i<<" =";
			while(1)
			{
				cin>>x[i];
				if(x[i]!=0&&x[i]!=1)
				{
					cout<<"Ban nhap sai, moi nhap lai...";
					continue;
				}
				else
					break;
			}
		}
		BinToDec(x, a);
		cout<<"Day bit vua nhap:\n";
		DecToBin(a);
		cout<<"Gia tri = ";
		PrintfBigint(a);
		break;
	default:
		cout<<"Ban nhap khong chinh xac!\n";
	}
	getch();
}
