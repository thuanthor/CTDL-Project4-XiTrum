#ifndef XULICHUOI_H_INCLUDED_
#define XULICHUOI_H_INCLUDED_

#include <string>
#include <vector>

class XuLiChuoi
{
public:
    /**********************************************************
     * @Description Xoa ky tu '\r' o cuoi chuoi khi doc file CRLF
     * @return      void
     **********************************************************/
    static void xoaKyTuCR(std::string& strChuoi);

    /**********************************************************
     * @Description Cat bo khoang trang thua o dau va cuoi chuoi
     * @return      Chuoi da duoc cat khoang trang hai dau
     **********************************************************/
    static std::string catKhoangTrang(const std::string& strChuoi);

    /**********************************************************
     * @Description Chuyen toan bo chu cai ASCII sang chu IN HOA
     * @return      Chuoi chu hoa
     **********************************************************/
    static std::string chuyenChuHoa(const std::string& strChuoi);

    /**********************************************************
     * @Description Chuyen toan bo chu cai ASCII sang chu thuong
     * @return      Chuoi chu thuong
     **********************************************************/
    static std::string chuyenChuThuong(const std::string& strChuoi);

    /**********************************************************
     * @Description Kiem tra chuoi khong rong va chi gom chu so 0-9
     * @return      true neu toan chu so, false neu nguoc lai
     **********************************************************/
    static bool laSoNguyenKhongAm(const std::string& strChuoi);

    /**********************************************************
     * @Description Tach chuoi theo ky tu phan cach
     * @return      Danh sach cac chuoi con sau khi tach
     **********************************************************/
    static std::vector<std::string> tachChuoi(const std::string& strChuoi, const char cPhanCach);

    /**********************************************************
     * @Description Dinh dang so tien co dau cham phan nhom nghin
     * @return      Chuoi tien te da dinh dang (vd: "1.500.000")
     **********************************************************/
    static std::string dinhDangTien(const long long lSoTien);
};

#endif
