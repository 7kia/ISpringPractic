#include "stdafx.h"
#include "D2DImageFactory.h"

CD2DImageFactory::CD2DImageFactory()
{
	HRESULT hr = S_OK;

	// Create WIC factory
	hr = CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&m_pIWICFactory)
	);

	if (!SUCCEEDED(hr))
	{
		throw std::runtime_error("m_pIWICFactory not create");
	}

}

void CD2DImageFactory::SetRenderTarget(ID2D1HwndRenderTarget * pRenderTarget)
{
	m_pRenderTarget = pRenderTarget;
}

CComPtr<ID2D1Bitmap> CD2DImageFactory::CreateTexture(const std::string & name)
{
	CComPtr<ID2D1Bitmap> texture;

	IWICBitmapDecoder *pDecoder = nullptr;

	HRESULT hr = S_OK;

	hr = m_pIWICFactory->CreateDecoderFromFilename(
		CString(name.data()),                      // Image to be decoded
		nullptr,                         // Do not prefer a particular vendor
		GENERIC_READ,                    // Desired read access to the file
		WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
		&pDecoder                        // Pointer to the decoder
	);

	// Retrieve the first frame of the image from the decoder
	CComPtr<IWICBitmapFrameDecode> pFrame = nullptr;

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pFrame);
	}

	//Step 3: Format convert the frame to 32bppPBGRA
	if (SUCCEEDED(hr))
	{
		m_pConvertedSourceBitmap.Release();
		hr = m_pIWICFactory->CreateFormatConverter(&m_pConvertedSourceBitmap);
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pConvertedSourceBitmap->Initialize(
			pFrame,                          // Input bitmap to convert
			GUID_WICPixelFormat32bppPBGRA,   // Destination pixel format
			WICBitmapDitherTypeNone,         // Specified dither pattern
			nullptr,                         // Specify a particular palette 
			0.f,                             // Alpha threshold
			WICBitmapPaletteTypeCustom       // Palette translation type
		);
	}

	//Step 4: Create render target and D2D bitmap from IWICBitmapSource
	if (SUCCEEDED(hr))
	{
		if (m_pRenderTarget == nullptr)
		{
			throw std::runtime_error("RenderTarget not create");
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = m_pRenderTarget->CreateBitmapFromWicBitmap(m_pConvertedSourceBitmap, nullptr, &texture);
	}

	return texture;
}
