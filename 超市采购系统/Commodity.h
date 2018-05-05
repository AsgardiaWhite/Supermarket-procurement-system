#pragma once
#include <string>
#include <fstream>
using namespace std;
struct User
{
	char id[11];
	char pwd[20];
};
struct Node
{
	string Name;
	int Num;
	int ID;
	float SellOut;
	float BuyIn;
	Node* Next;
};
class Commodity
{
	
public:
	Node * head;
	void AddNew();//������Ʒģ��
	void Buy();//������Ʒģ��
	void Sell();//������Ʒģ��
	void Create_File();//�������ڱ����˺ź�������ļ�
	void Register(); //ע��ģ��
	bool Login();//��¼ģ��
	void Save();//������Ʒģ��
	void Save(int _ID, int flag);//�����¼ģ��
	void del_info();//�¼���Ʒģ��
	void Add_up();//ͳ��ģ��
	void Modify();//�޸���Ʒģ��
	void GetInformathion();//��ѯģ��
	void Sort();//����ģ��
	void SortbyId();
	void SortbyNum();
	void SortbyBuyIn();
	void SortbySellOut();
	void ShowJournal();//��ʾ��¼
	Commodity();
	~Commodity();
};