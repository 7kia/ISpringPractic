#pragma once

#include <wincodec.h>
#include <commdlg.h>
#include <d2d1.h>
#include <atlbase.h>
#include <iostream> 
#include <atlstr.h> 

class CD2DImageFactory
{
public:
	CD2DImageFactory();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	void					SetRenderTarget(ID2D1HwndRenderTarget * pRenderTarget);

	// Create texture require change data class, as work Direct2d
	CComPtr<ID2D1Bitmap>	CreateTexture(const std::wstring & name);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CComPtr<IWICBitmapDecoder>					m_bitmapDecoder;
	CComPtr<IWICImagingFactory>					m_pIWICFactory;
	CComPtr<IWICFormatConverter>				m_pConvertedSourceBitmap;
	ID2D1HwndRenderTarget *						m_pRenderTarget = nullptr;
};