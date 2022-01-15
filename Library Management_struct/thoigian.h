#pragma once

struct DATE {
	int d, m, y;
};
void ChuyenThanhChuoiKyTuNgay(char dateCh[11], DATE date);
bool KiemTraNamNhuan(DATE d);
int SoNgayTrongThang(DATE d);
void NhapNgay(DATE& d);
void CongNNgay(DATE& d, int n);
bool SoSanhNgayNhoHon(DATE d1, DATE d2);
int TinhKhoangCach2Ngay(DATE d1, DATE d2);
void TachChuoiKiTuNgay(char date[11], DATE& d);
/*
bool KiemTraNamNhuan(int y);
int SoNgayTrongThang(int m, int y);
void ChuyenThanhChuoiKyTuNgay(char dateCh[11], int d, int m, int y);
void NhapNgay(int& d, int& m, int& y);
void CongNNgay(int& d, int& m, int& y, int n);
bool SoSanhNgayNhoHon(int d1, int m1, int y1, int d2, int m2, int y2);
int TinhKhoangCach2Ngay(int d1, int m1, int y1, int d2, int m2, int y2);
void TachChuoiKiTuNgay(string date, int& d, int& m, int& y);
*/