// GiaoDien.h - Giao dien console mau sac cho chuong trinh quan li ban hang online
// Ho tro Windows Console (mau ANSI, khung bang Unicode, an mat khau bang '*', phim ESC)
#ifndef GIAODIEN_H
#define GIAODIEN_H

#include <conio.h>
#include <io.h>
#include <windows.h>

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

using namespace std;

class GiaoDien {
public:
    enum Mau { MAC_DINH, DO, XANH_LA, VANG, XANH_DUONG, TIM, XANH_NGOC, TRANG, XAM, DEN };

    // Mo ta 1 cot trong bang: tieu de, do rong, co can phai hay khong
    struct Cot {
        string tieuDe;
        int rong;
        bool canPhai;
        Cot(const string& t, int r, bool phai = false)
            : tieuDe(t), rong(r), canPhai(phai) {}
    };

    // Khoi tao console Windows: bat UTF-8 va bat che do mau ANSI
    static void khoiTao() {
        SetConsoleOutputCP(65001);
        HANDLE ra = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD cheDo = 0;
        if (GetConsoleMode(ra, &cheDo)) {
            if (SetConsoleMode(ra, cheDo | ENABLE_VIRTUAL_TERMINAL_PROCESSING)) {
                mauHoatDong() = (_isatty(_fileno(stdout)) != 0);
            }
        }
    }

    // ---------- Mau sac ----------
    static void datMau(Mau mau) {
        if (!mauHoatDong()) return;
        static const char* maMau[] = {
            "\033[0m",    "\033[1;31m", "\033[1;32m", "\033[1;33m", "\033[1;34m",
            "\033[1;35m", "\033[1;36m", "\033[1;37m", "\033[0;90m", "\033[0;30m"
        };
        cout << maMau[mau];
    }

    static void datMauNen(Mau chu, Mau nen) {
        if (!mauHoatDong()) return;
        cout << "\033[" << (chu == DEN ? "22;" : "1;") << "3" << maAnsi(chu)
             << ";4" << maAnsi(nen) << "m";
    }

    static void xoaManHinh() {
        if (mauHoatDong()) {
            cout << "\033[2J\033[H";
        } else {
            cout << "\n";
        }
    }

    // ---------- Banner, tieu de, menu ----------
    static void inBanner() {
        const int rong = 76;
        static const Mau mauHang[5] = {XANH_NGOC, XANH_NGOC, XANH_DUONG, TIM, TIM};
        const string tenShop = "LANG XI TRUM SHOP";
        cout << "\n";
        inVien(0, rong, XANH_NGOC);
        inDongKhung("", rong, XANH_NGOC, MAC_DINH, true);
        for (int h = 0; h < 5; ++h) {
            string dong = "";
            for (size_t i = 0; i < tenShop.size(); ++i) {
                if (i > 0) dong += " ";
                dong += veChuLogo(tenShop[i], h);
            }
            inDongKhung(dong, rong, XANH_NGOC, mauHang[h], true);
        }
        inDongKhung("", rong, XANH_NGOC, MAC_DINH, true);
        inDongKhung("CHUONG TRINH QUAN LI BAN HANG ONLINE", rong, XANH_NGOC, VANG, true);
        inDongKhung("Website thuong mai dien tu", rong, XANH_NGOC, TRANG, true);
        inDongKhung("Mon Cau truc du lieu - Project 4 (PRO_CTDL_4)", rong, XANH_NGOC, XANH_LA, true);
        inDongKhung("", rong, XANH_NGOC, MAC_DINH, true);
        inVien(2, rong, XANH_NGOC);
    }

    // Tieu de chuc nang binh thuong
    static void inTieuDe(const string& tieuDe, Mau mau = XANH_NGOC) {
        int rong = max(44, doRong(tieuDe) + 8);
        cout << "\n";
        inVien(0, rong, mau);
        inDongKhung(tieuDe, rong, mau, VANG, true);
        inVien(2, rong, mau);
    }

    // Khung dang nhap theo mau dau '*' cua de bai (trang 198)
    static void inTieuDeDangNhap() {
        cout << "\n";
        datMau(VANG);
        cout << "  *******************************************\n";
        cout << "  *";
        datMau(XANH_NGOC);
        cout << "            DANG NHAP HE THONG           ";
        datMau(VANG);
        cout << "*\n";
        cout << "  *******************************************\n";
        datMau(MAC_DINH);
    }

    // Menu co khung: cac muc 1..n va muc 0 de thoat / quay lai
    static void inMenu(const string& tieuDe, const vector<string>& cacMuc,
                       const string& mucThoat) {
        int rong = 46;
        if (doRong(tieuDe) + 8 > rong) rong = doRong(tieuDe) + 8;
        for (size_t i = 0; i < cacMuc.size(); ++i) {
            if (doRong(cacMuc[i]) + 10 > rong) rong = doRong(cacMuc[i]) + 10;
        }
        if (doRong(mucThoat) + 10 > rong) rong = doRong(mucThoat) + 10;

        cout << "\n";
        inVien(0, rong, XANH_NGOC);
        datMau(XANH_NGOC);
        cout << "  " << kyTuKhung(5);
        datMauNen(TRANG, XANH_DUONG);
        cout << canGiua(tieuDe, rong);
        datMau(XANH_NGOC);
        cout << kyTuKhung(5);
        datMau(MAC_DINH);
        cout << "\n";
        inVien(1, rong, XANH_NGOC);
        for (size_t i = 0; i < cacMuc.size(); ++i) {
            inMucMenu(to_string(i + 1), cacMuc[i], rong, VANG, TRANG);
        }
        inMucMenu("0", mucThoat, rong, DO, DO);
        inVien(2, rong, XANH_NGOC);
    }

    // ---------- Bang du lieu ke o ----------
    static void inBang(const vector<Cot>& cot,
                       const vector<vector<string> >& hang,
                       const vector<Mau>& mauHang = vector<Mau>()) {
        inVienBang(cot, 0);
        // Dong tieu de
        datMau(XANH_NGOC);
        cout << "  " << kyTuBang(10);
        for (size_t j = 0; j < cot.size(); ++j) {
            datMauNen(TRANG, XANH_DUONG);
            cout << " " << vuaO(cot[j].tieuDe, cot[j].rong, cot[j].canPhai) << " ";
            datMau(MAC_DINH);
            datMau(XANH_NGOC);
            cout << kyTuBang(10);
        }
        datMau(MAC_DINH);
        cout << "\n";
        inVienBang(cot, 1);

        // Cac dong du lieu
        for (size_t r = 0; r < hang.size(); ++r) {
            Mau mauChu = (r < mauHang.size()) ? mauHang[r] : MAC_DINH;
            datMau(XANH_NGOC);
            cout << "  " << kyTuBang(10);
            for (size_t j = 0; j < cot.size(); ++j) {
                string o = (j < hang[r].size()) ? hang[r][j] : "";
                datMau(mauChu);
                cout << " " << vuaO(o, cot[j].rong, cot[j].canPhai) << " ";
                datMau(XANH_NGOC);
                cout << kyTuBang(10);
            }
            datMau(MAC_DINH);
            cout << "\n";
        }
        inVienBang(cot, 2);
    }

    // The thong tin chi tiet: tieu de + cac cap "nhan : gia tri"
    static void inThongTin(const string& tieuDe,
                           const vector<pair<string, string> >& truong,
                           Mau mau = XANH_NGOC) {
        int rongNhan = 0;
        for (size_t i = 0; i < truong.size(); ++i) {
            rongNhan = max(rongNhan, doRong(truong[i].first));
        }
        int rong = max(46, doRong(tieuDe) + 8);
        for (size_t i = 0; i < truong.size(); ++i) {
            rong = max(rong, rongNhan + 6 + doRong(truong[i].second));
        }
        inVien(0, rong, mau);
        datMau(mau);
        cout << "  " << kyTuKhung(5);
        datMauNen(TRANG, XANH_DUONG);
        cout << canGiua(tieuDe, rong);
        datMau(mau);
        cout << kyTuKhung(5);
        datMau(MAC_DINH);
        cout << "\n";
        inVien(1, rong, mau);
        for (size_t i = 0; i < truong.size(); ++i) {
            const string& nhan = truong[i].first;
            const string& giaTri = truong[i].second;
            datMau(mau);
            cout << "  " << kyTuKhung(5) << " ";
            datMau(VANG);
            cout << nhan << khoangTrang(rongNhan - doRong(nhan));
            datMau(XAM);
            cout << " : ";
            datMau(TRANG);
            cout << giaTri << khoangTrang(rong - rongNhan - 4 - doRong(giaTri));
            datMau(mau);
            cout << kyTuKhung(5);
            datMau(MAC_DINH);
            cout << "\n";
        }
        inVien(2, rong, mau);
    }

    static void inDongNoiBat(const string& nhan, const string& giaTri) {
        datMau(VANG);
        cout << "  " << nhan << " ";
        datMau(XANH_LA);
        cout << giaTri << "\n";
        datMau(MAC_DINH);
    }

    // ---------- Cac ham in thong bao ----------
    static void inDong(const string& noiDung, Mau mau = MAC_DINH) {
        datMau(mau);
        cout << noiDung << "\n";
        datMau(MAC_DINH);
    }

    static void thongBaoLoi(const string& noiDung) {
        inHuyHieu("LOI", TRANG, DO, noiDung, DO);
    }

    static void thongBaoThanhCong(const string& noiDung) {
        inHuyHieu("OK", TRANG, XANH_LA, noiDung, XANH_LA);
    }

    static void thongBaoThongTin(const string& noiDung) {
        inHuyHieu("!", DEN, VANG, noiDung, VANG);
    }

    // ---------- Cac ham nhap lieu ----------
    static bool hetDuLieuVao() {
        return cin.eof();
    }

    static string nhapDong(const string& nhan) {
        datMau(XANH_NGOC);
        cout << nhan;
        datMau(MAC_DINH);
        cout << flush;
        string dong;
        if (!getline(cin, dong)) {
            dong.clear();
        }
        if (!dong.empty() && dong[dong.size() - 1] == '\r') {
            dong.erase(dong.size() - 1);
        }
        return dong;
    }

    // Hoi Co/Khong (c/k), nhap sai thi bao loi va hoi lai
    static bool hoiCoKhong(const string& cauHoi) {
        while (true) {
            string tl = nhapDong(cauHoi);
            if (hetDuLieuVao()) return false;
            if (tl == "c" || tl == "C") return true;
            if (tl == "k" || tl == "K") return false;
            thongBaoLoi("Khong hop le: chi duoc nhap 'c' (co) hoac 'k' (khong).");
        }
    }

    static void tamDung(const string& nhan = "Nhan Enter de tiep tuc...") {
        datMau(XAM);
        cout << "\n  " << nhan << flush;
        datMau(MAC_DINH);
        string bo;
        getline(cin, bo);
    }

    // Nhap chuoi bang tung phim khi dang nhap:
    //   an = true  -> hien dau '*' thay cho ky tu vua go (mat khau)
    //   Tra ve false neu nguoi dung nhan phim ESC de thoat he thong.
    static bool nhapDangNhap(const string& nhan, bool an, string& ketQua) {
        datMau(XANH_NGOC);
        cout << nhan;
        datMau(MAC_DINH);
        cout << flush;
        ketQua.clear();

        // Neu doc tu file/pipe (khi kiem thu tu dong) thi dung getline
        if (_isatty(_fileno(stdin)) == 0) {
            if (!getline(cin, ketQua)) return false;
            if (!ketQua.empty() && ketQua[ketQua.size() - 1] == '\r') {
                ketQua.erase(ketQua.size() - 1);
            }
            if (ketQua == "ESC") return false;
            return true;
        }

        // Nhap truc tiep tu ban phim console Windows
        while (true) {
            int phim = _getch();
            if (phim == 0 || phim == 224) {
                // Bo qua phim mui ten va phim chuc nang F1..F12
                _getch();
                continue;
            }
            if (phim == 27 || phim == 3) {  // ESC hoac Ctrl+C -> thoat
                cout << "\n";
                return false;
            }
            if (phim == '\r' || phim == '\n') {  // Enter -> ket thuc nhap
                cout << "\n";
                return true;
            }
            if (phim == 8) {  // Backspace -> xoa 1 ky tu
                if (!ketQua.empty()) {
                    ketQua.erase(ketQua.size() - 1);
                    cout << "\b \b" << flush;
                }
                continue;
            }
            if (phim >= 32 && phim <= 126) {
                ketQua += static_cast<char>(phim);
                cout << (an ? '*' : static_cast<char>(phim)) << flush;
            }
        }
    }

private:
    static bool& mauHoatDong() {
        static bool hoatDong = false;
        return hoatDong;
    }

    static int maAnsi(Mau mau) {
        static const int kMa[] = {7, 1, 2, 3, 4, 5, 6, 7, 7, 0};
        return kMa[mau];
    }

    static bool dungKhungUnicode() {
        return true;
    }

    static string khoangTrang(int n) {
        if (n <= 0) return "";
        return string(static_cast<size_t>(n), ' ');
    }

    static string lap(const string& s, int n) {
        string ketQua;
        for (int i = 0; i < n; ++i) ketQua += s;
        return ketQua;
    }

    // Dem so ky tu hien thi cua chuoi UTF-8
    static int doRong(const string& s) {
        int dem = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            if ((static_cast<unsigned char>(s[i]) & 0xC0) != 0x80) {
                ++dem;
            }
        }
        return dem;
    }

    static string canGiua(const string& s, int rong) {
        int d = doRong(s);
        if (d >= rong) return s;
        int trai = (rong - d) / 2;
        return khoangTrang(trai) + s + khoangTrang(rong - d - trai);
    }

    // Cat/can chinh chuoi cho vua do rong o cua bang
    static string vuaO(const string& s, int rong, bool canPhai) {
        string cat = s;
        if (doRong(s) > rong) {
            cat.clear();
            int dem = 0;
            size_t i = 0;
            while (i < s.size() && dem < rong - 1) {
                size_t n = 1;
                while (i + n < s.size() &&
                       (static_cast<unsigned char>(s[i + n]) & 0xC0) == 0x80) {
                    ++n;
                }
                cat.append(s, i, n);
                i += n;
                ++dem;
            }
            cat += ".";
        }
        string demKhoang = khoangTrang(rong - doRong(cat));
        return canPhai ? (demKhoang + cat) : (cat + demKhoang);
    }

    // Ky tu ve khung doi: 0 ╔  1 ╗  2 ╚  3 ╝  4 ═  5 ║  6 ╠  7 ╣
    static string kyTuKhung(int loai) {
        static const char* kUni[] = {
            "\xE2\x95\x94", "\xE2\x95\x97", "\xE2\x95\x9A", "\xE2\x95\x9D",
            "\xE2\x95\x90", "\xE2\x95\x91", "\xE2\x95\xA0", "\xE2\x95\xA3"
        };
        static const char* kAscii[] = {"+", "+", "+", "+", "-", "|", "+", "+"};
        return dungKhungUnicode() ? kUni[loai] : kAscii[loai];
    }

    // Ky tu ve bang don: 0 ┌  1 ┬  2 ┐  3 ├  4 ┼  5 ┤  6 └  7 ┴  8 ┘  9 ─  10 │
    static string kyTuBang(int loai) {
        static const char* kUni[] = {
            "\xE2\x94\x8C", "\xE2\x94\xAC", "\xE2\x94\x90", "\xE2\x94\x9C",
            "\xE2\x94\xBC", "\xE2\x94\xA4", "\xE2\x94\x94", "\xE2\x94\xB4",
            "\xE2\x94\x98", "\xE2\x94\x80", "\xE2\x94\x82"
        };
        static const char* kAscii[] = {"+", "+", "+", "+", "+", "+", "+", "+", "+", "-", "|"};
        return dungKhungUnicode() ? kUni[loai] : kAscii[loai];
    }

    static void inVien(int viTri, int rong, Mau mau) {
        string trai = kyTuKhung(viTri == 0 ? 0 : (viTri == 1 ? 6 : 2));
        string phai = kyTuKhung(viTri == 0 ? 1 : (viTri == 1 ? 7 : 3));
        datMau(mau);
        cout << "  " << trai << lap(kyTuKhung(4), rong) << phai << "\n";
        datMau(MAC_DINH);
    }

    static void inDongKhung(const string& noiDung, int rong, Mau mauKhung,
                            Mau mauChu, bool giua) {
        datMau(mauKhung);
        cout << "  " << kyTuKhung(5);
        datMau(mauChu);
        if (giua) {
            cout << canGiua(noiDung, rong);
        } else {
            string s = " " + noiDung;
            cout << s << khoangTrang(rong - doRong(s));
        }
        datMau(mauKhung);
        cout << kyTuKhung(5);
        datMau(MAC_DINH);
        cout << "\n";
    }

    static void inMucMenu(const string& so, const string& chu, int rong,
                          Mau mauSo, Mau mauChu) {
        datMau(XANH_NGOC);
        cout << "  " << kyTuKhung(5);
        datMau(mauSo);
        cout << "  [" << so << "] ";
        datMau(mauChu);
        cout << chu << khoangTrang(rong - 6 - doRong(chu));
        datMau(XANH_NGOC);
        cout << kyTuKhung(5);
        datMau(MAC_DINH);
        cout << "\n";
    }

    static void inVienBang(const vector<Cot>& cot, int viTri) {
        int trai = (viTri == 0) ? 0 : ((viTri == 1) ? 3 : 6);
        int giua = (viTri == 0) ? 1 : ((viTri == 1) ? 4 : 7);
        int phai = (viTri == 0) ? 2 : ((viTri == 1) ? 5 : 8);
        datMau(XANH_NGOC);
        cout << "  " << kyTuBang(trai);
        for (size_t j = 0; j < cot.size(); ++j) {
            cout << lap(kyTuBang(9), cot[j].rong + 2)
                 << kyTuBang(j + 1 == cot.size() ? phai : giua);
        }
        datMau(MAC_DINH);
        cout << "\n";
    }

    static void inHuyHieu(const string& nhan, Mau mauChuNhan, Mau nenNhan,
                          const string& noiDung, Mau mauNoiDung) {
        cout << "  ";
        if (mauHoatDong()) {
            datMauNen(mauChuNhan, nenNhan);
            cout << " " << nhan << " ";
            datMau(MAC_DINH);
        } else {
            cout << "[" << nhan << "]";
        }
        cout << " ";
        datMau(mauNoiDung);
        cout << noiDung << "\n";
        datMau(MAC_DINH);
    }

    static string veChuLogo(char c, int hang) {
        static const char* const kS[] = {"###", "#  ", "###", "  #", "###"};
        static const char* const kH[] = {"# #", "# #", "###", "# #", "# #"};
        static const char* const kO[] = {"###", "# #", "# #", "# #", "###"};
        static const char* const kP[] = {"###", "# #", "###", "#  ", "#  "};
        static const char* const kN[] = {"#  #", "## #", "# ##", "#  #", "#  #"};
        static const char* const kL[] = {"#  ", "#  ", "#  ", "#  ", "###"};
        static const char* const kI[] = {"###", " # ", " # ", " # ", "###"};
        static const char* const kE[] = {"###", "#  ", "###", "#  ", "###"};
        static const char* const kA[] = {" # ", "# #", "###", "# #", "# #"};
        static const char* const kG[] = {" ###", "#   ", "# ##", "#  #", " ###"};
        static const char* const kX[] = {"# #", "# #", " # ", "# #", "# #"};
        static const char* const kT[] = {"###", " # ", " # ", " # ", " # "};
        static const char* const kR[] = {"###", "# #", "###", "## ", "# #"};
        static const char* const kU[] = {"# #", "# #", "# #", "# #", "###"};
        static const char* const kM[] = {"#   #", "## ##", "# # #", "#   #", "#   #"};
        static const char* const kCach[] = {"  ", "  ", "  ", "  ", "  "};
        const char* const* mau = kCach;
        switch (c) {
            case 'S': mau = kS; break;
            case 'H': mau = kH; break;
            case 'O': mau = kO; break;
            case 'P': mau = kP; break;
            case 'N': mau = kN; break;
            case 'L': mau = kL; break;
            case 'I': mau = kI; break;
            case 'E': mau = kE; break;
            case 'A': mau = kA; break;
            case 'G': mau = kG; break;
            case 'X': mau = kX; break;
            case 'T': mau = kT; break;
            case 'R': mau = kR; break;
            case 'U': mau = kU; break;
            case 'M': mau = kM; break;
            default: break;
        }
        string ketQua;
        for (const char* p = mau[hang]; *p != '\0'; ++p) {
            if (*p == '#') {
                ketQua += dungKhungUnicode() ? "\xE2\x96\x88" : "#";
            } else {
                ketQua += ' ';
            }
        }
        return ketQua;
    }
};

#endif  // GIAODIEN_H
