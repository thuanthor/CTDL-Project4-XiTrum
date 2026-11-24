#ifndef GIAODIEN_H_INCLUDED_
#define GIAODIEN_H_INCLUDED_

#include <string>
#include <utility>
#include <vector>

#include "CotBang.h"

class GiaoDien
{
public:
    enum MauSac
    {
        MAC_DINH = 0,
        DO = 1,
        XANH_LA = 2,
        VANG = 3,
        XANH_DUONG = 4,
        TIM = 5,
        XANH_NGOC = 6,
        TRANG = 7,
        XAM = 8,
        DEN = 9
    };

    /**********************************************************
     * @Description Khoi tao console Windows UTF-8 va che do mau ANSI
     * @return      void
     **********************************************************/
    static void khoiTao();

    static bool laBanPhimTuongTac();
    static void datMau(const MauSac eMau);
    static void datMauNen(const MauSac eMauChu, const MauSac eMauNen);
    static void xoaManHinh();

    static void inBanner();
    static void inTieuDe(const std::string& strTieuDe, const MauSac eMau = XANH_NGOC);
    static void inTieuDeDangNhap();
    static void inMenu(const std::string& strTieuDe,
                       const std::vector<std::string>& vecMuc,
                       const std::string& strMucThoat);

    static void inBang(const std::vector<CotBang>& vecCot,
                       const std::vector<std::vector<std::string> >& vecHang,
                       const std::vector<MauSac>& vecMauHang = std::vector<MauSac>());

    static void inThongTin(const std::string& strTieuDe,
                           const std::vector<std::pair<std::string, std::string> >& vecTruong,
                           const MauSac eMau = XANH_NGOC);

    static void inDongNoiBat(const std::string& strNhan, const std::string& strGiaTri);
    static void inDong(const std::string& strNoiDung, const MauSac eMau = MAC_DINH);
    static void thongBaoLoi(const std::string& strNoiDung);
    static void thongBaoThanhCong(const std::string& strNoiDung);
    static void thongBaoThongTin(const std::string& strNoiDung);

    static bool hetDuLieuVao();
    static std::string nhapDong(const std::string& strNhan);
    static bool hoiCoKhong(const std::string& strCauHoi);
    static void tamDung(const std::string& strNhan = "Nhan Enter de tiep tuc...");

    /**********************************************************
     * @Description Nhap chuoi bang tung phim, ho tro an '*' va ESC
     * @return      false neu nhan ESC, true neu nhan Enter
     **********************************************************/
    static bool nhapDangNhap(const std::string& strNhan, const bool bAnMatKhau,
                             std::string& strKetQua);

private:
    static bool& mauHoatDong();
    static int maAnsi(const MauSac eMau);
    static bool dungKhungUnicode();
    static std::string khoangTrang(const int iSoKyTu);
    static std::string lapChuoi(const std::string& strMau, const int iSoLan);
    static int doRongHienThi(const std::string& strChuoi);
    static std::string canGiua(const std::string& strChuoi, const int iRong);
    static std::string vuaO(const std::string& strChuoi, const int iRong, const bool bCanPhai);
    static std::string kyTuKhung(const int iLoai);
    static std::string kyTuBang(const int iLoai);
    static void inVien(const int iViTri, const int iRong, const MauSac eMau);
    static void inDongKhung(const std::string& strNoiDung, const int iRong,
                            const MauSac eMauKhung, const MauSac eMauChu, const bool bGiua);
    static void inMucMenu(const std::string& strSo, const std::string& strChu,
                          const int iRong, const MauSac eMauSo, const MauSac eMauChu);
    static void inVienBang(const std::vector<CotBang>& vecCot, const int iViTri);
    static void inHuyHieu(const std::string& strNhan, const MauSac eMauChuNhan,
                          const MauSac eNenNhan, const std::string& strNoiDung,
                          const MauSac eMauNoiDung);
    static std::string veChuLogo(const char cKyTu, const int iHang);
};

#endif
