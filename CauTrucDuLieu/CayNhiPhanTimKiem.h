#ifndef CAYNHIPHANTIMKIEM_H_INCLUDED_
#define CAYNHIPHANTIMKIEM_H_INCLUDED_

#include <vector>

#include "NutCay.h"

// Chuong 5: Cay nhi phan tim kiem (BST) cai dat bang OOP va Template
// Yeu cau DataType dinh nghia toan tu < va > theo khoa tim kiem
template <class DataType>
class CayNhiPhanTimKiem
{
public:
    CayNhiPhanTimKiem() : _pGoc(NULL), _iSoPhanTu(0)
    {
    }

    ~CayNhiPhanTimKiem()
    {
        this->xoaTatCa();
    }

    /**********************************************************
     * @Description Chen phan tu moi vao cay BST (khong chen trung khoa)
     * @return      true neu chen thanh cong, false neu trung khoa
     **********************************************************/
    bool chen(const DataType& duLieu)
    {
        bool bDaChen = false;
        this->_pGoc = this->chenDeQuy(this->_pGoc, duLieu, bDaChen);
        if (bDaChen)
        {
            ++this->_iSoPhanTu;
        }
        return bDaChen;
    }

    /**********************************************************
     * @Description Tim kiem phan tu tren BST theo vat mau chua khoa
     * @return      Pointer tro den DataType hoac NULL neu khong thay
     **********************************************************/
    DataType* timKiem(const DataType& khoaMau)
    {
        NutCay<DataType>* pChay = this->_pGoc;
        while (pChay != NULL)
        {
            if (khoaMau < pChay->_data)
            {
                pChay = pChay->_pTrai;
            }
            else if (khoaMau > pChay->_data)
            {
                pChay = pChay->_pPhai;
            }
            else
            {
                return &pChay->_data;
            }
        }
        return NULL;
    }

    const DataType* timKiem(const DataType& khoaMau) const
    {
        const NutCay<DataType>* pChay = this->_pGoc;
        while (pChay != NULL)
        {
            if (khoaMau < pChay->_data)
            {
                pChay = pChay->_pTrai;
            }
            else if (khoaMau > pChay->_data)
            {
                pChay = pChay->_pPhai;
            }
            else
            {
                return &pChay->_data;
            }
        }
        return NULL;
    }

    /**********************************************************
     * @Description Xoa phan tu khoi BST (xu li du 3 truong hop xoa nut)
     * @return      true neu xoa thanh cong, false neu khong tim thay
     **********************************************************/
    bool xoa(const DataType& khoaMau)
    {
        bool bDaXoa = false;
        this->_pGoc = this->xoaDeQuy(this->_pGoc, khoaMau, bDaXoa);
        if (bDaXoa)
        {
            --this->_iSoPhanTu;
        }
        return bDaXoa;
    }

    /**********************************************************
     * @Description Duyet trung thu tu (Left - Node - Right) tang dan
     * @return      void
     **********************************************************/
    void layDanhSachLNR(std::vector<const DataType*>& vecKetQua) const
    {
        vecKetQua.clear();
        this->duyetLNR(this->_pGoc, vecKetQua);
    }

    int kichThuoc() const
    {
        return this->_iSoPhanTu;
    }

    bool laRong() const
    {
        return (this->_iSoPhanTu == 0);
    }

    void xoaTatCa()
    {
        this->giaiPhong(this->_pGoc);
        this->_pGoc = NULL;
        this->_iSoPhanTu = 0;
    }

private:
    CayNhiPhanTimKiem(const CayNhiPhanTimKiem<DataType>&);
    CayNhiPhanTimKiem<DataType>& operator=(const CayNhiPhanTimKiem<DataType>&);

    NutCay<DataType>* chenDeQuy(NutCay<DataType>* pNut, const DataType& duLieu, bool& bDaChen)
    {
        if (pNut == NULL)
        {
            bDaChen = true;
            return new NutCay<DataType>(duLieu);
        }
        if (duLieu < pNut->_data)
        {
            pNut->_pTrai = this->chenDeQuy(pNut->_pTrai, duLieu, bDaChen);
        }
        else if (duLieu > pNut->_data)
        {
            pNut->_pPhai = this->chenDeQuy(pNut->_pPhai, duLieu, bDaChen);
        }
        else
        {
            bDaChen = false;
        }
        return pNut;
    }

    NutCay<DataType>* timNutNhoNhat(NutCay<DataType>* pNut) const
    {
        NutCay<DataType>* pChay = pNut;
        while (pChay != NULL && pChay->_pTrai != NULL)
        {
            pChay = pChay->_pTrai;
        }
        return pChay;
    }

    NutCay<DataType>* xoaDeQuy(NutCay<DataType>* pNut, const DataType& khoaMau, bool& bDaXoa)
    {
        if (pNut == NULL)
        {
            bDaXoa = false;
            return NULL;
        }
        if (khoaMau < pNut->_data)
        {
            pNut->_pTrai = this->xoaDeQuy(pNut->_pTrai, khoaMau, bDaXoa);
        }
        else if (khoaMau > pNut->_data)
        {
            pNut->_pPhai = this->xoaDeQuy(pNut->_pPhai, khoaMau, bDaXoa);
        }
        else
        {
            bDaXoa = true;
            // Truong hop 1: nut la hoac chi co cay con phai
            if (pNut->_pTrai == NULL)
            {
                NutCay<DataType>* pConPhai = pNut->_pPhai;
                delete pNut;
                return pConPhai;
            }
            // Truong hop 2: chi co cay con trai
            if (pNut->_pPhai == NULL)
            {
                NutCay<DataType>* pConTrai = pNut->_pTrai;
                delete pNut;
                return pConTrai;
            }
            // Truong hop 3: co du 2 con -> thay bang nut nho nhat cua cay con phai
            NutCay<DataType>* pTheMang = this->timNutNhoNhat(pNut->_pPhai);
            pNut->_data = pTheMang->_data;
            bool bXoaTam = false;
            pNut->_pPhai = this->xoaDeQuy(pNut->_pPhai, pTheMang->_data, bXoaTam);
        }
        return pNut;
    }

    void duyetLNR(const NutCay<DataType>* pNut, std::vector<const DataType*>& vecKetQua) const
    {
        if (pNut == NULL)
        {
            return;
        }
        this->duyetLNR(pNut->_pTrai, vecKetQua);
        vecKetQua.push_back(&pNut->_data);
        this->duyetLNR(pNut->_pPhai, vecKetQua);
    }

    void giaiPhong(NutCay<DataType>* pNut)
    {
        if (pNut == NULL)
        {
            return;
        }
        this->giaiPhong(pNut->_pTrai);
        this->giaiPhong(pNut->_pPhai);
        delete pNut;
    }

    NutCay<DataType>* _pGoc;
    int _iSoPhanTu;
};

#endif
