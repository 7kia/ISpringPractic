#include "stdafx.h"
#include "TextureStorage.h"


CTextureStorage::CTextureStorage(const SSize maxSize)
	: m_maxSize(maxSize)
{
}

void CTextureStorage::AddTexture(const std::wstring & name, const CComPtr<ID2D1Bitmap>& pTexture)
{
	m_storage.emplace(std::make_pair<const std::wstring, CStorageCell>( name.data(), CStorageCell(pTexture) ));
}

ID2D1Bitmap * CTextureStorage::GetTexture(const std::wstring & name)
{
	return m_storage.at(name).GetTexture();
}

SSize CTextureStorage::GetCorrectSize(const std::wstring & name) const
{
	auto & cell = m_storage.at(name);
	const SSize sourceSize = cell.GetSize();
	SSize resultSize = sourceSize;

	if (sourceSize.width > m_maxSize.width)
	{
		const float scaleFactor = m_maxSize.width / sourceSize.width;
		resultSize.width *= scaleFactor;
		resultSize.height *= scaleFactor;

		return resultSize;
	}
	if (sourceSize.height > m_maxSize.height)
	{
		const float scaleFactor = m_maxSize.height / sourceSize.height;
		resultSize.width *= scaleFactor;
		resultSize.height *= scaleFactor;

		return resultSize;
	}
	return resultSize;
}

std::wstring CTextureStorage::GetNameTexture(ID2D1Bitmap * texture) const
{
	for (auto & cell : m_storage)
	{
		if (cell.second.GetTexture() == texture)
		{
			return cell.first;
		}
	}
	return std::wstring();
}

std::vector<std::wstring> CTextureStorage::GetNeedfullNames() const
{
	std::vector<std::wstring> names;
	for (const auto & cell : m_storage)
	{
		if (!cell.second.IsDelete())
		{
			names.push_back(cell.first);
		}
	}

	return names;
}

void CTextureStorage::SetDelete(const std::wstring & name, bool value)
{
	m_storage.at(name).SetDelete(value);
}

bool CTextureStorage::IsDelete(const std::wstring & name) const
{
	return m_storage.at(name).IsDelete();
}

size_t CTextureStorage::GetCount() const
{
	return m_storage.size();
}

void CTextureStorage::Clear()
{
	m_storage.clear();
}

std::vector<std::wstring> CTextureStorage::GetDeletable() const
{
	std::vector<std::wstring> deletable;
	for (auto cell : m_storage)
	{
		if (cell.second.IsDelete())
		{
			deletable.push_back(cell.first);
		}
	}
	return deletable;
}


CStorageCell::CStorageCell(const CComPtr<ID2D1Bitmap>& pTexture)
	: m_texture(pTexture)
{
	auto size = m_texture->GetSize();
	m_sourceSize = SSize(size.width, size.height);
}

ID2D1Bitmap * CStorageCell::GetTexture()
{
	return m_texture.p;
}

const ID2D1Bitmap * CStorageCell::GetTexture() const
{
	return m_texture.p;
}

void CStorageCell::SetDelete(bool value)
{
	m_isDelete = value;
}

bool CStorageCell::IsDelete() const
{
	return m_isDelete;
}

SSize CStorageCell::GetSize() const
{
	return m_sourceSize;
}
