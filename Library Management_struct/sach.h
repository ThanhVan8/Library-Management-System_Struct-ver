#pragma once
#include "docgia.h"

#define MAXS 50
#define MAXISBN 7

struct SACH {
	char isbn[MAXISBN], title[MAXNAME], author[MAXNAME], nxb[MAXNAME], type[MAXNAME];
	unsigned long price;
	int year, amt;
};

void Doc1Sach(FILE* fp, SACH& b);
void DocDSSach(FILE* fp, SACH Sach[MAXS], int& n);
void XuatDSSach(SACH Sach[MAXS], int n);
void GhiDSSach(FILE* fp, SACH Sach[MAXS], int n);
void ThemSach(FILE* fp, SACH Sach[MAXS], int n);
void NhapISBN(SACH Sach[MAXS], int n, char x[MAXISBN]);
int ViTriSachTheoISBN(SACH Sach[MAXS], int n, char x[MAXISBN]);
bool KiemTraISBN(SACH Sach[MAXS], int n, char x[MAXISBN]);
void ChinhSuaSach(FILE* fp, SACH Sach[MAXS], int n, char x[MAXISBN]);
void XoaSach(FILE* fp, SACH Sach[MAXS], int& n, char x[MAXISBN]);
void Xuat1Sach(SACH Sach[MAXS], int n, int k);
int TimSachTheoTen(SACH Sach[MAXS], int n, char x[MAXNAME]);
int DemSoLuongSach(SACH Sach[MAXS], int n);
bool KiemTraTonTaiTheLoaiTruocDo(SACH TheLoai[MAXS], int n, char x[MAXNAME]);
void ThongKeTheLoai(SACH Sach[MAXS], int n, SACH TheLoai[MAXS], int& m);
int DemSoLuongSachTheoTheLoai(SACH Sach[MAXS], int n, char x[MAXNAME]);
void XuatSoLuongSachTheoTheLoai(SACH Sach[MAXS], int n, SACH TheLoai[MAXS], int m);