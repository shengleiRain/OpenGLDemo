//
// Created by shenglei on 2022/6/27.
//

#ifndef OPENGLDEMO_COREIMAGE_H
#define OPENGLDEMO_COREIMAGE_H


#include <stdlib.h>
#include <memory>

//图像的像素格式
enum ImagePixelFormat
{
    FORMAT_UNKNOWN,
    FORMAT_GRAY8,            //gray
    FORMAT_GRAY8_ALPHA8,     //GRAY AND ALPHA
    FORMAT_RGBA8,            //RGBA32位
    FORMAT_RGB8,             //RGB
    FORMAT_RGBA4444,
    FORMAT_RGB5A1,
    FORMAT_R5G6B5,
    FORMAT_RGB_FLOAT,        //RGBfloat
};

//图像的存储格式  bmp/png等
enum ImageStoreFormat
{
    kUnknown_Format,
    kBMP_Format,
    kJPEG_Format,
    kPNG_Format,
    kTGA_Format,
};


/**
    图像数据的类
    重要！！！ 左上角的纹理坐标是(0,0)，左下角是(0,1)
 **/
class CoreImage
{
public:
    CoreImage();

    CoreImage(ImagePixelFormat format,
              unsigned int nWidth,
              unsigned int nHeight,
              const void* pData);

    ~CoreImage();

    /**
    * 分配图像内存
    *
    * @return 无
    */
    void AllocPixels();

    unsigned char* GetPixels() const;

    ImagePixelFormat GetFormat() const;

    unsigned int GetWidth() const;

    unsigned int GetHeight() const;

    unsigned int GetBytesPerPixel() const;

    unsigned int GetBytesPerLine() const;

    bool HasPremultipliedAlpha() const;

    void SetPremultipliedAlpha(bool bPremultipliedAlpha);

    /**
    * 设置图像的基本信息，基本信息设置后再使用的话需要调用AllocPixels分配内存
    *
    * @param format 像素格式
    * @param nWidth 图像宽度
    * @param nHeight 图像高度
    * @return 无
    */
    void SetImageInfo(ImagePixelFormat format, unsigned int nWidth, unsigned int nHeight);

    /**
    * 删除图像内存的回调函数
    *
    * @return 无
    */
    typedef void(*DeleteFun)(void *);

    /**
    * 获得图像数据指针的函数
    *
    * @return 无
    */
    typedef unsigned char* (*GetPixelsFunc)(void *);

    /**
    * 设置图像的基本信息
    *
    * @param format 像素格式
    * @param nWidth 图像宽度
    * @param nHeight 图像高度
    * @param pData 图像数据
    * @param pDeleteFunc 如果图像数据的内存释放需要由Image内部来释放，那么传入删除像素的回调函数，不需要的话传入NULL
    * @param pGetPixelsFunc 如果传入的数据是直接能访问的图像数据，例如malloc的内存，那么传入NULL，如果是iOS的CFDataRef数据，则需要传入获取CFDataRef原始指针的函数
    * @return 无
    */
    void SetImageInfo(ImagePixelFormat format, unsigned int nWidth, unsigned int nHeight, const void* pData, DeleteFun pDeleteFunc, GetPixelsFunc pGetPixelsFunc);

    /**
    * 释放图像的内存数据
    *
    * @return 无
    */
    void Release();

private:
    unsigned int                m_nWidth;                //宽
    unsigned int                m_nHeight;               //高
    unsigned int                m_nBytesPerPixel;        //每个像素的字节数，根据m_eFormat决定
    ImagePixelFormat            m_eFormat;               //数据格式
    bool                        m_bPremultipliedAlpha;   //是否预先乘以alpha
    void *                      m_pData;                 //数据
    DeleteFun                   m_pDeleteFunc;           //删除回调函数
    GetPixelsFunc               m_pGetPixelsFunc;        //获得像素的回调函数
};

typedef std::shared_ptr<CoreImage> ImageSharedPtr;


#endif //OPENGLDEMO_COREIMAGE_H
