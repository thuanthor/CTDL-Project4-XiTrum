#include "NgayThang.h"

#include <ctime>
#include <vector>

#include "HangSo.h"
#include "XuLiChuoi.h"

using namespace std;

NgayThang::NgayThang() : _iNgay(1), _iThang(1), _iNam(2000)
{
}

NgayThang::NgayThang(const int iNgay, const int iThang, const int iNam)
    : _iNgay(iNgay), _iThang(iThang), _iNam(iNam)
{
}

int NgayThang::layNgay() const
{
    return this->_iNgay;
}

int NgayThang::layThang() const
{
    return this->_iThang;
}

int NgayThang::layNam() const
{
    return this->_iNam;
}

bool NgayThang::laNamNhuan(const int iNam)
{
    const int CHU_KY_NHUAN_4 = 4;
    const int CHU_KY_THE_KY = 100;
    const int CHU_KY_NHUAN_400 = 400;
    return (iNam % CHU_KY_NHUAN_4 == 0 && iNam % CHU_KY_THE_KY != 0) ||
           (iNam % CHU_KY_NHUAN_400 == 0);
}

int NgayThang::soNgayTrongThang(const int iThang, const int iNam)
{
    static const int SO_NGAY_MOI_THANG[SO_THANG_TRONG_NAM] = {
        31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
    };
    if (iThang == THANG_HAI && NgayThang::laNamNhuan(iNam))
    {
        return NGAY_THANG_HAI_NHUAN;
    }
    return SO_NGAY_MOI_THANG[iThang - 1];
}

bool NgayThang::hopLe() const
{
    if (this->_iNam < NAM_TOI_THIEU || this->_iNam > NAM_TOI_DA)
    {
        return false;
    }
    if (this->_iThang < THANG_TOI_THIEU || this->_iThang > THANG_TOI_DA)
    {
        return false;
    }
    int iSoNgayToiDa = NgayThang::soNgayTrongThang(this->_iThang, this->_iNam);
    return (this->_iNgay >= 1 && this->_iNgay <= iSoNgayToiDa);
}

bool NgayThang::lonHon(const NgayThang& khac) const
{
    if (this->_iNam != khac._iNam)
    {
        return (this->_iNam > khac._iNam);
    }
    if (this->_iThang != khac._iThang)
    {
        return (this->_iThang > khac._iThang);
    }
    return (this->_iNgay > khac._iNgay);
}

NgayThang NgayThang::homNay()
{
    const int NAM_GOC_TM = 1900;
    time_t thoiGianHienTai = time(0);
    tm* pThoiGian = localtime(&thoiGianHienTai);
    if (pThoiGian == NULL)
    {
        return NgayThang();
    }
    return NgayThang(pThoiGian->tm_mday, pThoiGian->tm_mon + 1, pThoiGian->tm_year + NAM_GOC_TM);
}

string NgayThang::chuyenThanhChuoi() const
{
    const int GIOI_HAN_HAI_CHU_SO = 10;
    string strNgay = (this->_iNgay < GIOI_HAN_HAI_CHU_SO ? "0" : "") + to_string(this->_iNgay);
    string strThang = (this->_iThang < GIOI_HAN_HAI_CHU_SO ? "0" : "") + to_string(this->_iThang);
    return strNgay + "/" + strThang + "/" + to_string(this->_iNam);
}

bool NgayThang::taoTuChuoi(const string& strChuoi, NgayThang& ketQua)
{
    vector<string> vecPhan = XuLiChuoi::tachChuoi(strChuoi, '/');
    if (static_cast<int>(vecPhan.size()) != SO_TRUONG_NGAY)
    {
        return false;
    }
    for (int iChiSo = 0; iChiSo < SO_TRUONG_NGAY; ++iChiSo)
    {
        if (!XuLiChuoi::laSoNguyenKhongAm(vecPhan[iChiSo]))
        {
            return false;
        }
    }
    if (vecPhan[0].empty() || static_cast<int>(vecPhan[0].size()) > DO_DAI_NGAY_THANG_TOI_DA)
    {
        return false;
    }
    if (vecPhan[1].empty() || static_cast<int>(vecPhan[1].size()) > DO_DAI_NGAY_THANG_TOI_DA)
    {
        return false;
    }
    if (static_cast<int>(vecPhan[2].size()) != DO_DAI_NAM)
    {
        return false;
    }

    NgayThang ngayTam(stoi(vecPhan[0]), stoi(vecPhan[1]), stoi(vecPhan[2]));
    if (!ngayTam.hopLe())
    {
        return false;
    }
    ketQua = ngayTam;
    return true;
}
