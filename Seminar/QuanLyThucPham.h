#pragma once
#include "ThucPham.h"
#include "Menu.h"

void XuatMenu();
void SET_COLOR(int color);
void SetColor(int backgound_color, int text_color);

class QuanLyThucPham
{
protected:
	ThucPham tp[1000];
public:
	int getSoLuong()
	{
		return tp[0].soluong;
	}

	//Hàm nhằm mục đích hiển thị lại menu sau mỗi thao tác chương trình
	void rePrint()
	{
		system("cls");
		XuatMenu();
		if (tp[0].soluong != 0)
		{
			SetColor(0, 15);
			cout << "Danh sach hang hoa da nhap:\n\n";
			SetColor(0, 7);
			printTP();
			cout << endl;
		}
	}

	//Hàm nhập thủ công các loại hàng hóa theo ngày nhập kho
	void NhapHangHoa()
	{
		int sl = tp[0].soluong;
		cout << "\n-Nhap ngay nhap kho\n";
		DMY NNK;
		cin >> NNK;
		cout << "-Nhap so luong hang hoa: ";
		int n;
		cin >> n;
		rePrint();
		for (int i = sl, dem = 1; i < n + sl; i++)
		{
			cout << "¯¯Thong tin hang hoa nhap kho vao ngay " << NNK << ": " << endl;
			cout << "¯Nhap hang hoa thu " << dem++ << ": " << endl;
			tp[i].NhapHangHoa(NNK);
			rePrint();

		}
	}


	//Hiển thị hàng hóa theo ngày nhập kho
	void inHangHoaTheoNNK(DMY date)
	{
		bool flag = 0;	//Kiểm tra xem có hàng hóa nhập kho vào ngày này hay không
		for (int i = 0; i < tp[0].soluong; i++)
		{
			if (tp[i].getNNK() == date)
			{
				if (flag == 0)
				{
					cout << "Hang hoa nhap kho vao ngay " << date << ": " << endl;
					printTitle();
					flag = 1;
				}
				tp[i].InHangHoaDaNhap();
			}
		}
		if (flag == 0)
		{
			SET_COLOR(4);
			cout << "KHONG CO hang hoa nao nhap vao kho vao ngay " << date << "! " << endl;
			SET_COLOR(7);
		}
		else
			cout << "---------------------------------------------------------------------------------------------------------------------------------------";
		cout << endl;
	}

	//Hàm in các hàng hóa đã nhập theo ngày xuất kho
	void inHangHoatheoNXK(DMY date)
	{
		bool flag = 0;  //Kiểm tra xem có hàng hóa xuất kho vào ngày này hay không
		for (int i = 0; i < tp[0].soluong; i++)
		{
			if (tp[i].getNXK() == date)
			{
				if (flag == 0)
				{
					cout << "Hang hoa xuat kho vao ngay " << date << ": " << endl;
					printTitle();
					flag = 1;
				}
				tp[i].InHangHoaDaNhap();
			}
		}
		if (flag == 0)
		{
			SET_COLOR(4);
			cout << "KHONG CO hang hoa nao duoc xuat kho vao ngay " << date << "! " << endl;
			SET_COLOR(7);
		}
		else
			cout << "---------------------------------------------------------------------------------------------------------------------------------------";
		cout << endl;
	}

	//Hàm in ra những hàng hóa còn tồn kho
	void inHHConTonKho(DMY date)
	{
		bool flag = 0;  //Kiểm tra xem có hàng hóa tồn kho vào ngày này hay không
		for (int i = 0; i < tp[0].soluong; i++)
		{
			if (tp[i].getNNK() <= date && tp[i].getNXK() > date)
			{
				if (flag == 0)
				{
					cout << "Hang hoa con ton kho vao ngay " << date << ": " << endl;
					printTitle();
					flag = 1;
				}
				tp[i].InHangHoaDaNhap();
			}
		}
		if (flag == 0)
		{
			SET_COLOR(4);
			cout << "KHONG CO hang hoa nao ton kho vao ngay " << date << "!\n";
			SET_COLOR(7);
		}
		else
			cout << "---------------------------------------------------------------------------------------------------------------------------------------";
		cout << endl;
	}

	//Hàm kiểm tra 1 loại hàng hóa đã hết hạn hay chưa(Kiểm tra theo mã hàng hóa)
	int kiemTraHetHan(int temp, DMY today)
	{
		for (int i = 0; i < tp[0].soluong; i++)
		{
			if (tp[i].getMahang() == temp)
			{
				if (tp[i].getNHH() < today)
					return 1;
				return 0;
			}
		}
		return -1;
	}

	//Hàm tính tổng giá tiền các hàng hóa đã xuất bán trong ngày
	int tongTienTrongNgay(DMY d)
	{
		int sum = 0;
		for (int i = 0; i < tp[0].soluong; i++)
		{
			if (tp[i].getNXK() == d)
				sum += tp[i].getDonGia() * tp[i].getSL();
		}
		return sum;
	}

	//Hàm tính tổng giá tiền các hàng hóa đã xuất bán trong tháng
	int tongTienTrongThang(DMY d)
	{
		int sum = 0;
		for (int i = 0; i < tp[0].soluong; i++)
		{
			if (tp[i].getNXK().getThang() == d.getThang() && tp[i].getNXK().getNam() == d.getNam())
				sum += tp[i].getDonGia() * tp[i].getSL();
		}
		return sum;
	}

	//Hàm tính tổng giá tiền các hàng hóa đã xuất bán trong năm
	int tongTienTrongNam(DMY d)
	{
		int sum = 0;
		for (int i = 0; i < tp[0].soluong; i++)
		{
			if (tp[i].getNXK().getNam() == d.getNam())
				sum += tp[i].getDonGia() * tp[i].getSL();
		}
		return sum;
	}

	//Hàm in bảng tên các thuộc tính
	void printTitle()
	{
		SET_COLOR(11);
		cout << "---------------------------------------------------------------------------------------------------------------------------------------\n"
			<< "|Ma hang | Ten hang | So luong | Don gia | Loai hang | Ma kho luu hang | Ngay san xuat | Ngay het han | Ngay nhap kho | Ngay xuat kho |\n"
			<< "---------------------------------------------------------------------------------------------------------------------------------------\n";
		SET_COLOR(7);
	}


	//Hàm in 1 loại thực phẩm
	void printTP()
	{
		bool flag = 0;		//In bảng bảng thuộc tính một lần
		for (int i = 0; i < tp[0].soluong; i++)
		{
			if (flag == 0)
			{
				printTitle();
				flag = 1;
			}
			if (tp[i].soluong != 0)
				tp[i].InHangHoaDaNhap();
		}
		SET_COLOR(11);
		cout << "---------------------------------------------------------------------------------------------------------------------------------------\n";
		SET_COLOR(7);
	}


	//Hàm nhập hàng hóa từ file
	void NhapFile(int sl, string path)
	{
		int ngay, thang, nam;
		string tempString;
		int tempInt, n;
		DMY NNK;
		DMY tempNgay;
		cout << "Nhap tu file:\n";

		ifstream FILE(path);
		FILE >> ngay >> thang >> nam;
		NNK.SetDMY(ngay, thang, nam);
		cout << "-Da nhap ngay nhap kho: " << NNK << endl;

		FILE >> n;
		cout << "-Da nhap so luong: " << n << endl;

		for (int i = sl, dem = 1; i < n + sl; i++)
		{
			cout << "¯¯Thong tin hang hoa nhap kho vao ngay " << NNK << ": " << endl;
			cout << "¯Thong tin hang hoa thu " << dem++ << ": " << endl;
			tp[i].setNNK(NNK);
			while (getline(FILE, tempString) && tempString == "");
			tempInt = stoi(tempString);     //Chuyển string sang int
			tp[i].setMaHang(tempInt);
			cout << "-Da nhap ma hang: " << tempInt << endl;

			getline(FILE, tempString);
			tp[i].setTenHang(tempString);
			cout << "-Da nhap ten hang: " << tempString << endl;

			FILE >> tempInt;
			tp[i].setSL(tempInt);
			cout << "-Da nhap so luong: " << tempInt << endl;


			while (getline(FILE, tempString) && tempString == "");
			tempInt = stoi(tempString);		//Chuyển string sang int
			tp[i].setDonGia(tempInt);
			cout << "-Da nhap don gia: " << tempInt << endl;

			FILE >> tempInt;
			tp[i].setLoaiHang(tempInt);
			cout << "-Da nhap loai hang: ";
			if (tempInt == 0) cout << "Ngan han\n";
			else cout << "Dai han\n";

			while (getline(FILE, tempString) && tempString == "");
			int tempInt = stoi(tempString);
			tp[i].setMaKhoLuuHang(tempInt);
			cout << "-Da nhap ma kho luu hang: " << tempInt << endl;

			FILE >> ngay >> thang >> nam;
			tempNgay.SetDMY(ngay, thang, nam);
			tp[i].setNSX(tempNgay);
			cout << "-Da nhap ngay san xuat: " << tempNgay << endl;

			FILE >> ngay >> thang >> nam;
			tempNgay.SetDMY(ngay, thang, nam);
			tp[i].setNHH(tempNgay);
			cout << "-Da nhap ngay het han: " << tempNgay << endl;

			FILE >> ngay >> thang >> nam;
			tempNgay.SetDMY(ngay, thang, nam);
			tp[i].setNXK(tempNgay);
			cout << "-Da nhap ngay xuat kho: " << tempNgay << endl;
			tp[i].soluong++;

			cout << "\nKiem tra tinh chinh xac va nhan phim bat ky de nhap vao kho. ";
			system("pause");
			rePrint();
		}
		FILE.close();
	}
};

