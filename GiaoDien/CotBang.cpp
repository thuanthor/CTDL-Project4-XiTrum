#include "CotBang.h"

using namespace std;

CotBang::CotBang(const string& strTieuDe, const int iDoRong, const bool bCanPhai)
    : _strTieuDe(strTieuDe), _iDoRong(iDoRong), _bCanPhai(bCanPhai)
{
}

const string& CotBang::layTieuDe() const
{
    return this->_strTieuDe;
}

int CotBang::layDoRong() const
{
    return this->_iDoRong;
}

bool CotBang::laCanPhai() const
{
    return this->_bCanPhai;
}
