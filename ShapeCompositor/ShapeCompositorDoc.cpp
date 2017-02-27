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
#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace
{
	std::string GetShapeName(ShapeType type)
	{
		switch (type)
		{
		case ShapeType::Triangle:
			return "Triangle";
		case ShapeType::Rectangle:
			return "Rectangle";
		case ShapeType::Ellipse:
			return "Ellipse";
		default:
			throw std::runtime_error("Incorrect shape type");
			break;
		}
		return "Triangle";
	}

	ShapeType GetShapeType(std::string const& typeStr)
	{
		if (typeStr == "Triangle")
		{
			return ShapeType::Triangle;
		}
		else if (typeStr == "Rectangle")
		{
			return ShapeType::Rectangle;
		}
		else if (typeStr == "Ellipse")
		{
			return ShapeType::Ellipse;
		}
		else
		{
			throw std::runtime_error("Incorrect shape type");
		}
	}
}


// CShapeCompositorDoc

IMPLEMENT_DYNCREATE(CShapeCompositorDoc, CDocument)

BEGIN_MESSAGE_MAP(CShapeCompositorDoc, CDocument)
	ON_COMMAND(ID_FILE_SAVE_AS, &CShapeCompositorDoc::OnFileSaveAs)
	ON_COMMAND(ID_FILE_OPEN, &CShapeCompositorDoc::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CShapeCompositorDoc::OnFileSave)
END_MESSAGE_MAP()


// создание/уничтожение CShapeCompositorDoc

CShapeCompositorDoc::CShapeCompositorDoc()
{
	// TODO: добавьте код для одноразового вызова конструктора

}

CShapeCompositorDoc::~CShapeCompositorDoc()
{
}

std::vector<CShapePtr>& CShapeCompositorDoc::GetShapes()
{
	return m_shapes;
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

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
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


bool CShapeCompositorDoc::Save(const std::wstring path, std::vector<CShapePtr> const & shapes)
{
	if (path.empty())
	{
		return false;
	}
	try
	{
		boost::property_tree::ptree propertyTree;
		for (auto &shape : shapes)
		{
			boost::property_tree::ptree child;
			child.add("Type", GetShapeName(shape->GetType()));
			child.add("X", std::to_string(shape->GetPosition().x));
			child.add("Y", std::to_string(shape->GetPosition().y));
			child.add("Width", std::to_string(shape->GetSize().width));
			child.add("Height", std::to_string(shape->GetSize().height));
			propertyTree.add_child("Shapes.Shape", child);
		}
		std::stringstream stream;
		boost::property_tree::write_xml(stream, propertyTree);

		std::ofstream out(path);
		std::string str;
		while (!stream.eof())
		{
			stream >> str;
			out << str;
		}
		out.close();
		return true;
	}
	catch (boost::property_tree::xml_parser_error)
	{
		std::cout << "XML parser error!" << std::endl;
		throw;
	}
	return false;
}

bool CShapeCompositorDoc::Open(const std::wstring path, CCanvas & canvas)
{
	if (path.empty())
	{
		return false;
	}
	try
	{
		std::ifstream stream(path);
		boost::property_tree::ptree propertyTree;
		boost::property_tree::read_xml(stream, propertyTree);
		for (auto &shape : propertyTree.get_child("Shapes"))
		{
			if (shape.first == "Shape")
			{
				std::string type = shape.second.get<std::string>("Type");
				float x = shape.second.get<float>("X");
				float y = shape.second.get<float>("Y");
				float width = shape.second.get<float>("Width");
				float height = shape.second.get<float>("Height");

				SShapeData data;
				data.type = GetShapeType(type);
				data.position = Vec2f(x, y);
				data.size = SSize(width, height);

				canvas.PushBackShape(data);
			}
		}
		stream.close();
		return true;
	}
	catch (boost::property_tree::xml_parser_error)
	{
		std::cout << "XML parser error!" << std::endl;
		throw;
	}
	return false;
}

void CShapeCompositorDoc::SetCanvas(CCanvas * pCanvas)
{
	m_pCanvas = pCanvas;
}

void CShapeCompositorDoc::SetHistory(CHistory * pHistory)
{
	m_pHistory = pHistory;
}


CString CShapeCompositorDoc::OpenSaveDialog()
{
	CString fileName;

	CFileDialog fileDlg(FALSE
		, _T("")
		, _T("*.xml")
		, OFN_HIDEREADONLY
		, L"XML Files\0"    L"*.xml\0");
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();

		// Implement opening and reading file in here.

		//Change the window's title to the opened file's title.
		fileName = fileDlg.GetFileTitle();

		//if(fileName.Find)
		// TODO : add checks for fromat
		fileName.Append(L".xml");
	}

	return fileName;// GetSaveFileName(&ofn);
}

CString CShapeCompositorDoc::OpenLoadDialog()
{
	CString fileName;

	CFileDialog fileDlg(TRUE
		, NULL
		, _T("*.xml")
		, OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST
		, L"XML Files\0"    L"*.xml\0");
	if (fileDlg.DoModal() == IDOK)
	{
		CString pathName = fileDlg.GetPathName();

		// Implement opening and reading file in here.

		//Change the window's title to the opened file's title.
		fileName = fileDlg.GetFileTitle();

		//if(fileName.Find)
		// TODO : add checks for fromat
		fileName.Append(L".xml");
	}

	return fileName;// GetSaveFileName(&ofn);
}


void CShapeCompositorDoc::OnFileSaveAs()
{
	CString fileName = OpenSaveDialog();
	if (fileName.GetLength() != 0)
	{
		m_fileToSave = fileName.GetString();
		Save(m_fileToSave, m_shapes);
	}
}


void CShapeCompositorDoc::OnFileOpen()
{
	CString fileName = OpenLoadDialog();
	if (fileName.GetLength() != 0)
	{
		m_shapes.clear();
		m_pHistory->Clear();
		m_pCanvas->GetFrameSelectedShape()->ResetSelectShapePtr();// TODO : see can rewrite

		m_fileToSave = fileName.GetString();
		Open(m_fileToSave, *m_pCanvas);
	}
}

void CShapeCompositorDoc::OnFileSave()
{
	if (m_fileToSave.empty())
	{
		OnFileSaveAs();
	}
	else
	{
		Save(m_fileToSave, m_shapes);
	}
}