#pragma once

#include <wincodec.h>
#include <commdlg.h>
#include <d2d1.h>
#include <atlbase.h>
#include <iostream> 

class CD2DImageFactory
{
public:
	CD2DImageFactory();
	//////////////////////////////////////////////////////////////////////
	// Methods
public:

	void			SetRenderTarget(ID2D1HwndRenderTarget * pRenderTarget);
	//void			Get();
	CComPtr<ID2D1Bitmap>	CreateTexture(const std::string & name);
	//////////////////////////////////////////////////////////////////////
	// Data
private:
	CComPtr<IWICBitmapDecoder>					m_bitmapDecoder;
	CComPtr<IWICImagingFactory>					m_pIWICFactory;
	CComPtr<IWICFormatConverter>				m_pConvertedSourceBitmap;
	ID2D1HwndRenderTarget *						m_pRenderTarget = nullptr;
};