// Этот исходный код MFC Samples демонстрирует функционирование пользовательского интерфейса Fluent на основе MFC в Microsoft Office
// ("Fluent UI") и предоставляется исключительно как справочный материал в качестве дополнения к
// справочнику по пакету Microsoft Foundation Classes и связанной электронной документации,
// включенной в программное обеспечение библиотеки MFC C++.  
// Условия лицензионного соглашения на копирование, использование или распространение Fluent UI доступны отдельно.  
// Для получения дополнительных сведений о нашей лицензионной программе Fluent UI посетите веб-узел
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// (C) Корпорация Майкрософт (Microsoft Corp.)
// Все права защищены.

// ShapeCompositorDoc.cpp : реализация класса CShapeCompositorDoc
//

#include "stdafx.h"
// SHARED_HANDLERS можно определить в обработчиках фильтров просмотра реализации проекта ATL, эскизов
// и поиска; позволяет совместно использовать код документа в данным проекте.
#ifndef SHARED_HANDLERS
#include "ShapeCompositor.h"
#endif

#include "ShapeCompositorDoc.h"
#include "ShapeCompositorView.h"
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CShapeCompositorDoc

IMPLEMENT_DYNCREATE(CShapeCompositorDoc, CDocument)

BEGIN_MESSAGE_MAP(CShapeCompositorDoc, CDocument)
END_MESSAGE_MAP()


// создание/уничтожение CShapeCompositorDoc

CShapeCompositorDoc::CShapeCompositorDoc()
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CShapeCompositorDoc::~CShapeCompositorDoc()
{
}


BOOL CShapeCompositorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: добавьте код повторной инициализации
	// (Документы SDI будут повторно использовать этот документ)

	return TRUE;
}




// сериализация CShapeCompositorDoc

void CShapeCompositorDoc::Serialize(CArchive& ar)
{

	if (ar.IsStoring())
	{
		// TODO: добавьте код сохранения
	}
	else
	{
		// TODO: добавьте код загрузки
	}
}

#ifdef SHARED_HANDLERS

// Поддержка для эскизов
void CShapeCompositorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Измените этот код для отображения данных документа
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Поддержка обработчиков поиска
void CShapeCompositorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Задайте содержимое поиска из данных документа. 
	// Части содержимого должны разделяться точкой с запятой ";"

	// Например:  strSearchContent = _T("точка;прямоугольник;круг;объект ole;");
	SetSearchContent(strSearchContent);
}

void CShapeCompositorDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// диагностика CShapeCompositorDoc

#ifdef _DEBUG
void CShapeCompositorDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CShapeCompositorDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// команды CShapeCompositorDoc

bool CShapeCompositorDoc::IsNewDocument() const
{
	return m_fileManager.IsNewDocument();
}

void CShapeCompositorDoc::ResetCurrentFolder()
{
	m_fileManager.ResetCurrentFolder();
	m_fileManager.RecreateTempFolder();
}

void CShapeCompositorDoc::SetParentWndForFileManager(CWnd * pParentWnd)
{
	m_fileManager.SetParentWnd(pParentWnd);
}

bool CShapeCompositorDoc::OnFileSaveAs(std::vector<CShapePtr> const & shapes)
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


bool CShapeCompositorDoc::OnFileOpen(CShapeCompositorView * view)
{
	CString fileName = OpenLoadDialog();
	if (fileName.GetLength() != 0)
	{
		view->ClearHistory();
		view->ResetSelectedShape();

		m_fileManager.SetFilePath(fileName.GetString());
		return m_xmlReader.Open(m_fileManager.GetFilePath(), view->GetCanvas(), view->GetShapeFactory());
	}
	return false;
}

bool CShapeCompositorDoc::OnFileSave(std::vector<CShapePtr> const & shapes)
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

CString CShapeCompositorDoc::OpenSaveDialog()
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

CString CShapeCompositorDoc::OpenLoadDialog()
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

CString CShapeCompositorDoc::GetFileName()
{
	return CString(m_fileManager.GetFileName().data());
}
