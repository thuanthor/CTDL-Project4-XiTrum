#include "XuLiChuoi.h"

#include <cctype>
#include <sstream>

using namespace std;

void XuLiChuoi::xoaKyTuCR(string& strChuoi)
{
    if (!strChuoi.empty() && strChuoi[strChuoi.size() - 1] == '\r')
    {
        strChuoi.erase(strChuoi.size() - 1);
    }
}

string XuLiChuoi::catKhoangTrang(const string& strChuoi)
{
    size_t iDau = 0;
    size_t iCuoi = strChuoi.size();
    while (iDau < iCuoi && isspace(static_cast<unsigned char>(strChuoi[iDau])))
    {
        ++iDau;
    }
    while (iCuoi > iDau && isspace(static_cast<unsigned char>(strChuoi[iCuoi - 1])))
    {
        --iCuoi;
    }
    return strChuoi.substr(iDau, iCuoi - iDau);
}

string XuLiChuoi::chuyenChuHoa(const string& strChuoi)
{
    string strKetQua = strChuoi;
    for (size_t iViTri = 0; iViTri < strKetQua.size(); ++iViTri)
    {
        strKetQua[iViTri] = static_cast<char>(toupper(static_cast<unsigned char>(strKetQua[iViTri])));
    }
    return strKetQua;
}

string XuLiChuoi::chuyenChuThuong(const string& strChuoi)
{
    string strKetQua = strChuoi;
    for (size_t iViTri = 0; iViTri < strKetQua.size(); ++iViTri)
    {
        strKetQua[iViTri] = static_cast<char>(tolower(static_cast<unsigned char>(strKetQua[iViTri])));
    }
    return strKetQua;
}

bool XuLiChuoi::laSoNguyenKhongAm(const string& strChuoi)
{
    if (strChuoi.empty())
    {
        return false;
    }
    for (size_t iViTri = 0; iViTri < strChuoi.size(); ++iViTri)
    {
        if (!isdigit(static_cast<unsigned char>(strChuoi[iViTri])))
        {
            return false;
        }
    }
    return true;
}

vector<string> XuLiChuoi::tachChuoi(const string& strChuoi, const char cPhanCach)
{
    vector<string> vecKetQua;
    string strPhan = "";
    istringstream luongChuoi(strChuoi);
    while (getline(luongChuoi, strPhan, cPhanCach))
    {
        vecKetQua.push_back(strPhan);
    }
    if (!strChuoi.empty() && strChuoi[strChuoi.size() - 1] == cPhanCach)
    {
        vecKetQua.push_back("");
    }
    return vecKetQua;
}

string XuLiChuoi::dinhDangTien(const long long lSoTien)
{
    const int KHOANG_CACH_NGHIN = 3;
    string strSo = to_string(lSoTien);
    string strKetQua = "";
    int iDem = 0;
    for (int iViTri = static_cast<int>(strSo.size()) - 1; iViTri >= 0; --iViTri)
    {
        strKetQua.insert(strKetQua.begin(), strSo[iViTri]);
        ++iDem;
        if (iDem % KHOANG_CACH_NGHIN == 0 && iViTri > 0)
        {
            strKetQua.insert(strKetQua.begin(), '.');
        }
    }
    return strKetQua;
}
