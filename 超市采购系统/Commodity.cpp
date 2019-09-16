#include "stdafx.h"
#include "Commodity.h"
#include <time.h>
#include<string>
#include<fstream>
#include<iostream>
fstream  file;
using namespace std;
void Commodity::AddNew(){
	Node *p,*s;
	s = new Node;
	p = head;
	// �����������β��
	while (p->Next){
		p = p->Next;
	}
	s->Next = NULL;
	p->Next = s;
	
	cout << "��������Ʒ��ţ��������֣�" << endl;
	cin >> s->ID;
	if (cin.fail()){
		cin.clear();
		system("cls");
		cout << "���ʹ���" << endl;
		cin.get();
		return;
	}
	cout << "��������Ʒ����" << endl;
	cin >> s->Name;
	while (true){
		if (s->Name == ""){
			cout << "��Ʒ���Ʋ���Ϊ�գ�����������" << endl;
			cin >> s->Name;
		}else{
			break;
		}
	}
	cout << "������ɹ��������������֣�" << endl;
	cin >> s->Num;
	while (true){
		if (cin.fail()){
			cin.clear();
			system("cls");
			cout << "���ʹ���" << endl;
			cin.get();
			return;
		}else if (!(s->Num > 0)){
			cout << "�ɹ��������ܵ���1������������" << endl;
			cin >> s->Num;
		}else{
			break;
		}
	}
	cout << "������ɹ��ۣ��������֣�" << endl;
	cin >> s->BuyIn;
	while (true){
		if (cin.fail()){
			cin.clear();
			system("cls");
			cout << "���ʹ���" << endl;
			cin.get();
			return;
		}else if (s->BuyIn < 0){
			cout << "�ɹ��۲��ܵ���0Ԫ������������" << endl;
			cin >> s->BuyIn;
		}else{
			break;
		}
	}
	cout << "�������ۼۣ��������֣�" << endl;
	cin >> s->SellOut;
	while (true){
		if (cin.fail()){
			cin.clear();
			system("cls");
			cout << "���ʹ���" << endl;
			cin.get();
			return;
		}else if (s->SellOut < 0){
			cout << "�ۼ۲��ܵ���0Ԫ������������" << endl;
			cin >> s->SellOut;
		}else{
			break;
		}
	}
	system("cls");
	cout << "��ӳɹ�" << endl;
}
void Commodity::Buy(){
	string Name;
	cout << "������Ҫ�������Ʒ���ƣ�\n";
	cout << "Name:"; 
	cin >> Name;
	Node *phead, *temp;
	phead = head;
	temp = NULL;
	while (phead){
		if (phead->Name == Name)
			break;
		else{
			temp = phead;
			phead = phead->Next;
		}
	}
	if (phead != NULL){
		cout << "��������������" << endl;
		int number; 
		cin >> number;
		phead->Num = phead->Num + number;
		system("cls");
		cout << "��ӳɹ�!\n";
		SaveLog(phead->ID, 3);
	}
	else {
		system("cls");
		cout << "Sorry,δ�ҵ���Ʒ!\n";
	}
}
void Commodity::Sell(){
	string Name;
	cout << "������Ҫ��������Ʒ���ƣ�\n";
	cout << "Name:"; 
	cin >> Name;
	Node *phead, *temp;
	phead = head;
	temp = NULL;
	while (phead){
		if (phead->Name == Name)
			break;
		else{
			temp = phead;
			phead = phead->Next;
		}
	}
	if (phead != NULL){
		cout << "��������������" << endl;
		int number;
		cin >> number;
		if ((phead->Num - number) < 0){
			system("cls");
			cout << "���������" << endl;
		}else{
			phead->Num = phead->Num - number;
			system("cls");
			cout << "�����ɹ�!\n";
			SaveLog(phead->ID, 2);
		}
	}
	else {
		system("cls");
		cout << "Sorry,δ�ҵ���Ʒ!\n";
	}
}
void Commodity::Create_File(){
	FILE *fp;
	if ((fp=fopen("user.txt","rb"))==NULL){ //������ļ�������
		if ((fp = fopen("user.txt", "wb+")) == NULL){ //����ļ�����ʧ��
			system("cls");
			cout << "�޷������ļ�" << endl;
		}
	}
}
void Commodity::Register(){
	string pwd;
	cout << "���������Ա����" << endl;
	cin >> pwd;
	while (true){
		if (pwd !="password"){
			cout << "�������" << endl;
			break;
		}else{
			User loginUser, checkUser; //ע����Ϣ������Ϣ
			FILE *fp;
			fp = fopen("user.txt", "r");

			fread(&checkUser, sizeof(struct User), 1, fp);//����һ���ṹ���ַ��鵽b
			cout << "�������˺�" << endl;
			cin >> loginUser.id;

			while (true){
				if (strcmp(loginUser.id, checkUser.id)){ //������������
					if (!feof(fp)){ //���δ���ļ�β
						fread(&checkUser, sizeof(struct User), 1, fp);
					}
					else
						break;
				}else{
					cout << "���û����Ѵ���" << endl;
					fclose(fp);
					Register();
				}
			}
			cout << "����������" << endl;
			cin >> loginUser.pwd;
			fp = fopen("user.txt", "a");
			fwrite(&loginUser, sizeof(struct User), 1, fp);
			system("cls");
			cout << "�˺�ע��ɹ�" << endl;
			fclose(fp);
			break;
		}
	}
}
bool Commodity::Login(){
	User loginUser, checkUser;
	FILE *fp; //����һ���ļ�����ָ��
	fp = fopen("user.txt", "r");
	fread(&checkUser, sizeof(struct User), 1, fp); //���ļ��ж�ȡ��Ϣ
	cout << "�������˺�" << endl;
	cin >> loginUser.id;
	while (true){
		if (strcmp(loginUser.id, checkUser.id) == 0){ 
			//������ļ���ƥ�䵽�˶�Ӧ���û���������¼�ɹ�
			break;
		}else{
			if (!feof(fp)){ //����ļ�û�ж���
				fread(&checkUser, sizeof(struct User), 1, fp);
			}else{
				cout << "���û��������ڣ�" << endl;
				fclose(fp);
				Login(); //���������û���
			}
		}
	}
	cout << "����������" << endl;
	cin >> loginUser.pwd;
	if (strcmp(loginUser.pwd, checkUser.pwd) == 0){ 
		//�������ƥ��ɹ�
		fclose(fp);
		system("cls");
		cout << "��¼�ɹ�����ӭʹ��!" << endl;
	}else{
		system("cls");
		cout << "���벻��ȷ" << endl;
		fclose(fp);
		Login();
	}
	return false;
}
void Commodity::Save(){
	file.open("stock.txt", ios::in | ios::out | ios::binary|ios::trunc);
	Node p,*q = head;
	while (q->Next) {
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
void Commodity::SaveLog(int _ID, int flag){ //flag Ϊ��־λ��2�������ۼ�¼��3�������¼��_ID Ϊ��Ʒ���ID
	ofstream  file;
	Node * p = head;
	time_t t = time(0);
	char temp[50];
	strftime(temp, sizeof(temp), "%Y��%m��%d��%X%A", localtime(&t));
	if (flag == 2){
		file.open("journal.txt", ios::out | ios::ate | ios::app);
		if (!file.fail()){
			while (p->Next && p->Next->ID != _ID)
				p = p->Next;
			if (p->Next){
				file << "��Ʒ���:" << p->Next->ID
					<< "\t��Ʒ����:" << p->Next->Name
					<< "\t�����:" << p->Next->BuyIn
					<< "\t�ۼ�:" << p->Next->SellOut
					<< "\t�����:" << p->Next->Num
					<< "\tʱ��:" << temp
					<< "\t��������:" << "����"
					<< "\n";
			}
		}else{
			cout << "��־�ļ�����ʧ�ܣ�" << endl;
		}
		file.close();
	}else if (flag == 3){
		file.open("journal.txt", ios::out | ios::ate | ios::app);
		if (!file.fail()){
			while (p->Next && p->Next->ID != _ID)
				p = p->Next;
			if (p->Next){
				file << "��Ʒ���:" << p->Next->ID
					<< "\t��Ʒ����:" << p->Next->Name
					<< "\t�����:" << p->Next->BuyIn
					<< "\t�ۼ�:" << p->Next->SellOut
					<< "\t�����:" << p->Next->Num
					<< "\tʱ��:" << temp
					<< "\t��������:" << "����"
					<< "\n";
			}
		}else{
			cout << "��־�ļ�����ʧ�ܣ�" << endl;
		}
		file.close();
	}
}
void Commodity::del_info(){
	Node * p = head, *q;
	int _ID;
	cout << "��������ɾ���ı��" << endl;
	cin >> _ID;
	int info_num = _ID;
	while (p->Next && p->Next->ID != info_num)
		p = p->Next;
	if (p->Next){
		q = p->Next;
		p->Next = q->Next;
		delete q;
	}else
		system("cls");
		cout << "��Ϣ����ɾ��ʧ�ܣ�" << endl;
}
void Commodity::ShowJournal(){
	system("cls");
	ifstream infile("journal.txt", ios::in | ios::binary);//��һ����Ϣ
	char ch;
	while (infile.get(ch))  
		cout << ch;
	infile.close();
}
void Commodity::Add_up(){ 
	//ͳ�Ƴ�����Ʒ���������ֵ
	system("cls");
	cout << "****��Ʒͳ��****\n";
	int Amount = 0; 
	float Price = 0, Value = 0;
	string Name;
	cout << "\n������Ҫͳ�Ƶ���Ʒ���ƣ�\n";
	cin >> Name;
	Node *phead;
	phead = head;
	while (phead){
		if (phead->Name == Name) 
			break;
		else 
			phead = phead->Next;
	}
	if (phead){
		while (phead &&phead->Name==Name){
			Amount += phead->Num;
			Value += phead->Num*phead->BuyIn;
			Price = phead->SellOut;
			phead = phead->Next;
		}
		cout << "��Ʒ�������ǣ�\n";
		cout << Amount;
		cout << "\n��Ʒ�ܼ�ֵ�ǣ�\n";
		cout << Value << "\n";
		cout << "ȫ���۳��ɻ������Ϊ��\n";
		cout << (Amount*Price) - Value << "\n";
	}else
		cout << "\nSorry,δ�ҵ�������Ʒ!\n";
}
void Commodity::Modify(){ //�޸���Ʒ��Ϣ
	int amount,ID;
	string Name;
	float SellOut,Price;
	system("cls");
	cout << "�޸���Ʒ��������Ҫ���ҵ���Ʒ���ƣ�\n";
	cout << "Name:"; 
	cin >> Name;//����Ҫ�޸ĵĽ��
	Node *phead, *temp;
	phead = head;
	temp = NULL;
	while (phead){
		if (phead->Name == Name)
			break;
		else{
			temp = phead;
			phead = phead->Next;
		}
	}
	if (phead != NULL){
		//���ҵ����
		cout << "���:" << phead->ID << " ����:" << phead->Name << " ����:" << phead->SellOut << " �����:" << phead->Num << endl;
		cout << "\n��ѡ��Ҫ�޸ĵ���Ϣ��1����Ʒ���룬2����Ʒ���ƣ�3�����ۣ�4������Ʒ�������:\n";
		int opt; 
		cin >> opt;
		switch (opt){
			case 1:cout << "�������´��룺"; cin >> ID;
				Name = phead->Name; SellOut = phead->SellOut; amount = phead->Num; Price = phead->BuyIn; break;
			case 2:cout << "�����������ƣ�"; cin >> Name;
				ID = phead->ID; SellOut = phead->SellOut; amount = phead->Num; Price = phead->BuyIn; break;
			case 3:cout << "�������µ��ۣ�"; cin >> SellOut;
				ID = phead->ID; Name = phead->Name; amount = phead->Num; Price = phead->BuyIn; break;
			case 4:cout << "�������¿�����ݣ�"; cin >> amount;
				ID = phead->ID; Name = phead->Name; SellOut = phead->SellOut; Price = phead->BuyIn; break;
			default:
				system("cls");
				cout << "��Ч��ţ�����������" << endl;
				break;
		}
		//�����µ���Ʒ���
		Node *newComdity;
		newComdity = new Node;
		newComdity->ID = ID;
		newComdity->Name = Name;
		newComdity->SellOut = SellOut;
		newComdity->BuyIn = Price;
		newComdity->Num = amount;
		//Ա������滻������
		newComdity->Next = phead->Next;
		if (phead == head) //��Ҫ�滻�Ľ���ǵ�һ�����
			head = newComdity;
		else //��Ҫ�滻�Ľ���Ǻ������
			temp->Next = newComdity;
		delete phead; //ɾ��ԭ������Ʒ���
		cout << "�޸ĳɹ�!\n";
	}else //δ�ҵ����
		cout << "Sorry,δ�ҵ�!\n";
}
void Commodity::GetInformathion(){
	int _ID;
	cout << "���������ѯ�ı��" << endl;
	cin >> _ID;
	if (cin.fail()){
		cin.clear();
		system("cls");
		cout << "���ʹ���" << endl;
		cin.get();
		return;
	}
	Node *p;
	p = head;
	while (p->Next != NULL && p->ID != _ID){
		p = p->Next;
	}
	if (p->ID == _ID){
		system("cls");
		cout << "��Ʒ����" << p->Name << endl;
		cout << "��Ʒ��ţ�" << p->ID << endl;
		cout << "��Ʒ��棺" << p->Num << endl;
		cout << "��Ʒ���ۣ�" << p->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << p->SellOut << endl;
	}else if(p->Next == NULL){
		system("cls");
		cout << "�����������Ʒ��Ų�����,�����²�ѯ��" << endl;
	}
}
void Commodity::Sort(){
	if (head->Next->Next){
		cout << "*********��ѡ��鿴��ʽ**********" << endl;
		cout << "1������������ƷID����" << endl;
		cout << "2������������Ʒ�������" << endl;
		cout << "3������������Ʒ���������" << endl;
		cout << "4������������Ʒ�۳�������" << endl;
		int opt, choice = 1;
		while (choice) {
			cout << "��������ѡ�������ʽ:";
			cin >> opt;
			if (opt == 1) {
				SortbyId();
			}
			else if (opt == 2) {
				SortbyNum();
			}
			else if (opt == 3) {
				SortbyBuyIn();
			}
			else if (opt == 4) {
				SortbySellOut();
			}
			else {
				cout << "�����������������룡" << endl;
				continue;
			}
			cout << "�Ƿ����ѡ������ʽ��1��������������0������������" << endl;
			cin >> choice;
		}
	}else{
		system("cls");
		cout << "���Ϊ0����¼����Ʒ��" << endl;
	}
}
void Commodity::SortbyId(){
	Node *p, *q, *r;
	r = new Node;
	p = new Node;
	q = new Node;
	for (p = head->Next; p->Next; p = p->Next){
		for (q = p->Next; q; q = q->Next){
			if ((p->ID) > (q->ID)){
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
	Node *newLink = head;
	system("cls");
	while (newLink->Next->Next){
		cout << "��Ʒ����" << newLink->Next->Next->Name << endl;
		cout << "��Ʒ��ţ�" << newLink->Next->Next->ID << endl;
		cout << "��Ʒ��棺" << newLink->Next->Next->Num << endl;
		cout << "��Ʒ���ۣ�" << newLink->Next->Next->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << newLink->Next->Next->SellOut << endl;
		newLink = newLink->Next;
	}
}
void Commodity::SortbyNum(){
	Node *p, *q, *r;
	r = new Node;
	p = new Node;
	q = new Node;
	for (p = head->Next; p->Next; p = p->Next){
		for (q = p->Next; q; q = q->Next){
			if ((p->Num) > (q->Num)){
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
	Node *newLink = head;
	system("cls");
	while (newLink->Next->Next){
		cout << "��Ʒ����" << newLink->Next->Next->Name << endl;
		cout << "��Ʒ��ţ�" << newLink->Next->Next->ID << endl;
		cout << "��Ʒ��棺" << newLink->Next->Next->Num << endl;
		cout << "��Ʒ���ۣ�" << newLink->Next->Next->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << newLink->Next->Next->SellOut << endl;
		newLink = newLink->Next;
	}
}
void Commodity::SortbyBuyIn(){
	Node *p, *q, *r;
	r = new Node;
	p = new Node;
	q = new Node;
	for (p = head->Next; p->Next; p = p->Next){
		for (q = p->Next; q; q = q->Next){
			if ((p->BuyIn) > (q->BuyIn)){
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
	Node *newLink = head;
	system("cls");
	while (newLink->Next->Next){
		cout << "��Ʒ����" << newLink->Next->Next->Name << endl;
		cout << "��Ʒ��ţ�" << newLink->Next->Next->ID << endl;
		cout << "��Ʒ��棺" << newLink->Next->Next->Num << endl;
		cout << "��Ʒ���ۣ�" << newLink->Next->Next->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << newLink->Next->Next->SellOut << endl;
		newLink = newLink->Next;
	}
}
void Commodity::SortbySellOut(){
	Node *p, *q, *r;
	r = new Node;
	p = new Node;
	q = new Node;
	for (p = head->Next; p->Next; p = p->Next){
		for (q = p->Next; q; q = q->Next){
			if ((p->SellOut) > (q->SellOut)){
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
	Node *newLink = head;
	system("cls");
	while (newLink->Next->Next){
		cout << "��Ʒ����" << newLink->Next->Next->Name << endl;
		cout << "��Ʒ��ţ�" << newLink->Next->Next->ID << endl;
		cout << "��Ʒ��棺" << newLink->Next->Next->Num << endl;
		cout << "��Ʒ���ۣ�" << newLink->Next->Next->BuyIn << endl;
		cout << "��Ʒ�ۼۣ�" << newLink->Next->Next->SellOut << endl;
		newLink = newLink->Next;
	}
}
Commodity::Commodity(){
	head=new Node;
	head->Name = "NULL";
	head->ID = 0;
	head->BuyIn = 0;
	head->Num = 0;
	head->SellOut = 0;
	head->Next = NULL;
}
Commodity::~Commodity(){
	Node *p;
	p = head;
	while (p){
		p = p->Next;
		delete head;
		head = p;
	}
	head = NULL;
}