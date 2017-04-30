#pragma once

#include <afxwin.h>         // �������� � ����������� ���������� MFC
#include <afxext.h>         // ���������� MFC
#include <afxcmn.h>             // ��������� MFC ��� ������� ��������� ���������� Windows
#include <afxdtctl.h>           // ��������� MFC ��� ������� ��������� ���������� Internet Explorer 4


#include "Canvas\Canvas.h"
#include "Canvas\History.h"
#include "FileWork\XMLReader.h"
#include "FileWork\FileManager.h"
#include "Canvas\Picture\TextureStorage.h"
#include "Canvas\Picture\D2DImageFactory.h"

class IDataForSave;
class IDataForOpen;


class CMyDocument
{
public:
	CMyDocument() = default;
	~CMyDocument();

	enum class FileType
	{
		Shapes,
		Pictures
	};
	enum class DialogType
	{
		Save,
		Open
	};
	struct DataForAlteration
	{
		DataForAlteration(
			IDataForSave * pDataForSave,
			IDataForOpen * pDataForOpen,
			IHistoryManipulator * pHistoryManipulator,
			CSelectedShape & selectedShape
		);

		IDataForSave * pDataForSave;
		IDataForOpen * pDataForOpen;
		IHistoryManipulator *pHistoryManipulator;
		CSelectedShape & selectedShape;
	};


	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	bool IsNewDocument() const;
	void RecreateTempFolder();

	boost::filesystem::path LoadTexture();
	void DeletePictures(const std::vector<std::wstring> & names) const;

	static CString OpenDialog(const DialogType dialogType, const FileType fileType);

	CString GetFileName() const;

	bool OnFileSaveAs(std::vector<CShapePtr> const & shapes, const CTextureStorage & textureStorage);
	bool OnFileOpen(DataForAlteration & data);
	bool OnFileSave(std::vector<CShapePtr> const & shapes, const CTextureStorage & textureStorage);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CXMLReader m_xmlReader;
	CFileManager m_fileManager;
};