#ifndef HANGDOI_H_INCLUDED_
#define HANGDOI_H_INCLUDED_

#include "Node.h"

// Chuong 4: Hang doi FIFO cai dat bang OOP va Template
template <class DataType>
class HangDoi
{
public:
    HangDoi() : _pDau(NULL), _pCuoi(NULL), _iSoPhanTu(0)
    {
    }

    HangDoi(const HangDoi<DataType>& khac) : _pDau(NULL), _pCuoi(NULL), _iSoPhanTu(0)
    {
        this->saoChep(khac);
    }

    HangDoi<DataType>& operator=(const HangDoi<DataType>& khac)
    {
        if (this != &khac)
        {
            this->xoaTatCa();
            this->saoChep(khac);
        }
        return *this;
    }

    ~HangDoi()
    {
        this->xoaTatCa();
    }

    /**********************************************************
     * @Description Enqueue: Them phan tu vao cuoi hang doi
     * @return      void
     **********************************************************/
    void them(const DataType& duLieu)
    {
        Node<DataType>* pNutMoi = new Node<DataType>(duLieu);
        if (this->_pCuoi == NULL)
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

    /**********************************************************
     * @Description Lay phan tu o dau hang doi
     * @return      Tham chieu hang den phan tu dau
     * @attention   Hang doi phai khong rong truoc khi goi
     **********************************************************/
    const DataType& layDau() const
    {
        return this->_pDau->_data;
    }

    /**********************************************************
     * @Description Dequeue: Loai bo phan tu o dau hang doi
     * @return      void
     **********************************************************/
    void boDau()
    {
        if (this->_pDau == NULL)
        {
            return;
        }
        Node<DataType>* pTam = this->_pDau;
        this->_pDau = this->_pDau->_pNext;
        if (this->_pDau == NULL)
        {
            this->_pCuoi = NULL;
        }
        delete pTam;
        --this->_iSoPhanTu;
    }

    const Node<DataType>* layNutDau() const
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

    void xoaTatCa()
    {
        while (!this->laRong())
        {
            this->boDau();
        }
    }

private:
    void saoChep(const HangDoi<DataType>& khac)
    {
        const Node<DataType>* pChay = khac._pDau;
        while (pChay != NULL)
        {
            this->them(pChay->_data);
            pChay = pChay->_pNext;
        }
    }

    Node<DataType>* _pDau;
    Node<DataType>* _pCuoi;
    int _iSoPhanTu;
};

#endif
