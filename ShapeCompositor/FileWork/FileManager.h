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
	void SetFilePath(const std::wstring & name);
	std::wstring GetFileName() const;
	std::wstring GetFilePath() const;
	void CreateFolder(const std::wstring & name);
	void CopyFiles(
		const std::vector<std::wstring> & files,
		const std::wstring & from,
		const std::wstring & to
	) const;

	bool IsNewDocument() const;
	std::wstring GetCurrentFolder() const;
	BOOL DirectoryExists(const std::wstring & dirName);


	void ResetCurrentFolder();
	void RecreateTempFolder();
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	boost::filesystem::path m_filePath;
	boost::filesystem::path m_tempFolderPath;
};