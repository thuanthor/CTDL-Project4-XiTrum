#ifndef NOMINMAX
#define NOMINMAX
#endif

#include "GiaoDien.h"

#include <conio.h>
#include <io.h>
#include <windows.h>

#include <algorithm>
#include <cstdio>
#include <iostream>

#include "HangSo.h"

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

using namespace std;

void GiaoDien::khoiTao()
{
    SetConsoleOutputCP(MA_TRANG_UTF8);
    HANDLE hDauRa = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwCheDo = 0;
    if (GetConsoleMode(hDauRa, &dwCheDo))
    {
        if (SetConsoleMode(hDauRa, dwCheDo | ENABLE_VIRTUAL_TERMINAL_PROCESSING))
        {
            GiaoDien::mauHoatDong() = (_isatty(_fileno(stdout)) != 0);
        }
    }
}

bool GiaoDien::laBanPhimTuongTac()
{
    return (_isatty(_fileno(stdin)) != 0);
}

void GiaoDien::datMau(const MauSac eMau)
{
    if (!GiaoDien::mauHoatDong())
    {
        return;
    }
    static const char* MA_MAU_ANSI[] = {
        "\033[0m",    "\033[1;31m", "\033[1;32m", "\033[1;33m", "\033[1;34m",
        "\033[1;35m", "\033[1;36m", "\033[1;37m", "\033[0;90m", "\033[0;30m"
    };
    cout << MA_MAU_ANSI[eMau];
}

void GiaoDien::datMauNen(const MauSac eMauChu, const MauSac eMauNen)
{
    if (!GiaoDien::mauHoatDong())
    {
        return;
    }
    string strDoDam = (eMauChu == DEN) ? "22;" : "1;";
    cout << "\033[" << strDoDam << "3" << GiaoDien::maAnsi(eMauChu)
         << ";4" << GiaoDien::maAnsi(eMauNen) << "m";
}

void GiaoDien::xoaManHinh()
{
    if (GiaoDien::mauHoatDong())
    {
        cout << "\033[2J\033[H";
    }
    else
    {
        cout << "\n";
    }
}

void GiaoDien::inBanner()
{
    static const MauSac MAU_HANG_LOGO[SO_DONG_LOGO] = {
        XANH_NGOC, XANH_NGOC, XANH_DUONG, TIM, TIM
    };
    const string strTenShop = "LANG XI TRUM SHOP";
    cout << "\n";
    GiaoDien::inVien(0, RONG_BANNER, XANH_NGOC);
    GiaoDien::inDongKhung("", RONG_BANNER, XANH_NGOC, MAC_DINH, true);
    for (int iHang = 0; iHang < SO_DONG_LOGO; ++iHang)
    {
        string strDong = "";
        for (size_t iViTri = 0; iViTri < strTenShop.size(); ++iViTri)
        {
            if (iViTri > 0)
            {
                strDong += " ";
            }
            strDong += GiaoDien::veChuLogo(strTenShop[iViTri], iHang);
        }
        GiaoDien::inDongKhung(strDong, RONG_BANNER, XANH_NGOC, MAU_HANG_LOGO[iHang], true);
    }
    GiaoDien::inDongKhung("", RONG_BANNER, XANH_NGOC, MAC_DINH, true);
    GiaoDien::inDongKhung("CHUONG TRINH QUAN LI BAN HANG ONLINE", RONG_BANNER, XANH_NGOC, VANG, true);
    GiaoDien::inDongKhung("Website thuong mai dien tu", RONG_BANNER, XANH_NGOC, TRANG, true);
    GiaoDien::inDongKhung("Mon Cau truc du lieu - Project 4 (PRO_CTDL_4)", RONG_BANNER, XANH_NGOC, XANH_LA, true);
    GiaoDien::inDongKhung("", RONG_BANNER, XANH_NGOC, MAC_DINH, true);
    GiaoDien::inVien(2, RONG_BANNER, XANH_NGOC);
}

void GiaoDien::inTieuDe(const string& strTieuDe, const MauSac eMau)
{
    int iRong = max(RONG_MENU_TOI_THIEU, GiaoDien::doRongHienThi(strTieuDe) + RONG_TIEU_DE_DEM);
    cout << "\n";
    GiaoDien::inVien(0, iRong, eMau);
    GiaoDien::inDongKhung(strTieuDe, iRong, eMau, VANG, true);
    GiaoDien::inVien(2, iRong, eMau);
}

void GiaoDien::inTieuDeDangNhap()
{
    cout << "\n";
    GiaoDien::datMau(VANG);
    cout << "  *******************************************\n";
    cout << "  *";
    GiaoDien::datMau(XANH_NGOC);
    cout << "            DANG NHAP HE THONG           ";
    GiaoDien::datMau(VANG);
    cout << "*\n";
    cout << "  *******************************************\n";
    GiaoDien::datMau(MAC_DINH);
}

void GiaoDien::inMenu(const string& strTieuDe, const vector<string>& vecMuc,
                      const string& strMucThoat)
{
    int iRong = RONG_MENU_TOI_THIEU;
    int iRongTieuDe = GiaoDien::doRongHienThi(strTieuDe) + RONG_TIEU_DE_DEM;
    if (iRongTieuDe > iRong)
    {
        iRong = iRongTieuDe;
    }
    for (size_t iChiSo = 0; iChiSo < vecMuc.size(); ++iChiSo)
    {
        int iRongMuc = GiaoDien::doRongHienThi(vecMuc[iChiSo]) + RONG_MUC_MENU_DEM;
        if (iRongMuc > iRong)
        {
            iRong = iRongMuc;
        }
    }
    int iRongThoat = GiaoDien::doRongHienThi(strMucThoat) + RONG_MUC_MENU_DEM;
    if (iRongThoat > iRong)
    {
        iRong = iRongThoat;
    }

    cout << "\n";
    GiaoDien::inVien(0, iRong, XANH_NGOC);
    GiaoDien::datMau(XANH_NGOC);
    cout << "  " << GiaoDien::kyTuKhung(5);
    GiaoDien::datMauNen(TRANG, XANH_DUONG);
    cout << GiaoDien::canGiua(strTieuDe, iRong);
    GiaoDien::datMau(XANH_NGOC);
    cout << GiaoDien::kyTuKhung(5);
    GiaoDien::datMau(MAC_DINH);
    cout << "\n";
    GiaoDien::inVien(1, iRong, XANH_NGOC);
    for (size_t iChiSo = 0; iChiSo < vecMuc.size(); ++iChiSo)
    {
        GiaoDien::inMucMenu(to_string(iChiSo + 1), vecMuc[iChiSo], iRong, VANG, TRANG);
    }
    GiaoDien::inMucMenu("0", strMucThoat, iRong, DO, DO);
    GiaoDien::inVien(2, iRong, XANH_NGOC);
}

void GiaoDien::inBang(const vector<CotBang>& vecCot,
                      const vector<vector<string> >& vecHang,
                      const vector<MauSac>& vecMauHang)
{
    const int KY_TU_DOC = 10;
    GiaoDien::inVienBang(vecCot, 0);
    GiaoDien::datMau(XANH_NGOC);
    cout << "  " << GiaoDien::kyTuBang(KY_TU_DOC);
    for (size_t iCot = 0; iCot < vecCot.size(); ++iCot)
    {
        GiaoDien::datMauNen(TRANG, XANH_DUONG);
        cout << " " << GiaoDien::vuaO(vecCot[iCot].layTieuDe(), vecCot[iCot].layDoRong(),
                                      vecCot[iCot].laCanPhai()) << " ";
        GiaoDien::datMau(MAC_DINH);
        GiaoDien::datMau(XANH_NGOC);
        cout << GiaoDien::kyTuBang(KY_TU_DOC);
    }
    GiaoDien::datMau(MAC_DINH);
    cout << "\n";
    GiaoDien::inVienBang(vecCot, 1);

    for (size_t iHang = 0; iHang < vecHang.size(); ++iHang)
    {
        MauSac eMauChu = (iHang < vecMauHang.size()) ? vecMauHang[iHang] : MAC_DINH;
        GiaoDien::datMau(XANH_NGOC);
        cout << "  " << GiaoDien::kyTuBang(KY_TU_DOC);
        for (size_t iCot = 0; iCot < vecCot.size(); ++iCot)
        {
            string strO = (iCot < vecHang[iHang].size()) ? vecHang[iHang][iCot] : "";
            GiaoDien::datMau(eMauChu);
            cout << " " << GiaoDien::vuaO(strO, vecCot[iCot].layDoRong(),
                                          vecCot[iCot].laCanPhai()) << " ";
            GiaoDien::datMau(XANH_NGOC);
            cout << GiaoDien::kyTuBang(KY_TU_DOC);
        }
        GiaoDien::datMau(MAC_DINH);
        cout << "\n";
    }
    GiaoDien::inVienBang(vecCot, 2);
}

void GiaoDien::inThongTin(const string& strTieuDe,
                          const vector<pair<string, string> >& vecTruong,
                          const MauSac eMau)
{
    const int DO_RONG_PHAN_CACH = 6;
    const int BU_LE_PHAI = 4;
    int iRongNhan = 0;
    for (size_t iChiSo = 0; iChiSo < vecTruong.size(); ++iChiSo)
    {
        iRongNhan = max(iRongNhan, GiaoDien::doRongHienThi(vecTruong[iChiSo].first));
    }
    int iRong = max(RONG_MENU_TOI_THIEU, GiaoDien::doRongHienThi(strTieuDe) + RONG_TIEU_DE_DEM);
    for (size_t iChiSo = 0; iChiSo < vecTruong.size(); ++iChiSo)
    {
        int iRongDong = iRongNhan + DO_RONG_PHAN_CACH + GiaoDien::doRongHienThi(vecTruong[iChiSo].second);
        iRong = max(iRong, iRongDong);
    }

    GiaoDien::inVien(0, iRong, eMau);
    GiaoDien::datMau(eMau);
    cout << "  " << GiaoDien::kyTuKhung(5);
    GiaoDien::datMauNen(TRANG, XANH_DUONG);
    cout << GiaoDien::canGiua(strTieuDe, iRong);
    GiaoDien::datMau(eMau);
    cout << GiaoDien::kyTuKhung(5);
    GiaoDien::datMau(MAC_DINH);
    cout << "\n";
    GiaoDien::inVien(1, iRong, eMau);

    for (size_t iChiSo = 0; iChiSo < vecTruong.size(); ++iChiSo)
    {
        const string& strNhan = vecTruong[iChiSo].first;
        const string& strGiaTri = vecTruong[iChiSo].second;
        GiaoDien::datMau(eMau);
        cout << "  " << GiaoDien::kyTuKhung(5) << " ";
        GiaoDien::datMau(VANG);
        cout << strNhan << GiaoDien::khoangTrang(iRongNhan - GiaoDien::doRongHienThi(strNhan));
        GiaoDien::datMau(XAM);
        cout << " : ";
        GiaoDien::datMau(TRANG);
        cout << strGiaTri << GiaoDien::khoangTrang(iRong - iRongNhan - BU_LE_PHAI -
                                                   GiaoDien::doRongHienThi(strGiaTri));
        GiaoDien::datMau(eMau);
        cout << GiaoDien::kyTuKhung(5);
        GiaoDien::datMau(MAC_DINH);
        cout << "\n";
    }
    GiaoDien::inVien(2, iRong, eMau);
}

void GiaoDien::inDongNoiBat(const string& strNhan, const string& strGiaTri)
{
    GiaoDien::datMau(VANG);
    cout << "  " << strNhan << " ";
    GiaoDien::datMau(XANH_LA);
    cout << strGiaTri << "\n";
    GiaoDien::datMau(MAC_DINH);
}

void GiaoDien::inDong(const string& strNoiDung, const MauSac eMau)
{
    GiaoDien::datMau(eMau);
    cout << strNoiDung << "\n";
    GiaoDien::datMau(MAC_DINH);
}

void GiaoDien::thongBaoLoi(const string& strNoiDung)
{
    GiaoDien::inHuyHieu("LOI", TRANG, DO, strNoiDung, DO);
}

void GiaoDien::thongBaoThanhCong(const string& strNoiDung)
{
    GiaoDien::inHuyHieu("OK", TRANG, XANH_LA, strNoiDung, XANH_LA);
}

void GiaoDien::thongBaoThongTin(const string& strNoiDung)
{
    GiaoDien::inHuyHieu("!", DEN, VANG, strNoiDung, VANG);
}

bool GiaoDien::hetDuLieuVao()
{
    return cin.eof();
}

string GiaoDien::nhapDong(const string& strNhan)
{
    GiaoDien::datMau(XANH_NGOC);
    cout << strNhan;
    GiaoDien::datMau(MAC_DINH);
    cout << flush;
    string strDong = "";
    if (!getline(cin, strDong))
    {
        strDong.clear();
    }
    if (!strDong.empty() && strDong[strDong.size() - 1] == '\r')
    {
        strDong.erase(strDong.size() - 1);
    }
    return strDong;
}

bool GiaoDien::hoiCoKhong(const string& strCauHoi)
{
    while (true)
    {
        string strTraLoi = GiaoDien::nhapDong(strCauHoi);
        if (GiaoDien::hetDuLieuVao())
        {
            return false;
        }
        if (strTraLoi == "c" || strTraLoi == "C")
        {
            return true;
        }
        if (strTraLoi == "k" || strTraLoi == "K")
        {
            return false;
        }
        GiaoDien::thongBaoLoi("Khong hop le: chi duoc nhap 'c' (co) hoac 'k' (khong).");
    }
}

void GiaoDien::tamDung(const string& strNhan)
{
    GiaoDien::datMau(XAM);
    cout << "\n  " << strNhan << flush;
    GiaoDien::datMau(MAC_DINH);
    string strBoQua = "";
    getline(cin, strBoQua);
}

bool GiaoDien::nhapDangNhap(const string& strNhan, const bool bAnMatKhau, string& strKetQua)
{
    GiaoDien::datMau(XANH_NGOC);
    cout << strNhan;
    GiaoDien::datMau(MAC_DINH);
    cout << flush;
    strKetQua.clear();

    if (!GiaoDien::laBanPhimTuongTac())
    {
        if (!getline(cin, strKetQua))
        {
            return false;
        }
        if (!strKetQua.empty() && strKetQua[strKetQua.size() - 1] == '\r')
        {
            strKetQua.erase(strKetQua.size() - 1);
        }
        if (strKetQua == "ESC")
        {
            return false;
        }
        return true;
    }

    while (true)
    {
        int iPhim = _getch();
        if (iPhim == PHIM_DAC_BIET_0 || iPhim == PHIM_DAC_BIET_224)
        {
            _getch();
            continue;
        }
        if (iPhim == PHIM_ESC || iPhim == PHIM_CTRL_C)
        {
            cout << "\n";
            return false;
        }
        if (iPhim == PHIM_ENTER_CR || iPhim == PHIM_ENTER_LF)
        {
            cout << "\n";
            return true;
        }
        if (iPhim == PHIM_BACKSPACE)
        {
            if (!strKetQua.empty())
            {
                strKetQua.erase(strKetQua.size() - 1);
                cout << "\b \b" << flush;
            }
            continue;
        }
        if (iPhim >= KY_TU_IN_DUOC_DAU && iPhim <= KY_TU_IN_DUOC_CUOI)
        {
            char cKyTu = static_cast<char>(iPhim);
            strKetQua += cKyTu;
            cout << (bAnMatKhau ? '*' : cKyTu) << flush;
        }
    }
}

bool& GiaoDien::mauHoatDong()
{
    static bool bHoatDong = false;
    return bHoatDong;
}

int GiaoDien::maAnsi(const MauSac eMau)
{
    static const int BANG_MA_ANSI[] = {7, 1, 2, 3, 4, 5, 6, 7, 7, 0};
    return BANG_MA_ANSI[eMau];
}

bool GiaoDien::dungKhungUnicode()
{
    return true;
}

string GiaoDien::khoangTrang(const int iSoKyTu)
{
    if (iSoKyTu <= 0)
    {
        return "";
    }
    return string(static_cast<size_t>(iSoKyTu), ' ');
}

string GiaoDien::lapChuoi(const string& strMau, const int iSoLan)
{
    string strKetQua = "";
    for (int iDem = 0; iDem < iSoLan; ++iDem)
    {
        strKetQua += strMau;
    }
    return strKetQua;
}

int GiaoDien::doRongHienThi(const string& strChuoi)
{
    const unsigned char MAT_NA_UTF8 = 0xC0;
    const unsigned char TIEP_NOI_UTF8 = 0x80;
    int iDem = 0;
    for (size_t iViTri = 0; iViTri < strChuoi.size(); ++iViTri)
    {
        if ((static_cast<unsigned char>(strChuoi[iViTri]) & MAT_NA_UTF8) != TIEP_NOI_UTF8)
        {
            ++iDem;
        }
    }
    return iDem;
}

string GiaoDien::canGiua(const string& strChuoi, const int iRong)
{
    int iDoRong = GiaoDien::doRongHienThi(strChuoi);
    if (iDoRong >= iRong)
    {
        return strChuoi;
    }
    int iTrai = (iRong - iDoRong) / 2;
    return GiaoDien::khoangTrang(iTrai) + strChuoi + GiaoDien::khoangTrang(iRong - iDoRong - iTrai);
}

string GiaoDien::vuaO(const string& strChuoi, const int iRong, const bool bCanPhai)
{
    const unsigned char MAT_NA_UTF8 = 0xC0;
    const unsigned char TIEP_NOI_UTF8 = 0x80;
    string strCat = strChuoi;
    if (GiaoDien::doRongHienThi(strChuoi) > iRong)
    {
        strCat.clear();
        int iDem = 0;
        size_t iViTri = 0;
        while (iViTri < strChuoi.size() && iDem < iRong - 1)
        {
            size_t iSoByte = 1;
            while (iViTri + iSoByte < strChuoi.size() &&
                   (static_cast<unsigned char>(strChuoi[iViTri + iSoByte]) & MAT_NA_UTF8) == TIEP_NOI_UTF8)
            {
                ++iSoByte;
            }
            strCat.append(strChuoi, iViTri, iSoByte);
            iViTri += iSoByte;
            ++iDem;
        }
        strCat += ".";
    }
    string strDemKhoang = GiaoDien::khoangTrang(iRong - GiaoDien::doRongHienThi(strCat));
    return bCanPhai ? (strDemKhoang + strCat) : (strCat + strDemKhoang);
}

string GiaoDien::kyTuKhung(const int iLoai)
{
    static const char* KHUNG_UNICODE[] = {
        "\xE2\x95\x94", "\xE2\x95\x97", "\xE2\x95\x9A", "\xE2\x95\x9D",
        "\xE2\x95\x90", "\xE2\x95\x91", "\xE2\x95\xA0", "\xE2\x95\xA3"
    };
    static const char* KHUNG_ASCII[] = {"+", "+", "+", "+", "-", "|", "+", "+"};
    return GiaoDien::dungKhungUnicode() ? KHUNG_UNICODE[iLoai] : KHUNG_ASCII[iLoai];
}

string GiaoDien::kyTuBang(const int iLoai)
{
    static const char* BANG_UNICODE[] = {
        "\xE2\x94\x8C", "\xE2\x94\xAC", "\xE2\x94\x90", "\xE2\x94\x9C",
        "\xE2\x94\xBC", "\xE2\x94\xA4", "\xE2\x94\x94", "\xE2\x94\xB4",
        "\xE2\x94\x98", "\xE2\x94\x80", "\xE2\x94\x82"
    };
    static const char* BANG_ASCII[] = {"+", "+", "+", "+", "+", "+", "+", "+", "+", "-", "|"};
    return GiaoDien::dungKhungUnicode() ? BANG_UNICODE[iLoai] : BANG_ASCII[iLoai];
}

void GiaoDien::inVien(const int iViTri, const int iRong, const MauSac eMau)
{
    string strTrai = GiaoDien::kyTuKhung(iViTri == 0 ? 0 : (iViTri == 1 ? 6 : 2));
    string strPhai = GiaoDien::kyTuKhung(iViTri == 0 ? 1 : (iViTri == 1 ? 7 : 3));
    GiaoDien::datMau(eMau);
    cout << "  " << strTrai << GiaoDien::lapChuoi(GiaoDien::kyTuKhung(4), iRong) << strPhai << "\n";
    GiaoDien::datMau(MAC_DINH);
}

void GiaoDien::inDongKhung(const string& strNoiDung, const int iRong,
                           const MauSac eMauKhung, const MauSac eMauChu, const bool bGiua)
{
    GiaoDien::datMau(eMauKhung);
    cout << "  " << GiaoDien::kyTuKhung(5);
    GiaoDien::datMau(eMauChu);
    if (bGiua)
    {
        cout << GiaoDien::canGiua(strNoiDung, iRong);
    }
    else
    {
        string strDong = " " + strNoiDung;
        cout << strDong << GiaoDien::khoangTrang(iRong - GiaoDien::doRongHienThi(strDong));
    }
    GiaoDien::datMau(eMauKhung);
    cout << GiaoDien::kyTuKhung(5);
    GiaoDien::datMau(MAC_DINH);
    cout << "\n";
}

void GiaoDien::inMucMenu(const string& strSo, const string& strChu, const int iRong,
                         const MauSac eMauSo, const MauSac eMauChu)
{
    GiaoDien::datMau(XANH_NGOC);
    cout << "  " << GiaoDien::kyTuKhung(5);
    GiaoDien::datMau(eMauSo);
    cout << "  [" << strSo << "] ";
    GiaoDien::datMau(eMauChu);
    cout << strChu << GiaoDien::khoangTrang(iRong - RONG_NHAN_MENU - GiaoDien::doRongHienThi(strChu));
    GiaoDien::datMau(XANH_NGOC);
    cout << GiaoDien::kyTuKhung(5);
    GiaoDien::datMau(MAC_DINH);
    cout << "\n";
}

void GiaoDien::inVienBang(const vector<CotBang>& vecCot, const int iViTri)
{
    const int KY_TU_NGANG = 9;
    int iTrai = (iViTri == 0) ? 0 : ((iViTri == 1) ? 3 : 6);
    int iGiua = (iViTri == 0) ? 1 : ((iViTri == 1) ? 4 : 7);
    int iPhai = (iViTri == 0) ? 2 : ((iViTri == 1) ? 5 : 8);
    GiaoDien::datMau(XANH_NGOC);
    cout << "  " << GiaoDien::kyTuBang(iTrai);
    for (size_t iCot = 0; iCot < vecCot.size(); ++iCot)
    {
        int iKyTuNoi = (iCot + 1 == vecCot.size()) ? iPhai : iGiua;
        cout << GiaoDien::lapChuoi(GiaoDien::kyTuBang(KY_TU_NGANG), vecCot[iCot].layDoRong() + 2)
             << GiaoDien::kyTuBang(iKyTuNoi);
    }
    GiaoDien::datMau(MAC_DINH);
    cout << "\n";
}

void GiaoDien::inHuyHieu(const string& strNhan, const MauSac eMauChuNhan,
                         const MauSac eNenNhan, const string& strNoiDung,
                         const MauSac eMauNoiDung)
{
    cout << "  ";
    if (GiaoDien::mauHoatDong())
    {
        GiaoDien::datMauNen(eMauChuNhan, eNenNhan);
        cout << " " << strNhan << " ";
        GiaoDien::datMau(MAC_DINH);
    }
    else
    {
        cout << "[" << strNhan << "]";
    }
    cout << " ";
    GiaoDien::datMau(eMauNoiDung);
    cout << strNoiDung << "\n";
    GiaoDien::datMau(MAC_DINH);
}

string GiaoDien::veChuLogo(const char cKyTu, const int iHang)
{
    static const char* const CHU_S[] = {"###", "#  ", "###", "  #", "###"};
    static const char* const CHU_H[] = {"# #", "# #", "###", "# #", "# #"};
    static const char* const CHU_O[] = {"###", "# #", "# #", "# #", "###"};
    static const char* const CHU_P[] = {"###", "# #", "###", "#  ", "#  "};
    static const char* const CHU_N[] = {"#  #", "## #", "# ##", "#  #", "#  #"};
    static const char* const CHU_L[] = {"#  ", "#  ", "#  ", "#  ", "###"};
    static const char* const CHU_I[] = {"###", " # ", " # ", " # ", "###"};
    static const char* const CHU_E[] = {"###", "#  ", "###", "#  ", "###"};
    static const char* const CHU_A[] = {" # ", "# #", "###", "# #", "# #"};
    static const char* const CHU_G[] = {" ###", "#   ", "# ##", "#  #", " ###"};
    static const char* const CHU_X[] = {"# #", "# #", " # ", "# #", "# #"};
    static const char* const CHU_T[] = {"###", " # ", " # ", " # ", " # "};
    static const char* const CHU_R[] = {"###", "# #", "###", "## ", "# #"};
    static const char* const CHU_U[] = {"# #", "# #", "# #", "# #", "###"};
    static const char* const CHU_M[] = {"#   #", "## ##", "# # #", "#   #", "#   #"};
    static const char* const KHOANG_CACH[] = {"  ", "  ", "  ", "  ", "  "};

    const char* const* pMau = KHOANG_CACH;
    switch (cKyTu)
    {
        case 'S':
            pMau = CHU_S;
            break;
        case 'H':
            pMau = CHU_H;
            break;
        case 'O':
            pMau = CHU_O;
            break;
        case 'P':
            pMau = CHU_P;
            break;
        case 'N':
            pMau = CHU_N;
            break;
        case 'L':
            pMau = CHU_L;
            break;
        case 'I':
            pMau = CHU_I;
            break;
        case 'E':
            pMau = CHU_E;
            break;
        case 'A':
            pMau = CHU_A;
            break;
        case 'G':
            pMau = CHU_G;
            break;
        case 'X':
            pMau = CHU_X;
            break;
        case 'T':
            pMau = CHU_T;
            break;
        case 'R':
            pMau = CHU_R;
            break;
        case 'U':
            pMau = CHU_U;
            break;
        case 'M':
            pMau = CHU_M;
            break;
        default:
            break;
    }

    string strKetQua = "";
    for (const char* pConTro = pMau[iHang]; *pConTro != '\0'; ++pConTro)
    {
        if (*pConTro == '#')
        {
            strKetQua += GiaoDien::dungKhungUnicode() ? "\xE2\x96\x88" : "#";
        }
        else
        {
            strKetQua += ' ';
        }
    }
    return strKetQua;
}
