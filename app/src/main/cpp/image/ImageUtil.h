//
// Created by shenglei on 2022/6/27.
//

#ifndef OPENGLDEMO_IMAGEUTIL_H
#define OPENGLDEMO_IMAGEUTIL_H

#include <android/bitmap.h>
#include "CoreImage.h"

class ImageUtil {
public:
    static ImageSharedPtr convertBitmap2Image(void* pImageData, const AndroidBitmapInfo& bitmapInfo);
};


#endif //OPENGLDEMO_IMAGEUTIL_H
