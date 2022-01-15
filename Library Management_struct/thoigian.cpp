#include <string.h>
#include <iostream>
#include "thoigian.h"

using namespace std;

// Chuc nang: Chuyen cac du lieu ve ngay, thang, nam duoc nhap tu ban phim thanh chuoi ky tu dd/mm/yyyy
// Tham so truyen vao:	
//							char dateCh[11]: chuoi ki tu theo dang dd/mm/yyyy	
//							DATE date: ngay thang nam
// Gia tri tra ve:
//							char dateCh[11]
void ChuyenThanhChuoiKyTuNgay(char dateCh[11], DATE date) {
	char dStr[3] = "0", mStr[3] = "0", yStr[5]="0";
	int x;
	dateCh[0] = 0;

	if (date.d - 10 < 0) {	// ngay co 1 chu so
		dStr[1] = '0' + date.d;
	}
	else {				// ngay co 2 chu so
		x = date.d / 10;
		dStr[0] = '0' + x;
		x = date.d % 10;
		dStr[1] = '0' + x;
	}
	strcat_s(dateCh, 11, dStr);
	strcat_s(dateCh, 11, "/");
	if (date.m - 10 < 0) {	// thang co 1 chu so
		mStr[1] = '0' + date.m;
	}
	else {				// thang co 2 chu so
		x = date.m / 10;
		mStr[0] = '0' + x;
		x = date.m % 10;
		mStr[1] = '0' + x;
	}
	strcat_s(dateCh, 11, mStr);
	strcat_s(dateCh, 11, "/");

	int i = 3;
	while (date.y > 0) {
		x = date.y % 10;
		yStr[i] = '0' + x;
		date.y = date.y / 10;
		i--;
	}
	strcat_s(dateCh, 11, yStr);
}


// Chuc nang: Kiem tra mot nam co phai la nam nhuan hay khong
// Tham so truyen vao:
//						DATE d: ngay thang nam
// Gia tri tra ve:
//						1 (true)		neu la nam nhuan
//						0 (false)		neu khong la nam nhuan
bool KiemTraNamNhuan(DATE d) {
	if ((d.y % 4 == 0 && d.y % 100 != 0) || (d.y % 100 == 0 && d.y % 400 == 0)) {
		return 1;
	}
	else {
		return 0;
	}
}

// Chuc nang: Xac dinh so ngay trong mot thang
// Tham so truyen vao:
//						DATE d: ngay thang nam
// Gia tri tra ve:
//						29		neu la thang 2 cua nam nhuan
//						28		neu la thang 2 cua nam khong nhuan
//						31		neu la thang 1, 3, 5, 7, 8, 10, 12
//						30		neu la thang 4, 6, 9, 11
int SoNgayTrongThang(DATE d) {
	switch (d.m) {
	case 2:
		if (KiemTraNamNhuan(d)) {
			return 29;
		}
		else {
			return 28;
		}
	case 1: case 3: case 5: case 7: case 8: case 10: case 12:
		return 31;
	case 4: case 6: case 9: case 11:
		return 30;
	}
	return 0;
}

// Chuc nang: Nhap ngay (neu ngay khong hop le thi nhap lai)
// Tham so truyen vao:
//							DATE& d: ngay thang nam
// Gia tri tra ve: (khong co)
void NhapNgay(DATE& d) {
	int count = 0;
	do {
		if (count > 0) {
			cout << "Ngay khong hop le. Moi ban nhap lai.\n";
		}
		cout << "Ngay: ";
		cin >> d.d;
		cout << "Thang: ";
		cin >> d.m;
		cout << "Nam: ";
		cin >> d.y;
		count++;
	} while (!(d.m >= 1 && d.m <= 12 && d.y >= 1 && d.y <= 1000000000 && d.d >= 1 && d.d <= SoNgayTrongThang(d)));
}

// Chuc nang: Cong them n ngay
// Tham so truyen vao:
//						DATE& d: ngay thang nam
//						int n: so ngay cong them
// Gia tri tra ve: (khong co)
void CongNNgay(DATE& d, int n) {
	d.d = d.d + n;
	while (d.d > SoNgayTrongThang(d)) {
		d.d = d.d - SoNgayTrongThang(d);
		d.m = d.m + 1;
		if (d.m > 12) {
			d.m = d.m - 12;
			d.y = d.y + 1;
		}
	}
}

// Chuc nang: So sanh ngay thu nhat co nho hon ngay thu hai hay khong
// Tham so truyen vao:
//						DATE d1: ngay thang nam thu nhat
//						DATE d2: ngay thang nam thu hai
// Gia tri tra ve:
//						1 (true)	neu ngay thu nhat nho hon ngay thu hai
//						0 (false)	neu ngay thu nhat khong nho hon ngay thu hai
bool SoSanhNgayNhoHon(DATE d1, DATE d2) {
	if (d1.y < d2.y) {
		return 1;
	}
	else if (d1.y == d2.y) {
		if (d1.m < d2.m) {
			return 1;
		}
		else if (d1.m == d2.m) {
			if (d1.d < d2.d) {
				return 1;
			}
		}
	}
	return 0;
}

// Chuc nang: Tim khoang cach giua ngay thu nhat và ngay thu hai (voi dieu kien: ngay thu nhat < ngay thu hai)
// Tham so truyen vao:
//						DATE d1: ngay thang nam thu nhat
//						DATE d2: ngay thang nam thu hai
// Gia tri tra ve:
//						int dis: khoang cach giua 2 ngay
int TinhKhoangCach2Ngay(DATE d1, DATE d2) {
	int dis = 0;
	if (!SoSanhNgayNhoHon(d1, d2)) {
		return 0;
	}
	while (d1.d != d2.d || d1.m != d2.m || d1.y != d2.y) {
		CongNNgay(d1, 1);
		dis++;
	}
	return dis;
}

// Chuc nang: Tach chuoi ki tu ngay (dd/mm/yyyy) thanh tung gia tri ngay, thang, nam theo kieu so nguyen
// Tham so truyen vao:
//						char date[11]: chuoi ki tu ngay theo dinh dang (dd/mm/yyyy)
//						DATE& d: ngay thang nam
// Gia tri tra ve: (khong co)
void TachChuoiKiTuNgay(char date[11], DATE& d) {
	d.d = (date[0] - '0') * 10 + (date[1] - '0');
	d.m = (date[3] - '0') * 10 + (date[4] - '0');
	d.y = (date[6] - '0') * 1000 + (date[7] - '0') * 100 + (date[8] - '0') * 10 + (date[9] - '0');
}
