#ifndef TAIKHOAN_H_INCLUDED_
#define TAIKHOAN_H_INCLUDED_

#include <string>

class TaiKhoan
{
public:
    TaiKhoan();
    TaiKhoan(const std::string& strUser, const std::string& strMatKhau);

    const std::string& layUser() const;

    /**********************************************************
     * @Description Kiem tra cap user va password co khop tai khoan
     * @return      true neu trung khop, false neu sai
     **********************************************************/
    bool khop(const std::string& strUser, const std::string& strMatKhau) const;

    /**********************************************************
     * @Description Doc 1 dong tu file Admin.txt (dinh dang user|password)
     * @return      true neu hop le, false neu sai dinh dang
     **********************************************************/
    static bool taoTuChuoi(const std::string& strDong, TaiKhoan& ketQua);

private:
    std::string _strUser;
    std::string _strMatKhau;
};

#endif
