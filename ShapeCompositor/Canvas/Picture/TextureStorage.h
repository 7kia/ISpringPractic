#pragma once

#include <memory>
#include <commdlg.h>
#include <d2d1.h>

class CTexture
{
public:
	CTexture() =default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	//void			Set();
	//void			Get();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::shared_ptr<CD2DBitmap> m_spBitmap;

};