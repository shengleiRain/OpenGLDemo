package com.sl.java.opengl.rendering.cnative;

/*********************************************************************
 * Created by shenglei on 2022/6/26.
 *********************************************************************/
class JNIBase {
    static {
        System.loadLibrary("opengl");
    }
}
