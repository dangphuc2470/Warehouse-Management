#pragma once
#include <iostream>
#include <ostream>

using namespace std;


class DMY
{
private:
	int ngay;
	int thang;
	int nam;
public:
	//Gán ngày
	void SetDMY(int d, int m, int y)
	{
		ngay = d;
		thang = m;
		nam = y;
	}

	//Ki?m tra ngày h?p l?
	bool isValid()
	{
		int maxDay;
		switch (thang)
		{
		case 1:
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			maxDay = 31;
			break;
		case 2:
			if (nam % 4 == 0)
				maxDay = 29;
			else maxDay = 28;
			break;
		default:
			maxDay = 30;
			break;
		}
		if (ngay > maxDay)
			return 0;
		if (thang > 12 || thang < 1)
			return 0;
		return 1;
	}

	//Nh?p ngày
	friend istream& operator>>(istream& is, DMY& d)
	{
		do {
			cout << "   Ngay: ";
			is >> d.ngay;
			cout << "   Thang: ";
			is >> d.thang;
			cout << "   Nam: ";
			is >> d.nam;
			if (d.isValid() == 0)
			{
				cout << "Ngay thang khong hop le, vui long nhap lai!\n";
			}
		} while (d.isValid() == 0);
		return is;
	}

	//Xu?t ngày
	friend ostream& operator<<(ostream& os, DMY& d)
	{
		if (d.ngay < 10)
			os << "0";
		os << d.ngay << "/";
		if (d.thang < 10)
			os << "0";
		os << d.thang << "/" << d.nam;
		return os;
	}

	//L?y ngày
	int getNgay()
	{
		return ngay;
	}

	//L?y tháng
	int getThang()
	{
		return thang;
	}

	//L?y n?m
	int getNam()
	{
		return nam;
	}

	//So sánh ngày
	bool operator==(DMY dmy)
	{
		if (this->ngay == dmy.ngay && this->thang == dmy.thang && this->nam == dmy.nam)
			return 1;
		return 0;
	}

	//So sánh ngày
	bool operator>(DMY dmy)
	{
		if (this->nam > dmy.nam)
			return 1;
		else if (this->nam < dmy.nam)
			return 0;

		if (this->thang > dmy.thang)
			return 1;
		else if (this->thang < dmy.thang)
			return 0;

		if (this->ngay > dmy.ngay)
			return 1;
		return 0;
	}

	//So sánh ngày
	bool operator<(DMY dmy)
	{
		if (this->nam < dmy.nam)
			return 1;
		else if (this->nam > dmy.nam)
			return 0;

		if (this->thang < dmy.thang)
			return 1;
		else if (this->thang > dmy.thang)
			return 0;

		if (this->ngay < dmy.ngay)
			return 1;
		return 0;
	}

	//So sánh ngày
	bool operator<=(DMY dmy)
	{
		return !(*this > dmy);
	}

	//So sánh ngày
	bool operator>=(DMY dmy)
	{
		return !(*this < dmy);
	}
};