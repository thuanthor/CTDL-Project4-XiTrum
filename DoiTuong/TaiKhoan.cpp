#include "TaiKhoan.h"

#include <vector>

#include "HangSo.h"
#include "XuLiChuoi.h"

using namespace std;

TaiKhoan::TaiKhoan()
{
}

TaiKhoan::TaiKhoan(const string& strUser, const string& strMatKhau)
    : _strUser(strUser), _strMatKhau(strMatKhau)
{
}

const string& TaiKhoan::layUser() const
{
    return this->_strUser;
}

bool TaiKhoan::khop(const string& strUser, const string& strMatKhau) const
{
    return (this->_strUser == strUser && this->_strMatKhau == strMatKhau);
}

bool TaiKhoan::taoTuChuoi(const string& strDong, TaiKhoan& ketQua)
{
    vector<string> vecPhan = XuLiChuoi::tachChuoi(strDong, '|');
    if (static_cast<int>(vecPhan.size()) != SO_TRUONG_TAI_KHOAN)
    {
        return false;
    }
    if (vecPhan[0].empty() || vecPhan[1].empty())
    {
        return false;
    }
    ketQua = TaiKhoan(vecPhan[0], vecPhan[1]);
    return true;
}
