#ifndef NGAYTHANG_H_INCLUDED_
#define NGAYTHANG_H_INCLUDED_

#include <string>

class NgayThang
{
public:
    NgayThang();
    NgayThang(const int iNgay, const int iThang, const int iNam);

    int layNgay() const;
    int layThang() const;
    int layNam() const;

    /**********************************************************
     * @Description Kiem tra mot nam co phai la nam nhuan hay khong
     * @return      true neu la nam nhuan, false neu khong phai
     **********************************************************/
    static bool laNamNhuan(const int iNam);

    /**********************************************************
     * @Description Tra ve so ngay toi da trong thang cua nam tuong ung
     * @return      So ngay trong thang (28..31)
     **********************************************************/
    static int soNgayTrongThang(const int iThang, const int iNam);

    /**********************************************************
     * @Description Kiem tra ngay thang nam co ton tai thuc te tren lich
     * @return      true neu hop le, false neu khong hop le
     **********************************************************/
    bool hopLe() const;

    /**********************************************************
     * @Description So sanh ngay hien tai co lon hon ngay khac khong
     * @return      true neu lon hon, false neu nho hon hoac bang
     **********************************************************/
    bool lonHon(const NgayThang& khac) const;

    /**********************************************************
     * @Description Lay ngay hien tai tu dong ho he thong
     * @return      Doi tuong NgayThang cua ngay hom nay
     **********************************************************/
    static NgayThang homNay();

    /**********************************************************
     * @Description Chuyen doi tuong sang chuoi dinh dang dd/mm/yyyy
     * @return      Chuoi ngay thang
     **********************************************************/
    std::string chuyenThanhChuoi() const;

    /**********************************************************
     * @Description Phan tich chuoi dd/mm/yyyy thanh doi tuong NgayThang
     * @return      true neu dung dinh dang va ton tai tren lich
     **********************************************************/
    static bool taoTuChuoi(const std::string& strChuoi, NgayThang& ketQua);

private:
    int _iNgay;
    int _iThang;
    int _iNam;
};

#endif
