#include "HangHoa.h"

#include <vector>

#include "HangSo.h"
#include "KiemTra.h"
#include "XuLiChuoi.h"

using namespace std;

HangHoa::HangHoa() : _lGiaBan(0), _iSoLuong(0)
{
}

HangHoa::HangHoa(const string& strMaHang)
    : _strMaHang(strMaHang), _lGiaBan(0), _iSoLuong(0)
{
}

HangHoa::HangHoa(const string& strMaHang, const string& strTenHang,
                 const string& strNoiSanXuat, const string& strMauSac,
                 const long long lGiaBan, const NgayThang& ngayNhapKho,
                 const int iSoLuong)
    : _strMaHang(strMaHang), _strTenHang(strTenHang), _strNoiSanXuat(strNoiSanXuat),
      _strMauSac(strMauSac), _lGiaBan(lGiaBan), _ngayNhapKho(ngayNhapKho),
      _iSoLuong(iSoLuong)
{
}

const string& HangHoa::layMa() const
{
    return this->_strMaHang;
}

const string& HangHoa::layTen() const
{
    return this->_strTenHang;
}

const string& HangHoa::layNoiSanXuat() const
{
    return this->_strNoiSanXuat;
}

const string& HangHoa::layMauSac() const
{
    return this->_strMauSac;
}

long long HangHoa::layGiaBan() const
{
    return this->_lGiaBan;
}

const NgayThang& HangHoa::layNgayNhapKho() const
{
    return this->_ngayNhapKho;
}

int HangHoa::laySoLuong() const
{
    return this->_iSoLuong;
}

void HangHoa::datSoLuong(const int iSoLuong)
{
    this->_iSoLuong = iSoLuong;
}

bool HangHoa::operator<(const HangHoa& khac) const
{
    return (this->_strMaHang < khac._strMaHang);
}

bool HangHoa::operator>(const HangHoa& khac) const
{
    return (this->_strMaHang > khac._strMaHang);
}

string HangHoa::chuyenThanhChuoi() const
{
    return this->_strMaHang + "|" + this->_strTenHang + "|" + this->_strNoiSanXuat + "|" +
           this->_strMauSac + "|" + to_string(this->_lGiaBan) + "|" +
           this->_ngayNhapKho.chuyenThanhChuoi() + "|" + to_string(this->_iSoLuong);
}

bool HangHoa::taoTuChuoi(const string& strDong, HangHoa& ketQua)
{
    vector<string> vecPhan = XuLiChuoi::tachChuoi(strDong, '|');
    if (static_cast<int>(vecPhan.size()) != SO_TRUONG_HANG_HOA)
    {
        return false;
    }

    string strLoi = "";
    string strMa = "";
    if (!KiemTra::maHang(vecPhan[0], strMa, strLoi))
    {
        return false;
    }

    string strTen = "";
    if (!KiemTra::chuoiKhongRong(vecPhan[1], "Ten hang", strTen, strLoi))
    {
        return false;
    }

    string strNoi = "";
    if (!KiemTra::chuoiKhongCoSo(vecPhan[2], "Noi san xuat", strNoi, strLoi))
    {
        return false;
    }

    string strMau = "";
    if (!KiemTra::chuoiKhongCoSo(vecPhan[3], "Mau sac", strMau, strLoi))
    {
        return false;
    }

    long long lGia = 0;
    if (!KiemTra::giaBan(vecPhan[4], lGia, strLoi))
    {
        return false;
    }

    NgayThang ngayNhap;
    if (!KiemTra::ngayNhapKho(vecPhan[5], ngayNhap, strLoi))
    {
        return false;
    }

    long long lSoLuong = 0;
    if (!KiemTra::soNguyen(vecPhan[6], "So luong", 0, SO_LUONG_TOI_DA, lSoLuong, strLoi))
    {
        return false;
    }

    ketQua = HangHoa(strMa, strTen, strNoi, strMau, lGia, ngayNhap, static_cast<int>(lSoLuong));
    return true;
}

bool HangHoa::dungTruocTheoGiaTang(const HangHoa* pTrai, const HangHoa* pPhai)
{
    if (pTrai == NULL || pPhai == NULL)
    {
        return false;
    }
    if (pTrai->_lGiaBan != pPhai->_lGiaBan)
    {
        return (pTrai->_lGiaBan < pPhai->_lGiaBan);
    }
    return (pTrai->_strMaHang < pPhai->_strMaHang);
}

bool HangHoa::dungTruocTheoGiaGiam(const HangHoa* pTrai, const HangHoa* pPhai)
{
    if (pTrai == NULL || pPhai == NULL)
    {
        return false;
    }
    if (pTrai->_lGiaBan != pPhai->_lGiaBan)
    {
        return (pTrai->_lGiaBan > pPhai->_lGiaBan);
    }
    return (pTrai->_strMaHang < pPhai->_strMaHang);
}

bool HangHoa::dungTruocTheoTen(const HangHoa* pTrai, const HangHoa* pPhai)
{
    if (pTrai == NULL || pPhai == NULL)
    {
        return false;
    }
    string strTenTrai = XuLiChuoi::chuyenChuThuong(pTrai->_strTenHang);
    string strTenPhai = XuLiChuoi::chuyenChuThuong(pPhai->_strTenHang);
    if (strTenTrai != strTenPhai)
    {
        return (strTenTrai < strTenPhai);
    }
    return (pTrai->_strMaHang < pPhai->_strMaHang);
}

bool HangHoa::khopTenThuong(const HangHoa* pHang, const string& strTuKhoaThuong)
{
    if (pHang == NULL)
    {
        return false;
    }
    string strTenThuong = XuLiChuoi::chuyenChuThuong(pHang->_strTenHang);
    return (strTenThuong.find(strTuKhoaThuong) != string::npos);
}
