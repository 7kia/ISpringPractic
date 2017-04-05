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



#include "Canvas\Canvas.h"
#include "Canvas\History.h"
#include "XMLReader\XMLReader.h"
#include "FileManager.h"

class CShapeCompositorView;
class CShapeCompositorDoc : public CDocument
{
protected: // ������� ������ �� ������������
	CShapeCompositorDoc();
	DECLARE_DYNCREATE(CShapeCompositorDoc)

// ��������
public:
// ��������
public:
	bool IsNewDocument() const;
	void ResetCurrentFolder();
	void SetParentWndForFileManager(CWnd * pParentWnd);// For CDialog need parent wnd

	CString OpenSaveDialog();
	CString OpenLoadDialog();
	
	CString GetFileName();

	afx_msg bool OnFileSaveAs(std::vector<CShapePtr> const & shapes);
	afx_msg bool OnFileOpen(CShapeCompositorView * view);
	afx_msg bool OnFileSave(std::vector<CShapePtr> const & shapes);
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
	CXMLReader m_xmlReader;
	CFileManager m_fileManager;
// ��������� ������� ����� ���������
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// ��������������� �������, �������� ���������� ������ ��� ����������� ������
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
