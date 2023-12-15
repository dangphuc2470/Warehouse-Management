#include "ThucPham.h"
#include "Menu.h"

int main()
{
	QuanLyThucPham a;
	int control = 0;
	int pathSize = 3; //Số lượng file cần nhập
	string* path = new string[pathSize]; //Mảng string chứa 3 tên file cần nhập
	path[0] = "20_05_2022.txt";
	path[1] = "26_05_2022.txt";
	path[2] = "01_06_2022.txt";
	do
	{
		XuLy(a,path, pathSize);
	} while (control != 0);
	cout << "Thanks for using! ";
	delete[] path;
	system("pause");
	return 0;
}


