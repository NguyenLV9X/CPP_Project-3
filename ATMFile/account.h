#pragma once
class Account
{
private:
	int account_number_; // So tai khoan
	char name_[100]; // Ho ten chu tai khoan
	int balance_; // So du tai khoan
	char type_; // Kieu tai khoan. N: binh thuong. V: tai khoan Vip
public:
	void CreateAccount();
	void Modify();
	void Deposit(int);
	void Withdraw(int);
	void PrintAccount() const;
	void PrintAccountInFormat() const;
	int GetAccountNumber() const;
	int GetBalance() const;
	char GetType() const;
	char * GetName() const;
};
