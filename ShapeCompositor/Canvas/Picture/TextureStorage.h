#pragma once

#include <memory>
#include <commdlg.h>
#include <d2d1.h>
#include <atlbase.h>

#include "Canvas\Shapes\ShapeAttributes.h"

using TextureStorage = std::vector<CComPtr<ID2D1Bitmap>>;

	
class CStorageCell
{
public:
	CStorageCell(const CComPtr<ID2D1Bitmap> & pTexture);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void SetDelete(bool value);
	bool IsDelete() const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	SSize m_sourceSize;
	SSize m_currentSize;
	bool m_isDelete = false;
	CComPtr<ID2D1Bitmap> m_texture;
};