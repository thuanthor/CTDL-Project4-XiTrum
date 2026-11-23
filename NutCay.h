#ifndef NUTCAY_H_INCLUDED_
#define NUTCAY_H_INCLUDED_

#include <cstddef>

template <class DataType>
class CayNhiPhanTimKiem;

template <class DataType>
class NutCay
{
public:
    explicit NutCay(const DataType& duLieu) : _data(duLieu), _pTrai(NULL), _pPhai(NULL)
    {
    }

    DataType& layDuLieu()
    {
        return this->_data;
    }

    const DataType& layDuLieu() const
    {
        return this->_data;
    }

    friend class CayNhiPhanTimKiem<DataType>;

private:
    DataType _data;
    NutCay<DataType>* _pTrai;
    NutCay<DataType>* _pPhai;
};

#endif
