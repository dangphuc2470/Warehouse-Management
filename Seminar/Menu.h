#pragma once
#include "ThucPham.h"
#include "QuanLyThucPham.h"
#include "Date.h"
#include <ctime>


//Lấy ngày tháng năm hiện tại
time_t now = time(0);
tm* ltm = localtime(&now);
/*=========================*/

//Xuất menu
void XuatMenu()
{
	time_t now = time(0);
	tm* ltm = localtime(&now);
	DMY currentTime;
	currentTime.SetDMY(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
	cout << "Hom nay la ngay: " << currentTime << "\n\n"
		<< "===============================================================\n"
		<< "||                      == Main Menu ==                      ||\n"
		<< "||      1. Nhap hang hoa thu cong                            ||\n"
		<< "||      2. Nhap hang hoa tu file                             ||\n"
		<< "||      3. Hien thi hang hoa da nhap vao kho                 ||\n"
		<< "||      4. Hien thi hang hoa xuat kho                        ||\n"
		<< "||      5. Hien thi hang hoa con ton kho                     ||\n"
		<< "||      6. Kiem tra han su dung cua hang hoa                 ||\n"
		<< "||      7. Tinh tong gia tien cac hang hoa da xuat ban       ||\n"
		<< "||      0. Ket thuc chuong trinh                             ||\n"
		<< "||                                                           ||\n"
		<< "||                         Nhap lua chon trong khoang [0-7]  ||\n"
		<< "===============================================================\n\n";
}

//Hàm thay đổi màu chữ
void SET_COLOR(int color)
{
	WORD wColor;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
	{
		wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
		SetConsoleTextAttribute(hStdOut, wColor);
	}
}


//Hàm thay đổi màu chữ và màu nền
void SetColor(int backgound_color, int text_color)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	int color_code = backgound_color * 16 + text_color;
	SetConsoleTextAttribute(hStdout, color_code);
}


//Xử lý tác vụ
void XuLy(QuanLyThucPham hh, string path[], int pathSize)
{
	int control;
	hh.rePrint();
	do
	{
		do
		{
			cout << "\nNhap lua chon cua ban trong khoang [0-7]: ";
			cin >> control;
			if (control < 0 || control > 7)
			{
				SET_COLOR(4);
				cout << "Khong hop le, vui long nhap lai!!";
				SET_COLOR(7);
			}
		} while (control < 0 || control > 7);
		hh.rePrint();
		switch (control)
		{
		case 1:
			hh.NhapHangHoa();
			break;


		case 2:
			//Mỗi file chỉ chứa các thực phẩm được nhập kho trong cùng một ngày,
			//các thông tin thuộc tính được lưu trong file với định dạng mỗi thuộc tính nằm trên 1 dòng
			//(kể cả ngày tháng năm, ngày trên 1 dòng, tương tự với tháng và năm).
		{
			for (int j = 0; j < pathSize; j++)
			{
				hh.NhapFile(hh.getSoLuong(), path[j]);
			}
			break;
		}
		case 3:
			DMY date;
			cout << "Nhap ngay nhap kho cua hang hoa can hien thi:\n";
			cin >> date;
			hh.inHangHoaTheoNNK(date);
			break;
		case 4:
			cout << "Nhap ngay xuat kho cua hang hoa can hien thi:\n";
			cin >> date;
			hh.inHangHoatheoNXK(date);
			break;
		case 5:
			cout << "Nhap ngay can kiem tra hang ton kho:\n";
			cin >> date;
			hh.inHHConTonKho(date);
			break;
		case 6:
			cout << "Nhap ma hang hoa cua hang hoa can kiem tra han su dung: ";
			int temp;
			cin >> temp;
			DMY today;
			today.SetDMY(ltm->tm_mday, 1 + ltm->tm_mon, 1900 + ltm->tm_year);
			if (hh.kiemTraHetHan(temp, today) == 1)
			{
				SET_COLOR(4);
				cout << "Hang hoa da het han su dung!\n";
				SET_COLOR(7);
			}
			else if (hh.kiemTraHetHan(temp, today) == 0)
			{
				SET_COLOR(2);
				cout << "Hang hoa van con han su dung!\n";
				SET_COLOR(7);
			}
			else
			{
				SET_COLOR(4);
				cout << "Khong tim thay ma hang hoa!\n";
				SET_COLOR(7);
			}
			break;
		case 7:
			cout << "Tinh tong gia tien trong: \n1.Ngay\n2.Thang\n3.Nam\nNhap lua chon: ";
			int l;
			cin >> l;
			switch (l)
			{
			case 1:
				cin >> date;
				cout << "Tong gia hang hoa da ban trong ngay " << date << " la: " << hh.tongTienTrongNgay(date);
				break;
			case 2:
				int t, n;
				cout << "    Thang: ";
				cin >> t;
				cout << "    Nam: ";
				cin >> n;
				date.SetDMY(1, t, n);
				cout << "Tong gia hang hoa da ban trong thang " << t << "/" << n << " la: " << hh.tongTienTrongThang(date);
				break;
			case 3:
				int temp;
				cout << "    Nam: ";
				cin >> temp;
				date.SetDMY(1, 1, temp);
				cout << "Tong gia hang hoa da ban trong nam " << temp << " la: " << hh.tongTienTrongNam(date);
				break;
			default:
				cout << "Khong hop le!";
				break;
			}
			break;
		default:
			break;
		}

	} while (control != 0);
}

