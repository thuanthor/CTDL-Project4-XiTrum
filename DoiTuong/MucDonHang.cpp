#include "MucDonHang.h"

using namespace std;

MucDonHang::MucDonHang() : _iSoLuong(0), _lThanhTien(0)
{
}

MucDonHang::MucDonHang(const string& strMaHang, const int iSoLuong, const long long lThanhTien)
    : _strMaHang(strMaHang), _iSoLuong(iSoLuong), _lThanhTien(lThanhTien)
{
}

const string& MucDonHang::layMaHang() const
{
    return this->_strMaHang;
}

int MucDonHang::laySoLuong() const
{
    return this->_iSoLuong;
}

long long MucDonHang::layThanhTien() const
{
    return this->_lThanhTien;
}
