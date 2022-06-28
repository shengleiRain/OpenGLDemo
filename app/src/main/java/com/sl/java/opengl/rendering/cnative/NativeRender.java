package com.sl.java.opengl.rendering.cnative;

import android.graphics.Bitmap;

/*********************************************************************
 * Created by shenglei on 2022/6/26.
 *********************************************************************/
public class NativeRender extends JNIBase{
    public NativeRender() {
        nativeOnInit();
    }

    public void onSurfaceCreated() {
        nativeOnSurfaceCreated();
    }

    public void onSurfaceChanged(int width, int height) {
        nativeOnSurfaceChanged(width, height);
    }

    public void onDrawFrame() {
        nativeOnDrawFrame();
    }

    public void setBitmap(Bitmap bitmap) {
        nativeSetBitmap(bitmap);
    }

    public void moveCamera(int direction) {
        nativeMoveCamera(direction);
    }


    private native void nativeOnInit();
    private native void nativeOnUnInit();
    private native void nativeOnSurfaceCreated();
    private native void nativeOnSurfaceChanged(int width, int height);
    private native void nativeOnDrawFrame();
    private native void nativeSetBitmap(Bitmap bitmap);
    private native void nativeMoveCamera(int direction);

}
