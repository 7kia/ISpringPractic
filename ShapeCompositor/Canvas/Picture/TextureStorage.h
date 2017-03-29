#pragma once

#include <memory>
#include <commdlg.h>
#include <d2d1.h>
#include <atlbase.h>


namespace Texture
{
	enum class Id
	{
		House = 0
		, Map
	};

	using TextureStorage = std::vector<CComPtr<ID2D1Bitmap>>;

	
	//class CStorageCell : public IClass
	//{
	//public:
	//	CClass();
	//	//////////////////////////////////////////////////////////////////////
	//	// Methods
	//public:
	//	//--------------------------------------------
	//	// NameInterface

	//	/*
	//	there place  something inheritance methods from NameInterface
	//	*/

	//	//--------------------------------------------

	//	void			Set();
	//	void			Get();
	//	//////////////////////////////////////////////////////////////////////
	//	// Data
	//private:
	//};
}
