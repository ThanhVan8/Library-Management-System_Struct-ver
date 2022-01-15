#pragma once
#include "sach.h"
#include "thoigian.h"

#define MAXP 20
#define MAXBORROW 5

struct ISBN {
	char isbn[MAXISBN];
};

struct PHIEUSACH {
	char code[MAXCODE], dateBor[MAXDATE], dateExp[MAXDATE], dateCur[MAXDATE];
	int	amtBor, amtRet, amtLost;
	ISBN isbnBor[MAXBORROW], isbnRet[MAXBORROW];
	unsigned long fee;
};

void Doc1Phieu(FILE* fp, PHIEUSACH& p);
void DocDSPhieu(FILE* fp, PHIEUSACH PhieuSach[MAXP], int& n);
int DemSoSachDocGiaDaMuon(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE]);
void DienPhieuMuon(FILE* fp, PHIEUSACH PhieuSach[MAXP], int& nP, DOCGIA DocGia[MAXD], int nD, SACH Sach[MAXS], int nS, char x[MAXCODE]);
void XuatPhieuMuon(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE]);
void GhiDSPhieu(FILE* fp, PHIEUSACH PhieuSach[MAXP], int n);
bool KiemTraDocGiaCoMuonSach(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE]);
int TimDocGiaMuonSach(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE]);
bool KiemTraISBNDuocMuon(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE], char isbn[MAXISBN]);
void TimNgayTraDuKien(char dateExp[MAXDATE], PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE], char isbn[MAXISBN]);
void DienPhieuTra(PHIEUSACH PhieuSach[MAXP], int nP, DOCGIA DocGia[MAXD], int nD, SACH Sach[MAXS], int nS, char x[MAXCODE]);
void XoaDocGiaDaTraHet(PHIEUSACH PhieuSach[MAXP], int& nP, int k);
void XoaISBNDaTra(PHIEUSACH PhieuSach[MAXP], int& nP, char x[MAXCODE], char isbn[MAXISBN]);
void XuatPhieuTra(PHIEUSACH PhieuSach[MAXP], int& nP, char x[MAXCODE]);
int DemSoSachDuocMuon(PHIEUSACH PhieuSach[MAXP], int nP);
bool KiemTraTonTaiDocGiaTreHanTruocDo(PHIEUSACH TreHan[MAXP], int nTh, char x[MAXCODE]);
void ThongKeDocGiaTreHan(PHIEUSACH PhieuSach[MAXP], int nP, DATE dCur, PHIEUSACH TreHan[MAXP], int& nTh);
void XuatDSDocGiaTreHan(PHIEUSACH TreHan[MAXP], int nTh, DOCGIA DocGia[MAXD], int nD);
int DemSoLuongDocGiaMuonSach(PHIEUSACH PhieuSach[MAXP], int nP);