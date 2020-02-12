#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include "account.h"

using namespace std;

void CreateAccount();
void SearchAndPrintAccount(int);
void SearchAndModifyAccount(int);
void DeleteAccount(int);
void PrintAllAccountInFormat();
void DepositOrWithdraw(int, int);
bool checkacc(int account_number);

// Tao moi tai khoan:
// Nhap so tai khoan, ten chu tai khoan, loai tai khoan
// va so du ban dau tu ban phim
void Account::CreateAccount()
{
	 
	cout << "Nhap so tai khoan: ";
	cin >> account_number_;
	cin.ignore();
	cout << "Nhap ten chu tai khoan: ";
	cin.getline(name_, 100);
	cout << "Nhap loai tai khoan : ";
	cin >> type_;
	cout << "Nhap so du ban dau : ";
	cin >> balance_;

}

// Sua doi tai khoan:
// Nhap moi ten chu tai khoan, loai tai khoan va so du
void Account::Modify()
{
	cout << "\nNhap thong tin de thay doi:";
	cout << "\nTen chu tai khoan: ";
	 
	cin.ignore();
	cin.getline(name_, 100);
	cout << "\nLoai tai khoan: ";
	cin >> type_;
	cout << "\nSo du: ";
	cin >> balance_;

}

// Nap them tien vao tai khoan
void Account::Deposit(int amount)
{
	 
	balance_ += amount;

}

// Rut tien tu tai khoan
void Account::Withdraw(int amount)
{
	 
	balance_ -= amount;
}

// Hien thi thong tin tai khoan (khong in theo dinh dang)
// Thong tin hien thi tren 4 dong:
// Dong 1: So tai khoan
// Dong 2: Ten chu tai khoan
// Dong 3: Loai tai khoan
// Dong 4: So du tai khoan
void Account::PrintAccount() const
{
	cout << "\nSo tai khoan: " << account_number_;
	cout << "\nTen chu tai khoan: ";
	 
	cout << name_;
	cout << "\nLoai Tai Khoan: " << type_;
	cout << "\nSo du: " << balance_;
}

// In ra thong tin tai khoan tren mot dong theo dinh dang
// So tai khoan: do rong 11 ky tu, can le trai
// Ten chu tai khoan: do rong 19 ky tu, can le trai
// Loai tai khoan: do rong 8 ky tu, can le trai
// So du tai khoan: do rong 14 ky tu, can le trai
void Account::PrintAccountInFormat() const
{
	 
	cout << setw(11) << left << account_number_ <<
		setw(19) << left << name_ <<
		setw(8) << left << type_ <<
		setw(14) << left << balance_ << endl;
	
}

// Lay ra so tai khoan
int Account::GetAccountNumber() const
{
	 
	return account_number_;

}

// Lay ra so du
int Account::GetBalance() const
{
	 
	return balance_;

}

// Lay ra kieu tai khoan
char Account::GetType() const
{
	 
	return type_;

}

// Lay ra ten chu tai khoan
char * Account::GetName() const
{
	return (char *) name_;
}

int main()
{
	char menu_option;
	int account_number; // Nhap tu ban phim
	do
	{
		system("cls");
		cout << "\n\n\n\tMenu";
		cout << "\n\n\t1. Tao tai khoan";
		cout << "\n\n\t2. Nop tien";
		cout << "\n\n\t3. Rut tien";
		cout << "\n\n\t4. Tra cuu tai khoan";
		cout << "\n\n\t5. Danh sach tai khoan";
		cout << "\n\n\t6. Xoa tai khoan";
		cout << "\n\n\t7. Sua tai khoan";
		cout << "\n\n\t8. Thoat";
		cout << "\n\n\tChon menu (so tu 1 den 8) ";
		cin >> menu_option;
		system("cls");
		switch (menu_option)
		{
		case '1':
			 
			CreateAccount();

			break;
		case '2':
			cout << "\n\n\tChon so tai khoan: ";
			 
			cin >> account_number;
			DepositOrWithdraw(account_number, 1);

			break;
		case '3':
			cout << "\n\n\tChon tai khoan: ";
			 
			cin >> account_number;
			DepositOrWithdraw(account_number, 2);

			break;
		case '4':
			cout << "\n\n\tNhap so tai khoan: ";
			 
			cin >> account_number;
			SearchAndPrintAccount(account_number);

			break;
		case '5':
			 
			PrintAllAccountInFormat();

			break;
		case '6':
			 
			cout << "\n\n\tNhap so tai khoan: ";
			cin >> account_number;
			DeleteAccount(account_number);

			break;
		case '7':
			cout << "\n\n\tNhap so tai khoan: ";
			 
			cin >> account_number;
			SearchAndModifyAccount(account_number);

			break;
		case '8':
			 
			cout << "\n\n\t Cam on ban da su dung dich vu, hen gap lai";

			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (menu_option != '8');
	return 0;
}

// Tao mot tai khoan bang cach nhap tu ban phim
// roi luu tai khoan vua tao vao file "account.dat"
void CreateAccount()
{
	Account account;
	ofstream out_file;
	 
	account.CreateAccount();
	int inTemp = account.GetAccountNumber();
	bool blTemp = checkacc(inTemp);
	if (!blTemp)
	{
		cout << endl;
		cout << endl;
		cout << "Tai khoan da duoc tao thanh cong";
		out_file.open("account.dat", ios::binary | ios::out | ios::app);
		if (out_file.is_open())
		{
			out_file.write(reinterpret_cast<char *>(&account), sizeof(Account));
		}

		out_file.close();
	}
	else
	{
		cout << endl;
		cout << endl;
		cout << "Tai khoan da ton tai";
	}
}

// Tim va in tai khoan co so tai khoan la account_number (không in theo dinh dang)
// Tim tai khoan trong file "account.dat"
void SearchAndPrintAccount(int account_number)
{
	Account account;
	bool found = false;
	ifstream in_file;

	in_file.open("account.dat", ios::binary);
	if (!in_file)
	{
		 
		cout << "Khong mo duoc file, hay an phim enter de quay lai menu chinh";


		return;
	}
	cout << "\nKet qua tim kiem:\n";

	while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
	{
		 
		if (account.GetAccountNumber() == account_number)
		{
			account.PrintAccount();
			found = true;
		}

	}

	in_file.close();
	if (found == false)
		cout << "\n\nKhong tim thay tai khoan";
}

// Tim tai khoan co so tai khoan la account_number (khong in theo dinh dang)
// trong file "account.dat"
// Sau do cho phep nguoi dung sua doi tai khoan nay
// bang cach thay doi ten chu tai khoan, loai tai khoan va so du
// Cuoi cung, luu thay doi vao file "account.dat"
void SearchAndModifyAccount(int account_number)
{
	bool found = false;
	Account account;
	fstream file;

	file.open("account.dat", ios::binary | ios::in | ios::out);
	if (!file)
	{
		 
		cout << "Khong mo duoc file, hay an phim enter de quay lai menu chinh";

		return;
	}

	while (!file.eof() && found == false)
	{
		 
		file.read(reinterpret_cast<char *> (&account), sizeof(Account));
		if (account.GetAccountNumber()==account_number)
		{
			account.Modify();
			int size = sizeof(account);
			file.seekp(-size, ios::cur);
			file.write(reinterpret_cast<char *>(&account), sizeof(Account));
			found = true;
			cout << "\n\n\t Tai khoan da sua thanh cong";
		}

	}

	file.close();
	if (found == false)
		cout << "\n\nKhong tim thay tai khoan";
}

// Tim tai khoan co so tai khoan la account_number
// trong file "account.dat"
// Sau do xoa tai khoan nay trong file "account.dat"
void DeleteAccount(int account_number)
{
	Account account;
	ifstream in_file;
	ofstream out_file;
	in_file.open("account.dat", ios::binary);
	
	if (!in_file)
	{
		 
		cout << "Khong mo duoc file, hay an phim enter de quay lai menu chinh";

		return;
	}
	//Phan Nang Cao
	//Kiem tra tai khoan co ton tai khong truoc khi xoa
	bool blTemp = checkacc(account_number);
	if (blTemp)
	{
		// Luu tat ca cac tai khoan trong file "account.dat", tru tai khoan muon xoa vao file "temp.dat"
		out_file.open("temp.dat", ios::binary);
		in_file.seekg(0, ios::beg);
		while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
		{
			 
			if (account.GetAccountNumber() != account_number)
			{
				out_file.write(reinterpret_cast<char *> (&account), sizeof(Account));
			}

		}

		// Dong cac file da mo, xoa file "account.dat", doi ten file "temp.dat" thanh "account.dat"
		 
		in_file.close();
		out_file.close();
		remove("account.dat");
		rename("temp.dat", "account.dat");

		cout << "\n\n\tTai khoan da xoa thanh cong";
	}
	else
		cout << "\n\n\tTai khoan khong ton tai";
}

// In ra tat ca cac tai khoan luu trong file "account.dat" theo dinh dang
// Moi tai khoan in tren mot dong
void PrintAllAccountInFormat()
{
	Account account;
	ifstream in_file;
	in_file.open("account.dat", ios::binary);
	if (!in_file)
	{
		 
		cout << "Khong mo duoc file, hay an phim enter de quay lai menu chinh";

		return;
	}
	cout << "\n\n\t\tDanh sach tai khoan:\n\n";
	cout << "====================================================\n";
	cout << "So TK      Chu TK             Loai    So du\n";
	cout << "====================================================\n";
	while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
	{
		 
		account.PrintAccountInFormat();

	}
	in_file.close();
}

// Tim tai khoan co so tai khoan la account_number trong file "account.dat"
// Roi nop hoac rut tien vao tai khoan tim duoc
// option = 1: nop tien
// option = 2: rut tien
// So tien nop hoac rut duoc nhap tu ban phim
// Sau cung, luu tai khoan vua sua doi vao file "account.dat"
void DepositOrWithdraw(int account_number, int option)
{
	int amount; // So tien muon rut/nop duoc nhap tu ban phim
	bool found = false;
	Account account;
	fstream file;

	file.open("account.dat", ios::binary | ios::in | ios::out);
	if (!file)
	{
		 
		cout << "Khong mo duoc file, hay an phim enter de quay lai menu chinh";

		return;
	}

	while (!file.eof() && found == false)
	{
		file.read(reinterpret_cast<char *> (&account), sizeof(Account));
		if (account.GetAccountNumber() == account_number)
		{
			account.PrintAccount();
			if (option == 1)
			{
				cout << "\n\n\tNop tien ";
				cout << "\n\nNhap so tien nop: ";
				 
				cin >> amount;
				account.Deposit(amount);

			}
			else if (option == 2)
			{
				if (account.GetBalance() >= 50000)
				{
					cout << "\n\n\tRut tien ";
					cout << "\n\nNhap so tien rut: ";
					 
					cin >> amount;
					account.Withdraw(amount);
				}
				else
				{
					cout << "\n\n\t So du nho hon 50.000 khong duoc phep rut tien";
					found = true;
					break;
				}

			}

			 
			int size =  sizeof(account);
			file.seekp(-size , ios::cur);
			file.write(reinterpret_cast<char *>(&account), sizeof(Account));

			cout << "\n\n\t Giao dich thuc hien thanh cong";
			found = true;
		}
	}

	file.close();
	if (found == false)
		cout << "\n\nKhong tim thay tai khoan";
}

//Phan nang cao
//Kiem tra tai khoan ton tai chua
bool checkacc(int account_number)
{
	Account account;
	ifstream in_file;
	in_file.open("account.dat", ios::binary);
	while (in_file.read(reinterpret_cast<char *> (&account), sizeof(Account)))
	{
		if (account.GetAccountNumber() == account_number)
		{
			return true;
		}
	}
	in_file.close();
	return false;
}