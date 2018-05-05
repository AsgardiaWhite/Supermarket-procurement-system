#include "stdafx.h"
#include "Commodity.h"
#include <time.h>
#include<string>
#include<fstream>
#include<iostream>
fstream  file;
using namespace std;
//����Դ����
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
	
	cout << "��������Ʒ��ţ��������֣�" << endl;
	cin >> s->ID;
	if (cin.fail())
	{
		cin.clear();
		system("cls");
		cout << "���ʹ���" << endl;
		cin.get();
		return;
	}

	cout << "��������Ʒ����" << endl;
	cin >> s->Name;
	while (1)
	{
		if (s->Name == "")
		{
			cout << "��Ʒ���Ʋ���Ϊ�գ�����������" << endl;
			cin >> s->Name;
		}
		else
		{
			break;
		}
	}

	cout << "������ɹ��������������֣�" << endl;
	cin >> s->Num;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			system("cls");
			cout << "���ʹ���" << endl;
			cin.get();
			return;
		}
		else if (!(s->Num > 0))
		{
			cout << "�ɹ��������ܵ���1������������" << endl;
			cin >> s->Num;
		}
		else
		{
			break;
		}
	}

	cout << "������ɹ��ۣ��������֣�" << endl;
	cin >> s->BuyIn;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			system("cls");
			cout << "���ʹ���" << endl;
			cin.get();
			return;
		}
		else if (s->BuyIn < 0)
		{
			cout << "�ɹ��۲��ܵ���0Ԫ������������" << endl;
			cin >> s->BuyIn;
		}
		else
		{
			break;
		}
	}

	cout << "�������ۼۣ��������֣�" << endl;
	cin >> s->SellOut;
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			system("cls");
			cout << "���ʹ���" << endl;
			cin.get();
			return;
		}
		else if (s->SellOut < 0)
		{
			cout << "�ۼ۲��ܵ���0Ԫ������������" << endl;
			cin >> s->SellOut;
		}
		else
		{
			break;
		}
	}
	system("cls");
	Save();
	cout << "��ӳɹ�" << endl;
}
void Commodity::Buy()
{
	string Name;
	cout << "������Ҫ�������Ʒ���ƣ�\n";
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
		cout << "��������������" << endl;
		int a; 
		cin >> a;
		p1->Num = p1->Num + a;
		system("cls");
		cout << "��ӳɹ�!\n";
		Save();
		Save(p1->ID, 3);
	}
	else
		system("cls");
		cout << "Sorry,δ�ҵ���Ʒ!\n";
}
void Commodity::Sell()
{
	string Name;
	cout << "������Ҫ��������Ʒ���ƣ�\n";
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
		cout << "��������������" << endl;
		int a;
		cin >> a;
		if ((p1->Num - a) < 0)
		{
			system("cls");
			cout << "���������" << endl;
		}
		else
		{
			p1->Num = p1->Num - a;
			system("cls");
			cout << "�����ɹ�!\n";
			Save();
			Save(p1->ID, 2);
		}
	}
	else
		system("cls");
		cout << "Sorry,δ�ҵ���Ʒ!\n";
}
void Commodity::Create_File()
{
	FILE *fp;
	if ((fp=fopen("user.txt","rb"))==NULL)//������ļ�������
	{
		if ((fp = fopen("user.txt", "wb+")) == NULL)//����ļ�����ʧ��
		{
			system("cls");
			cout << "�޷������ļ�" << endl;
		}
	}
}
void Commodity::Register()
{
	string pwd;
	cout << "���������Ա����" << endl;
	cin >> pwd;
	while (1)
	{
		if (pwd !="password")
		{
			cout << "�������" << endl;
			break;
		}
		else
		{
			User a, b;
			FILE *fp;
			fp = fopen("user.txt", "r");

			fread(&b, sizeof(struct User), 1, fp);//����һ���ṹ���ַ��鵽b
			cout << "�������˺�" << endl;
			cin >> a.id;

			while (1)
			{
				if (strcmp(a.id, b.id))//������������
				{
					if (!feof(fp))//���δ���ļ�β
					{
						fread(&b, sizeof(struct User), 1, fp);
					}
					else
						break;
				}
				else
				{
					cout << "���û����Ѵ���" << endl;
					fclose(fp);
					Register();
				}
			}
			cout << "����������" << endl;
			cin >> a.pwd;
			fp = fopen("user.txt", "a");
			fwrite(&a, sizeof(struct User), 1, fp);
			system("cls");
			cout << "�˺�ע��ɹ�" << endl;
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
	cout << "�������˺�" << endl;
	cin >> a.id;
	while (1)
	{
		if (strcmp(a.id, b.id) == 0)//����д��û���
		{
			break;
		}
		else
		{
			if (!feof(fp))//����ļ�û�ж���
			{
				fread(&b, sizeof(struct User), 1, fp);
			}
			else
			{
				cout << "���û��������ڣ�" << endl;
				fclose(fp);
				Login();
			}
		}
	}
	cout << "����������" << endl;
	cin >> a.pwd;
	if (strcmp(a.pwd, b.pwd) == 0)//�������ƥ��
	{
		fclose(fp);
		system("cls");
		cout << "��¼�ɹ�����ӭʹ��!" << endl;
	}
	else
	{
		system("cls");
		cout << "���벻��ȷ" << endl;
		fclose(fp);
		Login();
	}
	return false;
}
//����긺��
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
void Commodity::Save(int _ID, int flag)//flag Ϊ��־λ��2�������ۼ�¼��3�������¼��_ID Ϊ��Ʒ���ID
{
	ofstream  file;
	Node * p = head;
	time_t t = time(0);
	char temp[50];
	strftime(temp, sizeof(temp), "%Y��%m��%d��%X%A", localtime(&t));
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
			cout << "��־�ļ�����ʧ�ܣ�" << endl;
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
			cout << "��־�ļ�����ʧ�ܣ�" << endl;
		}
		file.close();
	}
}
void Commodity::del_info()
{
	Node * p = head, *q;
	int _ID;
	cout << "��������ɾ���ı��" << endl;
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
		cout << " ��Ϣ����ɾ��ʧ�ܣ�" << endl;
}
void Commodity::ShowJournal()
{
	ifstream infile("journal.txt", ios::in | ios::binary);//��һ����Ϣ
	char ch;
	while (infile.get(ch))  cout << ch;
	infile.close();
}
//�γ�����
void Commodity::Add_up() //ͳ�Ƴ�����Ʒ�������ڼ�ֵ
{
	system("cls");
	cout << "****��Ʒͳ��****\n";
	int Amount = 0; 
	float jiage = 0, Value = 0;
	string Name;
	cout << "\n������Ҫͳ�Ƶ���Ʒ���ƣ�\n";
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
		cout << "��Ʒ�������ǣ�\n";
		cout << Amount;
		cout << "\n��Ʒ�ܼ�ֵ�ǣ�\n";
		cout << Value << "\n";
		cout << "ȫ���۳��ɻ������Ϊ��\n";
		cout << (Amount*jiage) - Value << "\n";
	}
	else
		cout << "\nSorry,δ�ҵ�������Ʒ!\n";
}
void Commodity::Modify() //�޸���Ʒ��Ϣ
{
	int amount;
	string Name;
	int ID;
	float SellOut;
	float Price;
	system("Cls");
	cout << "�޸���Ʒ��������Ҫ�����Ʒ���ƣ�\n";
	cout << "Name:"; cin >> Name;//����Ҫ�޸ĵĽ��
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
	}//�޸Ľ��
	if (p1 != NULL) //���ҵ����
	{

		cout << "ID:" << p1->ID << " Name:" << p1->Name << "SellOut:" << p1->SellOut << " amount:" << p1->Num << endl;

		cout << "\n��ѡ��Ҫ�޸ĵ���Ϣ��1����Ʒ���룬2����Ʒ���ƣ�3�����ۣ�4������Ʒ�������5���޸�ȫ����Ϣ��:\n";
		int a; cin >> a;
		switch (a)
		{
		case 1:cout << "�������´��룺"; cin >> ID;
			Name = p1->Name; SellOut = p1->SellOut; amount = p1->Num; Price = p1->BuyIn; break;
		case 2:cout << "�����������ƣ�"; cin >> Name;
			ID = p1->ID; SellOut = p1->SellOut; amount = p1->Num; Price = p1->BuyIn; break;
		case 3:cout << "�������µ��ۣ�"; cin >> SellOut;
			ID = p1->ID; Name = p1->Name; amount = p1->Num; Price = p1->BuyIn; break;
		case 4:cout << "�������¿�����ݣ�"; cin >> amount;
			ID = p1->ID; Name = p1->Name; SellOut = p1->SellOut; Price = p1->BuyIn; break;
		case 5:cout << "����������Ϣ��\n";
			cout << "��Ʒ����:"; cin >> ID;
			cout << "��Ʒ����:"; cin >> Name;
			cout << "��Ʒ����:"; cin >> SellOut;
			cout << "����Ʒ�����:"; cin >> amount; break;
		}//��������Ʒ���
		Node *p3;
		p3 = new Node;
		p3->ID = ID;
		p3->Name = Name;
		p3->SellOut = SellOut;
		p3->BuyIn = Price;
		p3->Num = amount;
		//Ա������滻������
		p3->Next = p1->Next;
		if (p1 == head) //��Ҫ�滻�Ľ���ǵ�һ�����
			head = p3;
		else //��Ҫ�滻�Ľ���Ǻ������
			p2->Next = p3;
		delete p1; //ɾ��ԭ������Ʒ���
		Save();
		cout << "�޸ĳɹ�!\n";
	}
	else //δ�ҵ����
		cout << "Sorry,δ�ҵ�!\n";
}


//���γ�����
void Commodity::GetInformathion()
{
	int _ID;
	cout << "���������ѯ�ı��" << endl;
	cin >> _ID;
	if (cin.fail())
	{
		cin.clear();
		system("cls");
		cout << "���ʹ���" << endl;
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
		cout << "��Ʒ����" << p->Name << endl;
		cout << "��Ʒ��ţ�" << p->ID << endl;
		cout << "��Ʒ��棺" << p->Num << endl;
		cout << "��Ʒ���ۣ�" << p->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << p->SellOut << endl;
	}
	else if(p->Next == NULL)
	{
		system("cls");
		cout << "�����������Ʒ��Ų�����,�����²�ѯ��" << endl;
	}
}
void Commodity::Sort()
{
	cout << "*********��ѡ��鿴��ʽ**********" << endl;
	cout << "1������������ƷID����" << endl;
	cout << "2������������Ʒ�������" << endl;
	cout << "3������������Ʒ���������" << endl;
	cout << "4������������Ʒ�۳�������" << endl;
	int n, i = 1;
	while (i)
	{
		cout << "��������ѡ�������ʽ:";
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
			cout << "�����������������룡" << endl;
			continue;
		}
		cout << "�Ƿ����ѡ������ʽ��1��������������0������������" << endl;
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
		cout << "��Ʒ����" << l->Next->Name << endl;
		cout << "��Ʒ��ţ�" << l->Next->ID << endl;
		cout << "��Ʒ��棺" << l->Next->Num << endl;
		cout << "��Ʒ���ۣ�" << l->Next->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << l->Next->SellOut << endl;
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
		cout << "��Ʒ����" << l->Next->Name << endl;
		cout << "��Ʒ��ţ�" << l->Next->ID << endl;
		cout << "��Ʒ��棺" << l->Next->Num << endl;
		cout << "��Ʒ���ۣ�" << l->Next->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << l->Next->SellOut << endl;
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
		cout << "��Ʒ����" << l->Next->Name << endl;
		cout << "��Ʒ��ţ�" << l->Next->ID << endl;
		cout << "��Ʒ��棺" << l->Next->Num << endl;
		cout << "��Ʒ���ۣ�" << l->Next->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << l->Next->SellOut << endl;
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
		cout << "��Ʒ����" << l->Next->Name << endl;
		cout << "��Ʒ��ţ�" << l->Next->ID << endl;
		cout << "��Ʒ��棺" << l->Next->Num << endl;
		cout << "��Ʒ���ۣ�" << l->Next->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << l->Next->SellOut << endl;
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