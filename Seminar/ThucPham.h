#pragma once
#pragma warning(disable : 4996)
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <ctime>
#include <Windows.h>
#include "Date.h"
using namespace std;


//Hàm đổi màu chữ
void SET_COLOR(int color);


class ThucPham
{
private:
	int maHang;			//Định dạng là số nguyên gồm 4 chữ số (0000)
	string tenHang;		//Chuỗi kí tự lưu tên hàng
	int donGia;			//Đơn vị VND
	bool loaiHang;		//0 - Loại hàng ngắn hạn | 1 - Loại hàng dài hạn
	int maKhoLuuHang;	//Định dạng gồm số có 2 chữ số (00)
	DMY ngaySanXuat;	//Bao gồm ngày, tháng, năm
	DMY ngayHetHan;		//Bao gồm ngày, tháng, năm
	DMY ngayNhapKho;	//Bao gồm ngày, tháng, năm
	DMY ngayXuatKho;	//Bao gồm ngày, tháng, năm
	int SL;				//Số lượng hàng hóa thuộc mỗi loại hàng

public:
	static int soluong;//Tổng số loại hàng hóa đã nhập


	ThucPham() { };

	ThucPham(int maHang, string tenhang, int donGia, bool loaiHang, int maKhoLuuHang,
		DMY ngaySanXuat, DMY ngayHetHan, DMY ngayNhapKho, DMY ngayXuatKho)
	{
		this->maHang = maHang;
		this->tenHang = tenhang;
		this->donGia = donGia;
		this->loaiHang = loaiHang;
		this->maKhoLuuHang = maKhoLuuHang;
		this->ngaySanXuat = ngaySanXuat;
		this->ngayHetHan = ngayHetHan;
		this->ngayNhapKho = ngayNhapKho;
		this->ngayXuatKho = ngayXuatKho;
	}

	void setMaHang(int maHang = 0000)
	{
		this->maHang = maHang;
	}

	int getMahang()
	{
		return maHang;
	}

	void setTenHang(string tenhang)
	{
		this->tenHang = tenhang;
	}

	string getTenHang()
	{
		return tenHang;
	}

	void setDonGia(int dongia = 0)
	{
		this->donGia = dongia;
	}

	int getDonGia()
	{
		return donGia;
	}

	void setLoaiHang(bool loaiHang)
	{
		this->loaiHang = loaiHang;
	}

	char getLoaiHang()
	{
		return loaiHang;
	}

	void setMaKhoLuuHang(char maKhoLuuHang)
	{
		this->maKhoLuuHang = maKhoLuuHang;
	}

	int getMaKhoLuuHang()
	{
		return maKhoLuuHang;
	}

	void setNSX()
	{
		this->ngaySanXuat.SetDMY(00, 00, 0000);
	}

	void setNSX(DMY d)
	{
		this->ngaySanXuat = d;
	}

	DMY getNSX()
	{
		return ngaySanXuat;
	}

	void setNHH()
	{
		this->ngayHetHan.SetDMY(00, 00, 0000);
	}

	void setNHH(DMY d)
	{
		this->ngayHetHan = d;
	}

	DMY getNHH()
	{
		return ngayHetHan;
	}

	void setNNK()
	{
		this->ngayNhapKho.SetDMY(00, 00, 0000);
	}

	void setNNK(DMY d)
	{
		this->ngayNhapKho = d;
	}

	DMY getNNK()
	{
		return ngayNhapKho;
	}

	void setNXK()
	{
		this->ngayXuatKho.SetDMY(00, 00, 0000);
	}

	void setNXK(DMY d)
	{
		this->ngayXuatKho = d;
	}

	DMY getNXK()
	{
		return ngayXuatKho;
	}

	void setSL(int SL)
	{
		this->SL = SL;
	}

	int getSL()
	{
		return SL;
	}

	//Hàm nhập thủ công một hàng hóa
	void NhapHangHoa(DMY temp)
	{
		ngayNhapKho = temp;
		cout << "-Nhap ma hang hoa: ";
		cin >> maHang;
		cin.ignore();
		cout << "-Nhap ten hang hoa: ";
		getline(cin, tenHang);

		cout << "-Nhap so luong: ";
		cin >> SL;

		cout << "-Nhap don gia: ";
		cin >> donGia;
		if (donGia < 0)
			setDonGia();

		cout << "-Nhap loai hang (0: Ngan han, 1: Dai han): ";
		cin >> loaiHang;
		cout << "-Nhap ma kho luu hang hoa: ";
		cin >> maKhoLuuHang;
		cout << "-Nhap ngay san xuat:\n";
		while (cin >> ngaySanXuat && ngaySanXuat > ngayNhapKho)
		{
			cout << "Ngay san xuat khong duoc lon hon ngay nhap kho, vui long nhap lai:\n";
		}
		cout << "-Nhap ngay het han:\n";
		while (cin >> ngayHetHan && ngayHetHan < ngaySanXuat)
		{
			cout << "Ngay het han khong duoc nho hon ngay san xuat, vui long nhap lai:\n";
		}
		cout << "-Nhap ngay xuat kho:\n";
		while (cin >> ngayXuatKho && ngayXuatKho < ngayNhapKho)
		{
			cout << "Ngay xuat kho khong duoc nho hon ngay nhap kho, vui long nhap lai:\n";
		}
		soluong++;
	}

	//Hàm in 1 loại hàng hóa đã nhập kho
	void InHangHoaDaNhap()
	{
		SET_COLOR(11);
		cout << "|";
		SET_COLOR(7);
		cout << left << setw(10) << maHang << left << setw(11) << tenHang << left << setw(11) << SL << left << setw(10) << donGia << left << setw(12) << loaiHang << left << setw(11)
			<< maKhoLuuHang<< "\t " << ngaySanXuat << "\t " << ngayHetHan << "\t" << ngayNhapKho << "\t" << ngayXuatKho;
		SET_COLOR(11);
		cout << "    |" << endl;
		SET_COLOR(7);
	}

};

int ThucPham::soluong = 0;

