#ifndef KIEMTRA_H_INCLUDED_
#define KIEMTRA_H_INCLUDED_

#include <string>

#include "NgayThang.h"

class KiemTra
{
public:
    /**********************************************************
     * @Description Kiem tra chuoi bat buoc khong rong va khong chua '|'
     * @return      true neu hop le, false va gan strLoi neu vi pham
     **********************************************************/
    static bool chuoiKhongRong(const std::string& strVao, const std::string& strTenTruong,
                               std::string& strKetQua, std::string& strLoi);

    /**********************************************************
     * @Description Kiem tra chuoi khong chua chu so (Noi SX, Mau sac)
     * @return      true neu hop le, false va gan strLoi neu vi pham
     **********************************************************/
    static bool chuoiKhongCoSo(const std::string& strVao, const std::string& strTenTruong,
                               std::string& strKetQua, std::string& strLoi);

    /**********************************************************
     * @Description Kiem tra ten khach hang chi gom chu cai va khoang trang
     * @return      true neu hop le, false va gan strLoi neu vi pham
     **********************************************************/
    static bool tenKhachHang(const std::string& strVao, std::string& strKetQua,
                             std::string& strLoi);

    /**********************************************************
     * @Description Kiem tra ma hang dung 4 ky tu chu cai/chu so, in hoa
     * @return      true neu hop le, false va gan strLoi neu vi pham
     **********************************************************/
    static bool maHang(const std::string& strVao, std::string& strKetQua,
                       std::string& strLoi);

    /**********************************************************
     * @Description Kiem tra so nguyen khong am nam trong doan [lNho, lLon]
     * @return      true neu hop le, false va gan strLoi neu vi pham
     **********************************************************/
    static bool soNguyen(const std::string& strVao, const std::string& strTenTruong,
                         const long long lNho, const long long lLon,
                         long long& lKetQua, std::string& strLoi);

    /**********************************************************
     * @Description Kiem tra gia ban duong va la boi so cua 1.000 VND
     * @return      true neu hop le, false va gan strLoi neu vi pham
     **********************************************************/
    static bool giaBan(const std::string& strVao, long long& lKetQua,
                       std::string& strLoi);

    /**********************************************************
     * @Description Kiem tra so dien thoai gom dung 10 chu so, bat dau bang 0
     * @return      true neu hop le, false va gan strLoi neu vi pham
     **********************************************************/
    static bool soDienThoai(const std::string& strVao, std::string& strKetQua,
                            std::string& strLoi);

    /**********************************************************
     * @Description Kiem tra ngay nhap kho dd/mm/yyyy va khong o tuong lai
     * @return      true neu hop le, false va gan strLoi neu vi pham
     **********************************************************/
    static bool ngayNhapKho(const std::string& strVao, NgayThang& ngayKetQua,
                            std::string& strLoi);
};

#endif
