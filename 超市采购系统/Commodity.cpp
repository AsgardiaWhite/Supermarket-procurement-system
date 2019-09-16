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
	// 遍历到链表的尾部
	while (p->Next){
		p = p->Next;
	}
	s->Next = NULL;
	p->Next = s;
	
	cout << "请输入商品编号（仅限数字）" << endl;
	cin >> s->ID;
	if (cin.fail()){
		cin.clear();
		system("cls");
		cout << "类型错误" << endl;
		cin.get();
		return;
	}
	cout << "请输入商品名称" << endl;
	cin >> s->Name;
	while (true){
		if (s->Name == ""){
			cout << "商品名称不能为空，请重新输入" << endl;
			cin >> s->Name;
		}else{
			break;
		}
	}
	cout << "请输入采购数量（仅限数字）" << endl;
	cin >> s->Num;
	while (true){
		if (cin.fail()){
			cin.clear();
			system("cls");
			cout << "类型错误" << endl;
			cin.get();
			return;
		}else if (!(s->Num > 0)){
			cout << "采购数量不能低于1，请重新输入" << endl;
			cin >> s->Num;
		}else{
			break;
		}
	}
	cout << "请输入采购价（仅限数字）" << endl;
	cin >> s->BuyIn;
	while (true){
		if (cin.fail()){
			cin.clear();
			system("cls");
			cout << "类型错误" << endl;
			cin.get();
			return;
		}else if (s->BuyIn < 0){
			cout << "采购价不能低于0元，请重新输入" << endl;
			cin >> s->BuyIn;
		}else{
			break;
		}
	}
	cout << "请输入售价（仅限数字）" << endl;
	cin >> s->SellOut;
	while (true){
		if (cin.fail()){
			cin.clear();
			system("cls");
			cout << "类型错误" << endl;
			cin.get();
			return;
		}else if (s->SellOut < 0){
			cout << "售价不能低于0元，请重新输入" << endl;
			cin >> s->SellOut;
		}else{
			break;
		}
	}
	system("cls");
	cout << "添加成功" << endl;
}
void Commodity::Buy(){
	string Name;
	cout << "请输入要买入的商品名称：\n";
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
		cout << "请输入买入数量" << endl;
		int number; 
		cin >> number;
		phead->Num = phead->Num + number;
		system("cls");
		cout << "添加成功!\n";
		SaveLog(phead->ID, 3);
	}
	else {
		system("cls");
		cout << "Sorry,未找到商品!\n";
	}
}
void Commodity::Sell(){
	string Name;
	cout << "请输入要卖出的商品名称：\n";
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
		cout << "请输入卖出数量" << endl;
		int number;
		cin >> number;
		if ((phead->Num - number) < 0){
			system("cls");
			cout << "库存量不足" << endl;
		}else{
			phead->Num = phead->Num - number;
			system("cls");
			cout << "卖出成功!\n";
			SaveLog(phead->ID, 2);
		}
	}
	else {
		system("cls");
		cout << "Sorry,未找到商品!\n";
	}
}
void Commodity::Create_File(){
	FILE *fp;
	if ((fp=fopen("user.txt","rb"))==NULL){ //如果此文件不存在
		if ((fp = fopen("user.txt", "wb+")) == NULL){ //如果文件创建失败
			system("cls");
			cout << "无法建立文件" << endl;
		}
	}
}
void Commodity::Register(){
	string pwd;
	cout << "请输入管理员密码" << endl;
	cin >> pwd;
	while (true){
		if (pwd !="password"){
			cout << "密码错误" << endl;
			break;
		}else{
			User loginUser, checkUser; //注册信息与检查信息
			FILE *fp;
			fp = fopen("user.txt", "r");

			fread(&checkUser, sizeof(struct User), 1, fp);//读入一个结构体字符块到b
			cout << "请输入账号" << endl;
			cin >> loginUser.id;

			while (true){
				if (strcmp(loginUser.id, checkUser.id)){ //如果两串不相等
					if (!feof(fp)){ //如果未到文件尾
						fread(&checkUser, sizeof(struct User), 1, fp);
					}
					else
						break;
				}else{
					cout << "此用户名已存在" << endl;
					fclose(fp);
					Register();
				}
			}
			cout << "请输入密码" << endl;
			cin >> loginUser.pwd;
			fp = fopen("user.txt", "a");
			fwrite(&loginUser, sizeof(struct User), 1, fp);
			system("cls");
			cout << "账号注册成功" << endl;
			fclose(fp);
			break;
		}
	}
}
bool Commodity::Login(){
	User loginUser, checkUser;
	FILE *fp; //建立一个文件操作指针
	fp = fopen("user.txt", "r");
	fread(&checkUser, sizeof(struct User), 1, fp); //在文件中读取信息
	cout << "请输入账号" << endl;
	cin >> loginUser.id;
	while (true){
		if (strcmp(loginUser.id, checkUser.id) == 0){ 
			//如果在文件中匹配到了对应的用户名，即登录成功
			break;
		}else{
			if (!feof(fp)){ //如果文件没有读完
				fread(&checkUser, sizeof(struct User), 1, fp);
			}else{
				cout << "此用户名不存在！" << endl;
				fclose(fp);
				Login(); //重新输入用户名
			}
		}
	}
	cout << "请输入密码" << endl;
	cin >> loginUser.pwd;
	if (strcmp(loginUser.pwd, checkUser.pwd) == 0){ 
		//如果密码匹配成功
		fclose(fp);
		system("cls");
		cout << "登录成功，欢迎使用!" << endl;
	}else{
		system("cls");
		cout << "密码不正确" << endl;
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
void Commodity::SaveLog(int _ID, int flag){ //flag 为标志位，2代表销售记录，3代表购入记录，_ID 为商品编号ID
	ofstream  file;
	Node * p = head;
	time_t t = time(0);
	char temp[50];
	strftime(temp, sizeof(temp), "%Y年%m月%d日%X%A", localtime(&t));
	if (flag == 2){
		file.open("journal.txt", ios::out | ios::ate | ios::app);
		if (!file.fail()){
			while (p->Next && p->Next->ID != _ID)
				p = p->Next;
			if (p->Next){
				file << "商品编号:" << p->Next->ID
					<< "\t商品名称:" << p->Next->Name
					<< "\t买入价:" << p->Next->BuyIn
					<< "\t售价:" << p->Next->SellOut
					<< "\t库存量:" << p->Next->Num
					<< "\t时间:" << temp
					<< "\t操作类型:" << "卖出"
					<< "\n";
			}
		}else{
			cout << "日志文件创建失败！" << endl;
		}
		file.close();
	}else if (flag == 3){
		file.open("journal.txt", ios::out | ios::ate | ios::app);
		if (!file.fail()){
			while (p->Next && p->Next->ID != _ID)
				p = p->Next;
			if (p->Next){
				file << "商品编号:" << p->Next->ID
					<< "\t商品名称:" << p->Next->Name
					<< "\t买入价:" << p->Next->BuyIn
					<< "\t售价:" << p->Next->SellOut
					<< "\t库存量:" << p->Next->Num
					<< "\t时间:" << temp
					<< "\t操作类型:" << "买入"
					<< "\n";
			}
		}else{
			cout << "日志文件创建失败！" << endl;
		}
		file.close();
	}
}
void Commodity::del_info(){
	Node * p = head, *q;
	int _ID;
	cout << "请输入想删除的编号" << endl;
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
		cout << "信息错误，删除失败！" << endl;
}
void Commodity::ShowJournal(){
	system("cls");
	ifstream infile("journal.txt", ios::in | ios::binary);//读一条信息
	char ch;
	while (infile.get(ch))  
		cout << ch;
	infile.close();
}
void Commodity::Add_up(){ 
	//统计超市商品的数量与价值
	system("cls");
	cout << "****商品统计****\n";
	int Amount = 0; 
	float Price = 0, Value = 0;
	string Name;
	cout << "\n请输入要统计的商品名称：\n";
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
		cout << "商品总数量是：\n";
		cout << Amount;
		cout << "\n商品总价值是：\n";
		cout << Value << "\n";
		cout << "全部售出可获得利润为：\n";
		cout << (Amount*Price) - Value << "\n";
	}else
		cout << "\nSorry,未找到该类商品!\n";
}
void Commodity::Modify(){ //修改商品信息
	int amount,ID;
	string Name;
	float SellOut,Price;
	system("cls");
	cout << "修改商品，请输入要查找的商品名称：\n";
	cout << "Name:"; 
	cin >> Name;//查找要修改的结点
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
		//若找到结点
		cout << "编号:" << phead->ID << " 名称:" << phead->Name << " 单价:" << phead->SellOut << " 库存量:" << phead->Num << endl;
		cout << "\n请选择要修改的信息（1—商品代码，2—商品名称，3—单价，4—该商品库存量）:\n";
		int opt; 
		cin >> opt;
		switch (opt){
			case 1:cout << "请输入新代码："; cin >> ID;
				Name = phead->Name; SellOut = phead->SellOut; amount = phead->Num; Price = phead->BuyIn; break;
			case 2:cout << "请输入新名称："; cin >> Name;
				ID = phead->ID; SellOut = phead->SellOut; amount = phead->Num; Price = phead->BuyIn; break;
			case 3:cout << "请输入新单价："; cin >> SellOut;
				ID = phead->ID; Name = phead->Name; amount = phead->Num; Price = phead->BuyIn; break;
			case 4:cout << "请输入新库存数据："; cin >> amount;
				ID = phead->ID; Name = phead->Name; SellOut = phead->SellOut; Price = phead->BuyIn; break;
			default:
				system("cls");
				cout << "无效编号！请重新输入" << endl;
				break;
		}
		//创建新的商品结点
		Node *newComdity;
		newComdity = new Node;
		newComdity->ID = ID;
		newComdity->Name = Name;
		newComdity->SellOut = SellOut;
		newComdity->BuyIn = Price;
		newComdity->Num = amount;
		//员工结点替换到链表
		newComdity->Next = phead->Next;
		if (phead == head) //若要替换的结点是第一个结点
			head = newComdity;
		else //若要替换的结点是后续结点
			temp->Next = newComdity;
		delete phead; //删除原来的商品结点
		cout << "修改成功!\n";
	}else //未找到结点
		cout << "Sorry,未找到!\n";
}
void Commodity::GetInformathion(){
	int _ID;
	cout << "请输入想查询的编号" << endl;
	cin >> _ID;
	if (cin.fail()){
		cin.clear();
		system("cls");
		cout << "类型错误" << endl;
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
		cout << "商品名：" << p->Name << endl;
		cout << "商品编号：" << p->ID << endl;
		cout << "商品库存：" << p->Num << endl;
		cout << "商品进价：" << p->BuyIn << endl;
		cout << "商品售价：" << p->SellOut << endl;
	}else if(p->Next == NULL){
		system("cls");
		cout << "输入有误或商品编号不存在,请重新查询！" << endl;
	}
}
void Commodity::Sort(){
	if (head->Next->Next){
		cout << "*********请选择查看方式**********" << endl;
		cout << "1————按商品ID排序" << endl;
		cout << "2————按商品库存排序" << endl;
		cout << "3————按商品购入价排序" << endl;
		cout << "4————按商品售出价排序" << endl;
		int opt, choice = 1;
		while (choice) {
			cout << "请输入你选择的排序方式:";
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
				cout << "输入有误，请重新输入！" << endl;
				continue;
			}
			cout << "是否继续选择排序方式？1————继续，0————结束" << endl;
			cin >> choice;
		}
	}else{
		system("cls");
		cout << "库存为0，请录入商品！" << endl;
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
		cout << "商品名：" << newLink->Next->Next->Name << endl;
		cout << "商品编号：" << newLink->Next->Next->ID << endl;
		cout << "商品库存：" << newLink->Next->Next->Num << endl;
		cout << "商品进价：" << newLink->Next->Next->BuyIn << endl;
		cout << "商品售价：" << newLink->Next->Next->SellOut << endl;
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
		cout << "商品名：" << newLink->Next->Next->Name << endl;
		cout << "商品编号：" << newLink->Next->Next->ID << endl;
		cout << "商品库存：" << newLink->Next->Next->Num << endl;
		cout << "商品进价：" << newLink->Next->Next->BuyIn << endl;
		cout << "商品售价：" << newLink->Next->Next->SellOut << endl;
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
		cout << "商品名：" << newLink->Next->Next->Name << endl;
		cout << "商品编号：" << newLink->Next->Next->ID << endl;
		cout << "商品库存：" << newLink->Next->Next->Num << endl;
		cout << "商品进价：" << newLink->Next->Next->BuyIn << endl;
		cout << "商品售价：" << newLink->Next->Next->SellOut << endl;
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
		cout << "商品名：" << newLink->Next->Next->Name << endl;
		cout << "商品编号：" << newLink->Next->Next->ID << endl;
		cout << "商品库存：" << newLink->Next->Next->Num << endl;
		cout << "商品进价：" << newLink->Next->Next->BuyIn << endl;
		cout << "商品售价：" << newLink->Next->Next->SellOut << endl;
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