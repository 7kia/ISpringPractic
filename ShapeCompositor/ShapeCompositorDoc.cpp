// ���� �������� ��� MFC Samples ������������� ���������������� ����������������� ���������� Fluent �� ������ MFC � Microsoft Office
// ("Fluent UI") � ��������������� ������������� ��� ���������� �������� � �������� ���������� �
// ����������� �� ������ Microsoft Foundation Classes � ��������� ����������� ������������,
// ���������� � ����������� ����������� ���������� MFC C++.  
// ������� ������������� ���������� �� �����������, ������������� ��� ��������������� Fluent UI �������� ��������.  
// ��� ��������� �������������� �������� � ����� ������������ ��������� Fluent UI �������� ���-����
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// (C) ���������� ���������� (Microsoft Corp.)
// ��� ����� ��������.

// ShapeCompositorDoc.cpp : ���������� ������ CShapeCompositorDoc
//

#include "stdafx.h"
// SHARED_HANDLERS ����� ���������� � ������������ �������� ��������� ���������� ������� ATL, �������
// � ������; ��������� ��������� ������������ ��� ��������� � ������ �������.
#ifndef SHARED_HANDLERS
#include "ShapeCompositor.h"
#endif

#include "ShapeCompositorDoc.h"
#include "ShapeCompositorView.h"
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
END_MESSAGE_MAP()


// ��������/����������� CShapeCompositorDoc

CShapeCompositorDoc::CShapeCompositorDoc()
{
	// TODO: �������� ��� ��� ������������ ������ ������������

}

CShapeCompositorDoc::~CShapeCompositorDoc()
{
}


BOOL CShapeCompositorDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �������� ��� ��������� �������������
	// (��������� SDI ����� �������� ������������ ���� ��������)

	return TRUE;
}




// ������������ CShapeCompositorDoc

void CShapeCompositorDoc::Serialize(CArchive& ar)
{
	
	if (ar.IsStoring())
	{
		// TODO: �������� ��� ����������
	}
	else
	{
		// TODO: �������� ��� ��������
	}
}

#ifdef SHARED_HANDLERS

// ��������� ��� �������
void CShapeCompositorDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// �������� ���� ��� ��� ����������� ������ ���������
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

// ��������� ������������ ������
void CShapeCompositorDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// ������� ���������� ������ �� ������ ���������. 
	// ����� ����������� ������ ����������� ������ � ������� ";"

	// ��������:  strSearchContent = _T("�����;�������������;����;������ ole;");
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

// ����������� CShapeCompositorDoc

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


// ������� CShapeCompositorDoc


bool CShapeCompositorDoc::Save(const std::wstring path, std::vector<CShapePtr> const & shapes)
{
	if (path.empty())
	{
		return false;
	}
	try
	{
		boost::property_tree::ptree propertyTree;

		boost::property_tree::ptree child;
		if (shapes.size() == 0)
		{
			propertyTree.add_child("Shapes", child);
		}
		for (auto &shape : shapes)
		{		
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

bool CShapeCompositorDoc::Open(
	const std::wstring path
	, CCanvas & canvas
	, const CShapeFactory & factory
)
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

				canvas.PushBackShape(factory.CreateShape(data));
			}
		}
		stream.close();
		return true;
	}
	catch (boost::property_tree::xml_parser_error e)
	{
		std::cout << e.what() << std::endl;
		throw;
	}
	return false;
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


void CShapeCompositorDoc::OnFileSaveAs(std::vector<CShapePtr> const & shapes)
{
	CString fileName = OpenSaveDialog();
	if (fileName.GetLength() != 0)
	{
		m_fileToSave = fileName.GetString();
		Save(m_fileToSave, shapes);
	}
}


void CShapeCompositorDoc::OnFileOpen(CShapeCompositorView * view)
{
	CString fileName = OpenLoadDialog();
	if (fileName.GetLength() != 0)
	{
		m_shapesData.clear();
		view->ClearHistory();
		view->ResetSelectedShape();

		m_fileToSave = fileName.GetString();
		Open(m_fileToSave, view->GetCanvas(), view->GetShapeFactory());
	}
}

void CShapeCompositorDoc::OnFileSave(std::vector<CShapePtr> const & shapes)
{
	if (m_fileToSave.empty())
	{
		OnFileSaveAs(shapes);
	}
	else
	{
		Save(m_fileToSave, shapes);
	}
}