#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include "docgia.h"
#include "thoigian.h"
#include "menu.h"

using namespace std;

// Chuc nang: Doc 1 doc gia tu file du lieu quan ly doc gia
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly doc gia
//						DOCGIA& r: doc gia can doc
// Gia tri tra ve: (khong co)
void Doc1DocGia(FILE* fp, DOCGIA& r) {
	Doc1Dong(fp, r.code, MAXCODE);
	Doc1Dong(fp, r.name, MAXNAME);
	Doc1Dong(fp, r.id, MAXID);
	Doc1Dong(fp, r.birth, MAXDATE);
	Doc1Dong(fp, r.gender, MAXGENDER);
	Doc1Dong(fp, r.email, MAXEMAIL);
	Doc1Dong(fp, r.add, MAXADD);
	Doc1Dong(fp, r.cre, MAXDATE);
	Doc1Dong(fp, r.exp, MAXDATE);
}

// Chuc nang: Doc danh sach tat ca doc gia tu file du lieu quan ly doc gia
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly doc gia
//						DOCGIA DocGia[MAXD]: mang chua cac du lieu ve doc gia
//						int& n: so luong doc gia
// Gia tri tra ve: (khong co)
void DocDSDocGia(FILE* fp, DOCGIA DocGia[MAXD], int& n) {
	while (!feof(fp)) {
		n++;
		Doc1DocGia(fp, DocGia[n - 1]);
	}
}

// Chuc nang: Xuat danh sach doc gia trong thu vien
// Tham so truyen vao:	
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int n: so luong doc gia
// Gia tri tra ve: (khong co)
void XuatDSDocGia(DOCGIA DocGia[MAXD], int n) {
	cout << setw(13) << left << "Ma doc gia" << setw(28) << left << "Ho ten" << setw(15) << left << "CMND"
		<< setw(15) << left << "Ngay sinh" << setw(15) << left << "Gioi tinh" << setw(25) << left << "Email"
		<< setw(25) << left << "Dia chi" << setw(15) << left << "Ngay lap the" << "Ngay het han the\n";
	for (int i = 0; i < n; i++) {
		cout << setw(13) << left << DocGia[i].code << setw(28) << left << DocGia[i].name
			<< setw(15) << left << DocGia[i].id << setw(15) << left << DocGia[i].birth
			<< setw(15) << left << DocGia[i].gender << setw(25) << left << DocGia[i].email
			<< setw(25) << left << DocGia[i].add << setw(15) << left << DocGia[i].cre << DocGia[i].exp;
		cout << endl;
	}
}

// Chuc nang: Ghi danh sach tat ca doc gia vao file du lieu quan ly doc gia
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly doc gia
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int n: so luong doc gia
// Gia tri tra ve: (khong co)
void GhiDSDocGia(FILE* fp, DOCGIA DocGia[MAXD], int n) {
	for (int i = 0; i < n; i++) {
		if (i != 0) {
			fprintf(fp, "\n");
		}
		fprintf(fp, "%s\n", DocGia[i].code);
		fprintf(fp, "%s\n", DocGia[i].name);
		fprintf(fp, "%s\n", DocGia[i].id);
		fprintf(fp, "%s\n", DocGia[i].birth);
		fprintf(fp, "%s\n", DocGia[i].gender);
		fprintf(fp, "%s\n", DocGia[i].email);
		fprintf(fp, "%s\n", DocGia[i].add);
		fprintf(fp, "%s\n", DocGia[i].cre);
		fprintf(fp, "%s", DocGia[i].exp);
	}
}

// Chuc nang: Them 1 doc gia vao danh sach hien tai
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly doc gia
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int& n: so luong doc gia (sau khi them doc gia thi so luong se tang len)
// Gia tri tra ve: (khong co)
void ThemDocGia(FILE* fp, DOCGIA DocGia[MAXD], int& n) {
	n++;
	cin.ignore();
	fprintf(fp, "\n");
	cout << "([x] -> x la so ki tu toi da duoc nhap vao)\n";
	cout << "Ma doc gia [" << MAXCODE - 1 << "]: ";
	gets_s(DocGia[n - 1].code);
	fprintf(fp, "%s\n", DocGia[n - 1].code);
	cout << "Ho ten [" << MAXNAME - 1 << "]: ";
	gets_s(DocGia[n - 1].name);
	fprintf(fp, "%s\n", DocGia[n - 1].name);
	cout << "CMND [9/12]: ";
	gets_s(DocGia[n - 1].id);
	fprintf(fp, "%s\n", DocGia[n - 1].id);
	cout << "Ngay sinh (Nhap rieng tung gia tri)\n";
	DATE d;
	NhapNgay(d);
	cin.ignore();
	ChuyenThanhChuoiKyTuNgay(DocGia[n - 1].birth, d);
	fprintf(fp, "%s\n", DocGia[n - 1].birth);
	cout << "Gioi tinh (Nam/Nu): ";
	gets_s(DocGia[n - 1].gender);
	fprintf(fp, "%s\n", DocGia[n - 1].gender);
	cout << "Email [" << MAXEMAIL - 1 << "]: ";
	gets_s(DocGia[n - 1].email);
	fprintf(fp, "%s\n", DocGia[n - 1].email);
	cout << "Dia chi [" << MAXADD - 1 << "]: ";
	gets_s(DocGia[n - 1].add);
	fprintf(fp, "%s\n", DocGia[n - 1].add);
	cout << "Ngay lap the (Nhap rieng tung gia tri)\n";
	NhapNgay(d);
	ChuyenThanhChuoiKyTuNgay(DocGia[n - 1].cre, d);
	fprintf(fp, "%s\n", DocGia[n - 1].cre);
	d.y = d.y + 4;
	ChuyenThanhChuoiKyTuNgay(DocGia[n - 1].exp, d);
	fprintf(fp, "%s", DocGia[n - 1].exp);
}

// Chuc nang: Nhap ma doc gia (trong do kiem tra ma doc gia co ton tai trong danh sach doc gia hay khong)
// Tham so truyen vao:
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int n: so luong doc gia
//						char x[MAXCODE]: ma doc gia nhap vao
// Gia tri tra ve:
//						x[0] = 0		neu nguoi dung nhap sai ma khong muon nhap lai
//						x				neu nguoi dung nhap ma doc gia hop le
void NhapMaDocGia(DOCGIA DocGia[MAXD], int n, char x[MAXCODE]) {
	bool retype = 1;
	bool valid = 1;
	do {
		if (!valid) {
			cout << "Ma doc gia khong ton tai! Ban co muon nhap lai? (Co -> chon 1; Khong -> chon 0) ";
			cin >> retype;
			if (!retype) {
				x[0] = 0;
				return;
			}
		}
		cin.ignore();
		cout << "Nhap ma doc gia: ";
		fgets(x, MAXCODE, stdin);
		valid = 0;
	} while (!KiemTraMaDocGia(DocGia, n, x));
	return;
}

// Chuc nang: Tim vi tri cua doc gia theo ma doc gia
// Tham so truyen vao:
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int n: so luong doc gia
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve:
//						chi so dong chua ma doc gia		neu ma doc gia duoc tim thay
//						-1								neu ma doc gia khong duoc tim thay
int ViTriDocGiaTheoMaDocGia(DOCGIA DocGia[MAXD], int n, char x[MAXCODE]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(x, DocGia[i].code) == 0) {
			return i;
		}
	}
	return -1;
}

// Chuc nang: Kiem tra ma doc gia co hop le khong (co ton tai trong danh sach doc gia khong)
// Tham so truyen vao:
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int n: so luong doc gia
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve:
//						0 (false)		neu vi tri chua ma doc gia = -1 (khong tim thay)
//						1 (true)		neu vi tri chua ma doc gia khac 0 (duoc tim thay)
bool KiemTraMaDocGia(DOCGIA DocGia[MAXD], int n, char x[MAXCODE]) {
	if (ViTriDocGiaTheoMaDocGia(DocGia, n, x) == -1) {
		return 0;
	}
	return 1;
}

// Chuc nang: Chinh sua thong tin cua doc gia theo ma doc gia duoc nhap vao tu ban phim
// Tham so truyen vao:
//						FILE* fp: file du lieu quan ly doc gia
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int n: so luong doc gia
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve: (khong co)
void ChinhSuaDocGia(FILE* fp, DOCGIA DocGia[MAXD], int n, char x[MAXCODE]) {
	int index = ViTriDocGiaTheoMaDocGia(DocGia, n, x);

	bool edit;
	cout << "(Sua -> chon 1; Khong sua -> chon 0)\n";

	for (int i = 0; i < 8; i++) {
		switch (i)
		{
		case 0:
			cout << "Ma doc gia - ";
			break;
		case 1:
			cout << "Ho ten - ";
			break;
		case 2:
			cout << "CMND - ";
			break;
		case 3:
			cout << "Ngay sinh - ";
			break;
		case 4:
			cout << "Gioi tinh - ";
			break;
		case 5:
			cout << "Email - ";
			break;
		case 6:
			cout << "Dia chi - ";
			break;
		case 7:
			cout << "Ngay lap the - ";
			break;
		}
		cin >> edit;
		if (edit) {
			cin.ignore();
			DATE d;
			switch (i) {
			case 0:
				cout << "Thong tin cu: " << DocGia[index].code << endl;
				cout << "Nhap thong tin moi [" << MAXCODE - 1 << "]: ";
				gets_s(DocGia[index].code);
				break;

			case 1:
				cout << "Thong tin cu: " << DocGia[index].name << endl;
				cout << "Nhap thong tin moi [" << MAXNAME - 1 << "]: ";
				gets_s(DocGia[index].name);
				break;
			case 2:
				cout << "Thong tin cu: " << DocGia[index].id << endl;
				cout << "Nhap thong tin moi [" << MAXID - 1 << "]: ";
				gets_s(DocGia[index].id);
				break;
			case 3:
				cout << "Thong tin cu: " << DocGia[index].birth << endl;
				cout << "Nhap thong tin moi: (Nhap rieng tung gia tri)\n";
				NhapNgay(d);
				ChuyenThanhChuoiKyTuNgay(DocGia[index].birth, d);
				break;
			case 4:
				cout << "Thong tin cu: " << DocGia[index].gender << endl;
				cout << "Nhap thong tin moi (Nam/Nu): ";
				gets_s(DocGia[index].gender);
				break;
			case 5:
				cout << "Thong tin cu: " << DocGia[index].email << endl;
				cout << "Nhap thong tin moi [" << MAXEMAIL - 1 << "]: ";
				gets_s(DocGia[index].email);
				break;
			case 6:
				cout << "Thong tin cu: " << DocGia[index].add << endl;
				cout << "Nhap thong tin moi [" << MAXADD - 1 << "]: ";
				gets_s(DocGia[index].add);
				break;
			case 7:
				cout << "Thong tin cu: " << DocGia[index].cre << endl;
				cout << "Nhap thong tin moi: (Nhap rieng tung gia tri)\n";
				NhapNgay(d);
				ChuyenThanhChuoiKyTuNgay(DocGia[index].cre, d);
				d.y = d.y + 4;
				ChuyenThanhChuoiKyTuNgay(DocGia[index].exp, d);
				break;
			}
		}
	}
}

// Chuc nang: Xoa thong tin cua doc gia theo ma doc gia duoc nhap vao tu ban phim
// Tham so truyen vao:
//						FILE* fp: file du lieu quan ly doc gia
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int& n: so luong doc gia (sau khi xoa, so phan tu giam di 1)
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve: (khong co)
void XoaDocGia(FILE* fp, DOCGIA DocGia[MAXD], int& n, char x[MAXCODE]) {
	int index = ViTriDocGiaTheoMaDocGia(DocGia, n, x);
	for (int i = index; i < n - 1; i++) {
		DocGia[i] = DocGia[i + 1];
	}
	n--;
}

// Chuc nang: Xuat 1 thong tin 1 doc gia tu mang quan ly doc gia
// Tham so truyen vao:
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int n: so luong doc gia
//						int k: chi so cua phan tu muon xuat ra
// Gia tri tra ve: (khong co)
void Xuat1DocGia(DOCGIA DocGia[MAXD], int n, int k) {
	if (k < 0 || k > n - 1) return;
	cout << setw(13) << left << "Ma doc gia" << setw(28) << left << "Ho ten" << setw(15) << left << "CMND"
		<< setw(15) << left << "Ngay sinh" << setw(15) << left << "Gioi tinh" << setw(25) << left << "Email"
		<< setw(25) << left << "Dia chi" << setw(15) << left << "Ngay lap the" << "Ngay het han the\n";
	cout << setw(13) << left << DocGia[k].code << setw(28) << left << DocGia[k].name
		<< setw(15) << left << DocGia[k].id << setw(15) << left << DocGia[k].birth
		<< setw(15) << left << DocGia[k].gender << setw(25) << left << DocGia[k].email
		<< setw(25) << left << DocGia[k].add << setw(15) << left << DocGia[k].cre << DocGia[k].exp;
	cout << endl;
}

// Chuc nang: Tim vi tri cua 1 doc gia theo CMND duoc nhap vao tu ban phim
// Tham so truyen vao:
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int n: so luong doc gia
//						char x[MAXID]: CMND cua doc gia
// Gia tri tra ve:
//						chi so cua phan tu doc gia		neu CMND duoc tim thay
//						-1								neu CMND khong duoc tim thay
int TimDocGiaTheoCMND(DOCGIA DocGia[MAXD], int n, char x[MAXID]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(DocGia[i].id, x) == 0) {
			return i;
		}
	}
	return -1;
}

// Chuc nang: Tim vi tri cua 1 doc gia theo ho ten duoc nhap vao tu ban phim
// Tham so truyen vao:
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int n: so luong doc gia
//						char x[MAXNAME]: ho ten cua doc gia
// Gia tri tra ve:
//						chi so cua phan tu doc gia		neu ho ten duoc tim thay (hop le)
//						-1								neu ho ten khong duoc tim thay (khong hop le)
int TimDocGiaTheoHoTen(DOCGIA DocGia[MAXD], int n, char x[MAXNAME]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(DocGia[i].name, x) == 0) {
			return i;
		}
	}
	return -1;
}

// Chuc nang: Dem tong so doc gia theo gioi tinh
// Tham so truyen vao:
//						string a[MAXRD][MAXCD]: ma tran quan ly doc gia
//						int n: so dong cua ma tran
//						string x: gioi tinh ("Nam"/"Nu")
// Gia tri tra ve:
//						int s: tong so doc gia theo gioi tinh
int DemDocGiaTheoGioiTinh(DOCGIA DocGia[MAXD], int n, char gender[MAXGENDER]) {
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(gender, DocGia[i].gender) == 0) {
			s++;
		}
	}
	return s;
}