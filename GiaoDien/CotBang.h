#ifndef COTBANG_H_INCLUDED_
#define COTBANG_H_INCLUDED_

#include <string>

class CotBang
{
public:
    CotBang(const std::string& strTieuDe, const int iDoRong, const bool bCanPhai = false);

    const std::string& layTieuDe() const;
    int layDoRong() const;
    bool laCanPhai() const;

private:
    std::string _strTieuDe;
    int _iDoRong;
    bool _bCanPhai;
};

#endif
