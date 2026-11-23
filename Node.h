#ifndef NODE_H_INCLUDED_
#define NODE_H_INCLUDED_

#include <cstddef>

template <class DataType>
class DanhSachLienKet;

template <class DataType>
class HangDoi;

template <class DataType>
class Node
{
public:
    explicit Node(const DataType& duLieu) : _data(duLieu), _pNext(NULL)
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

    Node<DataType>* layTiep()
    {
        return this->_pNext;
    }

    const Node<DataType>* layTiep() const
    {
        return this->_pNext;
    }

    friend class DanhSachLienKet<DataType>;
    friend class HangDoi<DataType>;

private:
    DataType _data;
    Node<DataType>* _pNext;
};

#endif
