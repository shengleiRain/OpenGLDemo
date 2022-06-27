//
// Created by shenglei on 2022/6/27.
//

#include "ImageUtil.h"

ImageSharedPtr
ImageUtil::convertBitmap2Image(void *pImageData, const AndroidBitmapInfo &bitmapInfo) {
    ImagePixelFormat imagePixelFormat;
    switch (bitmapInfo.format) {
        case ANDROID_BITMAP_FORMAT_RGBA_8888:
            imagePixelFormat = FORMAT_RGBA8;
            break;
        case ANDROID_BITMAP_FORMAT_A_8:
            imagePixelFormat = FORMAT_GRAY8;
        default:
            return nullptr;
    }
    auto imageSharedPtr = std::make_shared<CoreImage>();
    imageSharedPtr->SetImageInfo(imagePixelFormat, bitmapInfo.width, bitmapInfo.height, pImageData,
                                 nullptr, nullptr);
    return imageSharedPtr;
}
