#include "CuaHang.h"

#include <fstream>
#include <iostream>
#include <utility>

#include "CotBang.h"
#include "GiaoDien.h"
#include "HangSo.h"
#include "KiemTra.h"
#include "ThuatToan.h"
#include "XuLiChuoi.h"

using namespace std;

CuaHang::CuaHang()
    : _strFileHangHoa("HangHoa.txt"), _strFileDonHang("DonHang.txt"),
      _strFileAdmin("Admin.txt"), _iSoDonTiepTheo(1)
{
}

void CuaHang::taiDuLieu()
{
    this->docFileHangHoa();
    this->docFileAdmin();
    this->docFileDonHang();
}

void CuaHang::hienThiHangHoa() const
{
    GiaoDien::inTieuDe("THONG TIN HANG HOA");
    if (this->_cayHangHoa.laRong())
    {
        GiaoDien::thongBaoThongTin("Hien chua co hang hoa nao trong kho.");
        return;
    }

    vector<const HangHoa*> vecDanhSach;
    this->_cayHangHoa.layDanhSachLNR(vecDanhSach);
    CuaHang::inBangHangHoa(vecDanhSach);
    GiaoDien::inDong("  Tong so mat hang: " + to_string(this->_cayHangHoa.kichThuoc()) +
                         "  (Dang hien thi theo Ma hang tang dan - duyet LNR cay BST)",
                     GiaoDien::XANH_NGOC);

    while (!GiaoDien::hetDuLieuVao())
    {
        GiaoDien::inDong(
            "\n  Tuy chon sap xep (Selection Sort): [1] Gia tang dan  |  [2] Gia giam dan  |  "
            "[3] Ten A-Z  |  [4] Ma hang (BST)  |  [0] Quay lai",
            GiaoDien::VANG);
        string strChon = XuLiChuoi::catKhoangTrang(GiaoDien::nhapDong("  >> Chon (0-4): "));
        if (strChon == "0" || GiaoDien::hetDuLieuVao())
        {
            return;
        }
        if (strChon == "1" || strChon == "2" || strChon == "3" || strChon == "4")
        {
            this->_cayHangHoa.layDanhSachLNR(vecDanhSach);
            string strMoTa = "Ma hang tang dan (duyet LNR cay BST)";
            if (strChon == "1")
            {
                ThuatToan::sapXepChon(vecDanhSach, &HangHoa::dungTruocTheoGiaTang);
                strMoTa = "Gia ban tang dan (Selection Sort)";
            }
            else if (strChon == "2")
            {
                ThuatToan::sapXepChon(vecDanhSach, &HangHoa::dungTruocTheoGiaGiam);
                strMoTa = "Gia ban giam dan (Selection Sort)";
            }
            else if (strChon == "3")
            {
                ThuatToan::sapXepChon(vecDanhSach, &HangHoa::dungTruocTheoTen);
                strMoTa = "Ten hang A -> Z (Selection Sort)";
            }
            cout << "\n";
            CuaHang::inBangHangHoa(vecDanhSach);
            GiaoDien::inDong("  Da sap xep theo: " + strMoTa, GiaoDien::XANH_LA);
        }
        else
        {
            GiaoDien::thongBaoLoi("Lua chon khong hop le! Vui long nhap so tu 0 den 4.");
        }
    }
}

void CuaHang::timKiemHangHoa() const
{
    GiaoDien::inTieuDe("TIM KIEM THONG TIN HANG HOA");
    if (this->_cayHangHoa.laRong())
    {
        GiaoDien::thongBaoThongTin("Hien chua co hang hoa nao de tim kiem.");
        return;
    }

    string strTuKhoa = "";
    string strLoi = "";
    if (!KiemTra::chuoiKhongRong(GiaoDien::nhapDong("  Nhap ten hang hoa can tim: "),
                                 "Ten hang can tim", strTuKhoa, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    string strTuKhoaThuong = XuLiChuoi::chuyenChuThuong(strTuKhoa);
    vector<const HangHoa*> vecTatCa;
    this->_cayHangHoa.layDanhSachLNR(vecTatCa);

    vector<const HangHoa*> vecKetQua;
    ThuatToan::timKiemTuyenTinh(vecTatCa, strTuKhoaThuong, &HangHoa::khopTenThuong, vecKetQua);

    if (vecKetQua.empty())
    {
        GiaoDien::thongBaoLoi("Khong tim thay hang hoa nao co ten chua \"" + strTuKhoa + "\".");
    }
    else
    {
        CuaHang::inBangHangHoa(vecKetQua);
        GiaoDien::thongBaoThanhCong("Tim thay " + to_string(vecKetQua.size()) +
                                    " mat hang phu hop voi tu khoa \"" + strTuKhoa + "\".");
    }
}

void CuaHang::datHang()
{
    GiaoDien::inTieuDe("DAT HANG ONLINE");
    if (!this->coHangDeDat())
    {
        GiaoDien::thongBaoLoi("Hien khong co mat hang nao con hang de dat.");
        return;
    }
    this->inBangTatCaHangHoa();
    cout << "\n";

    string strLoi = "";
    string strTenKhach = "";
    if (!KiemTra::tenKhachHang(GiaoDien::nhapDong("  Ten khach hang     : "), strTenKhach, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    string strDiaChi = "";
    if (!KiemTra::chuoiKhongRong(GiaoDien::nhapDong("  Dia chi khach hang : "),
                                 "Dia chi khach hang", strDiaChi, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    string strSoDienThoai = "";
    if (!KiemTra::soDienThoai(GiaoDien::nhapDong("  So dien thoai      : "), strSoDienThoai, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    DonHang donMoi(this->_iSoDonTiepTheo, strTenKhach, strDiaChi, strSoDienThoai, NgayThang::homNay());
    do
    {
        if (!this->nhapMotMucDonHang(donMoi))
        {
            return;
        }
    } while (GiaoDien::hoiCoKhong("  Ban co muon dat them ma hang khac vao don nay? (c/k): "));

    this->inChiTietDon(donMoi);
    if (!GiaoDien::hoiCoKhong("  Xac nhan dat don hang nay? (c/k): "))
    {
        GiaoDien::thongBaoThongTin("Da huy dat hang.");
        return;
    }

    this->_hangDoiDon.them(donMoi);
    ++this->_iSoDonTiepTheo;
    this->ghiFileDonHang();
    GiaoDien::thongBaoThanhCong("Don hang dang cho xu li (Don so " +
                                to_string(donMoi.laySoThuTu()) +
                                "). Da luu vao file " + this->_strFileDonHang + ".");
}

KetQuaDangNhap CuaHang::dangNhap() const
{
    for (int iLan = 1; iLan <= SO_LAN_DANG_NHAP_TOI_DA; ++iLan)
    {
        GiaoDien::xoaManHinh();
        GiaoDien::inTieuDeDangNhap();
        GiaoDien::thongBaoThongTin("Nhan ESC de thoat he thong. Nhap sai " +
                                   to_string(SO_LAN_DANG_NHAP_TOI_DA) + " lan se thoat he thong.");
        cout << "\n";

        string strUser = "";
        if (!GiaoDien::nhapDangNhap("    User     : ", false, strUser))
        {
            return DANG_NHAP_THOAT_ESC;
        }

        string strMatKhau = "";
        if (!GiaoDien::nhapDangNhap("    Password : ", true, strMatKhau))
        {
            return DANG_NHAP_THOAT_ESC;
        }

        if (XuLiChuoi::catKhoangTrang(strUser).empty() || strMatKhau.empty())
        {
            GiaoDien::thongBaoLoi("Khong hop le: User va Password khong duoc de trong (lan " +
                                  to_string(iLan) + "/" + to_string(SO_LAN_DANG_NHAP_TOI_DA) + ").");
        }
        else if (this->kiemTraTaiKhoan(strUser, strMatKhau))
        {
            GiaoDien::thongBaoThanhCong("Dang nhap thanh cong! Xin chao quan tri vien " +
                                        strUser + ".");
            return DANG_NHAP_THANH_CONG;
        }
        else
        {
            GiaoDien::thongBaoLoi("Sai user hoac password (lan " + to_string(iLan) + "/" +
                                  to_string(SO_LAN_DANG_NHAP_TOI_DA) + ").");
        }

        if (iLan < SO_LAN_DANG_NHAP_TOI_DA)
        {
            GiaoDien::tamDung("Nhan Enter de nhap lai...");
        }
    }
    return DANG_NHAP_SAI_QUA_3_LAN;
}

void CuaHang::xuLiDonHang()
{
    GiaoDien::inTieuDe("XU LI DON HANG (HANG DOI FIFO)");
    if (this->_hangDoiDon.laRong())
    {
        GiaoDien::thongBaoThongTin("Hien khong co don hang nao dang cho xu li.");
        return;
    }

    GiaoDien::inDong("  Co " + to_string(this->_hangDoiDon.kichThuoc()) +
                         " don hang dang cho (don dat truoc xu li truoc):",
                     GiaoDien::VANG);
    this->inBangDonCho();

    DonHang donDau = this->_hangDoiDon.layDau();
    GiaoDien::inDong("\n  Don hang duoc xu li tiep theo (dong mau vang - dau hang doi):",
                     GiaoDien::VANG);
    this->inChiTietDon(donDau);

    if (!GiaoDien::hoiCoKhong("  Xac nhan xu li don hang so " +
                              to_string(donDau.laySoThuTu()) + "? (c/k): "))
    {
        GiaoDien::thongBaoThongTin("Chua xu li don hang. Don van nam trong danh sach cho.");
        return;
    }

    string strLyDoLoi = "";
    if (!this->kiemTraDuKhoChoDon(donDau, strLyDoLoi))
    {
        this->_hangDoiDon.boDau();
        this->ghiFileDonHang();
        GiaoDien::thongBaoLoi("Khong the xu li don hang so " +
                              to_string(donDau.laySoThuTu()) + ": " + strLyDoLoi);
        GiaoDien::thongBaoThongTin("Da huy don hang nay khoi hang doi va cap nhat " +
                                   this->_strFileDonHang + ".");
        return;
    }

    this->truTonKhoTheoDon(donDau);
    this->_hangDoiDon.boDau();
    this->ghiFileHangHoa();
    this->ghiFileDonHang();
    GiaoDien::thongBaoThanhCong("Da xu li xong don hang so " + to_string(donDau.laySoThuTu()) +
                                ". Da xoa khoi " + this->_strFileDonHang +
                                " va cap nhat so luong trong " + this->_strFileHangHoa + ".");
}

void CuaHang::themHangHoa()
{
    GiaoDien::inTieuDe("THEM HANG HOA MOI");
    string strLoi = "";

    string strMa = "";
    if (!KiemTra::maHang(GiaoDien::nhapDong("  Ma hang (4 ky tu)       : "), strMa, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }
    if (this->_cayHangHoa.timKiem(HangHoa(strMa)) != NULL)
    {
        CuaHang::baoLoiVaHuy("Ma hang khong hop le: ma hang " + strMa +
                             " da ton tai trong he thong, khong duoc trung.");
        return;
    }

    string strTen = "";
    if (!KiemTra::chuoiKhongRong(GiaoDien::nhapDong("  Ten hang                : "),
                                 "Ten hang", strTen, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    string strNoi = "";
    if (!KiemTra::chuoiKhongCoSo(GiaoDien::nhapDong("  Noi san xuat            : "),
                                 "Noi san xuat", strNoi, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    string strMau = "";
    if (!KiemTra::chuoiKhongCoSo(GiaoDien::nhapDong("  Mau sac                 : "),
                                 "Mau sac", strMau, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    long long lGia = 0;
    if (!KiemTra::giaBan(GiaoDien::nhapDong("  Gia ban (boi so 1000)   : "), lGia, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    NgayThang ngayNhap;
    if (!KiemTra::ngayNhapKho(GiaoDien::nhapDong("  Ngay nhap (dd/mm/yyyy)  : "), ngayNhap, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    long long lSoLuong = 0;
    if (!KiemTra::soNguyen(GiaoDien::nhapDong("  So luong                : "),
                           "So luong", 1, SO_LUONG_TOI_DA, lSoLuong, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    HangHoa hangMoi(strMa, strTen, strNoi, strMau, lGia, ngayNhap, static_cast<int>(lSoLuong));
    this->_cayHangHoa.chen(hangMoi);
    this->ghiFileHangHoa();
    GiaoDien::thongBaoThanhCong("Da them hang hoa " + strMa + " - " + strTen +
                                " va luu vao file " + this->_strFileHangHoa + ".");
}

void CuaHang::xoaHangHoa()
{
    GiaoDien::inTieuDe("XOA HANG HOA THEO MA HANG");
    if (this->_cayHangHoa.laRong())
    {
        GiaoDien::thongBaoThongTin("Danh sach hang hoa dang rong.");
        return;
    }
    this->inBangTatCaHangHoa();
    cout << "\n";

    string strLoi = "";
    string strMa = "";
    if (!KiemTra::maHang(GiaoDien::nhapDong("  Nhap ma hang can xoa (4 ky tu): "), strMa, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    const HangHoa* pHang = this->_cayHangHoa.timKiem(HangHoa(strMa));
    if (pHang == NULL)
    {
        CuaHang::baoLoiVaHuy("Khong hop le: Ma hang " + strMa + " khong ton tai trong danh sach.");
        return;
    }

    int iDaGiu = this->soLuongDaGiu(strMa);
    if (iDaGiu > 0)
    {
        CuaHang::baoLoiVaHuy("Khong the xoa: ma hang " + strMa +
                             " dang nam trong don hang cho xu li (" + to_string(iDaGiu) +
                             " san pham). Vui long xu li don hang truoc.");
        return;
    }

    vector<const HangHoa*> vecChon;
    vecChon.push_back(pHang);
    CuaHang::inBangHangHoa(vecChon);

    if (!GiaoDien::hoiCoKhong("  Ban co chac chan muon xoa ma hang " + strMa + "? (c/k): "))
    {
        GiaoDien::thongBaoThongTin("Da huy thao tac xoa.");
        return;
    }

    this->_cayHangHoa.xoa(HangHoa(strMa));
    this->ghiFileHangHoa();
    GiaoDien::thongBaoThanhCong("Da xoa hang hoa " + strMa + " va cap nhat file " +
                                this->_strFileHangHoa + ".");
}

void CuaHang::capNhatSoLuong()
{
    GiaoDien::inTieuDe("CAP NHAT SO LUONG HANG HOA");
    if (this->_cayHangHoa.laRong())
    {
        GiaoDien::thongBaoThongTin("Danh sach hang hoa dang rong.");
        return;
    }
    this->inBangTatCaHangHoa();
    cout << "\n";

    string strLoi = "";
    string strMa = "";
    if (!KiemTra::maHang(GiaoDien::nhapDong("  Nhap ma hang can cap nhat (4 ky tu): "),
                         strMa, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }

    HangHoa* pHang = this->_cayHangHoa.timKiem(HangHoa(strMa));
    if (pHang == NULL)
    {
        CuaHang::baoLoiVaHuy("Khong hop le: Ma hang " + strMa + " khong ton tai trong danh sach.");
        return;
    }

    int iDaGiu = this->soLuongDaGiu(strMa);
    GiaoDien::inDong("  -> " + pHang->layTen() + " | So luong hien tai: " +
                         to_string(pHang->laySoLuong()) + " | Dang cho xu li: " +
                         to_string(iDaGiu),
                     GiaoDien::XANH_NGOC);

    long long lSoLuongMoi = 0;
    if (!KiemTra::soNguyen(GiaoDien::nhapDong("  Nhap so luong moi: "),
                           "So luong moi", 0, SO_LUONG_TOI_DA, lSoLuongMoi, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return;
    }
    if (lSoLuongMoi < iDaGiu)
    {
        CuaHang::baoLoiVaHuy("So luong moi (" + to_string(lSoLuongMoi) +
                             ") khong hop le: nho hon so luong cac don cho xu li dang can (" +
                             to_string(iDaGiu) + ").");
        return;
    }

    pHang->datSoLuong(static_cast<int>(lSoLuongMoi));
    this->ghiFileHangHoa();
    GiaoDien::thongBaoThanhCong("Da cap nhat so luong hang " + strMa + " thanh " +
                                to_string(lSoLuongMoi) + " va luu vao file " +
                                this->_strFileHangHoa + ".");
}

void CuaHang::docFileHangHoa()
{
    ifstream fileDoc;
    fileDoc.open(this->_strFileHangHoa.c_str());
    if (!fileDoc.is_open())
    {
        GiaoDien::thongBaoThongTin("Chua co file " + this->_strFileHangHoa +
                                   ", se tu dong tao khi luu du lieu.");
        return;
    }

    int iSoDongLoi = 0;
    string strDong = "";
    while (getline(fileDoc, strDong))
    {
        XuLiChuoi::xoaKyTuCR(strDong);
        if (strDong.empty() || strDong[0] == '#')
        {
            continue;
        }
        HangHoa hangDoc;
        if (!HangHoa::taoTuChuoi(strDong, hangDoc) || !this->_cayHangHoa.chen(hangDoc))
        {
            ++iSoDongLoi;
        }
    }
    fileDoc.close();

    if (iSoDongLoi > 0)
    {
        GiaoDien::thongBaoLoi("File " + this->_strFileHangHoa + " co " +
                              to_string(iSoDongLoi) + " dong sai dinh dang/trung ma, da bo qua.");
    }
}

void CuaHang::ghiFileHangHoa() const
{
    ofstream fileGhi;
    fileGhi.open(this->_strFileHangHoa.c_str());
    if (!fileGhi.is_open())
    {
        GiaoDien::thongBaoLoi("Khong the mo file " + this->_strFileHangHoa + " de ghi du lieu.");
        return;
    }

    vector<const HangHoa*> vecDanhSach;
    this->_cayHangHoa.layDanhSachLNR(vecDanhSach);
    for (size_t iChiSo = 0; iChiSo < vecDanhSach.size(); ++iChiSo)
    {
        fileGhi << vecDanhSach[iChiSo]->chuyenThanhChuoi() << "\n";
    }
    fileGhi.close();
}

void CuaHang::docFileAdmin()
{
    ifstream fileDoc;
    fileDoc.open(this->_strFileAdmin.c_str());
    if (!fileDoc.is_open())
    {
        GiaoDien::thongBaoLoi("Khong tim thay file " + this->_strFileAdmin + "!");
        return;
    }

    int iSoDongLoi = 0;
    string strDong = "";
    while (getline(fileDoc, strDong))
    {
        XuLiChuoi::xoaKyTuCR(strDong);
        if (strDong.empty() || strDong[0] == '#')
        {
            continue;
        }
        TaiKhoan taiKhoanDoc;
        if (TaiKhoan::taoTuChuoi(strDong, taiKhoanDoc))
        {
            this->_dsTaiKhoan.themCuoi(taiKhoanDoc);
        }
        else
        {
            ++iSoDongLoi;
        }
    }
    fileDoc.close();

    if (iSoDongLoi > 0)
    {
        GiaoDien::thongBaoLoi("File " + this->_strFileAdmin + " co " +
                              to_string(iSoDongLoi) + " dong sai dinh dang, da bo qua.");
    }
}

void CuaHang::docFileDonHang()
{
    const string TIEN_TO_NEXT = "#NEXT|";
    const int DO_DAI_CHU_SO_STT_TOI_DA = 9;

    ifstream fileDoc;
    fileDoc.open(this->_strFileDonHang.c_str());
    if (!fileDoc.is_open())
    {
        GiaoDien::thongBaoThongTin("Chua co file " + this->_strFileDonHang +
                                   ", se tu dong tao khi co don hang moi.");
        return;
    }

    int iSoDongLoi = 0;
    int iSoLonNhat = 0;
    int iSoTuTieuDe = 1;
    string strDong = "";
    while (getline(fileDoc, strDong))
    {
        XuLiChuoi::xoaKyTuCR(strDong);
        if (strDong.empty())
        {
            continue;
        }
        if (strDong.compare(0, TIEN_TO_NEXT.size(), TIEN_TO_NEXT) == 0)
        {
            string strPhanSo = XuLiChuoi::catKhoangTrang(strDong.substr(TIEN_TO_NEXT.size()));
            if (XuLiChuoi::laSoNguyenKhongAm(strPhanSo) &&
                static_cast<int>(strPhanSo.size()) <= DO_DAI_CHU_SO_STT_TOI_DA)
            {
                iSoTuTieuDe = stoi(strPhanSo);
            }
            continue;
        }
        if (strDong[0] == '#')
        {
            continue;
        }
        DonHang donDoc;
        if (DonHang::taoTuChuoi(strDong, donDoc))
        {
            this->_hangDoiDon.them(donDoc);
            if (donDoc.laySoThuTu() > iSoLonNhat)
            {
                iSoLonNhat = donDoc.laySoThuTu();
            }
        }
        else
        {
            ++iSoDongLoi;
        }
    }
    fileDoc.close();

    this->_iSoDonTiepTheo = (iSoTuTieuDe > iSoLonNhat) ? iSoTuTieuDe : (iSoLonNhat + 1);
    if (iSoDongLoi > 0)
    {
        GiaoDien::thongBaoLoi("File " + this->_strFileDonHang + " co " +
                              to_string(iSoDongLoi) + " dong sai dinh dang, da bo qua.");
    }
}

void CuaHang::ghiFileDonHang() const
{
    ofstream fileGhi;
    fileGhi.open(this->_strFileDonHang.c_str());
    if (!fileGhi.is_open())
    {
        GiaoDien::thongBaoLoi("Khong the mo file " + this->_strFileDonHang + " de ghi du lieu.");
        return;
    }

    fileGhi << "#NEXT|" << this->_iSoDonTiepTheo << "\n";
    const Node<DonHang>* pChay = this->_hangDoiDon.layNutDau();
    while (pChay != NULL)
    {
        fileGhi << pChay->layDuLieu().chuyenThanhChuoi() << "\n";
        pChay = pChay->layTiep();
    }
    fileGhi.close();
}

bool CuaHang::nhapMotMucDonHang(DonHang& donHang) const
{
    cout << "\n";
    string strLoi = "";
    string strMa = "";
    if (!KiemTra::maHang(GiaoDien::nhapDong("  Ma hang (4 ky tu)  : "), strMa, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return false;
    }
    if (donHang.coMaHang(strMa))
    {
        CuaHang::baoLoiVaHuy("Khong hop le: Ma hang " + strMa + " da co trong don hang nay.");
        return false;
    }

    const HangHoa* pHang = this->_cayHangHoa.timKiem(HangHoa(strMa));
    if (pHang == NULL)
    {
        CuaHang::baoLoiVaHuy("Khong hop le: Ma hang " + strMa + " khong ton tai trong he thong.");
        return false;
    }
    if (pHang->laySoLuong() <= 0)
    {
        CuaHang::baoLoiVaHuy("Khong hop le: Hang \"" + pHang->layTen() +
                             "\" da het hang (so luong = 0).");
        return false;
    }

    int iDaGiu = this->soLuongDaGiu(strMa);
    int iConLai = pHang->laySoLuong() - iDaGiu;
    if (iConLai <= 0)
    {
        CuaHang::baoLoiVaHuy("Khong hop le: Hang \"" + pHang->layTen() +
                             "\" da duoc cac don hang dat truoc dat het (ton kho: " +
                             to_string(pHang->laySoLuong()) + ", dang cho xu li: " +
                             to_string(iDaGiu) + ").");
        return false;
    }

    GiaoDien::inDong("  -> Ten hang: " + pHang->layTen() + " | Don gia: " +
                         XuLiChuoi::dinhDangTien(pHang->layGiaBan()) + " VND | Ton kho: " +
                         to_string(pHang->laySoLuong()) + " | Cho xu li: " +
                         to_string(iDaGiu) + " | Co the dat toi da: " + to_string(iConLai),
                     GiaoDien::XANH_NGOC);

    long long lSoLuong = 0;
    if (!KiemTra::soNguyen(GiaoDien::nhapDong("  So luong dat       : "),
                           "So luong dat", 1, iConLai, lSoLuong, strLoi))
    {
        CuaHang::baoLoiVaHuy(strLoi);
        return false;
    }

    donHang.themMuc(MucDonHang(strMa, static_cast<int>(lSoLuong), pHang->layGiaBan() * lSoLuong));
    return true;
}

void CuaHang::inBangDonCho() const
{
    const int RONG_DON_SO = 7;
    const int RONG_KHACH = 22;
    const int RONG_SDT = 10;
    const int RONG_NGAY = 10;
    const int RONG_TONG_TIEN = 15;

    vector<CotBang> vecCot;
    vecCot.push_back(CotBang("Don so", RONG_DON_SO, true));
    vecCot.push_back(CotBang("Khach hang", RONG_KHACH));
    vecCot.push_back(CotBang("SDT", RONG_SDT));
    vecCot.push_back(CotBang("Ngay dat", RONG_NGAY));
    vecCot.push_back(CotBang("Tong tien (VND)", RONG_TONG_TIEN, true));

    vector<vector<string> > vecBang;
    vector<GiaoDien::MauSac> vecMau;
    const Node<DonHang>* pChay = this->_hangDoiDon.layNutDau();
    while (pChay != NULL)
    {
        const DonHang& don = pChay->layDuLieu();
        vector<string> vecDong;
        vecDong.push_back(to_string(don.laySoThuTu()));
        vecDong.push_back(don.layTenKhach());
        vecDong.push_back(don.laySoDienThoai());
        vecDong.push_back(don.layNgayDat().chuyenThanhChuoi());
        vecDong.push_back(XuLiChuoi::dinhDangTien(don.layTongTien()));
        vecBang.push_back(vecDong);
        vecMau.push_back(vecBang.size() == 1 ? GiaoDien::VANG : GiaoDien::MAC_DINH);
        pChay = pChay->layTiep();
    }
    GiaoDien::inBang(vecCot, vecBang, vecMau);
}

bool CuaHang::kiemTraDuKhoChoDon(const DonHang& donHang, string& strLyDoLoi) const
{
    strLyDoLoi = "";
    const Node<MucDonHang>* pChay = donHang.layCacMuc().layDau();
    while (pChay != NULL)
    {
        const MucDonHang& muc = pChay->layDuLieu();
        const HangHoa* pHang = this->_cayHangHoa.timKiem(HangHoa(muc.layMaHang()));
        if (pHang == NULL)
        {
            strLyDoLoi = "Ma hang " + muc.layMaHang() + " khong con ton tai trong kho.";
            return false;
        }
        if (pHang->laySoLuong() < muc.laySoLuong())
        {
            strLyDoLoi = "Ma hang " + muc.layMaHang() + " khong du so luong (can " +
                         to_string(muc.laySoLuong()) + ", ton kho " +
                         to_string(pHang->laySoLuong()) + ").";
            return false;
        }
        pChay = pChay->layTiep();
    }
    return true;
}

void CuaHang::truTonKhoTheoDon(const DonHang& donHang)
{
    const Node<MucDonHang>* pChay = donHang.layCacMuc().layDau();
    while (pChay != NULL)
    {
        const MucDonHang& muc = pChay->layDuLieu();
        HangHoa* pHang = this->_cayHangHoa.timKiem(HangHoa(muc.layMaHang()));
        if (pHang != NULL)
        {
            pHang->datSoLuong(pHang->laySoLuong() - muc.laySoLuong());
        }
        pChay = pChay->layTiep();
    }
}

void CuaHang::baoLoiVaHuy(const string& strNoiDungLoi)
{
    GiaoDien::thongBaoLoi(strNoiDungLoi);
    GiaoDien::thongBaoLoi("Chuc nang dang thuc hien da bi huy do du lieu khong hop le.");
}

bool CuaHang::kiemTraTaiKhoan(const string& strUser, const string& strMatKhau) const
{
    const Node<TaiKhoan>* pChay = this->_dsTaiKhoan.layDau();
    while (pChay != NULL)
    {
        if (pChay->layDuLieu().khop(strUser, strMatKhau))
        {
            return true;
        }
        pChay = pChay->layTiep();
    }
    return false;
}

int CuaHang::soLuongDaGiu(const string& strMaHang) const
{
    int iTong = 0;
    const Node<DonHang>* pDon = this->_hangDoiDon.layNutDau();
    while (pDon != NULL)
    {
        const Node<MucDonHang>* pMuc = pDon->layDuLieu().layCacMuc().layDau();
        while (pMuc != NULL)
        {
            if (pMuc->layDuLieu().layMaHang() == strMaHang)
            {
                iTong += pMuc->layDuLieu().laySoLuong();
            }
            pMuc = pMuc->layTiep();
        }
        pDon = pDon->layTiep();
    }
    return iTong;
}

bool CuaHang::coHangDeDat() const
{
    vector<const HangHoa*> vecDanhSach;
    this->_cayHangHoa.layDanhSachLNR(vecDanhSach);
    for (size_t iChiSo = 0; iChiSo < vecDanhSach.size(); ++iChiSo)
    {
        int iConLai = vecDanhSach[iChiSo]->laySoLuong() -
                      this->soLuongDaGiu(vecDanhSach[iChiSo]->layMa());
        if (iConLai > 0)
        {
            return true;
        }
    }
    return false;
}

void CuaHang::inBangTatCaHangHoa() const
{
    vector<const HangHoa*> vecDanhSach;
    this->_cayHangHoa.layDanhSachLNR(vecDanhSach);
    CuaHang::inBangHangHoa(vecDanhSach);
}

void CuaHang::inBangHangHoa(const vector<const HangHoa*>& vecHangHoa)
{
    const int RONG_STT = 3;
    const int RONG_MA = 4;
    const int RONG_TEN = 18;
    const int RONG_NOI_SX = 11;
    const int RONG_MAU_SAC = 8;
    const int RONG_GIA = 13;
    const int RONG_NGAY = 10;
    const int RONG_SL = 8;

    vector<CotBang> vecCot;
    vecCot.push_back(CotBang("STT", RONG_STT, true));
    vecCot.push_back(CotBang("Ma", RONG_MA));
    vecCot.push_back(CotBang("Ten hang", RONG_TEN));
    vecCot.push_back(CotBang("Noi SX", RONG_NOI_SX));
    vecCot.push_back(CotBang("Mau sac", RONG_MAU_SAC));
    vecCot.push_back(CotBang("Gia ban (VND)", RONG_GIA, true));
    vecCot.push_back(CotBang("Ngay nhap", RONG_NGAY));
    vecCot.push_back(CotBang("So luong", RONG_SL, true));

    vector<vector<string> > vecBang;
    vector<GiaoDien::MauSac> vecMau;
    for (size_t iChiSo = 0; iChiSo < vecHangHoa.size(); ++iChiSo)
    {
        const HangHoa& hang = *vecHangHoa[iChiSo];
        vector<string> vecDong;
        vecDong.push_back(to_string(iChiSo + 1));
        vecDong.push_back(hang.layMa());
        vecDong.push_back(hang.layTen());
        vecDong.push_back(hang.layNoiSanXuat());
        vecDong.push_back(hang.layMauSac());
        vecDong.push_back(XuLiChuoi::dinhDangTien(hang.layGiaBan()));
        vecDong.push_back(hang.layNgayNhapKho().chuyenThanhChuoi());
        vecDong.push_back(hang.laySoLuong() == 0 ? "Het hang" : to_string(hang.laySoLuong()));
        vecBang.push_back(vecDong);
        vecMau.push_back(hang.laySoLuong() == 0 ? GiaoDien::DO : GiaoDien::MAC_DINH);
    }
    GiaoDien::inBang(vecCot, vecBang, vecMau);
}

void CuaHang::inChiTietDon(const DonHang& donHang) const
{
    const int RONG_MA = 4;
    const int RONG_TEN = 22;
    const int RONG_SL = 5;
    const int RONG_THANH_TIEN = 16;

    vector<pair<string, string> > vecTruong;
    vecTruong.push_back(make_pair(string("Khach hang"), donHang.layTenKhach()));
    vecTruong.push_back(make_pair(string("Dia chi"), donHang.layDiaChi()));
    vecTruong.push_back(make_pair(string("So dien thoai"), donHang.laySoDienThoai()));
    vecTruong.push_back(make_pair(string("Ngay dat"), donHang.layNgayDat().chuyenThanhChuoi()));
    cout << "\n";
    GiaoDien::inThongTin("DON HANG SO " + to_string(donHang.laySoThuTu()), vecTruong);

    vector<CotBang> vecCot;
    vecCot.push_back(CotBang("Ma", RONG_MA));
    vecCot.push_back(CotBang("Ten hang", RONG_TEN));
    vecCot.push_back(CotBang("SL", RONG_SL, true));
    vecCot.push_back(CotBang("Thanh tien (VND)", RONG_THANH_TIEN, true));

    vector<vector<string> > vecBang;
    const Node<MucDonHang>* pChay = donHang.layCacMuc().layDau();
    while (pChay != NULL)
    {
        const MucDonHang& muc = pChay->layDuLieu();
        const HangHoa* pHang = this->_cayHangHoa.timKiem(HangHoa(muc.layMaHang()));
        vector<string> vecDong;
        vecDong.push_back(muc.layMaHang());
        vecDong.push_back(pHang != NULL ? pHang->layTen() : "(da xoa)");
        vecDong.push_back(to_string(muc.laySoLuong()));
        vecDong.push_back(XuLiChuoi::dinhDangTien(muc.layThanhTien()));
        vecBang.push_back(vecDong);
        pChay = pChay->layTiep();
    }
    GiaoDien::inBang(vecCot, vecBang);
    GiaoDien::inDongNoiBat("TONG TIEN :",
                           XuLiChuoi::dinhDangTien(donHang.layTongTien()) + " VND");
}
