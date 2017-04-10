#include "stdafx.h"
#include "MyDocument.h"

namespace fs = boost::filesystem;
using fs::path;

bool CMyDocument::IsNewDocument() const
{
	return m_fileManager.IsNewDocument();
}

void CMyDocument::ResetCurrentFolder()
{
	m_fileManager.ResetCurrentFolder();
	m_fileManager.RecreateTempFolder();
}

bool CMyDocument::OnFileSaveAs(std::vector<CShapePtr> const & shapes, const CTextureStorage & textureStorage)
{
	CString fileName = OpenSaveDialog();
	if (fileName.GetLength() != 0)
	{
		const auto oldFolder = m_fileManager.GetCurrentFolder();
		m_fileManager.SetFilePath(fileName.GetString());

		if (textureStorage.GetCount())
		{
			auto newPath = path(fileName);
			auto nameNewFolder = newPath.stem().generic_wstring();
			auto p1 = newPath.root_path().generic_wstring();
			m_fileManager.CreateFolder(newPath.stem().generic_wstring());
			DeletePictures(textureStorage.GetDeletable());
			m_fileManager.CopyFiles(
				textureStorage.GetNeedfullNames(),
				oldFolder,
				nameNewFolder
			);
		}

		return m_xmlReader.Save(fileName.GetString(), shapes, textureStorage);
	}
	return false;
}

bool CMyDocument::OnFileOpen(DataForAlteration & data)
{
	CString fileName = OpenLoadDialog(FileType::Shapes);
	if (fileName.GetLength() != 0)
	{
		DeletePictures(data.textureStorage.GetDeletable());
		data.textureStorage.Clear();
		data.history.Clear();
		data.selectedShape.ResetSelectShapePtr();

		m_fileManager.SetFilePath(fileName.GetString());
		return m_xmlReader.Open(
			m_fileManager.GetFilePath(),
			data.canvas,
			data.factory,
			data.textureStorage,
			data.imageFactory
		);
	}
	return false;
}

bool CMyDocument::OnFileSave(std::vector<CShapePtr> const & shapes, const CTextureStorage & textureStorage)
{
	if (m_fileManager.IsNewDocument())
	{
		return OnFileSaveAs(shapes, textureStorage);
	}
	else
	{
		DeletePictures(textureStorage.GetDeletable());
		return m_xmlReader.Save(m_fileManager.GetFilePath(), shapes, textureStorage);
	}
}

boost::filesystem::path CMyDocument::LoadTexture()
{
	auto picturePath = OpenLoadDialog(CMyDocument::FileType::Pictures);
	auto currentFolder = m_fileManager.GetCurrentFolder();

	if (!boost::filesystem::exists(currentFolder))
	{
		boost::filesystem::create_directory(currentFolder);
	}

	auto pictureName = path(picturePath).filename().generic_wstring();
	BOOL isLoad = CopyFile(picturePath, CString((currentFolder + L"/"+ pictureName).data()),  FALSE);
	if (isLoad == 0)
	{
		throw std::runtime_error("Picture not copy");
	}

	return path(picturePath);
}

void CMyDocument::DeletePictures(const std::vector<std::wstring> & names) const
{
	for (const auto & name : names)
	{
		const auto path = (m_fileManager.GetCurrentFolder() + L"/" + name).data();
		if (PathFileExists(path))
		{
			DeleteFile((m_fileManager.GetCurrentFolder() + L"/" + name).data());
		}
	}
}

CString CMyDocument::OpenSaveDialog()
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

CString CMyDocument::OpenLoadDialog(const FileType fileType)
{
	CString fileName;

	std::wstring type;
	std::wstring expression;

	switch (fileType)
	{
	case FileType::Pictures:
		type = L"*.png";
		expression = L"Picture (*.png) | *.png;|";
		break;
	case FileType::Shapes:
		type = L"*.xml";
		expression = L"XML Files\0 *.xml\0";
		break;
	default:
		break;
	}

	CFileDialog fileDlg(
		TRUE
		, NULL
		, type.data()
		, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST
		, expression.data()
	);
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();

		fileName = pathName;
	}
	return fileName;
}

CString CMyDocument::GetFileName()
{
	return CString(m_fileManager.GetFileName().data());
}

CMyDocument::DataForAlteration::DataForAlteration(
	CCanvas & canvas,
	const CShapeFactory & factory,
	CHistory & history,
	CSelectedShape & selectedShape,
	CTextureStorage & textureStorage,
	CD2DImageFactory & imageFactory
)
	: canvas(canvas)
	, factory(factory)
	, history(history)
	, selectedShape(selectedShape)
	, textureStorage(textureStorage)
	, imageFactory(imageFactory)

{
}
