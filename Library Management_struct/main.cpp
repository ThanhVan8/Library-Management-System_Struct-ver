#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include "docgia.h"
#include "sach.h"
#include "phieusach.h"
#include "thoigian.h"
#include "menu.h"

using namespace std;

int main() {
	DOCGIA DocGia[MAXD];
	int nD = 0;
	FILE* fp;
	errno_t err = fopen_s(&fp, "docgia.txt", "rt");
	if (err == 0) {
		DocDSDocGia(fp, DocGia, nD);
		fclose(fp);
	}
	else {
		cout << "Mo file quan ly doc gia that bai!\n\n";
		return 0;
	}

	SACH Sach[MAXS];
	int nS = 0;
	err = fopen_s(&fp, "sach.txt", "rt");
	if (err == 0) {
		DocDSSach(fp, Sach, nS);
		fclose(fp);
	}
	else {
		cout << "Mo file quan ly sach that bai!\n\n";
		return 0;
	}

	PHIEUSACH PhieuSach[MAXP];
	int nP = 0;
	err = fopen_s(&fp, "phieusach.txt", "rt");
	if (err == 0) {
		DocDSPhieu(fp, PhieuSach, nP);
		fclose(fp);
	}
	else {
		cout << "Mo file quan ly muon/tra sach that bai!\n\n";
		return 0;
	}

	while (true) {
		system("CLS");
		XuatMenuChinh();
		int mainChoice;
		char subChoice = '0';
		cout << "\n\nMoi ban nhap chuc nang muon su dung: ";
		cin >> mainChoice;
		system("CLS");

		if (mainChoice == 0) {
			cout << endl << endl;
			cout << setw(60) << left << "" << "CAM ON BAN DA SU DUNG CHUONG TRINH\n\n";
			return 0;
		}

		else if (mainChoice == 1) {
			XuatMenu1();
			cout << "\n\nMoi ban nhap chuc nang cu the: ";
			cin >> subChoice;
			system("CLS");

			if (subChoice == 'a') {
				cout << setw(100) << right << "----- DANH SACH DOC GIA TRONG THU VIEN -----\n\n";
				XuatDSDocGia(DocGia, nD);
			}

			else if (subChoice == 'b') {
				cout << setw(88) << right << "----- THEM DOC GIA -----\n\n";
				err = fopen_s(&fp, "docgia.txt", "at");
				if (err == 0) {
					ThemDocGia(fp, DocGia, nD);
					fclose(fp);
					cout << "DA THEM DOC GIA!\n";
				}
				else {
					cout << "Mo file quan ly doc gia that bai!\n";
				}
			}

			else if (subChoice == 'c') {
				cout << setw(90) << right << "----- CHINH SUA DOC GIA -----\n\n";
				DOCGIA d;
				NhapMaDocGia(DocGia, nD, d.code);
				if (d.code[0] != 0) {
					err = fopen_s(&fp, "docgia.txt", "rt");
					if (err == 0) {
						ChinhSuaDocGia(fp, DocGia, nD, d.code);
						fclose(fp);

						err = fopen_s(&fp, "docgia.txt", "wt");
						if (err == 0) {
							GhiDSDocGia(fp, DocGia, nD);
							fclose(fp);
							cout << "DA CHINH SUA DOC GIA!\n";
						}
						else {
							cout << "Mo file quan ly doc gia that bai!\n";
						}
					}
					else {
						cout << "Mo file quan ly doc gia that bai!\n";
					}
				}
			}

			else if (subChoice == 'd') {
				cout << setw(88) << right << "----- XOA DOC GIA -----\n\n";
				DOCGIA d;
				NhapMaDocGia(DocGia, nD, d.code);
				if (d.code[0] != 0) {
					err = fopen_s(&fp, "docgia.txt", "rt");
					if (err == 0) {
						XoaDocGia(fp, DocGia, nD, d.code);
						fclose(fp);

						err = fopen_s(&fp, "docgia.txt", "wt");
						if (err == 0) {
							GhiDSDocGia(fp, DocGia, nD);
							fclose(fp);
							cout << "DA XOA DOC GIA!\n";
						}
						else {
							cout << "Mo file quan ly doc gia that bai!\n";
						}
					}
					else {
						cout << "Mo file quan ly doc gia that bai!\n";
					}
				}
			}

			else if (subChoice == 'e') {
				cout << setw(90) << right << "----- TIM DOC GIA THEO CMND -----\n\n";
				DOCGIA d;
				bool valid = 1;
				bool retype = 1;
				do {
					if (!valid) {
						cout << "CMND khong ton tai! Ban co muon nhap lai? (Co -> chon 1; Khong -> chon 0) ";
						cin >> retype;
						if (!retype) {
							cin.ignore();
							break;
						}
					}
					cin.ignore();
					cout << "Nhap CMND: ";
					gets_s(d.id);
					valid = 0;
				} while (TimDocGiaTheoCMND(DocGia, nD, d.id) == -1);

				if (retype) {
					int index = TimDocGiaTheoCMND(DocGia, nD, d.id);
					Xuat1DocGia(DocGia, nD, index);
				}
			}

			else if (subChoice == 'f') {
				cout << setw(100) << right << "----- TIM DOC GIA THEO HO TEN -----\n\n";
				DOCGIA d;
				bool valid = 1;
				bool retype = 1;
				do {
					if (!valid) {
						cout << "Ho ten khong ton tai! Ban co muon nhap lai? (Co -> chon 1; Khong -> chon 0) ";
						cin >> retype;
						if (!retype) {
							cin.ignore();
							break;
						}
					}
					cin.ignore();
					cout << "Nhap ho ten: ";
					gets_s(d.name);
					valid = 0;
				} while (TimDocGiaTheoHoTen(DocGia, nD, d.name) == -1);

				if (retype) {
					int index = TimDocGiaTheoHoTen(DocGia, nD, d.name);
					Xuat1DocGia(DocGia, nD, index);
				}
			}

			else {
				cout << "Chuc nang khong co trong danh sach!\n";
			}
		}

		else if (mainChoice == 2) {
			XuatMenu2();
			cout << "\n\nMoi ban nhap chuc nang cu the: ";
			cin >> subChoice;
			system("CLS");

			if (subChoice == 'a') {
				cout << setw(100) << right << "----- DANH SACH SACH TRONG THU VIEN -----\n\n";
				XuatDSSach(Sach, nS);
			}

			else if (subChoice == 'b') {
				cout << setw(88) << right << "----- THEM SACH -----\n\n";
				cin.ignore();
				nS++;
				cout << "([x] -> x la so ki tu toi da duoc nhap vao)\n";
				cout << "ISBN [" << MAXISBN - 1 << "]: ";
				gets_s(Sach[nS - 1].isbn);
				if (!KiemTraISBN(Sach, nS - 1, Sach[nS - 1].isbn)) {
					err = fopen_s(&fp, "sach.txt", "at");
					if (err == 0) {
						ThemSach(fp, Sach, nS);
						fclose(fp);
						cout << "DA THEM SACH!\n";
					}
					else {
						cout << "Mo file quan ly sach that bai!\n";
					}
				}
				else {
					int add, index;
					cout << "Sach dang co trong thu vien.\nNhap so luong muon them: ";
					cin >> add;
					index = ViTriSachTheoISBN(Sach, nS - 1, Sach[nS - 1].isbn);
					Sach[index].amt = Sach[index].amt + add;
					nS--;
					err = fopen_s(&fp, "sach.txt", "wt");
					if (err == 0) {
						GhiDSSach(fp, Sach, nS);
						fclose(fp);
						cout << "DA THEM SACH!\n";
					}
					else {
						cout << "Mo file quan ly sach that bai!\n";
					}
				}
			}

			else if (subChoice == 'c') {
				cout << setw(90) << right << "----- CHINH SUA SACH -----\n\n";
				SACH b;
				NhapISBN(Sach, nS, b.isbn);
				if (b.isbn[0] != 0) {
					err = fopen_s(&fp, "sach.txt", "rt");
					if (err == 0) {
						ChinhSuaSach(fp, Sach, nS, b.isbn);
						fclose(fp);

						err = fopen_s(&fp, "sach.txt", "wt");
						if (err == 0) {
							GhiDSSach(fp, Sach, nS);
							fclose(fp);
							cout << "DA CHINH SUA SACH!\n";
						}
						else {
							cout << "Mo file quan ly sach that bai!\n";
						}
					}
					else {
						cout << "Mo file quan ly sach that bai!\n";
					}
				}
			}

			else if (subChoice == 'd') {
				cout << setw(90) << right << "----- XOA SACH -----\n\n";
				SACH b;
				NhapISBN(Sach, nS, b.isbn);
				if (b.isbn[0] != 0) {
					err = fopen_s(&fp, "sach.txt", "rt");
					if (err == 0) {
						XoaSach(fp, Sach, nS, b.isbn);
						fclose(fp);

						err = fopen_s(&fp, "sach.txt", "wt");
						if (err == 0) {
							GhiDSSach(fp, Sach, nS);
							fclose(fp);
							cout << "DA XOA SACH!\n";
						}
						else {
							cout << "Mo file quan ly sach that bai!\n";
						}
					}
					else {
						cout << "Mo file quan ly sach that bai!\n";
					}
				}
			}

			else if (subChoice == 'e') {
				cout << setw(90) << right << "----- TIM SACH THEO ISBN -----\n\n";
				SACH b;
				NhapISBN(Sach, nS, b.isbn);
				if (b.isbn[0] != 0) {
					int index = ViTriSachTheoISBN(Sach, nS, b.isbn);
					Xuat1Sach(Sach, nS, index);
				}
			}

			else if (subChoice == 'f') {
				cout << setw(90) << right << "----- TIM SACH THEO TEN -----\n\n";
				SACH b;
				bool valid = 1;
				bool retype = 1;
				do {
					if (!valid) {
						cout << "Ten sach khong ton tai! Ban co muon nhap lai? (Co -> chon 1; Khong -> chon 0) ";
						cin >> retype;
						if (!retype) {
							cin.ignore();
							break;
						}
					}
					cout << "Nhap ten sach: ";
					cin.ignore();
					gets_s(b.title);
					valid = 0;
				} while (TimSachTheoTen(Sach, nS, b.title) == -1);

				if (retype) {
					int index = TimSachTheoTen(Sach, nS, b.title);
					Xuat1Sach(Sach, nS, index);
				}
			}

			else {
				cout << "Chuc nang khong co trong danh sach!\n";
			}
		}

		else if (mainChoice == 3) {
			cout << setw(100) << right << "----- LAP PHIEU MUON SACH -----\n\n";
			cout << setw(105) << right << "(Moi doc gia duoc muon toi da 5 cuon sach)\n";
			cout << "DIEN THONG TIN\n";
			char x[MAXCODE];
			err = fopen_s(&fp, "phieusach.txt", "at");
			if (err == 0) {
				DienPhieuMuon(fp, PhieuSach, nP, DocGia, nD, Sach, nS, x);
				fclose(fp);
				if (x[0] != 0) {
					cout << endl << setw(90) << right << "PHIEU MUON SACH\n";
					cout << setw(60) << left << "" << "Ma doc gia: " << x << endl << endl;
					XuatPhieuMuon(PhieuSach, nP, x);
				}
			}
			else {
				cout << "Mo file quan ly muon/tra sach that bai!\n";
			}
		}

		else if (mainChoice == 4) {
			cout << setw(100) << right << "----- LAP PHIEU TRA SACH -----\n\n";
			cout << "DIEN THONG TIN\n";
			char x[MAXCODE];
			DienPhieuTra(PhieuSach, nP, DocGia, nD, Sach, nS, x);
			if (x[0] != 0) {
				cout << endl << setw(90) << right << "PHIEU TRA SACH\n";
				cout << setw(60) << left << "" << "Ma doc gia: " << x << endl << endl;
				XuatPhieuTra(PhieuSach, nP, x);
				err = fopen_s(&fp, "phieusach.txt", "wt");
				if (err == 0) {
					GhiDSPhieu(fp, PhieuSach, nP);
					fclose(fp);
				}
				else {
					cout << "Mo file quan ly muon/tra sach that bai!\n";
				}
				err = fopen_s(&fp, "sach.txt", "wt");
				if (err == 0) {
					GhiDSSach(fp, Sach, nS);
					fclose(fp);
				}
				else {
					cout << "Mo file quan ly sach that bai!\n";
				}
			}
		}

		else if (mainChoice == 5) {
			XuatMenu5();
			cout << "\n\nMoi ban nhap chuc nang cu the: ";
			cin >> subChoice;
			system("CLS");

			if (subChoice == 'a') {
				cout << setw(108) << right << "----- THONG KE SO LUONG SACH TRONG THU VIEN -----\n\n";
				cout << setw(70) << left << "" << "Tong cong: " << DemSoLuongSach(Sach, nS) << " cuon\n";
			}

			else if (subChoice == 'b') {
				cout << setw(108) << right << "----- THONG KE SO LUONG SACH THEO THE LOAI -----\n\n";
				SACH TheLoai[MAXS];
				int nTl = 0;
				ThongKeTheLoai(Sach, nS, TheLoai, nTl);
				cout << setw(63) << left << "" << "Thu vien gom " << nTl << " the loai sach khac nhau\n\n";
				cout << setw(70) << left << "" << "(Don vi: cuon)\n";
				XuatSoLuongSachTheoTheLoai(Sach, nS, TheLoai, nTl);
			}

			else if (subChoice == 'c') {
				cout << setw(103) << right << "----- THONG KE SO LUONG DOC GIA -----\n\n";
				cout << setw(70) << left << "" << "Tong cong: " << nD << " doc gia\n";
			}

			else if (subChoice == 'd') {
				cout << setw(108) << right << "----- THONG KE SO LUONG DOC GIA THEO GIOI TINH -----\n\n";
				cout << setw(70) << left << "" << "(Don vi: doc gia)\n";
				char gender[MAXGENDER] = "Nam";
				cout << setw(70) << left << "" << "- " << "Nam: " << DemDocGiaTheoGioiTinh(DocGia, nD, gender) << endl;
				gender[0] = 'N'; gender[1] = 'u'; gender[2] = 0;
				cout << setw(70) << left << "" << "- " << "Nu: " << DemDocGiaTheoGioiTinh(DocGia, nD, gender) << endl;
			}

			else if (subChoice == 'e') {
				cout << setw(108) << right << "----- THONG KE SO LUONG SACH DANG DUOC MUON -----\n\n";
				cout << setw(70) << left << "" << "Tong cong: " << DemSoSachDuocMuon(PhieuSach, nP) << " cuon\n";
			}

			else if (subChoice == 'f') {
				cout << setw(108) << right << "----- THONG KE DANH SACH DOC GIA BI TRE HAN -----\n\n";
				PHIEUSACH TreHan[MAXP];
				int nTh = 0;
				cout << "Nhap ngay hom nay (Nhap rieng tung gia tri):\n";
				DATE dCur;
				NhapNgay(dCur);
				ThongKeDocGiaTreHan(PhieuSach, nP, dCur, TreHan, nTh);
				cout << setw(65) << left << "" << "Tong cong: " << nTh << " doc gia\n\n";
				XuatDSDocGiaTreHan(TreHan, nTh, DocGia, nD);
			}

			else if (subChoice == 'g') {
				cout << setw(108) << right << "----- THONG KE SO LUONG DOC GIA MUON SACH -----\n\n";
				cout << setw(65) << left << "" << "Tong cong: " << DemSoLuongDocGiaMuonSach(PhieuSach, nP) << " doc gia\n\n";
			}

			else {
				cout << "Chuc nang khong co trong danh sach!\n";
			}
		}

		else if (mainChoice == 6) {
			cout << setw(100) << right << "----- TIM PHIEU MUON SACH -----\n\n";
			char x[MAXCODE];
			NhapMaDocGia(DocGia, nD, x);
			if (x[0] != 0) {
				if (KiemTraDocGiaCoMuonSach(PhieuSach, nP, x)) {
					cout << endl << setw(90) << right << "PHIEU MUON SACH\n";
					cout << setw(60) << left << "" << "Ma doc gia: " << x << endl << endl;
					XuatPhieuMuon(PhieuSach, nP, x);
				}
				else {
					cout << "DOC GIA NAY KHONG MUON SACH!\n";
				}
			}
		}

		else {
			cout << "Chuc nang khong co trong danh sach!\n";
		}
		cout << endl;
		if (!((mainChoice == 1 && subChoice == 'e') || (mainChoice == 1 && subChoice == 'f') || (mainChoice == 2 && subChoice == 'f'))) {
			cin.ignore();
		}
		do {
			cout << "Nhan Enter de tro ve menu chinh ";
		} while (cin.get() != '\n');
	}
	return 0;
}