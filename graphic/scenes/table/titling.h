#pragma once

#include "tablesub.h"
#include "../../gametbl.h"
#include "../../text.h"

namespace mihajong_graphic {

using std::uint64_t;

class TableSubsceneTitling : public TableSubscene {
protected:
	HugeTextRenderer* myTextRenderer;
	void FadeinStr(const std::wstring& str);
public:
	TableSubsceneTitling(LPDIRECT3DDEVICE9 device);
	virtual ~TableSubsceneTitling();
};

class TableSubsceneTitlingHonba : public TableSubsceneTitling {
private:
	static const std::wstring Numeral;
public:
	TableSubsceneTitlingHonba(LPDIRECT3DDEVICE9 device);
	~TableSubsceneTitlingHonba();
	void Render();
};

}
