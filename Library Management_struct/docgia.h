#pragma once
#define MAXD 50

#define MAXCODE 7
#define MAXNAME 35
#define MAXID 13
#define MAXDATE 11
#define MAXGENDER 4
#define MAXEMAIL 30
#define MAXADD 40

struct DOCGIA {
	char code[MAXCODE], name[MAXNAME], id[MAXID], birth[MAXDATE], gender[MAXGENDER], email[MAXEMAIL], add[MAXADD], cre[MAXDATE], exp[MAXDATE];
};

void Doc1DocGia(FILE* fp, DOCGIA& r);
void DocDSDocGia(FILE* fp, DOCGIA DocGia[MAXD], int& n);
void XuatDSDocGia(DOCGIA DocGia[MAXD], int n);
void GhiDSDocGia(FILE* fp, DOCGIA DocGia[MAXD], int n);
void ThemDocGia(FILE* fp, DOCGIA DocGia[MAXD], int& n);
void NhapMaDocGia(DOCGIA DocGia[MAXD], int n, char x[MAXCODE]);
int ViTriDocGiaTheoMaDocGia(DOCGIA DocGia[MAXD], int n, char x[MAXCODE]);
bool KiemTraMaDocGia(DOCGIA DocGia[MAXD], int n, char x[MAXCODE]);
void ChinhSuaDocGia(FILE* fp, DOCGIA DocGia[MAXD], int n, char x[MAXCODE]);
void XoaDocGia(FILE* fp, DOCGIA DocGia[MAXD], int& n, char x[MAXCODE]);
void Xuat1DocGia(DOCGIA DocGia[MAXD], int n, int k);
int TimDocGiaTheoCMND(DOCGIA DocGia[MAXD], int n, char x[MAXID]);
int TimDocGiaTheoHoTen(DOCGIA DocGia[MAXD], int n, char x[MAXNAME]);
int DemDocGiaTheoGioiTinh(DOCGIA DocGia[MAXD], int n, char gender[MAXGENDER]);