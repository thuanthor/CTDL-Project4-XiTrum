#ifndef DONHANG_H_INCLUDED_
#define DONHANG_H_INCLUDED_

#include <string>

#include "DanhSachLienKet.h"
#include "MucDonHang.h"
#include "NgayThang.h"

class DonHang
{
public:
    DonHang();
    DonHang(const int iSoThuTu, const std::string& strTenKhach,
            const std::string& strDiaChi, const std::string& strSoDienThoai,
            const NgayThang& ngayDat);

    int laySoThuTu() const;
    const std::string& layTenKhach() const;
    const std::string& layDiaChi() const;
    const std::string& laySoDienThoai() const;
    const NgayThang& layNgayDat() const;
    long long layTongTien() const;
    const DanhSachLienKet<MucDonHang>& layCacMuc() const;

    /**********************************************************
     * @Description Them mot mat hang vao don va cong don tong tien
     * @return      void
     **********************************************************/
    void themMuc(const MucDonHang& mucMoi);

    /**********************************************************
     * @Description Kiem tra ma hang da ton tai trong don hang nay chua
     * @return      true neu da co, false neu chua co
     **********************************************************/
    bool coMaHang(const std::string& strMaHang) const;

    /**********************************************************
     * @Description Chuyen don hang thanh 1 dong ghi file DonHang.txt
     * @return      Chuoi bieu dien don hang
     **********************************************************/
    std::string chuyenThanhChuoi() const;

    /**********************************************************
     * @Description Doc va kiem tra 1 dong tu file DonHang.txt
     * @return      true neu hop le, false neu sai dinh dang/rang buoc
     **********************************************************/
    static bool taoTuChuoi(const std::string& strDong, DonHang& ketQua);

private:
    int _iSoThuTu;
    std::string _strTenKhach;
    std::string _strDiaChi;
    std::string _strSoDienThoai;
    NgayThang _ngayDat;
    long long _lTongTien;
    DanhSachLienKet<MucDonHang> _cacMuc;
};

#endif
