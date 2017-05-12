#include "stdafx.h"
#include "MyDocument.h"
#include "ShapeCompositorModel.h"

namespace fs = boost::filesystem;
using fs::path;

CMyDocument::~CMyDocument()
{
}

bool CMyDocument::IsNewDocument() const
{
	return m_fileManager.IsNewDocument();
}

void CMyDocument::RecreateTempFolder()
{
	m_fileManager.ResetCurrentFolder();
	m_fileManager.RecreateTempFolder();
}

bool CMyDocument::OnFileSaveAs(std::vector<CShapeModelPtr> const & shapes, const CTextureStorage & textureStorage)
{
	CString fileName = OpenDialog(CMyDocument::DialogType::Save, CMyDocument::FileType::Shapes);
	if (fileName.GetLength() != 0)
	{
		const auto oldFolder = m_fileManager.GetCurrentFolder();
		m_fileManager.SetFilePath(fileName.GetString());

		std::wstring folderForSave = oldFolder;
		if (textureStorage.GetCount())
		{
			auto newPath = path(fileName);
			auto newFolder = newPath.parent_path().generic_wstring() + L"/" + newPath.stem().generic_wstring();
			
			if (oldFolder != newFolder)
			{
				m_fileManager.CreateFolder(newFolder);

				DeletePictures(textureStorage.GetDeletable());

				m_fileManager.CopyFiles(
					textureStorage.GetTextureNames(),
					oldFolder,
					newFolder
				);
				folderForSave = newFolder;
			}
		}

		return m_xmlReader.Save(fileName.GetString(), shapes, textureStorage);
	}
	return false;
}

CXMLReader::ReadData CMyDocument::OnFileOpen(
	IModelReseter & reseter,
	std::vector<std::wstring> deleteTexture,
	CXMLReader::DataForCreation & data
)
{
	CString fileName = OpenDialog(CMyDocument::DialogType::Open, CMyDocument::FileType::Shapes);
	if (fileName.GetLength() != 0)
	{
		DeletePictures(deleteTexture);

		reseter.ResetModel();
		// Check save/open save document
		m_fileManager.SetFilePath(fileName.GetString());
		return m_xmlReader.Open(
			m_fileManager.GetFilePath(),
			data
		);
	}
	return CXMLReader::ReadData();
}

bool CMyDocument::OnFileSave(std::vector<CShapeModelPtr> const & shapes, const CTextureStorage & textureStorage)
{
	if (m_fileManager.IsNewDocument())
	{
		return OnFileSaveAs(shapes, textureStorage);
	}
	else
	{
		//DeletePictures(textureStorage.GetDeletable());
		m_fileManager.SetFilePath(m_fileManager.GetFilePath());
		return m_xmlReader.Save(m_fileManager.GetFilePath(), shapes, textureStorage);
	}
}

boost::filesystem::path CMyDocument::LoadTexture()
{
	const auto picturePath = OpenDialog(CMyDocument::DialogType::Open ,CMyDocument::FileType::Pictures);
	if (picturePath.GetLength())
	{
		const auto currentFolder = m_fileManager.GetCurrentFolder();

		if (!boost::filesystem::exists(currentFolder))
		{
			boost::filesystem::create_directory(currentFolder);
		}

		const auto pictureName = path(picturePath).filename().generic_wstring();
		const auto currentPath = currentFolder + L"/" + pictureName;
		if (currentPath.data() != path(picturePath))
		{
			BOOL isLoad = CopyFile(picturePath, currentPath.data(), FALSE);
			if (isLoad == 0)
			{
				throw std::runtime_error("Picture not copy");
			}
		}
	}
	else
	{
		return path();
	}
	return path(picturePath);
}

void CMyDocument::DeletePictures(const std::vector<std::wstring> & names) const
{
	for (const auto & name : names)
	{
		auto path = (m_fileManager.GetCurrentFolder() + L"/" + name);
		if(PathFileExists(path.data()))
		{
			DeleteFile(path.data());
		}
	}
}


CString CMyDocument::OpenDialog(const DialogType dialogType, const FileType fileType)
{
	std::wstring type;
	std::wstring expression;

	switch (fileType)
	{
	case FileType::Pictures:
		type = L"*.png";
		expression = L"Picture (*.png)|*.png|";
		break;
	case FileType::Shapes:
		type = L"*.xml";
		expression = L"XML Files (*.xml)| *.xml|";
		break;
	default:
		break;
	}

	CFileDialog fileDlg(
		(dialogType == DialogType::Open) ? TRUE : FALSE
		, NULL
		, type.data()
		, OFN_EXPLORER | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		, expression.data()
	);
	CString fileName;
	//const int maxFiles = 1;
	//const int bufferSize = (maxFiles * (MAX_PATH + 1)) + 1;
	//fileDlg.GetOFN().lpstrFile = fileName.GetBuffer(bufferSize);
	//fileDlg.GetOFN().nMaxFile = maxFiles;
	if (fileDlg.DoModal() == IDOK)
	{
		fileName = fileDlg.GetPathName();

		switch (fileType)
		{
		case FileType::Pictures:
			expression = L".png";
			break;
		case FileType::Shapes:
			expression = L".xml";
			break;
		default:
			break;
		}
		if (fileName.Find(expression.data()) == -1)
		{
			 fileName.SetString(fileName + CString(expression.data()));
		}
	}
	//fileName.ReleaseBuffer();

	return fileName;
}

CString CMyDocument::GetFileName() const
{
	return CString(m_fileManager.GetFileName().data());
}

