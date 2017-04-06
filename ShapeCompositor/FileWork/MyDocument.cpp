#include "stdafx.h"
#include "MyDocument.h"


bool CMyDocument::IsNewDocument() const
{
	return m_fileManager.IsNewDocument();
}

void CMyDocument::ResetCurrentFolder()
{
	m_fileManager.ResetCurrentFolder();
	m_fileManager.RecreateTempFolder();
}

bool CMyDocument::OnFileSaveAs(std::vector<CShapePtr> const & shapes)
{
	CString fileName = OpenSaveDialog();
	if (fileName.GetLength() != 0)
	{
		m_fileManager.SetFilePath(fileName.GetString());
		m_fileManager.CreateFolder(fileName.GetString());
		return m_xmlReader.Save(fileName.GetString(), shapes);
	}
	return false;
}

bool CMyDocument::OnFileOpen(DataForAlteration & data)
{
	CString fileName = OpenLoadDialog();
	if (fileName.GetLength() != 0)
	{
		data.history.Clear();
		data.selectedShape.ResetSelectShapePtr();

		m_fileManager.SetFilePath(fileName.GetString());
		return m_xmlReader.Open(m_fileManager.GetFilePath(), data.canvas, data.factory);
	}
	return false;
}

bool CMyDocument::OnFileSave(std::vector<CShapePtr> const & shapes)
{
	if (m_fileManager.IsNewDocument())
	{
		return OnFileSaveAs(shapes);
	}
	else
	{
		return m_xmlReader.Save(m_fileManager.GetFilePath(), shapes);
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

CString CMyDocument::OpenLoadDialog()
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

CString CMyDocument::GetFileName()
{
	return CString(m_fileManager.GetFileName().data());
}

CMyDocument::DataForAlteration::DataForAlteration(
	CCanvas & canvas,
	const CShapeFactory & factory,
	CHistory & history,
	CSelectedShape & selectedShape
)
	: canvas(canvas)
	, factory(factory)
	, history(history)
	, selectedShape(selectedShape)
{
}
