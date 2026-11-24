#ifndef CUAHANG_H_INCLUDED_
#define CUAHANG_H_INCLUDED_

#include <string>
#include <vector>

#include "CayNhiPhanTimKiem.h"
#include "DanhSachLienKet.h"
#include "DonHang.h"
#include "HangDoi.h"
#include "HangHoa.h"
#include "TaiKhoan.h"

enum KetQuaDangNhap
{
    DANG_NHAP_THANH_CONG = 0,
    DANG_NHAP_SAI_QUA_3_LAN = 1,
    DANG_NHAP_THOAT_ESC = 2
};

class CuaHang
{
public:
    CuaHang();

    /**********************************************************
     * @Description Doc toan bo du lieu tu 3 file khi khoi dong
     * @return      void
     **********************************************************/
    void taiDuLieu();

    /**********************************************************
     * @Description Hien thi bang hang hoa va tuy chon sap xep
     * @return      void
     **********************************************************/
    void hienThiHangHoa() const;

    /**********************************************************
     * @Description Tim kiem hang hoa theo ten (khong phan biet hoa/thuong)
     * @return      void
     **********************************************************/
    void timKiemHangHoa() const;

    /**********************************************************
     * @Description Tao don hang moi va dua vao hang doi cho xu li
     * @return      void
     **********************************************************/
    void datHang();

    /**********************************************************
     * @Description Dang nhap nhan vien quan li (toi da 3 lan, ho tro ESC)
     * @return      Trang thai KetQuaDangNhap
     **********************************************************/
    KetQuaDangNhap dangNhap() const;

    /**********************************************************
     * @Description Xu li don hang dau hang doi theo nguyen tac FIFO
     * @return      void
     **********************************************************/
    void xuLiDonHang();

    /**********************************************************
     * @Description Them hang hoa moi (ma 4 ky tu, khong trung)
     * @return      void
     **********************************************************/
    void themHangHoa();

    /**********************************************************
     * @Description Xoa hang hoa theo ma hang tren cay BST
     * @return      void
     **********************************************************/
    void xoaHangHoa();

    /**********************************************************
     * @Description Cap nhat lai so luong hang hoa theo ma hang
     * @return      void
     **********************************************************/
    void capNhatSoLuong();

private:
    void docFileHangHoa();
    void ghiFileHangHoa() const;
    void docFileAdmin();
    void docFileDonHang();
    void ghiFileDonHang() const;

    bool nhapMotMucDonHang(DonHang& donHang) const;
    void inBangDonCho() const;
    bool kiemTraDuKhoChoDon(const DonHang& donHang, std::string& strLyDoLoi) const;
    void truTonKhoTheoDon(const DonHang& donHang);

    static void baoLoiVaHuy(const std::string& strNoiDungLoi);
    bool kiemTraTaiKhoan(const std::string& strUser, const std::string& strMatKhau) const;
    int soLuongDaGiu(const std::string& strMaHang) const;
    bool coHangDeDat() const;
    void inBangTatCaHangHoa() const;
    static void inBangHangHoa(const std::vector<const HangHoa*>& vecHangHoa);
    void inChiTietDon(const DonHang& donHang) const;

    CayNhiPhanTimKiem<HangHoa> _cayHangHoa;
    HangDoi<DonHang> _hangDoiDon;
    DanhSachLienKet<TaiKhoan> _dsTaiKhoan;
    std::string _strFileHangHoa;
    std::string _strFileDonHang;
    std::string _strFileAdmin;
    int _iSoDonTiepTheo;
};

#endif
