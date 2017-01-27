#pragma once

#include <memory>

#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <afxwin.h>

#include <vector>

#include "Shapes\ShapeFactory.h"
#include "RenderShapeVisitor.h"
#include "CanvasCommands\AllCanvasCommand.h"

static const size_t MAX_COMMANDS = 5;

class CShapeCompositorView;

class CCanvas
	: public IRenderShapeVisitor
{
public:
	CCanvas();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	HRESULT		Render();

	HRESULT		CreateRecources(CShapeCompositorView * window);

	void		AddShape(TypeShape type);
	void		DeleteShape(PCShape pShape);
	void		DeleteLastShape();

private:

	void		RenderShapes();

	//--------------------------------------------
	// IRenderShapeVisitor

	void		Visit(const CRectangleShape & shape) override;
	void		Visit(const CEllipseShape & shape) override;
	void		Visit(const CTriangleShape & shape) override;

	//--------------------------------------------

	//////////////////////////////////////////////////////////////////////
	// Data
public:
	class CController;
	std::unique_ptr<CController>				m_controller;

	CComPtr<ID2D1Factory>						m_pDirect2dFactory;
	CComPtr<ID2D1HwndRenderTarget>				m_pRenderTarget;


	CShapeFactory								m_shapeFactory;

	CComPtr<ID2D1SolidColorBrush>				m_fillBrush;;
	CComPtr<ID2D1SolidColorBrush>				m_outlineBrush;
	CComPtr<ID2D1PathGeometry>					m_pathGeometry;
	CComPtr<ID2D1GeometrySink>					m_geometrySink;

	// TODO : delete it
	// TODO : transfer

	CComPtr<ID2D1SolidColorBrush>						m_pLightSlateGrayBrush;
	CComPtr<ID2D1SolidColorBrush>						m_pCornflowerBlueBrush;


private:

	// TODO : add
	// Shapes
	// ShapeFactory
	// D2DFactory

	CShapeCompositorView *	m_window = nullptr;
	std::vector<PCShape>	m_shapes;
};

class CCanvas::CController
{
public:
	CController(CCanvas * pCanvas);

	enum class Command
	{
		AddTriangle
		, AddRectangle
		, AddEllipse
		, Undo
		, Redo
	};
	//////////////////////////////////////////////////////////////////////
	// Methods
public:
	void ExecuteCommand(Command command);
private:
	void AddCommand(const PCanvasCommand command);
	void ExecuteCurrent();
	void UndoCommand();
	void RedoCommand();

	//////////////////////////////////////////////////////////////////////
	// Data
private:
	// TODO : transfer to other place(might class)
	std::vector<PCanvasCommand>						m_history;
	std::vector<PCanvasCommand>::reverse_iterator	m_currentCommand = m_history.rbegin();

	CCanvas * m_pCanvas = nullptr;
};