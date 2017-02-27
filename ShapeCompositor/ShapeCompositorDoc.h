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

// ShapeCompositorDoc.h : ��������� ������ CShapeCompositorDoc
//


#pragma once

#include <vector>
#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>
#include <string>
#include <boost\property_tree\ptree.hpp>
#include <boost\property_tree\xml_parser.hpp>

#include "Canvas\Canvas.h"
#include "Canvas\History.h"

class CShapeCompositorDoc : public CDocument
{
protected: // ������� ������ �� ������������
	CShapeCompositorDoc();
	DECLARE_DYNCREATE(CShapeCompositorDoc)

// ��������
public:
// ��������
public:
	std::vector<CShapePtr>& GetShapes();

	static bool Save(const std::wstring path, std::vector<CShapePtr> const& shapes);
	static bool Open(const std::wstring path, CCanvas & canvas);

	void SetCanvas(CCanvas * pCanvas);
	void SetHistory(CHistory * pHistory);

	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
// ���������������
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);


#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// ����������
public:
	virtual ~CShapeCompositorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	std::vector<CShapePtr> m_shapes;
	CCanvas* m_pCanvas = nullptr;
	CHistory* m_pHistory = nullptr;

	std::wstring m_fileToSave;
// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()

	CString OpenSaveDialog();
	CString OpenLoadDialog();

#ifdef SHARED_HANDLERS
	// ��������������� �������, �������� ���������� ������ ��� ����������� ������
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
