#pragma once

#include <afxwin.h>         // основные и стандартные компоненты MFC
#include <afxext.h>         // расширения MFC
#include <afxcmn.h>             // поддержка MFC для типовых элементов управления Windows
#include <afxdtctl.h>           // поддержка MFC для типовых элементов управления Internet Explorer 4


#include "Canvas\CanvasModel.h"
#include "Canvas\History.h"
#include "FileWork\XMLReader.h"
#include "FileWork\FileManager.h"
#include "Canvas\Shapes\Picture\TextureStorage.h"
#include "Canvas\Shapes\Picture\D2DImageFactory.h"


class IDataForSave
{
public:
	virtual ~IDataForSave() = default;


	virtual IShapeCollection& GetShapeCollection() = 0;
	virtual CTextureStorage & GetTextureStorage() = 0;
};

class IDataForOpen
{
public:
	virtual ~IDataForOpen() = default;

	virtual CShapeViewFactory & GetShapeFactory() = 0;
	virtual CD2DImageFactory & GetImageFactory() = 0;
};

class IDocumentManipulator
{
public:
	virtual ~IDocumentManipulator() = default;

	virtual bool SaveAsDocument() = 0;
	virtual bool SaveDocument() = 0;
	virtual bool OpenDocument() = 0;
	virtual bool NewDocument() = 0;
};

class IModelReseter;

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
	

	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	bool IsNewDocument() const;
	void RecreateTempFolder();

	boost::filesystem::path LoadTexture();
	void DeletePictures(const std::vector<std::wstring> & names) const;

	static CString OpenDialog(const DialogType dialogType, const FileType fileType);

	CString GetFileName() const;

	bool OnFileSaveAs(std::vector<CShapeModelPtr> const & shapes, const CTextureStorage & textureStorage);
	CXMLReader::ReadData OnFileOpen(
		IModelReseter & reseter,
		std::vector<std::wstring> deleteTexture,
		CXMLReader::DataForCreation & data
	);
	bool OnFileSave(std::vector<CShapeModelPtr> const & shapes, const CTextureStorage & textureStorage);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CXMLReader m_xmlReader;
	CFileManager m_fileManager;
};