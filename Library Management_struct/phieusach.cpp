#include <iostream>
#include <iomanip>
#include <string.h>
#include "docgia.h"
#include "sach.h"
#include "phieusach.h"
#include "thoigian.h"
#include "menu.h"

using namespace std;

// Chuc nang: Doc 1 phieu tu file du lieu quan ly phieu muon/tra sach
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly phieu muon/tra sach
//						PHIEUSACH& p: phieu can doc
// Gia tri tra ve: (khong co)
void Doc1Phieu(FILE* fp, PHIEUSACH& p) {
	Doc1Dong(fp, p.code, MAXCODE);
	fscanf_s(fp, "%d", &p.amtBor);
	char c = fgetc(fp);
	for (int i = 0; i < p.amtBor; i++) {
		fscanf_s(fp, "%s", &p.isbnBor[i].isbn, _countof(p.isbnBor[i].isbn));
		c = fgetc(fp);
	}
	c = fgetc(fp);
	Doc1Dong(fp, p.dateBor, MAXDATE);
	Doc1Dong(fp, p.dateExp, MAXDATE);
}

// Chuc nang: Doc danh sach tat ca phieu tu file du lieu quan ly phieu muon/tra sach
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly phieu muon/tra sach
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int& n: so luong phieu
// Gia tri tra ve: (khong co)
void DocDSPhieu(FILE* fp, PHIEUSACH PhieuSach[MAXP], int& n) {
	while (!feof(fp)) {
		n++;
		Doc1Phieu(fp, PhieuSach[n - 1]);
	}
}

// Chuc nang: Ghi danh sach tat ca phieu vao file du lieu quan ly phieu muon/tra sach
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly phieu muon/tra sach
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int n: so luong phieu
// Gia tri tra ve: (khong co)
void GhiDSPhieu(FILE* fp, PHIEUSACH PhieuSach[MAXP], int n) {
	for (int i = 0; i < n; i++) {
		if (i != 0) {
			fprintf(fp, "\n");
		}
		fprintf(fp, "%s\n", PhieuSach[i].code);
		fprintf(fp, "%d\n", PhieuSach[i].amtBor);
		for (int j = 0; j < PhieuSach[i].amtBor; j++) {
			fprintf(fp, "%s ", PhieuSach[i].isbnBor[j].isbn);
		}
		fprintf(fp, "\n%s\n", PhieuSach[i].dateBor);
		fprintf(fp, "%s", PhieuSach[i].dateExp);
	}
}

// Chuc nang: Dem tong so sach cua 1 doc gia da muon
// Tham so truyen vao:	
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve:
//						int s: tong so sach cua doc gia da muon
int DemSoSachDocGiaDaMuon(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE]) {
	int s = 0;
	for (int i = 0; i < nP; i++) {
		if (strcmp(x, PhieuSach[i].code) == 0) {
			s = s + PhieuSach[i].amtBor;
		}
	}
	return s;
}

// Chuc nang: Dien thong tin cho phieu muon sach (gom: ma doc gia, so luong sach muon, isbn, ngay muon)
// Tham so truyen vao:	
//						FILE* fp: file du lieu quan ly phieu muon/tra sach
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int& nP: so luong phieu
//						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int nD: so dong doc gia trong thu vien
//						SACH Sach[MAXS]: mang quan ly sach
//						int nS: so luong sach trong thu vien
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve: (khong co)
void DienPhieuMuon(FILE* fp, PHIEUSACH PhieuSach[MAXP], int& nP, DOCGIA DocGia[MAXD], int nD, SACH Sach[MAXS], int nS, char x[MAXCODE]) {
	nP++;

	// Nhap ma doc gia
	NhapMaDocGia(DocGia, nD, x);
	if (x[0] == 0) {
		nP--;
		return;
	}

	// Nhap so luong sach muon
	int quant = 0, quantBef = DemSoSachDocGiaDaMuon(PhieuSach, nP - 1, x);
	if (quantBef == 5) {
		cout << "DA MUON TOI DA SO SACH QUY DINH!\n";
		nP--;
		x[0] = 0;
		return;
	}

	strcpy_s(PhieuSach[nP - 1].code, x);
	fprintf(fp, "\n%s\n", PhieuSach[nP - 1].code);
	do {
		cout << "Nhap so luong sach muon (toi da " << MAXBORROW - quantBef << " cuon): ";
		cin >> PhieuSach[nP - 1].amtBor;
		quant = PhieuSach[nP - 1].amtBor + quantBef;
	} while (quant <= 0 || quant > MAXBORROW);
	fprintf(fp, "%d\n", PhieuSach[nP - 1].amtBor);

	//Nhap ISBN
	cout << "Nhap ISBN cua cac sach\n";
	for (int i = 0; i < PhieuSach[nP - 1].amtBor; i++) {
		bool valid = 1;
		do {
			if (!valid) {
				cout << "ISBN khong ton tai. Moi ban nhap lai.\n";
			}
			cin >> PhieuSach[nP - 1].isbnBor[i].isbn;
			valid = 0;
		} while (!KiemTraISBN(Sach, nS, PhieuSach[nP - 1].isbnBor[i].isbn));
		fprintf(fp, "%s ", PhieuSach[nP - 1].isbnBor[i].isbn);
	}

	// Nhap ngay muon
	DATE d;
	cout << "Nhap ngay muon (Nhap rieng tung gia tri) \n";
	NhapNgay(d);
	char date[11];
	ChuyenThanhChuoiKyTuNgay(date, d);
	strcpy_s(PhieuSach[nP - 1].dateBor, date);
	fprintf(fp, "\n%s\n", PhieuSach[nP - 1].dateBor);

	// Tinh ngay tra du kien
	CongNNgay(d, 7);
	ChuyenThanhChuoiKyTuNgay(date, d);
	strcpy_s(PhieuSach[nP - 1].dateExp, date);
	fprintf(fp, "%s", PhieuSach[nP - 1].dateExp);
}

// Chuc nang: Xuat phieu muon sach
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve: (khong co)
void XuatPhieuMuon(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE]) {
	cout << setw(60) << left << "" << "Danh sach ISBN cac sach dang duoc muon:\n";
	int quant = 0;
	// Xuat tat ca lan muon
	for (int i = 0; i < nP; i++) {
		if (strcmp(PhieuSach[i].code, x) == 0) {
			for (int j = 0; j < PhieuSach[i].amtBor; j++) {
				cout << setw(60) << "" << left << PhieuSach[i].isbnBor[j].isbn << endl;
				quant++;
			}
			cout << setw(63) << left << "" << "Ngay muon: " << PhieuSach[i].dateBor << endl;
			cout << setw(63) << left << "" << "Ngay tra du kien: " << PhieuSach[i].dateExp << endl;
		}
	}
	cout << endl;
	cout << setw(60) << left << "" << "TONG SO SACH DANG MUON: " << quant << " CUON\n";
	cout << setw(60) << left << "" << "SO SACH TOI DA CO THE MUON TIEP: " << MAXBORROW - quant << " CUON\n";
}

// Chuc nang: Kiem tra doc gia co muon sach hay khong
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve:
//						1 (true)	neu doc gia co muon sach
//						0 (false)	neu doc gia khong muon sach
bool KiemTraDocGiaCoMuonSach(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE]) {
	for (int i = 0; i < nP; i++) {
		if (strcmp(PhieuSach[i].code, x) == 0) {
			return 1;
		}
	}
	return 0;
}

// Chuc nang: Tim vi tri cua doc gia muon sach trong mang du lieu ve phieu muon/tra sach
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve:
//						i		vi tri cua doc gia
//						-1		neu khong doc gia khong muon sach
int TimDocGiaMuonSach(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE]) {
	for (int i = 0; i < nP; i++) {
		if (strcmp(PhieuSach[i].code, x) == 0) {
			return i;
		}
	}
	return -1;
}

// Chuc nang: Kiem tra doc gia co muon cuon sach nay hay khong
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
//						char x[MAXCODE]: ma doc gia
//						char isbn[MAXISBN]: ma sach can kiem tra
// Gia tri tra ve:
//						1 (true)	neu doc gia co muon sach nay
//						0 (false)	neu doc gia khong muon sach nay
bool KiemTraISBNDuocMuon(PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE], char isbn[MAXISBN]) {
	for (int i = 0; i < nP; i++) {
		if (strcmp(PhieuSach[i].code, x) == 0) {
			for (int j = 0; j < PhieuSach[i].amtBor; j++) {
				if (strcmp(PhieuSach[i].isbnBor[j].isbn, isbn) == 0) {
					return 1;
				}
			}
		}
	}
	return 0;
}

// Chuc nang: Tim ngay tra du kien cua 1 doc gia voi 1 quyen sach ma doc gia do muon
// Tham so truyen vao:
//						char dateExp[MAXDATE]: ngay tra du kien
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
//						char x[MAXCODE]: ma doc gia
//						char isbn[MAXISBN]: isbn cua sach can tim
// Gia tri tra ve: (khong co)
void TimNgayTraDuKien(char dateExp[MAXDATE], PHIEUSACH PhieuSach[MAXP], int nP, char x[MAXCODE], char isbn[MAXISBN]) {
	for (int i = 0; i < nP; i++) {
		if (strcmp(PhieuSach[i].code, x) == 0) {
			for (int j = 0; j < PhieuSach[i].amtBor; j++) {
				if (strcmp(PhieuSach[i].isbnBor[j].isbn, isbn) == 0) {
					for (int u = 0; u < MAXDATE - 1; u++) {
						dateExp[u] = PhieuSach[i].dateExp[u];
					}
					dateExp[MAXDATE - 1] = 0;
					return;
				}
			}
		}
	}
}

// Chuc nang: Dien thong tin cho phieu tra sach (gom: ma doc gia, bao mat sach, so luong sach, isbn, ngay tra thuc te)
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
//						DOCGIA DocGia[MAXD]: mang ly doc gia
//						int nD: so luong doc gia trong thu vien
//						SACH Sach[MAXS]: mang quan ly sach
//						int nS: so luong sach trong thu vien
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve: (khong co)
void DienPhieuTra(PHIEUSACH PhieuSach[MAXP], int nP, DOCGIA DocGia[MAXD], int nD, SACH Sach[MAXS], int nS, char x[MAXCODE]) {
	// Nhap ma doc gia
	NhapMaDocGia(DocGia, nD, x);
	if (x[0] == 0) {
		return;
	}
	bool retype = 1;
	if (!KiemTraDocGiaCoMuonSach(PhieuSach, nP, x)) {
		do {
			cout << "Doc gia nay khong muon sach! Ban co muon nhap lai? (Co -> chon 1; Khong -> chon 0) ";
			cin >> retype;
			if (!retype) {
				x[0] = 0;
				return;
			}
			NhapMaDocGia(DocGia, nD, x);
			if (x[0] == 0) {
				return;
			}
		} while (!KiemTraDocGiaCoMuonSach(PhieuSach, nP, x));
	}

	int index = TimDocGiaMuonSach(PhieuSach, nP, x);

	// Nhap ngay tra thuc te
	DATE d1;
	cout << "Nhap ngay tra sach (Nhap rieng tung gia tri)\n";
	NhapNgay(d1);
	ChuyenThanhChuoiKyTuNgay(PhieuSach[index].dateCur, d1);

	// Nhap so luong sach
	int quantBef = DemSoSachDocGiaDaMuon(PhieuSach, nP, x);
	do {
		cout << "Nhap so luong sach tra: ";
		cin >> PhieuSach[index].amtRet;
	} while (PhieuSach[index].amtRet <= 0 || PhieuSach[index].amtRet > quantBef);

	// Nhap ISBN
	PhieuSach[index].fee = 0;
	for (int i = 0; i < PhieuSach[index].amtRet; i++) {
		bool valid = 1;
		do {
			if (!valid) {
				cout << "Doc gia khong muon sach co ISBN nay! Moi ban nhap lai.\n";
			}
			cout << "Nhap ISBN:\n";
			cin >> PhieuSach[index].isbnRet[i].isbn;
			valid = 0;
		} while (!KiemTraISBNDuocMuon(PhieuSach, nP, x, PhieuSach[index].isbnRet[i].isbn));

		// Bao mat sach
		bool lost;
		cout << "Co mat sach khong? (Co -> chon 1; Khong -> chon 0) ";
		cin >> lost;

		PhieuSach[index].amtLost = 0;
		// Tinh tien phat
		if (lost) {
			for (int u = 0; u < nS; u++) {
				if (strcmp(PhieuSach[index].isbnRet[i].isbn, Sach[u].isbn) == 0) {
					PhieuSach[index].fee = PhieuSach[index].fee + Sach[u].price * 2;
					// Cap nhat lai so luong cua cuon sach nay trong thu vien
					Sach[u].amt--;
					break;
				}
			}
			PhieuSach[index].amtLost++;
		}
		else {
			// Tinh so ngay tre han
			DATE d2;
			char dateExp[MAXDATE];
			TimNgayTraDuKien(dateExp, PhieuSach, nP, x, PhieuSach[index].isbnRet[i].isbn);
			TachChuoiKiTuNgay(dateExp, d2);
			TachChuoiKiTuNgay(PhieuSach[index].dateCur, d1);
			int dist = TinhKhoangCach2Ngay(d2, d1);
			PhieuSach[index].fee = PhieuSach[index].fee + 5000 * dist;
		}
	}
}

// Chuc nang: Xoa thong tin cua doc gia khi da tra het 1 dot muon sach trong mang ve phieu muon/tra sach
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int& nP: so luong phieu
//						int k: chi so phan tu muon xoa
// Gia tri tra ve: (khong co)
void XoaDocGiaDaTraHet(PHIEUSACH PhieuSach[MAXP], int& nP, int k) {
	for (int i = k; i < nP - 1; i++) {
		PhieuSach[i] = PhieuSach[i + 1];
	}
	nP--;
}

// Chuc nang: Xoa ISBN cua sach doc gia da tra trong mang phieu muon/tra sach
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int& nP: so luong phieu (neu tra het sach thi xoa phan tu phieu do)
//						char x[MAXCODE]: ma doc gia
//						char isbn[MAXISBN]: isbn cua sach da tra
// Gia tri tra ve: (khong co)
void XoaISBNDaTra(PHIEUSACH PhieuSach[MAXP], int& nP, char x[MAXCODE], char isbn[MAXISBN]) {
	for (int i = 0; i < nP; i++) {
		if (strcmp(PhieuSach[i].code, x) == 0) {
			for (int j = 0; j < PhieuSach[i].amtBor; j++) {
				if (strcmp(PhieuSach[i].isbnBor[j].isbn, isbn) == 0) {
					for (int u = j; u < PhieuSach[i].amtBor - 1; u++) {
						strcpy_s(PhieuSach[i].isbnBor[j].isbn, PhieuSach[i].isbnBor[j + 1].isbn);
					}
					PhieuSach[i].isbnBor[PhieuSach[i].amtBor - 1].isbn[0] = 0;
					// Cap nhat lai so sach dang muon
					PhieuSach[i].amtBor--;
					// Neu da tra het thi xoa thong tin muon sach do
					if (PhieuSach[i].amtBor == 0) {
						XoaDocGiaDaTraHet(PhieuSach, nP, i);
					}
					return;
				}
			}
		}
	}
}

// Chuc nang: Xuat phieu tra sach
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int& nP: so luong phieu
//						char x[MAXCODE]: ma doc gia
// Gia tri tra ve: (khong co)
void XuatPhieuTra(PHIEUSACH PhieuSach[MAXP], int& nP, char x[MAXCODE]) {
	if (x[0] == 0 || !KiemTraDocGiaCoMuonSach(PhieuSach, nP, x)) {
		return;
	}
	int index = TimDocGiaMuonSach(PhieuSach, nP, x);
	cout << setw(60) << left << "" << "Ngay tra thuc te: " << PhieuSach[index].dateCur << endl << endl;
	cout << setw(60) << left << "" << "So sach chua tra: " << DemSoSachDocGiaDaMuon(PhieuSach, nP, x) - PhieuSach[index].amtRet << endl;
	cout << setw(60) << left << "" << "So sach da tra: " << PhieuSach[index].amtRet - PhieuSach[index].amtLost << endl;
	cout << setw(60) << left << "" << "So sach bi mat: " << PhieuSach[index].amtLost << endl << endl;
	cout << setw(60) << left << "" << "Tien phat: " << PhieuSach[index].fee << " dong" << endl;

	// Xoa thong tin sau khi tra
	for (int i = 0; i < PhieuSach[index].amtRet; i++) {
		XoaISBNDaTra(PhieuSach, nP, x, PhieuSach[index].isbnRet[i].isbn);
	}
	cout << endl;

	// Kiem tra doc gia tra het sach chua -> Xuat so sach dang duoc muon
	if (KiemTraDocGiaCoMuonSach(PhieuSach, nP, x)) {
		XuatPhieuMuon(PhieuSach, nP, x);
	}
	else {
		cout << setw(60) << left << "" << "DA TRA HET SACH!\n";
		cout << setw(60) << left << "" << "SO SACH TOI DA CO THE MUON TIEP: 5 CUON\n";
	}
}


// Chuc nang: Dem tong so sach ma tat ca doc gia da muon cua thu vien
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
// Gia tri tra ve:
//						int s: tong so sach duoc muon trong thu vien
int DemSoSachDuocMuon(PHIEUSACH PhieuSach[MAXP], int nP) {
	int s = 0;
	for (int i = 0; i < nP; i++) {
		s = s + PhieuSach[i].amtBor;
	}
	return s;
}

// Chuc nang: Kiem tra 1 doc gia co ton tai trong mang chua ma doc gia tre han truoc do hay chua
// Tham so truyen vao:
//						PHIEUSACH TreHan[MAXP]: mang chua ma doc gia tre han
//						int nTh: so luong phan tu cua mang
//						char x[MAXCODE]: ma doc gia can kiem tra
// Gia tri tra ve:
//						1 (true)	neu da ton tai trong mang
//						0 (false)	neu chua ton tai trong mang
bool KiemTraTonTaiDocGiaTreHanTruocDo(PHIEUSACH TreHan[MAXP], int nTh, char x[MAXCODE]) {
	for (int i = 0; i < nTh; i++) {
		if (strcmp(x, TreHan[i].code) == 0) {
			return 1;
		}
	}
	return 0;
}

// Chuc nang: Thong ke cac doc gia bi tre han va sao chep cac ma doc gia do vao mang
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
//						DATE dCur: ngay thang nam hien tai
//						PHIEUSACH TreHan[MAXP]: mang chua ma doc gia tre han
//						int& nTh: so luong phan tu cua mang
// Gia tri tra ve: (khong co)
void ThongKeDocGiaTreHan(PHIEUSACH PhieuSach[MAXP], int nP, DATE dCur, PHIEUSACH TreHan[MAXP], int& nTh) {
	DATE dExp;
	for (int i = 0; i < nP; i++) {
		TachChuoiKiTuNgay(PhieuSach[i].dateExp, dExp);
		if (SoSanhNgayNhoHon(dExp, dCur)) {
			if (!KiemTraTonTaiDocGiaTreHanTruocDo(TreHan, nTh, PhieuSach[i].code)) {
				nTh++;
				strcpy_s(TreHan[nTh - 1].code, PhieuSach[i].code);
			}
		}
	}
}

// Chuc nang: Xuat danh sach cac doc gia bi tre han
// Tham so truyen vao:
//						PHIEUSACH TreHan[MAXP]: mang chua ma doc gia tre han
//						int nTh: so luong phan tu cua mang
// 						DOCGIA DocGia[MAXD]: mang quan ly doc gia
//						int nD: so luong doc gia trong thu vien
// Gia tri tra ve: (khong co)
void XuatDSDocGiaTreHan(PHIEUSACH TreHan[MAXP], int nTh, DOCGIA DocGia[MAXD], int nD) {
	cout << setw(65) << left << "" << setw(20) << left << "Ma doc gia" << "Ho ten" << endl;
	for (int i = 0; i < nTh; i++) {
		for (int j = 0; j < nD; j++) {
			if (strcmp(TreHan[i].code, DocGia[j].code) == 0) {
				cout << setw(65) << left << "" << setw(20) << left << TreHan[i].code << DocGia[j].name << endl;
				break;
			}
		}
	}
}

// Chuc nang: Dem so luong doc gia dang muon sach cua thu vien
// Tham so truyen vao:
//						PHIEUSACH PhieuSach[MAXP]: mang chua cac du lieu ve phieu muon/tra sach
//						int nP: so luong phieu
// Gia tri tra ve:
//						int s: tong so doc gia muon sach
int DemSoLuongDocGiaMuonSach(PHIEUSACH PhieuSach[MAXP], int nP) {
	int s = 1;
	for (int i = 1; i < nP; i++) {
		bool exist = 0;
		for (int j = 0; j < i; j++) {
			if (strcmp(PhieuSach[i].code, PhieuSach[j].code) == 0) {
				exist = 1;
				break;
			}
		}
		if (!exist) {
			s++;
		}
	}
	return s;
}
