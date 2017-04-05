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

// ShapeCompositorDoc.h : интерфейс класса CShapeCompositorDoc
//


#pragma once



#include "Canvas\Canvas.h"
#include "Canvas\History.h"
#include "XMLReader\XMLReader.h"
#include "FileManager.h"

class CShapeCompositorView;
class CShapeCompositorDoc : public CDocument
{
protected: // создать только из сериализации
	CShapeCompositorDoc();
	DECLARE_DYNCREATE(CShapeCompositorDoc)

// Атрибуты
public:
// Операции
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
// Переопределение
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);


#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Реализация
public:
	virtual ~CShapeCompositorDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CXMLReader m_xmlReader;
	CFileManager m_fileManager;
// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
