#ifndef DANHSACHLIENKET_H_INCLUDED_
#define DANHSACHLIENKET_H_INCLUDED_

#include "Node.h"

// Chuong 3: Danh sach lien ket don cai dat bang OOP va Template
template <class DataType>
class DanhSachLienKet
{
public:
    DanhSachLienKet() : _pDau(NULL), _pCuoi(NULL), _iSoPhanTu(0)
    {
    }

    DanhSachLienKet(const DanhSachLienKet<DataType>& khac)
        : _pDau(NULL), _pCuoi(NULL), _iSoPhanTu(0)
    {
        this->saoChep(khac);
    }

    DanhSachLienKet<DataType>& operator=(const DanhSachLienKet<DataType>& khac)
    {
        if (this != &khac)
        {
            this->xoaTatCa();
            this->saoChep(khac);
        }
        return *this;
    }

    ~DanhSachLienKet()
    {
        this->xoaTatCa();
    }

    /**********************************************************
     * @Description Them mot phan tu moi vao cuoi danh sach - O(1)
     * @return      void
     **********************************************************/
    void themCuoi(const DataType& duLieu)
    {
        Node<DataType>* pNutMoi = new Node<DataType>(duLieu);
        if (this->_pDau == NULL)
        {
            this->_pDau = pNutMoi;
            this->_pCuoi = pNutMoi;
        }
        else
        {
            this->_pCuoi->_pNext = pNutMoi;
            this->_pCuoi = pNutMoi;
        }
        ++this->_iSoPhanTu;
    }

    Node<DataType>* layDau()
    {
        return this->_pDau;
    }

    const Node<DataType>* layDau() const
    {
        return this->_pDau;
    }

    int kichThuoc() const
    {
        return this->_iSoPhanTu;
    }

    bool laRong() const
    {
        return (this->_iSoPhanTu == 0);
    }

    /**********************************************************
     * @Description Giai phong toan bo cac nut da cap phat dong
     * @return      void
     **********************************************************/
    void xoaTatCa()
    {
        while (this->_pDau != NULL)
        {
            Node<DataType>* pTam = this->_pDau;
            this->_pDau = this->_pDau->_pNext;
            delete pTam;
        }
        this->_pCuoi = NULL;
        this->_iSoPhanTu = 0;
    }

private:
    void saoChep(const DanhSachLienKet<DataType>& khac)
    {
        const Node<DataType>* pChay = khac._pDau;
        while (pChay != NULL)
        {
            this->themCuoi(pChay->_data);
            pChay = pChay->_pNext;
        }
    }

    Node<DataType>* _pDau;
    Node<DataType>* _pCuoi;
    int _iSoPhanTu;
};

#endif
