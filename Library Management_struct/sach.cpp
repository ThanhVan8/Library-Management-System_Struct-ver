#include <iostream>
#include <iomanip>
#include <string.h>
#include "sach.h"
#include "menu.h"

using namespace std;

// Chuc nang: Doc 1 sach tu file du lieu quan ly sach
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly sach
//						SACH& b: sach can doc
// Gia tri tra ve: (khong co)
void Doc1Sach(FILE* fp, SACH& b) {
	Doc1Dong(fp, b.isbn, MAXISBN);
	Doc1Dong(fp, b.title, MAXNAME);
	Doc1Dong(fp, b.author, MAXNAME);
	Doc1Dong(fp, b.nxb, MAXNAME);
	fscanf_s(fp, "%d", &b.year);
	char c = fgetc(fp);
	Doc1Dong(fp, b.type, MAXNAME);
	fscanf_s(fp, "%lu", &b.price);
	c = fgetc(fp);
	fscanf_s(fp, "%d", &b.amt);
	c = fgetc(fp);
}

// Chuc nang: Doc danh sach tat ca sach tu file du lieu quan ly sach
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly sach
//						SACH Sach[MAXS]: mang chua cac du lieu ve sach
//						int& n: so luong sach
// Gia tri tra ve: (khong co)
void DocDSSach(FILE* fp, SACH Sach[MAXS], int& n) {
	while (!feof(fp)) {
		n++;
		Doc1Sach(fp, Sach[n - 1]);
	}
}

// Chuc nang: Xuat danh sach sach trong thu vien
// Tham so truyen vao:	
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach
// Gia tri tra ve: (khong co)
void XuatDSSach(SACH Sach[MAXS], int n) {
	cout << setw(10) << left << "ISBN" << setw(30) << left << "Ten sach" << setw(30) << left << "Tac gia"
		<< setw(30) << left << "Nha xuat ban" << setw(15) << left << "Nam xuat ban" << setw(20) << left << "The loai"
		<< setw(15) << left << "Gia sach" << "So quyen\n";
	for (int i = 0; i < n; i++) {
		cout << setw(10) << left << Sach[i].isbn << setw(30) << left << Sach[i].title
			<< setw(30) << left << Sach[i].author << setw(30) << left << Sach[i].nxb
			<< setw(15) << left << Sach[i].year << setw(20) << left << Sach[i].type
			<< setw(15) << left << Sach[i].price << Sach[i].amt;
		cout << endl;
	}
}

// Chuc nang: Ghi danh sach tat ca sach vao file du lieu quan ly sach
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly sach
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach
// Gia tri tra ve: (khong co)
void GhiDSSach(FILE* fp, SACH Sach[MAXS], int n) {
	for (int i = 0; i < n; i++) {
		if (i != 0) {
			fprintf(fp, "\n");
		}
		fprintf(fp, "%s\n", Sach[i].isbn);
		fprintf(fp, "%s\n", Sach[i].title);
		fprintf(fp, "%s\n", Sach[i].author);
		fprintf(fp, "%s\n", Sach[i].nxb);
		fprintf(fp, "%d\n", Sach[i].year);
		fprintf(fp, "%s\n", Sach[i].type);
		fprintf(fp, "%lu\n", Sach[i].price);
		fprintf(fp, "%d", Sach[i].amt);
	}
}

// Chuc nang: Them 1 sach vao danh sach hien tai
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly sach
//						SACH Sach[MAXS]: mang quan ly sach
//						int& n: so luong sach
// Gia tri tra ve: (khong co)
void ThemSach(FILE* fp, SACH Sach[MAXS], int n) {
	fprintf(fp, "\n");
	fprintf(fp, "%s\n", Sach[n - 1].isbn);
	cout << "Ten sach [" << MAXNAME - 1 << "]: ";
	gets_s(Sach[n - 1].title);
	fprintf(fp, "%s\n", Sach[n - 1].title);
	cout << "Tac gia [" << MAXNAME - 1 << "]: ";
	gets_s(Sach[n - 1].author);
	fprintf(fp, "%s\n", Sach[n - 1].author);
	cout << "Nha xuat ban [" << MAXNAME - 1 << "]: ";
	gets_s(Sach[n - 1].nxb);
	fprintf(fp, "%s\n", Sach[n - 1].nxb);
	cout << "Nam xuat ban: ";
	cin >> Sach[n - 1].year;
	cin.ignore();
	fprintf(fp, "%d\n", Sach[n - 1].year);
	cout << "The loai [" << MAXNAME - 1 << "]: ";
	gets_s(Sach[n - 1].type);
	fprintf(fp, "%s\n", Sach[n - 1].type);
	cout << "Gia sach: ";
	cin >> Sach[n - 1].price;
	cin.ignore();
	fprintf(fp, "%lu\n", Sach[n - 1].price);
	cout << "So quyen: ";
	cin >> Sach[n - 1].amt;
	fprintf(fp, "%d", Sach[n - 1].amt);
}

// Chuc nang: Nhap ISBN (trong do kiem tra ISBN co ton tai trong danh sach sach hay khong)
// Tham so truyen vao:
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach
//						char x[MAXISBN]: ISBN nhap vao
// Gia tri tra ve:
//						x[0] = 0		neu nguoi dung nhap sai ma khong muon nhap lai
//						x				neu nguoi dung nhap ISBN hop le
void NhapISBN(SACH Sach[MAXS], int n, char x[MAXISBN]) {
	bool retype = 1;
	bool valid = 1;
	do {
		if (!valid) {
			cout << "ISBN khong ton tai! Ban co muon nhap lai? (Co -> chon 1; Khong -> chon 0) ";
			cin >> retype;
			if (!retype) {
				x[0] = 0;
				return;
			}
		}
		cin.ignore();
		cout << "Nhap ISBN: ";
		fgets(x, MAXISBN, stdin);
		valid = 0;
	} while (!KiemTraISBN(Sach, n, x));
	return;
}

// Chuc nang: Tim vi tri cua sach theo ISBN
// Tham so truyen vao:
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach trong mang
//						char x[MAXISBN]: ISBN
// Gia tri tra ve:
//						chi so dong chua ISBN		neu ISBN duoc tim thay
//						-1							neu ISBN khong duoc tim thay
int ViTriSachTheoISBN(SACH Sach[MAXS], int n, char x[MAXISBN]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(x, Sach[i].isbn) == 0) {
			return i;
		}
	}
	return -1;
}

// Chuc nang: Kiem tra ISBN co hop le khong (co ton tai trong danh sach sach khong)
// Tham so truyen vao:
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach trong mang
//						char x[MAXISBN]: ISBN
// Gia tri tra ve:
//						0 (false)		neu vi tri chua ISBN = -1 (khong tim thay)
//						1 (true)		neu vi tri chua ISBN khac 0 (duoc tim thay)
bool KiemTraISBN(SACH Sach[MAXS], int n, char x[MAXISBN]) {
	if (ViTriSachTheoISBN(Sach, n, x) == -1) {
		return 0;
	}
	return 1;
}

// Chuc nang: Chinh sua thong tin cua sach theo ISBN duoc nhap vao tu ban phim
// Tham so truyen vao:
//						FILE* fp: file du lieu quan ly sach
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach trong mang
//						char x[MAXISBN]: ISBN
// Gia tri tra ve: (khong co)
void ChinhSuaSach(FILE* fp, SACH Sach[MAXS], int n, char x[MAXISBN]) {
	int index = ViTriSachTheoISBN(Sach, n, x);

	bool edit;
	cout << "(Sua -> chon 1; Khong sua -> chon 0)\n";

	for (int i = 0; i < 8; i++) {
		switch (i)
		{
		case 0:
			cout << "ISBN - ";
			break;
		case 1:
			cout << "Ten sach - ";
			break;
		case 2:
			cout << "Tac gia - ";
			break;
		case 3:
			cout << "Nha xuat ban - ";
			break;
		case 4:
			cout << "Nam xuat ban - ";
			break;
		case 5:
			cout << "The loai - ";
			break;
		case 6:
			cout << "Gia sach - ";
			break;
		case 7:
			cout << "So quyen - ";
			break;
		}
		cin >> edit;
		if (edit) {
			cin.ignore();
			switch (i) {
			case 0:
				cout << "Thong tin cu: " << Sach[index].isbn << endl;
				cout << "Nhap thong tin moi [" << MAXISBN - 1 << "]: ";
				gets_s(Sach[index].isbn);
				break;
			case 1:
				cout << "Thong tin cu: " << Sach[index].title << endl;
				cout << "Nhap thong tin moi [" << MAXNAME - 1 << "]: ";
				gets_s(Sach[index].title);
				break;
			case 2:
				cout << "Thong tin cu: " << Sach[index].author << endl;
				cout << "Nhap thong tin moi [" << MAXNAME - 1 << "]: ";
				gets_s(Sach[index].author);
				break;
			case 3:
				cout << "Thong tin cu: " << Sach[index].nxb << endl;
				cout << "Nhap thong tin moi [" << MAXNAME - 1 << "]: ";
				gets_s(Sach[index].nxb);
				break;
			case 4:
				cout << "Thong tin cu: " << Sach[index].year << endl;
				cout << "Nhap thong tin moi: ";
				cin >> Sach[index].year;
				break;
			case 5:
				cout << "Thong tin cu: " << Sach[index].type << endl;
				cout << "Nhap thong tin moi [" << MAXNAME - 1 << "]: ";
				gets_s(Sach[index].type);
				break;
			case 6:
				cout << "Thong tin cu: " << Sach[index].price << endl;
				cout << "Nhap thong tin moi: ";
				cin >> Sach[index].price;
				break;
			case 7:
				cout << "Thong tin cu: " << Sach[index].amt << endl;
				cout << "Nhap thong tin moi: (Nhap rieng tung gia tri)\n";
				cin >> Sach[index].amt;
				break;
			}
		}
	}
}

// Chuc nang: Xoa thong tin cua 1 quyen sach theo ISBN duoc nhap vao tu ban phim
// Tham so truyen vao:
//						FILE* fp: file du lieu quan ly doc gia
//						SACH Sach[MAXS]: mang quan ly sach
//						int& n: so luong sach trong mang
//						char x[MAXISBN]: ISBN
// Gia tri tra ve: (khong co)
void XoaSach(FILE* fp, SACH Sach[MAXS], int& n, char x[MAXISBN]) {
	int index = ViTriSachTheoISBN(Sach, n, x);
	for (int i = index; i < n - 1; i++) {
		Sach[i] = Sach[i + 1];
	}
	n--;
}

// Chuc nang: Xuat thong tin 1 quyen sach tu mang quan ly sach
// Tham so truyen vao:
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach trong mang
//						int k: chi so cua phan tu muon xuat ra
// Gia tri tra ve: (khong co)
void Xuat1Sach(SACH Sach[MAXS], int n, int k) {
	if (k < 0 || k > n - 1) return;
	cout << setw(10) << left << "ISBN" << setw(30) << left << "Ten sach" << setw(30) << left << "Tac gia"
		<< setw(30) << left << "Nha xuat ban" << setw(15) << left << "Nam xuat ban" << setw(20) << left << "The loai"
		<< setw(15) << left << "Gia sach" << "So quyen\n";
	cout << setw(10) << left << Sach[k].isbn << setw(30) << left << Sach[k].title
		<< setw(30) << left << Sach[k].author << setw(30) << left << Sach[k].nxb
		<< setw(15) << left << Sach[k].year << setw(20) << left << Sach[k].type
		<< setw(15) << left << Sach[k].price << Sach[k].amt;
	cout << endl;
}

// Chuc nang: Tim vi tri cua 1 quyen sach theo ten sach duoc nhap vao tu ban phim
// Tham so truyen vao:
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach trong mang
//						char x[MAXNAME]: ten sach
// Gia tri tra ve:
//						chi so cua phan tu sach		neu ten sach duoc tim thay (hop le)
//						-1							neu ten sach khong duoc tim thay (khong hop le)
int TimSachTheoTen(SACH Sach[MAXS], int n, char x[MAXNAME]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(Sach[i].title, x) == 0) {
			return i;
		}
	}
	return -1;
}

// Chuc nang: Dem tong so sach co trong thu vien
// Tham so truyen vao:
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach trong mang
// Gia tri tra ve:
//						int s: tong so sach trong thu vien
int DemSoLuongSach(SACH Sach[MAXS], int n) {
	int s = 0;
	for (int i = 0; i < n; i++) {
		s = s + Sach[i].amt;
	}
	return s;
}

// Chuc nang: Kiem tra 1 the loai sach co ton tai trong mang chua the loai truoc do hay chua
// Tham so truyen vao:
//						SACH tl[MAXS]: mang chua cac the loai sach
//						int n: so luong phan tu cua mang
//						char x[MAXNAME]: ten the loai can kiem tra
// Gia tri tra ve:
//						1 (true)	neu da ton tai trong mang
//						0 (false)	neu chua ton tai trong mang
bool KiemTraTonTaiTheLoaiTruocDo(SACH TheLoai[MAXS], int n, char x[MAXNAME]) {
	for (int i = 0; i < n; i++) {
		if (strcmp(x, TheLoai[i].type) == 0) {
			return 1;
		}
	}
	return 0;
}

// Chuc nang: Thong ke cac the loai co trong thu vien va sao chep cac the loai do vao mang chua cac the loai
// Tham so truyen vao:
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach trong mang
//						SACH tl[MAXS]: mang chua cac the loai sach
//						int& m: so luong the loai
// Gia tri tra ve: (khong co)
void ThongKeTheLoai(SACH Sach[MAXS], int n, SACH TheLoai[MAXS], int& m) {
	for (int i = 0; i < n; i++) {
		if (!KiemTraTonTaiTheLoaiTruocDo(TheLoai, m, Sach[i].type)) {
			m++;
			strcpy_s(TheLoai[m - 1].type, Sach[i].type);
		}
	}
}

// Chuc nang: Dem so luong sach cua 1 the loai
// Tham so truyen vao:
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach
//						char x[MAXNAME]: ten the loai
// Gia tri tra ve:
//						int s: tong so sach cua 1 the loai
int DemSoLuongSachTheoTheLoai(SACH Sach[MAXS], int n, char x[MAXNAME]) {
	int s = 0;
	for (int i = 0; i < n; i++) {
		if (strcmp(x, Sach[i].type) == 0) {
			s = s + Sach[i].amt;
		}
	}
	return s;
}

// Chuc nang: Xuat so luong sach theo cac the loai
// Tham so truyen vao:
//						SACH Sach[MAXS]: mang quan ly sach
//						int n: so luong sach
//						SACH tl[MAXS]: mang chua cac the loai
//						int m: so luong the loai
// Gia tri tra ve:
//						int s: tong so sach theo 1 the loai
void XuatSoLuongSachTheoTheLoai(SACH Sach[MAXS], int n, SACH TheLoai[MAXS], int m) {
	for (int i = 0; i < m; i++) {
		cout << setw(70) << left << "" << "- " << TheLoai[i].type << ": " << DemSoLuongSachTheoTheLoai(Sach, n, TheLoai[i].type) << endl;
	}
}