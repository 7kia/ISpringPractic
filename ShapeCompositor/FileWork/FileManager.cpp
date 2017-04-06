#include "stdafx.h"
#include "FileManager.h"


using namespace boost::filesystem;

namespace fs = boost::filesystem;
using fs::path;

CFileManager::CFileManager()
	: m_tempFolderPath(unique_path("temp%%%%"))
{
	if (!exists(m_tempFolderPath))
	{
		create_directory(m_tempFolderPath);
	}
	else
	{
		while (exists(m_tempFolderPath))
		{
			m_tempFolderPath = unique_path("temp%%%%");
		}
		create_directory(m_tempFolderPath);
	}

}

CFileManager::~CFileManager()
{
	remove_all(m_tempFolderPath);
}

void CFileManager::SetFilePath(const std::wstring & name)
{
	if (name != m_tempFolderPath)
	{
		m_filePath = name;
	}
}

std::wstring CFileManager::GetFileName() const
{
	return m_filePath.filename().generic_wstring();
}

std::wstring CFileManager::GetFilePath() const
{
	return m_filePath.generic_wstring();
}

void CFileManager::CreateFolder(const std::wstring & name)
{
	if (!exists(path(name)))
	{
		create_directory(path(name));
	}
}

bool CFileManager::IsNewDocument() const
{
	return m_filePath.empty();
}


BOOL CFileManager::DirectoryExists(const std::wstring & dirName)
{
	auto path = dirName.c_str();
	DWORD attribs = ::GetFileAttributes(path);
	if (attribs == INVALID_FILE_ATTRIBUTES)
	{
		return false;
	}
	return (attribs & FILE_ATTRIBUTE_DIRECTORY);
}

void CFileManager::ResetCurrentFolder()
{
	m_filePath.clear();
}

void CFileManager::RecreateTempFolder()
{
	remove_all(m_tempFolderPath);
	create_directory(m_tempFolderPath);
}
