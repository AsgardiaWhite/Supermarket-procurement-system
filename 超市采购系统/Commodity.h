#pragma once
#include <string>
#include <fstream>
using namespace std;
// 用户
struct User{
	char id[11];
	char pwd[20];
};
// 商品信息
struct Node{
	string Name;
	int Num;
	int ID;
	float SellOut;
	float BuyIn;
	Node* Next;
};
// 商品操作类
class Commodity{
	public:
		Node *head; //商品信息
		void AddNew();//新增商品模块
		void Buy();//购入商品模块
		void Sell();//卖出商品模块
		void Create_File();//创建用于保存账号和密码的文件
		void Register(); //注册模块
		bool Login();//登录模块
		void Save();//保存商品模块
		void SaveLog(int _ID, int flag);//保存记录模块
		void del_info();//下架商品模块
		void Add_up();//统计模块
		void Modify();//修改商品模块
		void GetInformathion();//查询模块
		void Sort();//排序模块
		void SortbyId();
		void SortbyNum();
		void SortbyBuyIn();
		void SortbySellOut();
		void ShowJournal();//显示记录
		Commodity();
		~Commodity();
};