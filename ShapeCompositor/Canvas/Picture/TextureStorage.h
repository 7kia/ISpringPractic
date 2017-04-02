#pragma once

#include <memory>
#include <commdlg.h>
#include <d2d1.h>
#include <atlbase.h>


using TextureStorage = std::vector<CComPtr<ID2D1Bitmap>>;

	
class CStorageCell
{
public:
	CStorageCell() = default;
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	//--------------------------------------------
	// NameInterface

	/*
	there place  something inheritance methods from NameInterface
	*/

	//--------------------------------------------

	//void			Set();
	//void			Get();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
};