#pragma once

#include <memory>
//#include <commdlg.h>
#include <d2d1.h>
#include <atlbase.h>
#include <string>
#include <map> 
#include "Canvas\Shapes\ShapeAttributes.h"

using TextureStorage = std::vector<CComPtr<ID2D1Bitmap>>;

class CStorageCell
{
public:
	CStorageCell(const CComPtr<ID2D1Bitmap> & pTexture);
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	ID2D1Bitmap * GetTexture();

	void SetDelete(bool value);
	bool IsDelete() const;

	SSize GetSize() const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	bool m_isDelete = false;
	CComPtr<ID2D1Bitmap> m_texture;
	SSize m_sourceSize;
};

class CTextureStorage
{
public:
	CTextureStorage(const SSize maxSize);

	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	

	void					AddTexture(const std::wstring & name, const CComPtr<ID2D1Bitmap> & pTexture);
	ID2D1Bitmap *			GetTexture(const std::wstring & name);
	SSize					GetCorrectSize(const std::wstring & name) const;

	void					SetDelete(const std::wstring & name, bool value);
	bool					IsDelete(const std::wstring & name) const;
	size_t					GetCount() const;

	void						Clear();
	std::vector<std::wstring>	GetDeletable() const;
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	std::map<const std::wstring, CStorageCell> m_storage;
	SSize m_maxSize = SSize(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
};
