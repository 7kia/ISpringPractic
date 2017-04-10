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
	struct DataForAlteration
	{
		DataForAlteration(
			CCanvas & canvas,
			const CShapeFactory & factory,
			CHistory & history,
			CSelectedShape & selectedShape,
			CTextureStorage & textureStorage,
			CD2DImageFactory & imageFactory
		);

		CCanvas & canvas;
		const CShapeFactory & factory;
		CHistory & history;
		CSelectedShape & selectedShape;
		CTextureStorage & textureStorage;
		CD2DImageFactory & imageFactory;
	};


	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	bool IsNewDocument() const;
	void ResetCurrentFolder();

	boost::filesystem::path LoadTexture();
	void DeletePictures(const std::vector<std::wstring> & names) const;
	CString OpenSaveDialog();
	CString OpenLoadDialog(const FileType fileType);

	CString GetFileName();

	bool OnFileSaveAs(std::vector<CShapePtr> const & shapes, const CTextureStorage & textureStorage);
	bool OnFileOpen(DataForAlteration & data);
	bool OnFileSave(std::vector<CShapePtr> const & shapes, const CTextureStorage & textureStorage);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CXMLReader m_xmlReader;
	CFileManager m_fileManager;
	bool m_folderExist = false;
};