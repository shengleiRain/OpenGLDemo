package com.sl.java.opengl.utils;

import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLES30;
import android.opengl.GLUtils;
import android.util.Log;

/*********************************************************************
 * Created by shenglei on 2022/6/23.
 *********************************************************************/
public final class TextureUtil {
    private static final String TAG = TextureUtil.class.getSimpleName();

    private TextureUtil() {

    }

    public static int loadTexture(Context context, int resId) {
        int[] textureObjectId = new int[1];
        GLES20.glGenTextures(1, textureObjectId, 0);
        if (textureObjectId[0] == 0) {
            Log.d(TAG, "纹理加载失败");
            return 0;
        }

        BitmapFactory.Options options = new BitmapFactory.Options();
        options.inScaled = false;

        Bitmap bitmap = BitmapFactory.decodeResource(context.getResources(), resId, options);
        if (bitmap == null) {
            Log.d(TAG, "加载图片为空");
            GLES20.glDeleteTextures(1, textureObjectId, 0);
            return 0;
        }
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureObjectId[0]);

        //设置过滤器
        /**
         * GL_TEXTURE_MIN_FILTER:在缩小的情况下用  GL_LINEAR_MIPMAP_LINEAR：三线性过滤
         * GL_TEXTURE_MAG_FILTER：在放大的情况下用  GL_TEXTURE_MAG_FILTER：双线性过滤
         */
//        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES30.GL_MIRRORED_REPEAT);
//        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_MIRRORED_REPEAT);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR_MIPMAP_LINEAR);
        GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_LINEAR);

        //把图片加载到opengl里面
        GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);
        //释放bitmap
        bitmap.recycle();
        //生成mip贴图
        GLES20.glGenerateMipmap(GLES20.GL_TEXTURE_2D);

        //解除纹理绑定  第二个参数传0 就是解除绑定
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, 0);
        return textureObjectId[0];
    }
}
