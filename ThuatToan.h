#ifndef THUATTOAN_H_INCLUDED_
#define THUATTOAN_H_INCLUDED_

#include <cstddef>
#include <vector>

// Chuong 2: Cac thuat toan Sap xep va Tim kiem cai dat bang Template
class ThuatToan
{
public:
    /**********************************************************
     * @Description Sap xep chon (Selection Sort) tong quat bang Template
     * @return      void
     **********************************************************/
    template <class DataType>
    static void sapXepChon(std::vector<const DataType*>& vecDuLieu,
                           bool (*pHamDungTruoc)(const DataType*, const DataType*))
    {
        int iSoPhanTu = static_cast<int>(vecDuLieu.size());
        for (int iDau = 0; iDau < iSoPhanTu - 1; ++iDau)
        {
            int iViTriTotNhat = iDau;
            for (int iChay = iDau + 1; iChay < iSoPhanTu; ++iChay)
            {
                if (pHamDungTruoc(vecDuLieu[iChay], vecDuLieu[iViTriTotNhat]))
                {
                    iViTriTotNhat = iChay;
                }
            }
            if (iViTriTotNhat != iDau)
            {
                const DataType* pTam = vecDuLieu[iDau];
                vecDuLieu[iDau] = vecDuLieu[iViTriTotNhat];
                vecDuLieu[iViTriTotNhat] = pTam;
            }
        }
    }

    /**********************************************************
     * @Description Tim kiem tuyen tinh (Linear Search) tong quat bang Template
     * @return      void
     **********************************************************/
    template <class DataType, class KhoaType>
    static void timKiemTuyenTinh(const std::vector<const DataType*>& vecNguon,
                                 const KhoaType& tuKhoa,
                                 bool (*pHamKhop)(const DataType*, const KhoaType&),
                                 std::vector<const DataType*>& vecKetQua)
    {
        vecKetQua.clear();
        for (size_t iViTri = 0; iViTri < vecNguon.size(); ++iViTri)
        {
            if (pHamKhop(vecNguon[iViTri], tuKhoa))
            {
                vecKetQua.push_back(vecNguon[iViTri]);
            }
        }
    }
};

#endif
