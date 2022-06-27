//
// Created by shenglei on 2022/6/27.
//

#include "CoreImage.h"
#include <string>

static int GetFormatByteCount(ImagePixelFormat format)
{
    switch (format)
    {
        case FORMAT_GRAY8:
            return 1;

        case FORMAT_GRAY8_ALPHA8:
        case FORMAT_RGBA4444:
        case FORMAT_RGB5A1:
        case FORMAT_R5G6B5:
            return 2;

        case FORMAT_RGBA8:
            return 4;

        case FORMAT_RGB8:
            return 3;

        case FORMAT_RGB_FLOAT:
            return 12;

        default:
            break;
    }

    return 0;
}

CoreImage::CoreImage(ImagePixelFormat format, unsigned int nWidth, unsigned int nHeight, const void *pData) :
        m_eFormat(format),
        m_nWidth(nWidth),
        m_nHeight(nHeight),
        m_pDeleteFunc(NULL),
        m_bPremultipliedAlpha(false)
{
    m_pData = (void *)pData;
    m_pGetPixelsFunc = NULL;
    m_nBytesPerPixel = GetFormatByteCount(m_eFormat);
}

CoreImage::CoreImage()
{
    m_eFormat = FORMAT_UNKNOWN;
    m_nWidth = 0;
    m_nHeight = 0;
    m_nBytesPerPixel = 0;
    m_pDeleteFunc = NULL;
    m_pData = NULL;
    m_bPremultipliedAlpha = true;
    m_pGetPixelsFunc = NULL;
}

CoreImage::~CoreImage()
{
    if (m_pDeleteFunc && m_pData)
    {
        m_pDeleteFunc(m_pData);
        m_pData = NULL;
    }

    m_eFormat = FORMAT_UNKNOWN;
    m_nWidth = 0;
    m_nHeight = 0;
    m_nBytesPerPixel = 0;
    m_pDeleteFunc = NULL;
    m_pGetPixelsFunc = NULL;
    m_bPremultipliedAlpha = false;
}

void CoreImage::AllocPixels()
{
    size_t nByteCount = m_nWidth * m_nHeight * GetFormatByteCount(m_eFormat);
    if (nByteCount == 0)
    {
        return;
    }

    m_pData = malloc(nByteCount);
    m_pDeleteFunc = free;
}

unsigned int CoreImage::GetWidth() const
{
    return m_nWidth;
}

unsigned int CoreImage::GetHeight() const
{
    return m_nHeight;
}

unsigned int CoreImage::GetBytesPerPixel() const
{
    return m_nBytesPerPixel;
}

unsigned int CoreImage::GetBytesPerLine() const
{
    return m_nBytesPerPixel * m_nWidth;
}

ImagePixelFormat CoreImage::GetFormat() const
{
    return m_eFormat;
}

unsigned char* CoreImage::GetPixels() const
{
    if (m_pGetPixelsFunc)
    {
        return m_pGetPixelsFunc(m_pData);
    }

    return (unsigned char*)m_pData;
}

bool CoreImage::HasPremultipliedAlpha() const
{
    return m_bPremultipliedAlpha;
}

void CoreImage::SetImageInfo(ImagePixelFormat format, unsigned int nWidth, unsigned int nHeight)
{
    m_eFormat = format;
    m_nBytesPerPixel = GetFormatByteCount(m_eFormat);
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_pData = NULL;

    m_pDeleteFunc = NULL;
    m_pGetPixelsFunc = NULL;
}

void CoreImage::SetImageInfo(ImagePixelFormat format, unsigned int nWidth, unsigned int nHeight, const void* pData, DeleteFun pDeleteFunc, GetPixelsFunc pGetPixelsFunc)
{
    m_eFormat = format;
    m_nBytesPerPixel = GetFormatByteCount(m_eFormat);
    m_nWidth = nWidth;
    m_nHeight = nHeight;
    m_pData = (void*)pData;

    m_pDeleteFunc = pDeleteFunc;
    m_pGetPixelsFunc = pGetPixelsFunc;
}

void CoreImage::SetPremultipliedAlpha(bool bPremultipliedAlpha)
{
    m_bPremultipliedAlpha = bPremultipliedAlpha;
}

void CoreImage::Release()
{
    if (m_pDeleteFunc && m_pData)
    {
        m_pDeleteFunc(m_pData);
        m_pData = NULL;
    }
    if (m_pGetPixelsFunc) {
        m_pGetPixelsFunc = NULL;
    }
}