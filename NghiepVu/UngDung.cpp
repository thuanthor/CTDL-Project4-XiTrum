#include "UngDung.h"

#include <iostream>
#include <string>
#include <vector>

#include "GiaoDien.h"
#include "NgayThang.h"
#include "XuLiChuoi.h"

using namespace std;

void UngDung::chay()
{
    GiaoDien::khoiTao();
    GiaoDien::inBanner();
    GiaoDien::inDong("\n  Dang tai du lieu tu file...", GiaoDien::XAM);
    this->_cuaHang.taiDuLieu();
    GiaoDien::tamDung("Nhan Enter de bat dau...");

    bool bTiepTuc = true;
    while (bTiepTuc && !GiaoDien::hetDuLieuVao())
    {
        GiaoDien::xoaManHinh();
        vector<string> vecMenuChinh;
        vecMenuChinh.push_back("Hien thi thong tin hang hoa");
        vecMenuChinh.push_back("Tim kiem thong tin hang hoa");
        vecMenuChinh.push_back("Dat hang");
        vecMenuChinh.push_back("Quan li");
        GiaoDien::inMenu("QUAN LI BAN HANG ONLINE", vecMenuChinh, "Thoat chuong trinh");
        GiaoDien::inDong("  Hom nay: " + NgayThang::homNay().chuyenThanhChuoi(), GiaoDien::XAM);

        int iLuaChon = this->docLuaChon();
        switch (iLuaChon)
        {
            case 1:
                this->_cuaHang.hienThiHangHoa();
                bTiepTuc = this->hoiTiepTucSauChucNang();
                break;
            case 2:
                this->_cuaHang.timKiemHangHoa();
                bTiepTuc = this->hoiTiepTucSauChucNang();
                break;
            case 3:
                this->_cuaHang.datHang();
                bTiepTuc = this->hoiTiepTucSauChucNang();
                break;
            case 4:
                bTiepTuc = this->chayKhuVucQuanLi();
                break;
            case 0:
                bTiepTuc = false;
                break;
            default:
                this->baoLuaChonSai();
                break;
        }
    }
    GiaoDien::thongBaoThongTin("Ket thuc chuong trinh. Tam biet!");
}

bool UngDung::hoiTiepTucSauChucNang() const
{
    if (GiaoDien::hetDuLieuVao())
    {
        return false;
    }
    cout << "\n";
    return GiaoDien::hoiCoKhong(
        "  Ban co muon thuc hien chuc nang khac? (c: Quay lai menu / k: Ket thuc): ");
}

bool UngDung::chayKhuVucQuanLi()
{
    KetQuaDangNhap eKetQua = this->_cuaHang.dangNhap();
    if (eKetQua != DANG_NHAP_THANH_CONG)
    {
        switch (eKetQua)
        {
            case DANG_NHAP_SAI_QUA_3_LAN:
                GiaoDien::thongBaoLoi("Nhap sai 3 lan. Thoat khoi he thong.");
                break;
            case DANG_NHAP_THOAT_ESC:
                GiaoDien::thongBaoThongTin("Da nhan ESC. Thoat khoi he thong.");
                break;
            default:
                break;
        }
        if (GiaoDien::laBanPhimTuongTac())
        {
            GiaoDien::tamDung("Nhan Enter de thoat...");
        }
        return false;
    }
    GiaoDien::tamDung();

    bool bDangNhap = true;
    while (bDangNhap && !GiaoDien::hetDuLieuVao())
    {
        GiaoDien::xoaManHinh();
        vector<string> vecMenuQuanLi;
        vecMenuQuanLi.push_back("Xu li don hang");
        vecMenuQuanLi.push_back("Quan li hang hoa");
        GiaoDien::inMenu("MENU QUAN LI", vecMenuQuanLi, "Dang xuat ve menu chinh");

        int iLuaChon = this->docLuaChon();
        switch (iLuaChon)
        {
            case 1:
                this->_cuaHang.xuLiDonHang();
                if (!this->hoiTiepTucSauChucNang())
                {
                    return false;
                }
                break;
            case 2:
                if (!this->chayMenuHangHoa())
                {
                    return false;
                }
                break;
            case 0:
                bDangNhap = false;
                break;
            default:
                this->baoLuaChonSai();
                break;
        }
    }
    return true;
}

bool UngDung::chayMenuHangHoa()
{
    bool bTiepTucMenu = true;
    while (bTiepTucMenu && !GiaoDien::hetDuLieuVao())
    {
        GiaoDien::xoaManHinh();
        vector<string> vecMenuHangHoa;
        vecMenuHangHoa.push_back("Them hang hoa moi");
        vecMenuHangHoa.push_back("Xoa hang hoa theo ma hang");
        vecMenuHangHoa.push_back("Cap nhat so luong hang hoa");
        GiaoDien::inMenu("QUAN LI HANG HOA", vecMenuHangHoa, "Quay lai menu quan li");

        int iLuaChon = this->docLuaChon();
        switch (iLuaChon)
        {
            case 1:
                this->_cuaHang.themHangHoa();
                if (!this->hoiTiepTucSauChucNang())
                {
                    return false;
                }
                break;
            case 2:
                this->_cuaHang.xoaHangHoa();
                if (!this->hoiTiepTucSauChucNang())
                {
                    return false;
                }
                break;
            case 3:
                this->_cuaHang.capNhatSoLuong();
                if (!this->hoiTiepTucSauChucNang())
                {
                    return false;
                }
                break;
            case 0:
                bTiepTucMenu = false;
                break;
            default:
                this->baoLuaChonSai();
                break;
        }
    }
    return true;
}

int UngDung::docLuaChon() const
{
    const int LUA_CHON_KHONG_HOP_LE = -1;
    string strNhap = XuLiChuoi::catKhoangTrang(GiaoDien::nhapDong("\n  >> Chon chuc nang: "));
    if (strNhap.size() == 1 && strNhap[0] >= '0' && strNhap[0] <= '9')
    {
        return static_cast<int>(strNhap[0] - '0');
    }
    return LUA_CHON_KHONG_HOP_LE;
}

void UngDung::baoLuaChonSai() const
{
    if (!GiaoDien::hetDuLieuVao())
    {
        GiaoDien::thongBaoLoi("Lua chon khong hop le! Vui long chon dung so trong menu.");
        GiaoDien::tamDung();
    }
}
