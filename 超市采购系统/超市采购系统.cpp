// 超市采购系统.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Commodity.h"
#include<iostream>
using namespace std;
int main()
{
	int c;
	Commodity a;
	a.Create_File();
	a.Login();
	fstream File;
	
	Node temp;
	Node *s = a.head;
	
	int n;
	int i;
	for (i = 0; !File.eof(); i++)
	{
		File.open("stock.txt", ios::in | ios::binary);
		File.seekg(i * sizeof(Node), ios::beg);
		File.read((char *)&temp, sizeof(Node));
		File.close();
	}
	n = i - 1;
	for (int i = 0; i<n; ++i)
	{
		File.open("stock.txt", ios::in | ios::binary);
		Node *q = new Node;
		File.seekg(i * sizeof(Node), ios::beg);
		File.read((char *)&temp, sizeof(Node));
		q->ID = temp.ID;
		q->Name = temp.Name;
		q->Num = temp.Num;
		q->BuyIn = temp.BuyIn;
		q->SellOut = temp.SellOut;
		q->Next = NULL;
		s->Next = q;
		s = s->Next;
		File.close();
	}
	
	do
	{
		cout  <<"\t╔═══════════════════════════╗\n";
		cout  <<"\t║               欢迎使用超市采购系统                   ║\n";
		cout  <<"\t╠═══════════════════════════╣\n";
		cout << "\t║                 1 -   添加新品                       ║\n";
		cout << "\t║                 2 -   下架商品                       ║\n";
		cout << "\t║                 3 -   买入商品                       ║\n";
		cout << "\t║                 4 -   卖出商品                       ║\n";
		cout << "\t║                 5 -   修改商品                       ║\n";
		cout << "\t║                 6 -   统计商品                       ║\n";
		cout << "\t║                 7 -   查询商品                       ║\n";
		cout << "\t║                 8 -   查看商品                       ║\n";
		cout << "\t║                 9 -   注册账号	                   ║\n";
		cout << "\t║                 10 -   查询日志记录                  ║\n";
		cout << "\t║                 11 -   退出                          ║\n";
		cout << "\t╚═══════════════════════════╝\n";
		cin >> c;
		switch (c)
		{
		case 1:a.AddNew(); break;
		case 2:a.del_info();  break;
		case 3:a.Buy();   break;
		case 4:a.Sell(); break;
		case 5:a.Modify();  break;
		case 6:a.Add_up();break;
		case 7:a.GetInformathion(); break;
		case 8:a.Sort(); break;
		case 9:a.Register(); break;
		case 10:a.ShowJournal(); break;
		case 11:exit(0);
		default:
			system("cls");
			cout << "无效编号！请重新输入" << endl;
			break;
		}
	} while (1);
	return 0;
}

