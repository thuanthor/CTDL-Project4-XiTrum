#ifndef HANGHOA_H_INCLUDED_
#define HANGHOA_H_INCLUDED_

#include <string>

#include "NgayThang.h"

class HangHoa
{
public:
    HangHoa();
    explicit HangHoa(const std::string& strMaHang);
    HangHoa(const std::string& strMaHang, const std::string& strTenHang,
            const std::string& strNoiSanXuat, const std::string& strMauSac,
            const long long lGiaBan, const NgayThang& ngayNhapKho,
            const int iSoLuong);

    const std::string& layMa() const;
    const std::string& layTen() const;
    const std::string& layNoiSanXuat() const;
    const std::string& layMauSac() const;
    long long layGiaBan() const;
    const NgayThang& layNgayNhapKho() const;
    int laySoLuong() const;

    void datSoLuong(const int iSoLuong);

    bool operator<(const HangHoa& khac) const;
    bool operator>(const HangHoa& khac) const;

    /**********************************************************
     * @Description Chuyen thong tin hang hoa thanh 1 dong ghi file
     * @return      Chuoi dinh dang ma|ten|noiSX|mau|gia|ngay|soLuong
     **********************************************************/
    std::string chuyenThanhChuoi() const;

    /**********************************************************
     * @Description Doc va kiem tra 1 dong tu file HangHoa.txt
     * @return      true neu hop le, false neu sai dinh dang/rang buoc
     **********************************************************/
    static bool taoTuChuoi(const std::string& strDong, HangHoa& ketQua);

    static bool dungTruocTheoGiaTang(const HangHoa* pTrai, const HangHoa* pPhai);
    static bool dungTruocTheoGiaGiam(const HangHoa* pTrai, const HangHoa* pPhai);
    static bool dungTruocTheoTen(const HangHoa* pTrai, const HangHoa* pPhai);
    static bool khopTenThuong(const HangHoa* pHang, const std::string& strTuKhoaThuong);

private:
    std::string _strMaHang;
    std::string _strTenHang;
    std::string _strNoiSanXuat;
    std::string _strMauSac;
    long long _lGiaBan;
    NgayThang _ngayNhapKho;
    int _iSoLuong;
};

#endif
