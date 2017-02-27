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
protected: // создать только из сериализации
	CShapeCompositorDoc();
	DECLARE_DYNCREATE(CShapeCompositorDoc)

// Атрибуты
public:
// Операции
public:
	std::vector<CShapePtr>& GetShapes();

	static bool Save(const std::wstring path, std::vector<CShapePtr> const& shapes);
	static bool Open(const std::wstring path, CCanvas & canvas);

	void SetCanvas(CCanvas * pCanvas);
	void SetHistory(CHistory * pHistory);

	afx_msg void OnFileSaveAs();
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
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
	std::vector<CShapePtr> m_shapes;
	CCanvas* m_pCanvas = nullptr;
	CHistory* m_pHistory = nullptr;

	std::wstring m_fileToSave;
// Созданные функции схемы сообщений
protected:
	DECLARE_MESSAGE_MAP()

	CString OpenSaveDialog();
	CString OpenLoadDialog();

#ifdef SHARED_HANDLERS
	// Вспомогательная функция, задающая содержимое поиска для обработчика поиска
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
