#include "KiemTra.h"

#include <cctype>

#include "HangSo.h"
#include "XuLiChuoi.h"

using namespace std;

bool KiemTra::chuoiKhongRong(const string& strVao, const string& strTenTruong,
                             string& strKetQua, string& strLoi)
{
    strKetQua = XuLiChuoi::catKhoangTrang(strVao);
    if (strKetQua.empty())
    {
        strLoi = strTenTruong + " khong hop le: khong duoc de trong hoac chi nhap khoang trang.";
        return false;
    }
    if (strKetQua.find('|') != string::npos)
    {
        strLoi = strTenTruong + " khong hop le: khong duoc chua ky tu '|'.";
        return false;
    }
    return true;
}

bool KiemTra::chuoiKhongCoSo(const string& strVao, const string& strTenTruong,
                             string& strKetQua, string& strLoi)
{
    if (!KiemTra::chuoiKhongRong(strVao, strTenTruong, strKetQua, strLoi))
    {
        return false;
    }
    for (size_t iViTri = 0; iViTri < strKetQua.size(); ++iViTri)
    {
        if (isdigit(static_cast<unsigned char>(strKetQua[iViTri])))
        {
            strLoi = strTenTruong + " khong hop le: khong duoc chua chu so.";
            return false;
        }
    }
    return true;
}

bool KiemTra::tenKhachHang(const string& strVao, string& strKetQua, string& strLoi)
{
    if (!KiemTra::chuoiKhongRong(strVao, "Ten khach hang", strKetQua, strLoi))
    {
        return false;
    }
    if (static_cast<int>(strKetQua.size()) < DO_DAI_TEN_TOI_THIEU)
    {
        strLoi = "Ten khach hang khong hop le: phai co it nhat 2 ky tu.";
        return false;
    }
    for (size_t iViTri = 0; iViTri < strKetQua.size(); ++iViTri)
    {
        unsigned char cKyTu = static_cast<unsigned char>(strKetQua[iViTri]);
        if (!isalpha(cKyTu) && cKyTu != ' ')
        {
            strLoi = "Ten khach hang khong hop le: chi duoc gom chu cai va khoang trang "
                     "(khong chua chu so hoac ky tu dac biet).";
            return false;
        }
    }
    return true;
}

bool KiemTra::maHang(const string& strVao, string& strKetQua, string& strLoi)
{
    strKetQua = XuLiChuoi::catKhoangTrang(strVao);
    if (strKetQua.empty())
    {
        strLoi = "Ma hang khong hop le: khong duoc de trong hoac chi nhap khoang trang.";
        return false;
    }
    if (static_cast<int>(strKetQua.size()) != DO_DAI_MA_HANG)
    {
        strLoi = "Ma hang khong hop le: phai gom DUNG 4 ky tu (ban nhap " +
                 to_string(strKetQua.size()) + " ky tu).";
        return false;
    }
    for (size_t iViTri = 0; iViTri < strKetQua.size(); ++iViTri)
    {
        if (!isalnum(static_cast<unsigned char>(strKetQua[iViTri])))
        {
            strLoi = "Ma hang khong hop le: chi duoc gom chu cai va chu so.";
            return false;
        }
    }
    strKetQua = XuLiChuoi::chuyenChuHoa(strKetQua);
    return true;
}

bool KiemTra::soNguyen(const string& strVao, const string& strTenTruong,
                       const long long lNho, const long long lLon,
                       long long& lKetQua, string& strLoi)
{
    string strChuoi = XuLiChuoi::catKhoangTrang(strVao);
    if (strChuoi.empty())
    {
        strLoi = strTenTruong + " khong hop le: khong duoc de trong.";
        return false;
    }
    if (strChuoi[0] == '-')
    {
        strLoi = strTenTruong + " khong hop le: khong duoc nhap so am.";
        return false;
    }
    if (!XuLiChuoi::laSoNguyenKhongAm(strChuoi) ||
        static_cast<int>(strChuoi.size()) > SO_CHU_SO_TOI_DA)
    {
        strLoi = strTenTruong + " khong hop le: phai la so nguyen khong am "
                                "(khong chua chu cai, dau cach hoac ky tu dac biet).";
        return false;
    }
    long long lGiaTri = stoll(strChuoi);
    if (lGiaTri < lNho || lGiaTri > lLon)
    {
        strLoi = strTenTruong + " khong hop le: phai nam trong khoang tu " +
                 to_string(lNho) + " den " + to_string(lLon) + ".";
        return false;
    }
    lKetQua = lGiaTri;
    return true;
}

bool KiemTra::giaBan(const string& strVao, long long& lKetQua, string& strLoi)
{
    if (!KiemTra::soNguyen(strVao, "Gia ban", GIA_BAN_TOI_THIEU, GIA_BAN_TOI_DA, lKetQua, strLoi))
    {
        return false;
    }
    if (lKetQua % BOI_SO_GIA_BAN != 0)
    {
        strLoi = "Gia ban khong hop le: phai la boi so cua 1.000 VND (vd: 50000, 150000).";
        return false;
    }
    return true;
}

bool KiemTra::soDienThoai(const string& strVao, string& strKetQua, string& strLoi)
{
    strKetQua = XuLiChuoi::catKhoangTrang(strVao);
    if (strKetQua.empty())
    {
        strLoi = "So dien thoai khong hop le: khong duoc de trong.";
        return false;
    }
    if (!XuLiChuoi::laSoNguyenKhongAm(strKetQua))
    {
        strLoi = "So dien thoai khong hop le: chi duoc gom cac chu so 0-9.";
        return false;
    }
    if (static_cast<int>(strKetQua.size()) != DO_DAI_SO_DIEN_THOAI)
    {
        strLoi = "So dien thoai khong hop le: phai gom DUNG 10 chu so (ban nhap " +
                 to_string(strKetQua.size()) + " chu so).";
        return false;
    }
    if (strKetQua[0] != '0')
    {
        strLoi = "So dien thoai khong hop le: phai bat dau bang chu so 0.";
        return false;
    }
    return true;
}

bool KiemTra::ngayNhapKho(const string& strVao, NgayThang& ngayKetQua, string& strLoi)
{
    string strChuoi = XuLiChuoi::catKhoangTrang(strVao);
    if (strChuoi.empty())
    {
        strLoi = "Ngay nhap kho khong hop le: khong duoc de trong.";
        return false;
    }
    if (!NgayThang::taoTuChuoi(strChuoi, ngayKetQua))
    {
        strLoi = "Ngay nhap kho khong hop le: phai dung dinh dang dd/mm/yyyy "
                 "va la ngay ton tai trong lich (vd: 15/10/2026).";
        return false;
    }
    if (ngayKetQua.lonHon(NgayThang::homNay()))
    {
        strLoi = "Ngay nhap kho khong hop le: khong duoc lon hon ngay hien tai (" +
                 NgayThang::homNay().chuyenThanhChuoi() + ").";
        return false;
    }
    return true;
}
