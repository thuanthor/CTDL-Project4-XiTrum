#ifndef MUCDONHANG_H_INCLUDED_
#define MUCDONHANG_H_INCLUDED_

#include <string>

class MucDonHang
{
public:
    MucDonHang();
    MucDonHang(const std::string& strMaHang, const int iSoLuong, const long long lThanhTien);

    const std::string& layMaHang() const;
    int laySoLuong() const;
    long long layThanhTien() const;

private:
    std::string _strMaHang;
    int _iSoLuong;
    long long _lThanhTien;
};

#endif
