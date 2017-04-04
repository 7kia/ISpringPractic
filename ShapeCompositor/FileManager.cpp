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

void CFileManager::SetFileName(const CString & name)
{
	if (name != m_tempFolderPath)
	{
		m_fileToSave = name;
	}
}

std::wstring CFileManager::GetFileName() const
{
	return m_fileToSave;
}

bool CFileManager::IsNewDocument() const
{
	return m_fileToSave.empty();
}

CString CFileManager::OpenSaveDialog()
{
	CString fileName;

	CFileDialog fileDlg(
		FALSE
		, _T("")
		, _T("*.xml")
		, OFN_HIDEREADONLY
		, L"XML Files\0"    L"*.xml\0"
	);
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();

		fileName = pathName;
	}

	return fileName;
}

CString CFileManager::OpenLoadDialog()
{
	CString fileName;

	CFileDialog fileDlg(
		TRUE
		, NULL
		, _T("*.xml")
		, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST
		, L"XML Files\0"    L"*.xml\0"
	);
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();

		fileName = pathName;
	}

	return fileName;
}

void CFileManager::CreateTemporaryDirectory()
{
	if (DirectoryExists(DEFAULT_TEMP_DIRECTORY))
	{
		CreateDirectory(DEFAULT_TEMP_DIRECTORY.data(), NULL);
	}
	else
	{

	}
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

