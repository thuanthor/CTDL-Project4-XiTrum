// main.cpp - PROJECT 4 (PRO_CTDL_4): CHUONG TRINH QUAN LI BAN HANG ONLINE
// Mon hoc: Cau truc du lieu (Chuong 2, 3, 4, 5)
// Cau truc du lieu & thuat toan su dung:
//   - Chuong 2: Tim kiem tuyen tinh theo ten hang hoa, Sap xep chon (Selection Sort)
//   - Chuong 3: Danh sach lien ket don (DanhSachLienKet) luu Tai khoan & Chi tiet don hang
//   - Chuong 4: Hang doi FIFO (HangDoi) luu Don hang cho xu li (dat truoc xu li truoc)
//   - Chuong 5: Cay nhi phan tim kiem (CayBST) luu danh sach Hang hoa theo Ma hang

#include <cctype>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "GiaoDien.h"

using namespace std;

// ============================================================================
// PHAN 1: TIEN ICH XU LI CHUOI, NGAY THANG VA KIEM TRA RANG BUOC DU LIEU
// ============================================================================

class XuLiChuoi {
public:
    // Xoa ky tu '\r' o cuoi dong (tranh loi dinh dang CRLF cua Windows khi doc file)
    static void xoaCR(string& s) {
        if (!s.empty() && s[s.size() - 1] == '\r') {
            s.erase(s.size() - 1);
        }
    }

    // Cat khoang trang thua o dau va cuoi chuoi
    static string catKhoangTrang(const string& s) {
        size_t dau = 0;
        size_t cuoi = s.size();
        while (dau < cuoi && isspace(static_cast<unsigned char>(s[dau]))) {
            ++dau;
        }
        while (cuoi > dau && isspace(static_cast<unsigned char>(s[cuoi - 1]))) {
            --cuoi;
        }
        return s.substr(dau, cuoi - dau);
    }

    static string chuHoa(string s) {
        for (size_t i = 0; i < s.size(); ++i) {
            s[i] = static_cast<char>(toupper(static_cast<unsigned char>(s[i])));
        }
        return s;
    }

    static string chuThuong(string s) {
        for (size_t i = 0; i < s.size(); ++i) {
            s[i] = static_cast<char>(tolower(static_cast<unsigned char>(s[i])));
        }
        return s;
    }

    // Kiem tra chuoi khong rong va chi gom chu so 0..9
    static bool laSoNguyenKhongAm(const string& s) {
        if (s.empty()) return false;
        for (size_t i = 0; i < s.size(); ++i) {
            if (!isdigit(static_cast<unsigned char>(s[i]))) {
                return false;
            }
        }
        return true;
    }

    // Tach chuoi theo ky tu phan cach
    static vector<string> tachChuoi(const string& s, char phanCach) {
        vector<string> ketQua;
        string phan;
        istringstream luong(s);
        while (getline(luong, phan, phanCach)) {
            ketQua.push_back(phan);
        }
        if (!s.empty() && s[s.size() - 1] == phanCach) {
            ketQua.push_back("");
        }
        return ketQua;
    }

    // Dinh dang tien te: 1500000 -> "1.500.000"
    static string dinhDangTien(long long soTien) {
        string so = to_string(soTien);
        string ketQua;
        int dem = 0;
        for (int i = static_cast<int>(so.size()) - 1; i >= 0; --i) {
            ketQua.insert(ketQua.begin(), so[i]);
            ++dem;
            if (dem % 3 == 0 && i > 0) {
                ketQua.insert(ketQua.begin(), '.');
            }
        }
        return ketQua;
    }
};

class NgayThang {
public:
    NgayThang() : m_ngay(1), m_thang(1), m_nam(2000) {}
    NgayThang(int ngay, int thang, int nam) : m_ngay(ngay), m_thang(thang), m_nam(nam) {}

    static bool laNamNhuan(int nam) {
        return (nam % 4 == 0 && nam % 100 != 0) || (nam % 400 == 0);
    }

    static int soNgayTrongThang(int thang, int nam) {
        static const int soNgay[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (thang == 2 && laNamNhuan(nam)) return 29;
        return soNgay[thang - 1];
    }

    bool hopLe() const {
        if (m_nam < 1900 || m_nam > 9999) return false;
        if (m_thang < 1 || m_thang > 12) return false;
        return m_ngay >= 1 && m_ngay <= soNgayTrongThang(m_thang, m_nam);
    }

    bool lonHon(const NgayThang& khac) const {
        if (m_nam != khac.m_nam) return m_nam > khac.m_nam;
        if (m_thang != khac.m_thang) return m_thang > khac.m_thang;
        return m_ngay > khac.m_ngay;
    }

    static NgayThang homNay() {
        time_t bayGio = time(0);
        tm* t = localtime(&bayGio);
        return NgayThang(t->tm_mday, t->tm_mon + 1, t->tm_year + 1900);
    }

    string chuyenThanhChuoi() const {
        string ngay = (m_ngay < 10 ? "0" : "") + to_string(m_ngay);
        string thang = (m_thang < 10 ? "0" : "") + to_string(m_thang);
        return ngay + "/" + thang + "/" + to_string(m_nam);
    }

    // Doc tu chuoi "dd/mm/yyyy"
    static bool taoTuChuoi(const string& chuoi, NgayThang& ketQua) {
        vector<string> phan = XuLiChuoi::tachChuoi(chuoi, '/');
        if (phan.size() != 3) return false;
        for (int i = 0; i < 3; ++i) {
            if (!XuLiChuoi::laSoNguyenKhongAm(phan[i])) return false;
        }
        if (phan[0].size() < 1 || phan[0].size() > 2) return false;
        if (phan[1].size() < 1 || phan[1].size() > 2) return false;
        if (phan[2].size() != 4) return false;

        NgayThang ngay(stoi(phan[0]), stoi(phan[1]), stoi(phan[2]));
        if (!ngay.hopLe()) return false;
        ketQua = ngay;
        return true;
    }

private:
    int m_ngay;
    int m_thang;
    int m_nam;
};

// Lop kiem tra rang buoc du lieu: moi ham tra ve true neu hop le,
// tra ve false va gan thong bao loi cu the ("khong hop le...") neu vi pham.
class KiemTra {
public:
    // Chuoi van ban bat buoc: khong rong, khong chi gom khoang trang, khong chua '|'
    static bool chuoiKhongRong(const string& s, const string& tenTruong,
                               string& ketQua, string& loi) {
        ketQua = XuLiChuoi::catKhoangTrang(s);
        if (ketQua.empty()) {
            loi = tenTruong + " khong hop le: khong duoc de trong hoac chi nhap khoang trang.";
            return false;
        }
        if (ketQua.find('|') != string::npos) {
            loi = tenTruong + " khong hop le: khong duoc chua ky tu '|'.";
            return false;
        }
        return true;
    }

    // Chuoi khong chua chu so (vd: Noi san xuat, Mau sac)
    static bool chuoiKhongCoSo(const string& s, const string& tenTruong,
                               string& ketQua, string& loi) {
        if (!chuoiKhongRong(s, tenTruong, ketQua, loi)) return false;
        for (size_t i = 0; i < ketQua.size(); ++i) {
            if (isdigit(static_cast<unsigned char>(ketQua[i]))) {
                loi = tenTruong + " khong hop le: khong duoc chua chu so.";
                return false;
            }
        }
        return true;
    }

    // Ten khach hang: khong rong, chi gom chu cai va khoang trang, it nhat 2 ky tu
    static bool tenKhachHang(const string& s, string& ketQua, string& loi) {
        if (!chuoiKhongRong(s, "Ten khach hang", ketQua, loi)) return false;
        if (ketQua.size() < 2) {
            loi = "Ten khach hang khong hop le: phai co it nhat 2 ky tu.";
            return false;
        }
        for (size_t i = 0; i < ketQua.size(); ++i) {
            unsigned char c = static_cast<unsigned char>(ketQua[i]);
            if (!isalpha(c) && c != ' ') {
                loi = "Ten khach hang khong hop le: chi duoc gom chu cai va khoang trang "
                      "(khong chua chu so hoac ky tu dac biet).";
                return false;
            }
        }
        return true;
    }

    // Ma hang: bat buoc DUNG 4 ky tu, chi gom chu cai va chu so (khong khoang trang)
    static bool maHang(const string& s, string& ketQua, string& loi) {
        ketQua = XuLiChuoi::catKhoangTrang(s);
        if (ketQua.empty()) {
            loi = "Ma hang khong hop le: khong duoc de trong hoac chi nhap khoang trang.";
            return false;
        }
        if (ketQua.size() != 4) {
            loi = "Ma hang khong hop le: phai gom DUNG 4 ky tu (ban nhap " +
                  to_string(ketQua.size()) + " ky tu).";
            return false;
        }
        for (size_t i = 0; i < ketQua.size(); ++i) {
            if (!isalnum(static_cast<unsigned char>(ketQua[i]))) {
                loi = "Ma hang khong hop le: chi duoc gom chu cai va chu so (khong khoang trang/ky tu dac biet).";
                return false;
            }
        }
        ketQua = XuLiChuoi::chuHoa(ketQua);
        return true;
    }

    // So nguyen trong khoang [nho, lon]
    static bool soNguyen(const string& s, const string& tenTruong,
                         long long nho, long long lon, long long& ketQua, string& loi) {
        string chuoi = XuLiChuoi::catKhoangTrang(s);
        if (chuoi.empty()) {
            loi = tenTruong + " khong hop le: khong duoc de trong.";
            return false;
        }
        if (chuoi[0] == '-') {
            loi = tenTruong + " khong hop le: khong duoc nhap so am.";
            return false;
        }
        if (!XuLiChuoi::laSoNguyenKhongAm(chuoi) || chuoi.size() > 15) {
            loi = tenTruong + " khong hop le: phai la so nguyen khong am "
                              "(khong chua chu cai, dau cach hoac ky tu dac biet).";
            return false;
        }
        long long giaTri = stoll(chuoi);
        if (giaTri < nho || giaTri > lon) {
            loi = tenTruong + " khong hop le: phai nam trong khoang tu " +
                  to_string(nho) + " den " + to_string(lon) + ".";
            return false;
        }
        ketQua = giaTri;
        return true;
    }

    // Gia ban: so nguyen tu 1.000 den 1.000.000.000 VND va phai la boi so cua 1.000 VND
    static bool giaBan(const string& s, long long& ketQua, string& loi) {
        if (!soNguyen(s, "Gia ban", 1000LL, 1000000000LL, ketQua, loi)) {
            return false;
        }
        if (ketQua % 1000 != 0) {
            loi = "Gia ban khong hop le: phai la boi so cua 1.000 VND (vd: 50000, 150000).";
            return false;
        }
        return true;
    }

    // So dien thoai Viet Nam: chi gom chu so, DUNG 10 chu so va bat dau bang '0'
    static bool soDienThoai(const string& s, string& ketQua, string& loi) {
        ketQua = XuLiChuoi::catKhoangTrang(s);
        if (ketQua.empty()) {
            loi = "So dien thoai khong hop le: khong duoc de trong.";
            return false;
        }
        if (!XuLiChuoi::laSoNguyenKhongAm(ketQua)) {
            loi = "So dien thoai khong hop le: chi duoc gom cac chu so 0-9.";
            return false;
        }
        if (ketQua.size() != 10) {
            loi = "So dien thoai khong hop le: phai gom DUNG 10 chu so (ban nhap " +
                  to_string(ketQua.size()) + " chu so).";
            return false;
        }
        if (ketQua[0] != '0') {
            loi = "So dien thoai khong hop le: phai bat dau bang chu so 0.";
            return false;
        }
        return true;
    }

    // Ngay nhap kho: dd/mm/yyyy hop le tren lich va khong lon hon ngay hien tai
    static bool ngayNhapKho(const string& s, NgayThang& ketQua, string& loi) {
        string chuoi = XuLiChuoi::catKhoangTrang(s);
        if (chuoi.empty()) {
            loi = "Ngay nhap kho khong hop le: khong duoc de trong.";
            return false;
        }
        if (!NgayThang::taoTuChuoi(chuoi, ketQua)) {
            loi = "Ngay nhap kho khong hop le: phai dung dinh dang dd/mm/yyyy "
                  "va la ngay ton tai trong lich (vd: 15/10/2026).";
            return false;
        }
        if (ketQua.lonHon(NgayThang::homNay())) {
            loi = "Ngay nhap kho khong hop le: khong duoc lon hon ngay hien tai (" +
                  NgayThang::homNay().chuyenThanhChuoi() + ").";
            return false;
        }
        return true;
    }
};

// ============================================================================
// PHAN 2: CAU TRUC DU LIEU TU CAI DAT (CHUONG 3: DSLK DON, CHUONG 4: HANG DOI)
// ============================================================================

template <class T>
struct Node {
    T data;
    Node<T>* next;
    explicit Node(const T& x) : data(x), next(NULL) {}
};

// Chuong 3: Danh sach lien ket don (LinkedList)
// Dung cho: danh sach tai khoan Admin va danh sach mat hang trong moi Don hang
template <class T>
class DanhSachLienKet {
public:
    DanhSachLienKet() : m_dau(NULL), m_cuoi(NULL), m_soPhanTu(0) {}

    DanhSachLienKet(const DanhSachLienKet& khac) : m_dau(NULL), m_cuoi(NULL), m_soPhanTu(0) {
        saoChep(khac);
    }

    DanhSachLienKet& operator=(const DanhSachLienKet& khac) {
        if (this != &khac) {
            xoaTatCa();
            saoChep(khac);
        }
        return *this;
    }

    ~DanhSachLienKet() {
        xoaTatCa();
    }

    // Them phan tu vao cuoi danh sach - O(1)
    void themCuoi(const T& x) {
        Node<T>* nutMoi = new Node<T>(x);
        if (m_dau == NULL) {
            m_dau = m_cuoi = nutMoi;
        } else {
            m_cuoi->next = nutMoi;
            m_cuoi = nutMoi;
        }
        ++m_soPhanTu;
    }

    Node<T>* layDau() { return m_dau; }
    const Node<T>* layDau() const { return m_dau; }
    int kichThuoc() const { return m_soPhanTu; }
    bool laRong() const { return m_soPhanTu == 0; }

    void xoaTatCa() {
        while (m_dau != NULL) {
            Node<T>* tam = m_dau;
            m_dau = m_dau->next;
            delete tam;
        }
        m_cuoi = NULL;
        m_soPhanTu = 0;
    }

private:
    void saoChep(const DanhSachLienKet& khac) {
        const Node<T>* p = khac.m_dau;
        while (p != NULL) {
            themCuoi(p->data);
            p = p->next;
        }
    }

    Node<T>* m_dau;
    Node<T>* m_cuoi;
    int m_soPhanTu;
};

// Chuong 4: Hang doi FIFO (Queue) cai dat bang danh sach lien ket
// Dung cho: danh sach Don hang cho xu li (don dat truoc xu li truoc)
template <class T>
class HangDoi {
public:
    HangDoi() : m_dau(NULL), m_cuoi(NULL), m_soPhanTu(0) {}

    HangDoi(const HangDoi& khac) : m_dau(NULL), m_cuoi(NULL), m_soPhanTu(0) {
        saoChep(khac);
    }

    HangDoi& operator=(const HangDoi& khac) {
        if (this != &khac) {
            xoaTatCa();
            saoChep(khac);
        }
        return *this;
    }

    ~HangDoi() {
        xoaTatCa();
    }

    // Enqueue: them vao cuoi hang doi - O(1)
    void them(const T& x) {
        Node<T>* nutMoi = new Node<T>(x);
        if (m_cuoi == NULL) {
            m_dau = m_cuoi = nutMoi;
        } else {
            m_cuoi->next = nutMoi;
            m_cuoi = nutMoi;
        }
        ++m_soPhanTu;
    }

    // GetFront: xem phan tu o dau hang doi (hang doi phai khong rong)
    const T& layDau() const {
        return m_dau->data;
    }

    // Dequeue: xoa phan tu o dau hang doi - O(1)
    void boDau() {
        if (m_dau == NULL) return;
        Node<T>* tam = m_dau;
        m_dau = m_dau->next;
        if (m_dau == NULL) {
            m_cuoi = NULL;
        }
        delete tam;
        --m_soPhanTu;
    }

    // Tra ve nut dau de duyet hien thi / ghi file theo dung thu tu FIFO
    const Node<T>* layNutDau() const { return m_dau; }
    int kichThuoc() const { return m_soPhanTu; }
    bool laRong() const { return m_soPhanTu == 0; }

    void xoaTatCa() {
        while (!laRong()) {
            boDau();
        }
    }

private:
    void saoChep(const HangDoi& khac) {
        const Node<T>* p = khac.m_dau;
        while (p != NULL) {
            them(p->data);
            p = p->next;
        }
    }

    Node<T>* m_dau;
    Node<T>* m_cuoi;
    int m_soPhanTu;
};

// ============================================================================
// PHAN 3: CAC LOP DOI TUONG NGHIEP VU (HangHoa, TaiKhoan, DonHang)
// ============================================================================

// Dinh dang 1 dong trong HangHoa.txt:
//   maHang|tenHang|noiSanXuat|mauSac|giaBan|ngayNhapKho|soLuong
class HangHoa {
public:
    HangHoa() : m_giaBan(0), m_soLuong(0) {}

    HangHoa(const string& maHang, const string& tenHang, const string& noiSanXuat,
            const string& mauSac, long long giaBan, const NgayThang& ngayNhapKho, int soLuong)
        : m_maHang(maHang), m_tenHang(tenHang), m_noiSanXuat(noiSanXuat), m_mauSac(mauSac),
          m_giaBan(giaBan), m_ngayNhapKho(ngayNhapKho), m_soLuong(soLuong) {}

    const string& layMaHang() const { return m_maHang; }
    const string& layTenHang() const { return m_tenHang; }
    const string& layNoiSanXuat() const { return m_noiSanXuat; }
    const string& layMauSac() const { return m_mauSac; }
    long long layGiaBan() const { return m_giaBan; }
    const NgayThang& layNgayNhapKho() const { return m_ngayNhapKho; }
    int laySoLuong() const { return m_soLuong; }

    void datSoLuong(int soLuong) { m_soLuong = soLuong; }

    string chuyenThanhChuoi() const {
        return m_maHang + "|" + m_tenHang + "|" + m_noiSanXuat + "|" + m_mauSac + "|" +
               to_string(m_giaBan) + "|" + m_ngayNhapKho.chuyenThanhChuoi() + "|" +
               to_string(m_soLuong);
    }

    static bool taoTuChuoi(const string& dong, HangHoa& ketQua) {
        vector<string> phan = XuLiChuoi::tachChuoi(dong, '|');
        if (phan.size() != 7) return false;

        string ma, ten, noi, mau, loi;
        long long gia = 0, soLuong = 0;
        NgayThang ngay;

        if (!KiemTra::maHang(phan[0], ma, loi)) return false;
        if (!KiemTra::chuoiKhongRong(phan[1], "Ten hang", ten, loi)) return false;
        if (!KiemTra::chuoiKhongCoSo(phan[2], "Noi san xuat", noi, loi)) return false;
        if (!KiemTra::chuoiKhongCoSo(phan[3], "Mau sac", mau, loi)) return false;
        if (!KiemTra::giaBan(phan[4], gia, loi)) return false;
        if (!KiemTra::ngayNhapKho(phan[5], ngay, loi)) return false;
        if (!KiemTra::soNguyen(phan[6], "So luong", 0, 1000000, soLuong, loi)) return false;

        ketQua = HangHoa(ma, ten, noi, mau, gia, ngay, static_cast<int>(soLuong));
        return true;
    }

private:
    string m_maHang;
    string m_tenHang;
    string m_noiSanXuat;
    string m_mauSac;
    long long m_giaBan;
    NgayThang m_ngayNhapKho;
    int m_soLuong;
};

// Dinh dang 1 dong trong Admin.txt: user|password
class TaiKhoan {
public:
    TaiKhoan() {}
    TaiKhoan(const string& user, const string& matKhau) : m_user(user), m_matKhau(matKhau) {}

    const string& layUser() const { return m_user; }

    bool khop(const string& user, const string& matKhau) const {
        return m_user == user && m_matKhau == matKhau;
    }

    static bool taoTuChuoi(const string& dong, TaiKhoan& ketQua) {
        vector<string> phan = XuLiChuoi::tachChuoi(dong, '|');
        if (phan.size() != 2 || phan[0].empty() || phan[1].empty()) {
            return false;
        }
        ketQua = TaiKhoan(phan[0], phan[1]);
        return true;
    }

private:
    string m_user;
    string m_matKhau;
};

// Mot mat hang trong don hang
class MucDonHang {
public:
    MucDonHang() : m_soLuong(0), m_thanhTien(0) {}
    MucDonHang(const string& maHang, int soLuong, long long thanhTien)
        : m_maHang(maHang), m_soLuong(soLuong), m_thanhTien(thanhTien) {}

    const string& layMaHang() const { return m_maHang; }
    int laySoLuong() const { return m_soLuong; }
    long long layThanhTien() const { return m_thanhTien; }

private:
    string m_maHang;
    int m_soLuong;
    long long m_thanhTien;
};

// Dinh dang 1 dong trong DonHang.txt:
//   soThuTu|tenKhach|diaChi|soDienThoai|ngayDat|tongTien|ma1:sl1:thanhTien1,ma2:sl2:thanhTien2
class DonHang {
public:
    DonHang() : m_soThuTu(0), m_tongTien(0) {}

    DonHang(int soThuTu, const string& tenKhach, const string& diaChi,
            const string& soDienThoai, const NgayThang& ngayDat)
        : m_soThuTu(soThuTu), m_tenKhach(tenKhach), m_diaChi(diaChi),
          m_soDienThoai(soDienThoai), m_ngayDat(ngayDat), m_tongTien(0) {}

    int laySoThuTu() const { return m_soThuTu; }
    const string& layTenKhach() const { return m_tenKhach; }
    const string& layDiaChi() const { return m_diaChi; }
    const string& laySoDienThoai() const { return m_soDienThoai; }
    const NgayThang& layNgayDat() const { return m_ngayDat; }
    long long layTongTien() const { return m_tongTien; }
    const DanhSachLienKet<MucDonHang>& layCacMuc() const { return m_cacMuc; }

    void themMuc(const MucDonHang& muc) {
        m_cacMuc.themCuoi(muc);
        m_tongTien += muc.layThanhTien();
    }

    // Kiem tra ma hang da co trong don hang nay chua
    bool coMaHang(const string& maHang) const {
        const Node<MucDonHang>* p = m_cacMuc.layDau();
        while (p != NULL) {
            if (p->data.layMaHang() == maHang) return true;
            p = p->next;
        }
        return false;
    }

    string chuyenThanhChuoi() const {
        string chuoiMuc = "";
        const Node<MucDonHang>* p = m_cacMuc.layDau();
        while (p != NULL) {
            if (!chuoiMuc.empty()) chuoiMuc += ",";
            chuoiMuc += p->data.layMaHang() + ":" + to_string(p->data.laySoLuong()) + ":" +
                        to_string(p->data.layThanhTien());
            p = p->next;
        }
        return to_string(m_soThuTu) + "|" + m_tenKhach + "|" + m_diaChi + "|" +
               m_soDienThoai + "|" + m_ngayDat.chuyenThanhChuoi() + "|" +
               to_string(m_tongTien) + "|" + chuoiMuc;
    }

    static bool taoTuChuoi(const string& dong, DonHang& ketQua) {
        vector<string> phan = XuLiChuoi::tachChuoi(dong, '|');
        if (phan.size() != 7) return false;

        string ten, diaChi, sdt, loi;
        long long stt = 0;
        NgayThang ngay;

        if (!KiemTra::soNguyen(phan[0], "So thu tu", 1, 999999999LL, stt, loi)) return false;
        if (!KiemTra::tenKhachHang(phan[1], ten, loi)) return false;
        if (!KiemTra::chuoiKhongRong(phan[2], "Dia chi", diaChi, loi)) return false;
        if (!KiemTra::soDienThoai(phan[3], sdt, loi)) return false;
        if (!NgayThang::taoTuChuoi(phan[4], ngay)) return false;

        DonHang don(static_cast<int>(stt), ten, diaChi, sdt, ngay);
        vector<string> dsMuc = XuLiChuoi::tachChuoi(phan[6], ',');
        if (dsMuc.empty()) return false;

        for (size_t i = 0; i < dsMuc.size(); ++i) {
            vector<string> truong = XuLiChuoi::tachChuoi(dsMuc[i], ':');
            if (truong.size() != 3) return false;
            string ma;
            long long sl = 0, tt = 0;
            if (!KiemTra::maHang(truong[0], ma, loi)) return false;
            if (!KiemTra::soNguyen(truong[1], "So luong", 1, 1000000LL, sl, loi)) return false;
            if (!KiemTra::soNguyen(truong[2], "Thanh tien", 0, 1000000000000LL, tt, loi)) return false;
            don.themMuc(MucDonHang(ma, static_cast<int>(sl), tt));
        }
        ketQua = don;
        return true;
    }

private:
    int m_soThuTu;
    string m_tenKhach;
    string m_diaChi;
    string m_soDienThoai;
    NgayThang m_ngayDat;
    long long m_tongTien;
    DanhSachLienKet<MucDonHang> m_cacMuc;
};

// ============================================================================
// PHAN 4: CAY NHI PHAN TIM KIEM (CHUONG 5) VA TIM KIEM / SAP XEP (CHUONG 2)
// ============================================================================

// Chuong 5: Cay nhi phan tim kiem (BST) luu HangHoa theo khoa la Ma hang
struct NutCay {
    HangHoa data;
    NutCay* trai;
    NutCay* phai;
    explicit NutCay(const HangHoa& h) : data(h), trai(NULL), phai(NULL) {}
};

class CayHangHoa {
public:
    CayHangHoa() : m_goc(NULL), m_soLuong(0) {}

    ~CayHangHoa() {
        xoaTatCa();
    }

    // Chen 1 hang hoa vao cay BST theo maHang. Tra ve false neu trung ma hang.
    bool chen(const HangHoa& h) {
        bool daChen = false;
        m_goc = chenDeQuy(m_goc, h, daChen);
        if (daChen) ++m_soLuong;
        return daChen;
    }

    // Tim kiem nhi phan tren BST theo maHang - do phuc tap trung binh O(log n)
    HangHoa* timTheoMa(const string& maHang) {
        NutCay* p = m_goc;
        while (p != NULL) {
            if (maHang == p->data.layMaHang()) return &p->data;
            if (maHang < p->data.layMaHang()) {
                p = p->trai;
            } else {
                p = p->phai;
            }
        }
        return NULL;
    }

    const HangHoa* timTheoMa(const string& maHang) const {
        const NutCay* p = m_goc;
        while (p != NULL) {
            if (maHang == p->data.layMaHang()) return &p->data;
            if (maHang < p->data.layMaHang()) {
                p = p->trai;
            } else {
                p = p->phai;
            }
        }
        return NULL;
    }

    // Xoa hang hoa theo maHang tren BST (xu li du 3 truong hop xoa nut BST)
    bool xoaTheoMa(const string& maHang) {
        bool daXoa = false;
        m_goc = xoaDeQuy(m_goc, maHang, daXoa);
        if (daXoa) --m_soLuong;
        return daXoa;
    }

    // Duyet trung thu tu (LNR) -> tra ve danh sach tang dan theo Ma hang
    void layDanhSachLNR(vector<const HangHoa*>& ds) const {
        ds.clear();
        duyetLNR(m_goc, ds);
    }

    int kichThuoc() const { return m_soLuong; }
    bool laRong() const { return m_soLuong == 0; }

    void xoaTatCa() {
        giaiPhong(m_goc);
        m_goc = NULL;
        m_soLuong = 0;
    }

private:
    NutCay* chenDeQuy(NutCay* nut, const HangHoa& h, bool& daChen) {
        if (nut == NULL) {
            daChen = true;
            return new NutCay(h);
        }
        if (h.layMaHang() < nut->data.layMaHang()) {
            nut->trai = chenDeQuy(nut->trai, h, daChen);
        } else if (h.layMaHang() > nut->data.layMaHang()) {
            nut->phai = chenDeQuy(nut->phai, h, daChen);
        } else {
            // Trung khoa maHang -> khong chen
            daChen = false;
        }
        return nut;
    }

    NutCay* timNutNhoNhat(NutCay* nut) const {
        NutCay* p = nut;
        while (p != NULL && p->trai != NULL) {
            p = p->trai;
        }
        return p;
    }

    NutCay* xoaDeQuy(NutCay* nut, const string& maHang, bool& daXoa) {
        if (nut == NULL) {
            daXoa = false;
            return NULL;
        }
        if (maHang < nut->data.layMaHang()) {
            nut->trai = xoaDeQuy(nut->trai, maHang, daXoa);
        } else if (maHang > nut->data.layMaHang()) {
            nut->phai = xoaDeQuy(nut->phai, maHang, daXoa);
        } else {
            // Da tim thay nut can xoa
            daXoa = true;
            // Truong hop 1: nut la hoac chi co 1 con phai
            if (nut->trai == NULL) {
                NutCay* conPhai = nut->phai;
                delete nut;
                return conPhai;
            }
            // Truong hop 2: chi co 1 con trai
            if (nut->phai == NULL) {
                NutCay* conTrai = nut->trai;
                delete nut;
                return conTrai;
            }
            // Truong hop 3: co du 2 con -> tim phan tu the mang nho nhat ben cay con phai
            NutCay* theMang = timNutNhoNhat(nut->phai);
            nut->data = theMang->data;
            bool xoaTam = false;
            nut->phai = xoaDeQuy(nut->phai, theMang->data.layMaHang(), xoaTam);
        }
        return nut;
    }

    void duyetLNR(const NutCay* nut, vector<const HangHoa*>& ds) const {
        if (nut == NULL) return;
        duyetLNR(nut->trai, ds);
        ds.push_back(&nut->data);
        duyetLNR(nut->phai, ds);
    }

    void giaiPhong(NutCay* nut) {
        if (nut == NULL) return;
        giaiPhong(nut->trai);
        giaiPhong(nut->phai);
        delete nut;
    }

    NutCay* m_goc;
    int m_soLuong;
};

// Chuong 2: Cac thuat toan Tim kiem & Sap xep tu cai dat
class ThuatToan {
public:
    // Tim kiem tuyen tinh (Linear Search) theo ten hang hoa, khong phan biet hoa/thuong
    static void timKiemTheoTen(const vector<const HangHoa*>& ds, const string& tuKhoa,
                               vector<const HangHoa*>& ketQua) {
        ketQua.clear();
        string khoaThuong = XuLiChuoi::chuThuong(tuKhoa);
        for (size_t i = 0; i < ds.size(); ++i) {
            string tenThuong = XuLiChuoi::chuThuong(ds[i]->layTenHang());
            if (tenThuong.find(khoaThuong) != string::npos) {
                ketQua.push_back(ds[i]);
            }
        }
    }

    // Sap xep chon (Selection Sort) theo tieu chi:
    //   loai = 1: Gia ban tang dan
    //   loai = 2: Gia ban giam dan
    //   loai = 3: Ten hang hoa A -> Z
    static void sapXepChon(vector<const HangHoa*>& ds, int loai) {
        int n = static_cast<int>(ds.size());
        for (int i = 0; i < n - 1; ++i) {
            int viTriTotNhat = i;
            for (int j = i + 1; j < n; ++j) {
                if (dungTruoc(ds[j], ds[viTriTotNhat], loai)) {
                    viTriTotNhat = j;
                }
            }
            if (viTriTotNhat != i) {
                const HangHoa* tam = ds[i];
                ds[i] = ds[viTriTotNhat];
                ds[viTriTotNhat] = tam;
            }
        }
    }

private:
    static bool dungTruoc(const HangHoa* a, const HangHoa* b, int loai) {
        if (loai == 1) {  // Gia tang dan
            if (a->layGiaBan() != b->layGiaBan()) return a->layGiaBan() < b->layGiaBan();
            return a->layMaHang() < b->layMaHang();
        }
        if (loai == 2) {  // Gia giam dan
            if (a->layGiaBan() != b->layGiaBan()) return a->layGiaBan() > b->layGiaBan();
            return a->layMaHang() < b->layMaHang();
        }
        // Ten A -> Z (khong phan biet hoa/thuong)
        string tenA = XuLiChuoi::chuThuong(a->layTenHang());
        string tenB = XuLiChuoi::chuThuong(b->layTenHang());
        if (tenA != tenB) return tenA < tenB;
        return a->layMaHang() < b->layMaHang();
    }
};

// ============================================================================
// PHAN 5: LOP QUAN LI CUA HANG (DOC/GHI FILE VA CAC CHUC NANG CHINH)
// ============================================================================

enum KetQuaDangNhap { DANG_NHAP_THANH_CONG, DANG_NHAP_SAI_QUA_3_LAN, DANG_NHAP_THOAT_ESC };

class CuaHang {
public:
    CuaHang()
        : m_fileHangHoa("HangHoa.txt"), m_fileDonHang("DonHang.txt"),
          m_fileAdmin("Admin.txt"), m_soDonTiepTheo(1) {}

    // ---------- Doc du lieu tu 3 file khi khoi dong ----------
    void taiDuLieu() {
        docFileHangHoa();
        docFileAdmin();
        docFileDonHang();
    }

    // ---------- Chuc nang 1: Hien thi thong tin hang hoa ----------
    void hienThiHangHoa() const {
        GiaoDien::inTieuDe("THONG TIN HANG HOA");
        if (m_hangHoa.laRong()) {
            GiaoDien::thongBaoThongTin("Hien chua co hang hoa nao trong kho.");
            return;
        }
        vector<const HangHoa*> ds;
        m_hangHoa.layDanhSachLNR(ds);
        inBangHangHoa(ds);
        GiaoDien::inDong("  Tong so mat hang: " + to_string(m_hangHoa.kichThuoc()) +
                             "  (Dang hien thi theo Ma hang tang dan - duyet LNR cay BST)",
                         GiaoDien::XANH_NGOC);

        // Cho phep xem sap xep bang thuat toan Selection Sort (Chuong 2)
        while (!GiaoDien::hetDuLieuVao()) {
            GiaoDien::inDong(
                "\n  Tuy chon sap xep (Selection Sort): [1] Gia tang dan  |  [2] Gia giam dan  |  "
                "[3] Ten A-Z  |  [4] Ma hang (BST)  |  [0] Quay lai",
                GiaoDien::VANG);
            string chon = XuLiChuoi::catKhoangTrang(GiaoDien::nhapDong("  >> Chon (0-4): "));
            if (chon == "0" || GiaoDien::hetDuLieuVao()) {
                return;
            }
            if (chon == "1" || chon == "2" || chon == "3" || chon == "4") {
                m_hangHoa.layDanhSachLNR(ds);
                string moTa = "Ma hang tang dan (duyet LNR cay BST)";
                if (chon == "1") {
                    ThuatToan::sapXepChon(ds, 1);
                    moTa = "Gia ban tang dan (Selection Sort)";
                } else if (chon == "2") {
                    ThuatToan::sapXepChon(ds, 2);
                    moTa = "Gia ban giam dan (Selection Sort)";
                } else if (chon == "3") {
                    ThuatToan::sapXepChon(ds, 3);
                    moTa = "Ten hang A -> Z (Selection Sort)";
                }
                cout << "\n";
                inBangHangHoa(ds);
                GiaoDien::inDong("  Da sap xep theo: " + moTa, GiaoDien::XANH_LA);
            } else {
                GiaoDien::thongBaoLoi("Lua chon khong hop le! Vui long nhap so tu 0 den 4.");
            }
        }
    }

    // ---------- Chuc nang 2: Tim kiem thong tin hang hoa theo ten ----------
    void timKiemHangHoa() const {
        GiaoDien::inTieuDe("TIM KIEM THONG TIN HANG HOA");
        if (m_hangHoa.laRong()) {
            GiaoDien::thongBaoThongTin("Hien chua co hang hoa nao de tim kiem.");
            return;
        }
        string tuKhoa, loi;
        if (!KiemTra::chuoiKhongRong(GiaoDien::nhapDong("  Nhap ten hang hoa can tim: "),
                                     "Ten hang can tim", tuKhoa, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        vector<const HangHoa*> tatCa, ketQua;
        m_hangHoa.layDanhSachLNR(tatCa);
        ThuatToan::timKiemTheoTen(tatCa, tuKhoa, ketQua);

        if (ketQua.empty()) {
            GiaoDien::thongBaoLoi("Khong tim thay hang hoa nao co ten chua \"" + tuKhoa + "\".");
        } else {
            inBangHangHoa(ketQua);
            GiaoDien::thongBaoThanhCong("Tim thay " + to_string(ketQua.size()) +
                                        " mat hang phu hop voi tu khoa \"" + tuKhoa + "\".");
        }
    }

    // ---------- Chuc nang 3: Dat hang ----------
    void datHang() {
        GiaoDien::inTieuDe("DAT HANG ONLINE");
        if (!coHangDeDat()) {
            GiaoDien::thongBaoLoi("Hien khong co mat hang nao con hang de dat.");
            return;
        }
        inBangTatCaHangHoa();
        cout << "\n";

        string ten, diaChi, sdt, loi;
        if (!KiemTra::tenKhachHang(GiaoDien::nhapDong("  Ten khach hang     : "), ten, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        if (!KiemTra::chuoiKhongRong(GiaoDien::nhapDong("  Dia chi khach hang : "),
                                     "Dia chi khach hang", diaChi, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        if (!KiemTra::soDienThoai(GiaoDien::nhapDong("  So dien thoai      : "), sdt, loi)) {
            baoLoiVaHuy(loi);
            return;
        }

        DonHang don(m_soDonTiepTheo, ten, diaChi, sdt, NgayThang::homNay());
        do {
            cout << "\n";
            string ma;
            if (!KiemTra::maHang(GiaoDien::nhapDong("  Ma hang (4 ky tu)  : "), ma, loi)) {
                baoLoiVaHuy(loi);
                return;
            }
            if (don.coMaHang(ma)) {
                baoLoiVaHuy("Khong hop le: Ma hang " + ma + " da co trong don hang nay.");
                return;
            }
            const HangHoa* hang = m_hangHoa.timTheoMa(ma);
            if (hang == NULL) {
                baoLoiVaHuy("Khong hop le: Ma hang " + ma + " khong ton tai trong he thong.");
                return;
            }
            if (hang->laySoLuong() <= 0) {
                baoLoiVaHuy("Khong hop le: Hang \"" + hang->layTenHang() +
                            "\" da het hang (so luong = 0).");
                return;
            }
            // Uu tien hang doi: tru di so luong cac don dat truoc dang cho xu li
            int daGiu = soLuongDaGiu(ma);
            int conLai = hang->laySoLuong() - daGiu;
            if (conLai <= 0) {
                baoLoiVaHuy("Khong hop le: Hang \"" + hang->layTenHang() +
                            "\" da duoc cac don hang dat truoc dat het (ton kho: " +
                            to_string(hang->laySoLuong()) + ", dang cho xu li: " +
                            to_string(daGiu) + ").");
                return;
            }
            GiaoDien::inDong("  -> Ten hang: " + hang->layTenHang() + " | Don gia: " +
                                 XuLiChuoi::dinhDangTien(hang->layGiaBan()) + " VND | Ton kho: " +
                                 to_string(hang->laySoLuong()) + " | Cho xu li: " +
                                 to_string(daGiu) + " | Co the dat toi da: " + to_string(conLai),
                             GiaoDien::XANH_NGOC);

            long long soLuong = 0;
            if (!KiemTra::soNguyen(GiaoDien::nhapDong("  So luong dat       : "),
                                   "So luong dat", 1, conLai, soLuong, loi)) {
                baoLoiVaHuy(loi);
                return;
            }
            don.themMuc(MucDonHang(ma, static_cast<int>(soLuong), hang->layGiaBan() * soLuong));
        } while (GiaoDien::hoiCoKhong("  Ban co muon dat them ma hang khac vao don nay? (c/k): "));

        inChiTietDon(don);
        if (!GiaoDien::hoiCoKhong("  Xac nhan dat don hang nay? (c/k): ")) {
            GiaoDien::thongBaoThongTin("Da huy dat hang.");
            return;
        }
        m_donCho.them(don);
        ++m_soDonTiepTheo;
        ghiFileDonHang();
        GiaoDien::thongBaoThanhCong("Don hang dang cho xu li (Don so " +
                                    to_string(don.laySoThuTu()) +
                                    "). Da luu vao file " + m_fileDonHang + ".");
    }

    // ---------- Chuc nang 4: Dang nhap khu vuc Quan li ----------
    KetQuaDangNhap dangNhap() const {
        const int soLanToiDa = 3;
        for (int lan = 1; lan <= soLanToiDa; ++lan) {
            GiaoDien::xoaManHinh();
            GiaoDien::inTieuDeDangNhap();
            GiaoDien::thongBaoThongTin("Nhan ESC de thoat he thong. Nhap sai " +
                                       to_string(soLanToiDa) + " lan se thoat he thong.");
            cout << "\n";
            string user, matKhau;
            if (!GiaoDien::nhapDangNhap("    User     : ", false, user)) {
                return DANG_NHAP_THOAT_ESC;
            }
            if (!GiaoDien::nhapDangNhap("    Password : ", true, matKhau)) {
                return DANG_NHAP_THOAT_ESC;
            }

            if (XuLiChuoi::catKhoangTrang(user).empty() || matKhau.empty()) {
                GiaoDien::thongBaoLoi("Khong hop le: User va Password khong duoc de trong (lan " +
                                      to_string(lan) + "/" + to_string(soLanToiDa) + ").");
            } else if (kiemTraTaiKhoan(user, matKhau)) {
                GiaoDien::thongBaoThanhCong("Dang nhap thanh cong! Xin chao quan tri vien " +
                                            user + ".");
                return DANG_NHAP_THANH_CONG;
            } else {
                GiaoDien::thongBaoLoi("Sai user hoac password (lan " + to_string(lan) + "/" +
                                      to_string(soLanToiDa) + ").");
            }

            if (lan < soLanToiDa) {
                GiaoDien::tamDung("Nhan Enter de nhap lai...");
            }
        }
        return DANG_NHAP_SAI_QUA_3_LAN;
    }

    // ---------- Quan li: Xu li don hang theo nguyen tac FIFO (Hang doi) ----------
    void xuLiDonHang() {
        GiaoDien::inTieuDe("XU LI DON HANG (HANG DOI FIFO)");
        if (m_donCho.laRong()) {
            GiaoDien::thongBaoThongTin("Hien khong co don hang nao dang cho xu li.");
            return;
        }
        GiaoDien::inDong("  Co " + to_string(m_donCho.kichThuoc()) +
                             " don hang dang cho (don dat truoc xu li truoc):",
                         GiaoDien::VANG);

        vector<GiaoDien::Cot> cot;
        cot.push_back(GiaoDien::Cot("Don so", 7, true));
        cot.push_back(GiaoDien::Cot("Khach hang", 22));
        cot.push_back(GiaoDien::Cot("SDT", 10));
        cot.push_back(GiaoDien::Cot("Ngay dat", 10));
        cot.push_back(GiaoDien::Cot("Tong tien (VND)", 15, true));

        vector<vector<string> > bang;
        vector<GiaoDien::Mau> mau;
        const Node<DonHang>* p = m_donCho.layNutDau();
        while (p != NULL) {
            const DonHang& d = p->data;
            vector<string> dong;
            dong.push_back(to_string(d.laySoThuTu()));
            dong.push_back(d.layTenKhach());
            dong.push_back(d.laySoDienThoai());
            dong.push_back(d.layNgayDat().chuyenThanhChuoi());
            dong.push_back(XuLiChuoi::dinhDangTien(d.layTongTien()));
            bang.push_back(dong);
            mau.push_back(bang.size() == 1 ? GiaoDien::VANG : GiaoDien::MAC_DINH);
            p = p->next;
        }
        GiaoDien::inBang(cot, bang, mau);

        // Lay don dau hang doi (FIFO)
        DonHang don = m_donCho.layDau();
        GiaoDien::inDong("\n  Don hang duoc xu li tiep theo (dong mau vang - dau hang doi):",
                         GiaoDien::VANG);
        inChiTietDon(don);

        if (!GiaoDien::hoiCoKhong("  Xac nhan xu li don hang so " +
                                  to_string(don.laySoThuTu()) + "? (c/k): ")) {
            GiaoDien::thongBaoThongTin("Chua xu li don hang. Don van nam trong danh sach cho.");
            return;
        }

        // Kiem tra lai ton kho cho tat ca ma hang trong don truoc khi tru
        string lyDoLoi = "";
        const Node<MucDonHang>* q = don.layCacMuc().layDau();
        while (q != NULL) {
            const HangHoa* h = m_hangHoa.timTheoMa(q->data.layMaHang());
            if (h == NULL) {
                lyDoLoi = "Ma hang " + q->data.layMaHang() + " khong con ton tai trong kho.";
                break;
            }
            if (h->laySoLuong() < q->data.laySoLuong()) {
                lyDoLoi = "Ma hang " + q->data.layMaHang() + " khong du so luong (can " +
                          to_string(q->data.laySoLuong()) + ", ton kho " +
                          to_string(h->laySoLuong()) + ").";
                break;
            }
            q = q->next;
        }

        if (!lyDoLoi.empty()) {
            m_donCho.boDau();
            ghiFileDonHang();
            GiaoDien::thongBaoLoi("Khong the xu li don hang so " + to_string(don.laySoThuTu()) +
                                  ": " + lyDoLoi);
            GiaoDien::thongBaoThongTin("Da huy don hang nay khoi hang doi va cap nhat " +
                                       m_fileDonHang + ".");
            return;
        }

        // Tru so luong hang hoa trong cay BST
        q = don.layCacMuc().layDau();
        while (q != NULL) {
            HangHoa* h = m_hangHoa.timTheoMa(q->data.layMaHang());
            h->datSoLuong(h->laySoLuong() - q->data.laySoLuong());
            q = q->next;
        }
        // Xoa don dau khoi hang doi va luu ca 2 file
        m_donCho.boDau();
        ghiFileHangHoa();
        ghiFileDonHang();
        GiaoDien::thongBaoThanhCong("Da xu li xong don hang so " + to_string(don.laySoThuTu()) +
                                    ". Da xoa khoi " + m_fileDonHang +
                                    " va cap nhat so luong trong " + m_fileHangHoa + ".");
    }

    // ---------- Quan li hang hoa: Them hang hoa moi ----------
    void themHangHoa() {
        GiaoDien::inTieuDe("THEM HANG HOA MOI");
        string ma, ten, noi, mau, loi;
        long long gia = 0, soLuong = 0;
        NgayThang ngay;

        if (!KiemTra::maHang(GiaoDien::nhapDong("  Ma hang (4 ky tu)       : "), ma, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        if (m_hangHoa.timTheoMa(ma) != NULL) {
            baoLoiVaHuy("Ma hang khong hop le: ma hang " + ma +
                        " da ton tai trong he thong, khong duoc trung.");
            return;
        }
        if (!KiemTra::chuoiKhongRong(GiaoDien::nhapDong("  Ten hang                : "),
                                     "Ten hang", ten, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        if (!KiemTra::chuoiKhongCoSo(GiaoDien::nhapDong("  Noi san xuat            : "),
                                     "Noi san xuat", noi, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        if (!KiemTra::chuoiKhongCoSo(GiaoDien::nhapDong("  Mau sac                 : "),
                                     "Mau sac", mau, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        if (!KiemTra::giaBan(GiaoDien::nhapDong("  Gia ban (boi so 1000)   : "), gia, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        if (!KiemTra::ngayNhapKho(GiaoDien::nhapDong("  Ngay nhap (dd/mm/yyyy)  : "), ngay, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        if (!KiemTra::soNguyen(GiaoDien::nhapDong("  So luong                : "),
                               "So luong", 1, 1000000, soLuong, loi)) {
            baoLoiVaHuy(loi);
            return;
        }

        m_hangHoa.chen(HangHoa(ma, ten, noi, mau, gia, ngay, static_cast<int>(soLuong)));
        ghiFileHangHoa();
        GiaoDien::thongBaoThanhCong("Da them hang hoa " + ma + " - " + ten +
                                    " va luu vao file " + m_fileHangHoa + ".");
    }

    // ---------- Quan li hang hoa: Xoa hang hoa theo ma hang ----------
    void xoaHangHoa() {
        GiaoDien::inTieuDe("XOA HANG HOA THEO MA HANG");
        if (m_hangHoa.laRong()) {
            GiaoDien::thongBaoThongTin("Danh sach hang hoa dang rong.");
            return;
        }
        inBangTatCaHangHoa();
        cout << "\n";

        string ma, loi;
        if (!KiemTra::maHang(GiaoDien::nhapDong("  Nhap ma hang can xoa (4 ky tu): "), ma, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        const HangHoa* hang = m_hangHoa.timTheoMa(ma);
        if (hang == NULL) {
            baoLoiVaHuy("Khong hop le: Ma hang " + ma + " khong ton tai trong danh sach.");
            return;
        }
        int daGiu = soLuongDaGiu(ma);
        if (daGiu > 0) {
            baoLoiVaHuy("Khong the xoa: ma hang " + ma +
                        " dang nam trong don hang cho xu li (" + to_string(daGiu) +
                        " san pham). Vui long xu li don hang truoc.");
            return;
        }
        vector<const HangHoa*> dsChon;
        dsChon.push_back(hang);
        inBangHangHoa(dsChon);

        if (!GiaoDien::hoiCoKhong("  Ban co chac chan muon xoa ma hang " + ma + "? (c/k): ")) {
            GiaoDien::thongBaoThongTin("Da huy thao tac xoa.");
            return;
        }
        m_hangHoa.xoaTheoMa(ma);
        ghiFileHangHoa();
        GiaoDien::thongBaoThanhCong("Da xoa hang hoa " + ma + " va cap nhat file " +
                                    m_fileHangHoa + ".");
    }

    // ---------- Quan li hang hoa: Cap nhat so luong hang hoa ----------
    void capNhatSoLuong() {
        GiaoDien::inTieuDe("CAP NHAT SO LUONG HANG HOA");
        if (m_hangHoa.laRong()) {
            GiaoDien::thongBaoThongTin("Danh sach hang hoa dang rong.");
            return;
        }
        inBangTatCaHangHoa();
        cout << "\n";

        string ma, loi;
        if (!KiemTra::maHang(GiaoDien::nhapDong("  Nhap ma hang can cap nhat (4 ky tu): "),
                             ma, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        HangHoa* hang = m_hangHoa.timTheoMa(ma);
        if (hang == NULL) {
            baoLoiVaHuy("Khong hop le: Ma hang " + ma + " khong ton tai trong danh sach.");
            return;
        }
        int daGiu = soLuongDaGiu(ma);
        GiaoDien::inDong("  -> " + hang->layTenHang() + " | So luong hien tai: " +
                             to_string(hang->laySoLuong()) + " | Dang cho xu li: " +
                             to_string(daGiu),
                         GiaoDien::XANH_NGOC);

        long long soLuongMoi = 0;
        if (!KiemTra::soNguyen(GiaoDien::nhapDong("  Nhap so luong moi: "),
                               "So luong moi", 0, 1000000, soLuongMoi, loi)) {
            baoLoiVaHuy(loi);
            return;
        }
        if (soLuongMoi < daGiu) {
            baoLoiVaHuy("So luong moi (" + to_string(soLuongMoi) +
                        ") khong hop le: nho hon so luong cac don cho xu li dang can (" +
                        to_string(daGiu) + ").");
            return;
        }
        hang->datSoLuong(static_cast<int>(soLuongMoi));
        ghiFileHangHoa();
        GiaoDien::thongBaoThanhCong("Da cap nhat so luong hang " + ma + " thanh " +
                                    to_string(soLuongMoi) + " va luu vao file " +
                                    m_fileHangHoa + ".");
    }

private:
    // ---------- Cac ham doc/ghi file ----------
    void docFileHangHoa() {
        ifstream file(m_fileHangHoa.c_str());
        if (!file.is_open()) {
            GiaoDien::thongBaoThongTin("Chua co file " + m_fileHangHoa +
                                       ", se tu dong tao khi luu du lieu.");
            return;
        }
        int soDongLoi = 0;
        string dong;
        while (getline(file, dong)) {
            XuLiChuoi::xoaCR(dong);
            if (dong.empty() || dong[0] == '#') continue;
            HangHoa h;
            if (HangHoa::taoTuChuoi(dong, h) && m_hangHoa.chen(h)) {
                // Chen thanh cong vao cay BST
            } else {
                ++soDongLoi;
            }
        }
        if (soDongLoi > 0) {
            GiaoDien::thongBaoLoi("File " + m_fileHangHoa + " co " + to_string(soDongLoi) +
                                  " dong sai dinh dang/trung ma, da bo qua.");
        }
    }

    void ghiFileHangHoa() const {
        ofstream file(m_fileHangHoa.c_str());
        if (!file.is_open()) {
            GiaoDien::thongBaoLoi("Khong the mo file " + m_fileHangHoa + " de ghi du lieu.");
            return;
        }
        vector<const HangHoa*> ds;
        m_hangHoa.layDanhSachLNR(ds);
        for (size_t i = 0; i < ds.size(); ++i) {
            file << ds[i]->chuyenThanhChuoi() << "\n";
        }
    }

    void docFileAdmin() {
        ifstream file(m_fileAdmin.c_str());
        if (!file.is_open()) {
            GiaoDien::thongBaoLoi("Khong tim thay file " + m_fileAdmin + "!");
            return;
        }
        int soDongLoi = 0;
        string dong;
        while (getline(file, dong)) {
            XuLiChuoi::xoaCR(dong);
            if (dong.empty() || dong[0] == '#') continue;
            TaiKhoan tk;
            if (TaiKhoan::taoTuChuoi(dong, tk)) {
                m_taiKhoan.themCuoi(tk);
            } else {
                ++soDongLoi;
            }
        }
        if (soDongLoi > 0) {
            GiaoDien::thongBaoLoi("File " + m_fileAdmin + " co " + to_string(soDongLoi) +
                                  " dong sai dinh dang, da bo qua.");
        }
    }

    void docFileDonHang() {
        ifstream file(m_fileDonHang.c_str());
        if (!file.is_open()) {
            GiaoDien::thongBaoThongTin("Chua co file " + m_fileDonHang +
                                       ", se tu dong tao khi co don hang moi.");
            return;
        }
        int soDongLoi = 0;
        int soLonNhat = 0;
        int soTuTieuDe = 1;
        string dong;
        while (getline(file, dong)) {
            XuLiChuoi::xoaCR(dong);
            if (dong.empty()) continue;
            if (dong.compare(0, 6, "#NEXT|") == 0) {
                string phanSo = XuLiChuoi::catKhoangTrang(dong.substr(6));
                if (XuLiChuoi::laSoNguyenKhongAm(phanSo) && phanSo.size() < 10) {
                    soTuTieuDe = stoi(phanSo);
                }
                continue;
            }
            if (dong[0] == '#') continue;
            DonHang don;
            if (DonHang::taoTuChuoi(dong, don)) {
                m_donCho.them(don);
                if (don.laySoThuTu() > soLonNhat) {
                    soLonNhat = don.laySoThuTu();
                }
            } else {
                ++soDongLoi;
            }
        }
        m_soDonTiepTheo = (soTuTieuDe > soLonNhat) ? soTuTieuDe : (soLonNhat + 1);
        if (soDongLoi > 0) {
            GiaoDien::thongBaoLoi("File " + m_fileDonHang + " co " + to_string(soDongLoi) +
                                  " dong sai dinh dang, da bo qua.");
        }
    }

    void ghiFileDonHang() const {
        ofstream file(m_fileDonHang.c_str());
        if (!file.is_open()) {
            GiaoDien::thongBaoLoi("Khong the mo file " + m_fileDonHang + " de ghi du lieu.");
            return;
        }
        file << "#NEXT|" << m_soDonTiepTheo << "\n";
        const Node<DonHang>* p = m_donCho.layNutDau();
        while (p != NULL) {
            file << p->data.chuyenThanhChuoi() << "\n";
            p = p->next;
        }
    }

    // ---------- Cac ham ho tro nghiep vu & hien thi ----------
    static void baoLoiVaHuy(const string& noiDungLoi) {
        GiaoDien::thongBaoLoi(noiDungLoi);
        GiaoDien::thongBaoLoi("Chuc nang dang thuc hien da bi huy do du lieu khong hop le.");
    }

    bool kiemTraTaiKhoan(const string& user, const string& matKhau) const {
        const Node<TaiKhoan>* p = m_taiKhoan.layDau();
        while (p != NULL) {
            if (p->data.khop(user, matKhau)) return true;
            p = p->next;
        }
        return false;
    }

    // Tinh tong so luong cua ma hang da duoc cac don dang cho xu li dat truoc
    int soLuongDaGiu(const string& maHang) const {
        int tong = 0;
        const Node<DonHang>* p = m_donCho.layNutDau();
        while (p != NULL) {
            const Node<MucDonHang>* q = p->data.layCacMuc().layDau();
            while (q != NULL) {
                if (q->data.layMaHang() == maHang) {
                    tong += q->data.laySoLuong();
                }
                q = q->next;
            }
            p = p->next;
        }
        return tong;
    }

    // Kiem tra co it nhat 1 mat hang con co the dat hay khong
    bool coHangDeDat() const {
        vector<const HangHoa*> ds;
        m_hangHoa.layDanhSachLNR(ds);
        for (size_t i = 0; i < ds.size(); ++i) {
            int conLai = ds[i]->laySoLuong() - soLuongDaGiu(ds[i]->layMaHang());
            if (conLai > 0) return true;
        }
        return false;
    }

    void inBangTatCaHangHoa() const {
        vector<const HangHoa*> ds;
        m_hangHoa.layDanhSachLNR(ds);
        inBangHangHoa(ds);
    }

    static void inBangHangHoa(const vector<const HangHoa*>& ds) {
        vector<GiaoDien::Cot> cot;
        cot.push_back(GiaoDien::Cot("STT", 3, true));
        cot.push_back(GiaoDien::Cot("Ma", 4));
        cot.push_back(GiaoDien::Cot("Ten hang", 18));
        cot.push_back(GiaoDien::Cot("Noi SX", 11));
        cot.push_back(GiaoDien::Cot("Mau sac", 8));
        cot.push_back(GiaoDien::Cot("Gia ban (VND)", 13, true));
        cot.push_back(GiaoDien::Cot("Ngay nhap", 10));
        cot.push_back(GiaoDien::Cot("So luong", 8, true));

        vector<vector<string> > bang;
        vector<GiaoDien::Mau> mau;
        for (size_t i = 0; i < ds.size(); ++i) {
            const HangHoa& h = *ds[i];
            vector<string> dong;
            dong.push_back(to_string(i + 1));
            dong.push_back(h.layMaHang());
            dong.push_back(h.layTenHang());
            dong.push_back(h.layNoiSanXuat());
            dong.push_back(h.layMauSac());
            dong.push_back(XuLiChuoi::dinhDangTien(h.layGiaBan()));
            dong.push_back(h.layNgayNhapKho().chuyenThanhChuoi());
            dong.push_back(h.laySoLuong() == 0 ? "Het hang" : to_string(h.laySoLuong()));
            bang.push_back(dong);
            mau.push_back(h.laySoLuong() == 0 ? GiaoDien::DO : GiaoDien::MAC_DINH);
        }
        GiaoDien::inBang(cot, bang, mau);
    }

    void inChiTietDon(const DonHang& don) const {
        vector<pair<string, string> > truong;
        truong.push_back(make_pair(string("Khach hang"), don.layTenKhach()));
        truong.push_back(make_pair(string("Dia chi"), don.layDiaChi()));
        truong.push_back(make_pair(string("So dien thoai"), don.laySoDienThoai()));
        truong.push_back(make_pair(string("Ngay dat"), don.layNgayDat().chuyenThanhChuoi()));
        cout << "\n";
        GiaoDien::inThongTin("DON HANG SO " + to_string(don.laySoThuTu()), truong);

        vector<GiaoDien::Cot> cot;
        cot.push_back(GiaoDien::Cot("Ma", 4));
        cot.push_back(GiaoDien::Cot("Ten hang", 22));
        cot.push_back(GiaoDien::Cot("SL", 5, true));
        cot.push_back(GiaoDien::Cot("Thanh tien (VND)", 16, true));

        vector<vector<string> > bang;
        const Node<MucDonHang>* p = don.layCacMuc().layDau();
        while (p != NULL) {
            const MucDonHang& muc = p->data;
            const HangHoa* h = m_hangHoa.timTheoMa(muc.layMaHang());
            vector<string> dong;
            dong.push_back(muc.layMaHang());
            dong.push_back(h != NULL ? h->layTenHang() : "(da xoa)");
            dong.push_back(to_string(muc.laySoLuong()));
            dong.push_back(XuLiChuoi::dinhDangTien(muc.layThanhTien()));
            bang.push_back(dong);
            p = p->next;
        }
        GiaoDien::inBang(cot, bang);
        GiaoDien::inDongNoiBat("TONG TIEN :",
                               XuLiChuoi::dinhDangTien(don.layTongTien()) + " VND");
    }

    CayHangHoa m_hangHoa;                   // Chuong 5: Cay nhi phan tim kiem (BST)
    HangDoi<DonHang> m_donCho;              // Chuong 4: Hang doi FIFO
    DanhSachLienKet<TaiKhoan> m_taiKhoan;   // Chuong 3: Danh sach lien ket don
    string m_fileHangHoa;
    string m_fileDonHang;
    string m_fileAdmin;
    int m_soDonTiepTheo;
};

// ============================================================================
// PHAN 6: DIEU KHIEN MENU CHUONG TRINH VA HAM MAIN
// ============================================================================

class UngDung {
public:
    void chay() {
        GiaoDien::khoiTao();
        GiaoDien::inBanner();
        GiaoDien::inDong("\n  Dang tai du lieu tu file...", GiaoDien::XAM);
        m_cuaHang.taiDuLieu();
        GiaoDien::tamDung("Nhan Enter de bat dau...");

        bool tiepTuc = true;
        while (tiepTuc && !GiaoDien::hetDuLieuVao()) {
            GiaoDien::xoaManHinh();
            vector<string> menuChinh;
            menuChinh.push_back("Hien thi thong tin hang hoa");
            menuChinh.push_back("Tim kiem thong tin hang hoa");
            menuChinh.push_back("Dat hang");
            menuChinh.push_back("Quan li");
            GiaoDien::inMenu("QUAN LI BAN HANG ONLINE", menuChinh, "Thoat chuong trinh");
            GiaoDien::inDong("  Hom nay: " + NgayThang::homNay().chuyenThanhChuoi(),
                             GiaoDien::XAM);

            int chon = docLuaChon();
            switch (chon) {
                case 1:
                    m_cuaHang.hienThiHangHoa();
                    tiepTuc = hoiTiepTucSauChucNang();
                    break;
                case 2:
                    m_cuaHang.timKiemHangHoa();
                    tiepTuc = hoiTiepTucSauChucNang();
                    break;
                case 3:
                    m_cuaHang.datHang();
                    tiepTuc = hoiTiepTucSauChucNang();
                    break;
                case 4:
                    tiepTuc = chayKhuVucQuanLi();
                    break;
                case 0:
                    tiepTuc = false;
                    break;
                default:
                    baoLuaChonSai();
                    break;
            }
        }
        GiaoDien::thongBaoThongTin("Ket thuc chuong trinh. Tam biet!");
    }

private:
    // Sau moi thao tac/chuc nang: cho phep chon thuc hien chuc nang khac hoac ket thuc
    bool hoiTiepTucSauChucNang() const {
        if (GiaoDien::hetDuLieuVao()) return false;
        cout << "\n";
        return GiaoDien::hoiCoKhong(
            "  Ban co muon thuc hien chuc nang khac? (c: Quay lai menu / k: Ket thuc): ");
    }

    // Tra ve false neu phai thoat toan bo chuong trinh (ESC, sai 3 lan, hoac chon ket thuc)
    bool chayKhuVucQuanLi() {
        KetQuaDangNhap kq = m_cuaHang.dangNhap();
        if (kq != DANG_NHAP_THANH_CONG) {
            if (kq == DANG_NHAP_SAI_QUA_3_LAN) {
                GiaoDien::thongBaoLoi("Nhap sai 3 lan. Thoat khoi he thong.");
            } else {
                GiaoDien::thongBaoThongTin("Da nhan ESC. Thoat khoi he thong.");
            }
            if (_isatty(_fileno(stdin)) != 0) {
                GiaoDien::tamDung("Nhan Enter de thoat...");
            }
            return false;
        }
        GiaoDien::tamDung();

        bool dangNhap = true;
        while (dangNhap && !GiaoDien::hetDuLieuVao()) {
            GiaoDien::xoaManHinh();
            vector<string> menuQL;
            menuQL.push_back("Xu li don hang");
            menuQL.push_back("Quan li hang hoa");
            GiaoDien::inMenu("MENU QUAN LI", menuQL, "Dang xuat ve menu chinh");

            int chon = docLuaChon();
            switch (chon) {
                case 1:
                    m_cuaHang.xuLiDonHang();
                    if (!hoiTiepTucSauChucNang()) return false;
                    break;
                case 2:
                    if (!chayMenuHangHoa()) return false;
                    break;
                case 0:
                    dangNhap = false;
                    break;
                default:
                    baoLuaChonSai();
                    break;
            }
        }
        return true;
    }

    // Tra ve false neu nguoi dung chon ket thuc toan bo chuong trinh
    bool chayMenuHangHoa() {
        bool tiepTucMenu = true;
        while (tiepTucMenu && !GiaoDien::hetDuLieuVao()) {
            GiaoDien::xoaManHinh();
            vector<string> menuHH;
            menuHH.push_back("Them hang hoa moi");
            menuHH.push_back("Xoa hang hoa theo ma hang");
            menuHH.push_back("Cap nhat so luong hang hoa");
            GiaoDien::inMenu("QUAN LI HANG HOA", menuHH, "Quay lai menu quan li");

            int chon = docLuaChon();
            switch (chon) {
                case 1:
                    m_cuaHang.themHangHoa();
                    if (!hoiTiepTucSauChucNang()) return false;
                    break;
                case 2:
                    m_cuaHang.xoaHangHoa();
                    if (!hoiTiepTucSauChucNang()) return false;
                    break;
                case 3:
                    m_cuaHang.capNhatSoLuong();
                    if (!hoiTiepTucSauChucNang()) return false;
                    break;
                case 0:
                    tiepTucMenu = false;
                    break;
                default:
                    baoLuaChonSai();
                    break;
            }
        }
        return true;
    }

    int docLuaChon() const {
        string s = XuLiChuoi::catKhoangTrang(GiaoDien::nhapDong("\n  >> Chon chuc nang: "));
        if (s.size() == 1 && s[0] >= '0' && s[0] <= '9') {
            return s[0] - '0';
        }
        return -1;
    }

    void baoLuaChonSai() const {
        if (!GiaoDien::hetDuLieuVao()) {
            GiaoDien::thongBaoLoi("Lua chon khong hop le! Vui long chon dung so trong menu.");
            GiaoDien::tamDung();
        }
    }

    CuaHang m_cuaHang;
};

int main() {
    UngDung ungDung;
    ungDung.chay();
    return 0;
}
