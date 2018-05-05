#include "stdafx.h"
#include "Commodity.h"
#include <time.h>
#include<string>
#include<fstream>
#include<iostream>
fstream  file;
using namespace std;
//耿梓源负责
void Commodity::AddNew()
{
	Node *p,*s;
	s = new Node;
	p = head;
	while (p->Next)
	{
		p = p->Next;
	}
	s->Next = NULL;
	p->Next = s;
	
	cout << "请输入商品编号（仅限数字）" << endl;
	cin >> s->ID;
	if (cin.fail())
	{
		cin.clear();
		system("cls");
		cout << "类型错误" << endl;
		cin.get();
		return;
	}

	cout << "请输入商品名称" << endl;
	cin >> s->Name;
	while (1)
	{
		if (s->Name == "")
		{
			cout << "商品名称不能为空，请重新输入" << endl;
			cin >> s->Name;
		}
		else
		{
			break;
		}
	}

	cout << "请输入采购数量（仅限数字）" << endl;
	cin >> s->Num;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			system("cls");
			cout << "类型错误" << endl;
			cin.get();
			return;
		}
		else if (!(s->Num > 0))
		{
			cout << "采购数量不能低于1，请重新输入" << endl;
			cin >> s->Num;
		}
		else
		{
			break;
		}
	}

	cout << "请输入采购价（仅限数字）" << endl;
	cin >> s->BuyIn;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			system("cls");
			cout << "类型错误" << endl;
			cin.get();
			return;
		}
		else if (s->BuyIn < 0)
		{
			cout << "采购价不能低于0元，请重新输入" << endl;
			cin >> s->BuyIn;
		}
		else
		{
			break;
		}
	}

	cout << "请输入售价（仅限数字）" << endl;
	cin >> s->SellOut;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			system("cls");
			cout << "类型错误" << endl;
			cin.get();
			return;
		}
		else if (s->SellOut < 0)
		{
			cout << "售价不能低于0元，请重新输入" << endl;
			cin >> s->SellOut;
		}
		else
		{
			break;
		}
	}
	system("cls");
	Save();
	cout << "添加成功" << endl;
}
void Commodity::Buy()
{
	string Name;
	cout << "请输入要买入的商品名称：\n";
	cout << "Name:"; 
	cin >> Name;
	Node *p1, *p2;
	p1 = head;
	p2 = NULL;
	while (p1)
	{
		if (p1->Name == Name) break;
		else
		{
			p2 = p1;
			p1 = p1->Next;
		}
	}
	if (p1 != NULL)
	{
		cout << "请输入买入数量" << endl;
		int a; 
		cin >> a;
		p1->Num = p1->Num + a;
		system("cls");
		cout << "添加成功!\n";
		Save();
		Save(p1->ID, 3);
	}
	else
		system("cls");
		cout << "Sorry,未找到商品!\n";
}
void Commodity::Sell()
{
	string Name;
	cout << "请输入要卖出的商品名称：\n";
	cout << "Name:"; 
	cin >> Name;
	Node *p1, *p2;
	p1 = head;
	p2 = NULL;
	while (p1)
	{
		if (p1->Name == Name) break;
		else
		{
			p2 = p1;
			p1 = p1->Next;
		}
	}
	if (p1 != NULL)
	{
		cout << "请输入卖出数量" << endl;
		int a;
		cin >> a;
		if ((p1->Num - a) < 0)
		{
			system("cls");
			cout << "库存量不足" << endl;
		}
		else
		{
			p1->Num = p1->Num - a;
			system("cls");
			cout << "卖出成功!\n";
			Save();
			Save(p1->ID, 2);
		}
	}
	else
		system("cls");
		cout << "Sorry,未找到商品!\n";
}
void Commodity::Create_File()
{
	FILE *fp;
	if ((fp=fopen("user.txt","rb"))==NULL)//如果此文件不存在
	{
		if ((fp = fopen("user.txt", "wb+")) == NULL)//如果文件创建失败
		{
			system("cls");
			cout << "无法建立文件" << endl;
		}
	}
}
void Commodity::Register()
{
	string pwd;
	cout << "请输入管理员密码" << endl;
	cin >> pwd;
	while (1)
	{
		if (pwd !="password")
		{
			cout << "密码错误" << endl;
			break;
		}
		else
		{
			User a, b;
			FILE *fp;
			fp = fopen("user.txt", "r");

			fread(&b, sizeof(struct User), 1, fp);//读入一个结构体字符块到b
			cout << "请输入账号" << endl;
			cin >> a.id;

			while (1)
			{
				if (strcmp(a.id, b.id))//如果两串不相等
				{
					if (!feof(fp))//如果未到文件尾
					{
						fread(&b, sizeof(struct User), 1, fp);
					}
					else
						break;
				}
				else
				{
					cout << "此用户名已存在" << endl;
					fclose(fp);
					Register();
				}
			}
			cout << "请输入密码" << endl;
			cin >> a.pwd;
			fp = fopen("user.txt", "a");
			fwrite(&a, sizeof(struct User), 1, fp);
			system("cls");
			cout << "账号注册成功" << endl;
			fclose(fp);
			break;
		}
	}
	
}
bool Commodity::Login()
{
	User a, b;
	FILE *fp;
	fp = fopen("user.txt", "r");
	fread(&b, sizeof(struct User), 1, fp);
	cout << "请输入账号" << endl;
	cin >> a.id;
	while (1)
	{
		if (strcmp(a.id, b.id) == 0)//如果有此用户名
		{
			break;
		}
		else
		{
			if (!feof(fp))//如果文件没有读完
			{
				fread(&b, sizeof(struct User), 1, fp);
			}
			else
			{
				cout << "此用户名不存在！" << endl;
				fclose(fp);
				Login();
			}
		}
	}
	cout << "请输入密码" << endl;
	cin >> a.pwd;
	if (strcmp(a.pwd, b.pwd) == 0)//如果密码匹配
	{
		fclose(fp);
		system("cls");
		cout << "登录成功，欢迎使用!" << endl;
	}
	else
	{
		system("cls");
		cout << "密码不正确" << endl;
		fclose(fp);
		Login();
	}
	return false;
}
//董殊宏负责
void Commodity::Save()
{
	file.open("stock.txt", ios::in | ios::out | ios::binary|ios::trunc);
	Node p;
	Node *q = head;
	/*p.ID = q->ID;
	p.Name = q->Name;
	p.Num = q->Num;
	p.BuyIn = q->BuyIn;
	p.SellOut = q->SellOut;
	file.write((char *)&p, sizeof(p));*/
	while (q->Next) 
	{

		p.ID = q->Next->ID;
		p.Name = q->Next->Name;
		p.Num = q->Next->Num;
		p.BuyIn = q->Next->BuyIn;
		p.SellOut = q->Next->SellOut;
		file.write((char *)&p, sizeof(p));
		q = q->Next;
	}
	file.close();
}
void Commodity::Save(int _ID, int flag)//flag 为标志位，2代表销售记录，3代表购入记录，_ID 为商品编号ID
{
	ofstream  file;
	Node * p = head;
	time_t t = time(0);
	char temp[50];
	strftime(temp, sizeof(temp), "%Y年%m月%d日%X%A", localtime(&t));
	if (flag == 2)
	{
		file.open("journal.txt", ios::out | ios::ate | ios::app);

		if (!file.fail())
		{
			while (p->Next && p->Next->ID != _ID)
				p = p->Next;
			if (p->Next)
			{
				file << "ID:" << p->Next->ID
					<< "\tNAME:" << p->Next->Name
					<< "\tCOST:" << p->Next->BuyIn
					<< "\tVALUE:" << p->Next->SellOut
					<< "\tSTOCK:" << p->Next->Num
					<< "\tTIME:" << temp
					<< "\tREMARKS:" << "SELLOUT"
					<< "\n";
			}
		}
		else
		{
			cout << "日志文件创建失败！" << endl;
		}
		file.close();
	}
	else if (flag == 3)
	{
		file.open("journal.txt", ios::out | ios::ate | ios::app);
		if (!file.fail())
		{
			while (p->Next && p->Next->ID != _ID)
				p = p->Next;
			if (p->Next)
			{
				file << "ID:" << p->Next->ID
					<< "\tNAME:" << p->Next->Name
					<< "\tCOST:" << p->Next->BuyIn
					<< "\tVALUE:" << p->Next->SellOut
					<< "\tSTOCK:" << p->Next->Num
					<< "\tTIME:" << temp
					<< "\tREMARKS:" << "BUYIN"
					<< "\n";
			}
		}
		else
		{
			cout << "日志文件创建失败！" << endl;
		}
		file.close();
	}
}
void Commodity::del_info()
{
	Node * p = head, *q;
	int _ID;
	cout << "请输入想删除的编号" << endl;
	cin >> _ID;
	int info_num = _ID;
	while (p->Next && p->Next->ID != info_num)
		p = p->Next;
	if (p->Next)
	{
		q = p->Next;
		p->Next = q->Next;
		delete q;
		Save();
	}
	else
		cout << " 信息错误，删除失败！" << endl;
}
void Commodity::ShowJournal()
{
	ifstream infile("journal.txt", ios::in | ios::binary);//读一条信息
	char ch;
	while (infile.get(ch))  cout << ch;
	infile.close();
}
//何畅负责
void Commodity::Add_up() //统计超市商品总数量于价值
{
	system("cls");
	cout << "****商品统计****\n";
	int Amount = 0; 
	float jiage = 0, Value = 0;
	string Name;
	cout << "\n请输入要统计的商品名称：\n";
	cin >> Name;
	Node *p1;
	p1 = head;
	while (p1)
	{
		if (p1->Name == Name) break;
		else p1 = p1->Next;
	}
	if (p1)
	{
		while (p1 &&p1->Name==Name)
		{
			Amount += p1->Num;
			Value += p1->Num*p1->BuyIn;
			jiage = p1->SellOut;
			p1 = p1->Next;
		}
		cout << "商品总数量是：\n";
		cout << Amount;
		cout << "\n商品总价值是：\n";
		cout << Value << "\n";
		cout << "全部售出可获得利润为：\n";
		cout << (Amount*jiage) - Value << "\n";
	}
	else
		cout << "\nSorry,未找到该类商品!\n";
}
void Commodity::Modify() //修改商品信息
{
	int amount;
	string Name;
	int ID;
	float SellOut;
	float Price;
	system("Cls");
	cout << "修改商品，请输入要查的商品名称：\n";
	cout << "Name:"; cin >> Name;//查找要修改的结点
	Node *p1, *p2;
	p1 = head;
	p2 = NULL;
	while (p1)
	{
		if (p1->Name == Name) break;
		else
		{
			p2 = p1;
			p1 = p1->Next;
		}
	}//修改结点
	if (p1 != NULL) //若找到结点
	{

		cout << "ID:" << p1->ID << " Name:" << p1->Name << "SellOut:" << p1->SellOut << " amount:" << p1->Num << endl;

		cout << "\n请选择要修改的信息（1—商品代码，2—商品名称，3—单价，4—该商品库存量，5—修改全部信息）:\n";
		int a; cin >> a;
		switch (a)
		{
		case 1:cout << "请输入新代码："; cin >> ID;
			Name = p1->Name; SellOut = p1->SellOut; amount = p1->Num; Price = p1->BuyIn; break;
		case 2:cout << "请输入新名称："; cin >> Name;
			ID = p1->ID; SellOut = p1->SellOut; amount = p1->Num; Price = p1->BuyIn; break;
		case 3:cout << "请输入新单价："; cin >> SellOut;
			ID = p1->ID; Name = p1->Name; amount = p1->Num; Price = p1->BuyIn; break;
		case 4:cout << "请输入新库存数据："; cin >> amount;
			ID = p1->ID; Name = p1->Name; SellOut = p1->SellOut; Price = p1->BuyIn; break;
		case 5:cout << "请输入新信息：\n";
			cout << "商品代码:"; cin >> ID;
			cout << "商品名称:"; cin >> Name;
			cout << "商品单价:"; cin >> SellOut;
			cout << "该商品库存量:"; cin >> amount; break;
		}//创建新商品结点
		Node *p3;
		p3 = new Node;
		p3->ID = ID;
		p3->Name = Name;
		p3->SellOut = SellOut;
		p3->BuyIn = Price;
		p3->Num = amount;
		//员工结点替换到链表
		p3->Next = p1->Next;
		if (p1 == head) //若要替换的结点是第一个结点
			head = p3;
		else //若要替换的结点是后续结点
			p2->Next = p3;
		delete p1; //删除原来的商品结点
		Save();
		cout << "修改成功!\n";
	}
	else //未找到结点
		cout << "Sorry,未找到!\n";
}


//刁鑫辰负责
void Commodity::GetInformathion()
{
	int _ID;
	cout << "请输入想查询的编号" << endl;
	cin >> _ID;
	if (cin.fail())
	{
		cin.clear();
		system("cls");
		cout << "类型错误" << endl;
		cin.get();
		return;
	}
	Node *p;
	p = head;
	while (p->Next != NULL && p->ID != _ID)
	{
		p = p->Next;
	}
	if (p->ID == _ID)
	{
		system("cls");
		cout << "商品名：" << p->Name << endl;
		cout << "商品编号：" << p->ID << endl;
		cout << "商品库存：" << p->Num << endl;
		cout << "商品进价：" << p->BuyIn << endl;
		cout << "商品售价：" << p->SellOut << endl;
	}
	else if(p->Next == NULL)
	{
		system("cls");
		cout << "输入有误或商品编号不存在,请重新查询！" << endl;
	}
}
void Commodity::Sort()
{
	cout << "*********请选择查看方式**********" << endl;
	cout << "1————按商品ID排序" << endl;
	cout << "2————按商品库存排序" << endl;
	cout << "3————按商品购入价排序" << endl;
	cout << "4————按商品售出价排序" << endl;
	int n, i = 1;
	while (i)
	{
		cout << "请输入你选择的排序方式:";
		cin >> n;
		if (n == 1)
		{
			SortbyId();
		}
		else if (n == 2)
		{
			SortbyNum();
		}
		else if (n == 3)
		{
			SortbyBuyIn();
		}
		else if (n == 4)
		{
			SortbySellOut();
		}
		else
		{
			cout << "输入有误，请重新输入！" << endl;
			continue;
		}
		cout << "是否继续选择排序方式？1————继续，0————结束" << endl;
		cin >> i;
	}
}
void Commodity::SortbyId()
{
	Node *p, *q, *r;
	r = new Node;
	p = new Node;
	q = new Node;
	for (p = head->Next; p->Next; p = p->Next)
	{
		for (q = p->Next; q; q = q->Next)
		{
			if ((p->ID) > (q->ID))
			{
				r->Name = p->Name;
				p->Name = q->Name;
				q->Name = r->Name;
				r->ID = p->ID;
				p->ID = q->ID;
				q->ID = r->ID;
				r->Num = p->Num;
				p->Num = q->Num;
				q->Num = r->Num;
				r->BuyIn = p->BuyIn;
				p->BuyIn = q->BuyIn;
				q->BuyIn = r->BuyIn;
				r->SellOut = p->SellOut;
				p->SellOut = q->SellOut;
				q->SellOut = r->SellOut;
			}
		}

	}
	Node *l = head;
	system("cls");
	while (l->Next)
	{
		cout << "商品名：" << l->Next->Name << endl;
		cout << "商品编号：" << l->Next->ID << endl;
		cout << "商品库存：" << l->Next->Num << endl;
		cout << "商品进价：" << l->Next->BuyIn << endl;
		cout << "商品售价：" << l->Next->SellOut << endl;
		l = l->Next;
	}

}
void Commodity::SortbyNum()
{
	Node *p, *q, *r;
	r = new Node;
	p = new Node;
	q = new Node;
	for (p = head->Next; p->Next; p = p->Next)
	{
		for (q = p->Next; q; q = q->Next)
		{
			if ((p->Num) > (q->Num))
			{
				r->Name = p->Name;
				p->Name = q->Name;
				q->Name = r->Name;
				r->ID = p->ID;
				p->ID = q->ID;
				q->ID = r->ID;
				r->Num = p->Num;
				p->Num = q->Num;
				q->Num = r->Num;
				r->BuyIn = p->BuyIn;
				p->BuyIn = q->BuyIn;
				q->BuyIn = r->BuyIn;
				r->SellOut = p->SellOut;
				p->SellOut = q->SellOut;
				q->SellOut = r->SellOut;
			}
		}

	}
	Node *l = head;
	system("cls");
	while (l->Next)
	{
		cout << "商品名：" << l->Next->Name << endl;
		cout << "商品编号：" << l->Next->ID << endl;
		cout << "商品库存：" << l->Next->Num << endl;
		cout << "商品进价：" << l->Next->BuyIn << endl;
		cout << "商品售价：" << l->Next->SellOut << endl;
		l = l->Next;
	}
}
void Commodity::SortbyBuyIn()
{
	Node *p, *q, *r;
	r = new Node;
	p = new Node;
	q = new Node;
	for (p = head->Next; p->Next; p = p->Next)
	{
		for (q = p->Next; q; q = q->Next)
		{
			if ((p->BuyIn) > (q->BuyIn))
			{
				r->Name = p->Name;
				p->Name = q->Name;
				q->Name = r->Name;
				r->ID = p->ID;
				p->ID = q->ID;
				q->ID = r->ID;
				r->Num = p->Num;
				p->Num = q->Num;
				q->Num = r->Num;
				r->BuyIn = p->BuyIn;
				p->BuyIn = q->BuyIn;
				q->BuyIn = r->BuyIn;
				r->SellOut = p->SellOut;
				p->SellOut = q->SellOut;
				q->SellOut = r->SellOut;
			}
		}

	}
	Node *l = head;
	system("cls");
	while (l->Next)
	{
		cout << "商品名：" << l->Next->Name << endl;
		cout << "商品编号：" << l->Next->ID << endl;
		cout << "商品库存：" << l->Next->Num << endl;
		cout << "商品进价：" << l->Next->BuyIn << endl;
		cout << "商品售价：" << l->Next->SellOut << endl;
		l = l->Next;
	}
}
void Commodity::SortbySellOut()
{
	Node *p, *q, *r;
	r = new Node;
	p = new Node;
	q = new Node;
	for (p = head->Next; p->Next; p = p->Next)
	{
		for (q = p->Next; q; q = q->Next)
		{
			if ((p->SellOut) > (q->SellOut))
			{
				r->Name = p->Name;
				p->Name = q->Name;
				q->Name = r->Name;
				r->ID = p->ID;
				p->ID = q->ID;
				q->ID = r->ID;
				r->Num = p->Num;
				p->Num = q->Num;
				q->Num = r->Num;
				r->BuyIn = p->BuyIn;
				p->BuyIn = q->BuyIn;
				q->BuyIn = r->BuyIn;
				r->SellOut = p->SellOut;
				p->SellOut = q->SellOut;
				q->SellOut = r->SellOut;
			}
		}

	}
	Node *l = head;
	system("cls");
	while (l->Next)
	{
		cout << "商品名：" << l->Next->Name << endl;
		cout << "商品编号：" << l->Next->ID << endl;
		cout << "商品库存：" << l->Next->Num << endl;
		cout << "商品进价：" << l->Next->BuyIn << endl;
		cout << "商品售价：" << l->Next->SellOut << endl;
		l = l->Next;
	}

}
Commodity::Commodity()
{
	head=new Node;
	head->Name = "NULL";
	head->ID = 0;
	head->BuyIn = 0;
	head->Num = 0;
	head->SellOut = 0;
	head->Next = NULL;
}
Commodity::~Commodity()
{
	Node *p;
	p = head;
	while (p)
	{
		p = p->Next;
		delete head;
		head = p;
	}
	head = NULL;
}