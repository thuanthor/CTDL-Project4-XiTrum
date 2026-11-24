#include "DonHang.h"

#include <vector>

#include "HangSo.h"
#include "KiemTra.h"
#include "XuLiChuoi.h"

using namespace std;

DonHang::DonHang() : _iSoThuTu(0), _lTongTien(0)
{
}

DonHang::DonHang(const int iSoThuTu, const string& strTenKhach,
                 const string& strDiaChi, const string& strSoDienThoai,
                 const NgayThang& ngayDat)
    : _iSoThuTu(iSoThuTu), _strTenKhach(strTenKhach), _strDiaChi(strDiaChi),
      _strSoDienThoai(strSoDienThoai), _ngayDat(ngayDat), _lTongTien(0)
{
}

int DonHang::laySoThuTu() const
{
    return this->_iSoThuTu;
}

const string& DonHang::layTenKhach() const
{
    return this->_strTenKhach;
}

const string& DonHang::layDiaChi() const
{
    return this->_strDiaChi;
}

const string& DonHang::laySoDienThoai() const
{
    return this->_strSoDienThoai;
}

const NgayThang& DonHang::layNgayDat() const
{
    return this->_ngayDat;
}

long long DonHang::layTongTien() const
{
    return this->_lTongTien;
}

const DanhSachLienKet<MucDonHang>& DonHang::layCacMuc() const
{
    return this->_cacMuc;
}

void DonHang::themMuc(const MucDonHang& mucMoi)
{
    this->_cacMuc.themCuoi(mucMoi);
    this->_lTongTien += mucMoi.layThanhTien();
}

bool DonHang::coMaHang(const string& strMaHang) const
{
    const Node<MucDonHang>* pChay = this->_cacMuc.layDau();
    while (pChay != NULL)
    {
        if (pChay->layDuLieu().layMaHang() == strMaHang)
        {
            return true;
        }
        pChay = pChay->layTiep();
    }
    return false;
}

string DonHang::chuyenThanhChuoi() const
{
    string strCacMuc = "";
    const Node<MucDonHang>* pChay = this->_cacMuc.layDau();
    while (pChay != NULL)
    {
        if (!strCacMuc.empty())
        {
            strCacMuc += ",";
        }
        const MucDonHang& muc = pChay->layDuLieu();
        strCacMuc += muc.layMaHang() + ":" + to_string(muc.laySoLuong()) + ":" +
                     to_string(muc.layThanhTien());
        pChay = pChay->layTiep();
    }
    return to_string(this->_iSoThuTu) + "|" + this->_strTenKhach + "|" +
           this->_strDiaChi + "|" + this->_strSoDienThoai + "|" +
           this->_ngayDat.chuyenThanhChuoi() + "|" + to_string(this->_lTongTien) + "|" +
           strCacMuc;
}

bool DonHang::taoTuChuoi(const string& strDong, DonHang& ketQua)
{
    vector<string> vecPhan = XuLiChuoi::tachChuoi(strDong, '|');
    if (static_cast<int>(vecPhan.size()) != SO_TRUONG_DON_HANG)
    {
        return false;
    }

    string strLoi = "";
    long long lSoThuTu = 0;
    if (!KiemTra::soNguyen(vecPhan[0], "So thu tu", 1, SO_THU_TU_DON_TOI_DA, lSoThuTu, strLoi))
    {
        return false;
    }

    string strTen = "";
    if (!KiemTra::tenKhachHang(vecPhan[1], strTen, strLoi))
    {
        return false;
    }

    string strDiaChi = "";
    if (!KiemTra::chuoiKhongRong(vecPhan[2], "Dia chi", strDiaChi, strLoi))
    {
        return false;
    }

    string strSdt = "";
    if (!KiemTra::soDienThoai(vecPhan[3], strSdt, strLoi))
    {
        return false;
    }

    NgayThang ngayDat;
    if (!NgayThang::taoTuChuoi(vecPhan[4], ngayDat))
    {
        return false;
    }

    DonHang donMoi(static_cast<int>(lSoThuTu), strTen, strDiaChi, strSdt, ngayDat);
    vector<string> vecMuc = XuLiChuoi::tachChuoi(vecPhan[6], ',');
    if (vecMuc.empty())
    {
        return false;
    }

    for (size_t iChiSo = 0; iChiSo < vecMuc.size(); ++iChiSo)
    {
        vector<string> vecTruong = XuLiChuoi::tachChuoi(vecMuc[iChiSo], ':');
        if (static_cast<int>(vecTruong.size()) != SO_TRUONG_MUC_DON)
        {
            return false;
        }
        string strMa = "";
        if (!KiemTra::maHang(vecTruong[0], strMa, strLoi))
        {
            return false;
        }
        long long lSoLuong = 0;
        if (!KiemTra::soNguyen(vecTruong[1], "So luong", 1, SO_LUONG_TOI_DA, lSoLuong, strLoi))
        {
            return false;
        }
        long long lThanhTien = 0;
        if (!KiemTra::soNguyen(vecTruong[2], "Thanh tien", 0, THANH_TIEN_TOI_DA, lThanhTien, strLoi))
        {
            return false;
        }
        donMoi.themMuc(MucDonHang(strMa, static_cast<int>(lSoLuong), lThanhTien));
    }
    ketQua = donMoi;
    return true;
}
