#pragma once

#include <string>
#include <sstream>
#include <fstream>
#include <atlstr.h> 
#include <boost/filesystem.hpp>
#include <boost/system/config.hpp>
class CFileManager
{
public:
	CFileManager();
	~CFileManager();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	const std::wstring DEFAULT_TEMP_DIRECTORY = L"temp";

	void SetFilePath(const CString & name);
	std::wstring GetFileName() const;
	std::wstring GetFilePath() const;
	void CreateFolder(const CString & name);

	bool IsNewDocument() const;

	BOOL DirectoryExists(const std::wstring & dirName);

	void ResetCurrentFolder();
	void RecreateTempFolder();

	void SetParentWnd(CWnd * pParentWnd);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CWnd * m_pParentWnd = nullptr;
	boost::filesystem::path m_filePath;
	boost::filesystem::path m_tempFolderPath;
};