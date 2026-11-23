#ifndef UNGDUNG_H_INCLUDED_
#define UNGDUNG_H_INCLUDED_

#include "CuaHang.h"

class UngDung
{
public:
    /**********************************************************
     * @Description Khoi chay vong lap menu chinh cua chuong trinh
     * @return      void
     **********************************************************/
    void chay();

private:
    bool hoiTiepTucSauChucNang() const;
    bool chayKhuVucQuanLi();
    bool chayMenuHangHoa();
    int docLuaChon() const;
    void baoLuaChonSai() const;

    CuaHang _cuaHang;
};

#endif
