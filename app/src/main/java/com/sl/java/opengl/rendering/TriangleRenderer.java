package com.sl.java.opengl.rendering;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLES30;

import com.sl.java.opengl.utils.ShaderUtil;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;

/*********************************************************************
 * Created by shenglei on 2022/6/2.
 *********************************************************************/
public class TriangleRenderer {
    private static final String TAG = TriangleRenderer.class.getSimpleName();

    // Shader names.
    private static final String VERTEX_SHADER_NAME = "shaders/triangle.vert";
    private static final String FRAGMENT_SHADER_NAME = "shaders/triangle.frag";

    private int programId;
    private int trianglePosAttrib;
    private float[] vertices = {
            // 第一个三角形
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, 0.5f, 0.0f,  // 左上角
    };
    private FloatBuffer buffer;

    public void createOnGlThread(Context context) throws IOException {
        int vertexShader = ShaderUtil.loadGLShader(TAG, context, GLES30.GL_VERTEX_SHADER, VERTEX_SHADER_NAME);
        int fragmentShader = ShaderUtil.loadGLShader(TAG, context, GLES30.GL_FRAGMENT_SHADER, FRAGMENT_SHADER_NAME);

        programId = GLES30.glCreateProgram();
        GLES30.glAttachShader(programId, vertexShader);
        GLES30.glAttachShader(programId, fragmentShader);
        GLES30.glLinkProgram(programId);
        GLES30.glUseProgram(programId);

        trianglePosAttrib = GLES30.glGetAttribLocation(programId, "aPos");
        ShaderUtil.checkGLError(TAG, "Program creation");

        buffer = ByteBuffer.allocateDirect(vertices.length * 4)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        buffer.put(vertices);
    }

    public void draw() {
        GLES30.glUseProgram(programId);
        GLES30.glEnableVertexAttribArray(trianglePosAttrib);
        buffer.rewind();
        GLES30.glVertexAttribPointer(trianglePosAttrib, 3, GLES20.GL_FLOAT, false, 0, buffer);
        GLES30.glDrawArrays(GLES30.GL_TRIANGLES, 0, buffer.remaining()/3);
        GLES30.glDisableVertexAttribArray(trianglePosAttrib);

        ShaderUtil.checkGLError(TAG, "Draw");
        GLES30.glUseProgram(0);
    }
 }
