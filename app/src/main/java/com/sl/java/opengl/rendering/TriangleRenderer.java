package com.sl.java.opengl.rendering;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLES30;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

import androidx.annotation.NonNull;

import com.sl.java.opengl.utils.ShaderUtil;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.util.Random;

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
    private int uniColorAttrib;
    private final float[] vertices = {
            // 第一个三角形
            0.0f, 0.5f, 0.0f,
            -0.5f,-0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
    };
    private FloatBuffer buffer;

    private int seed = 0;
    private final Random random = new Random();

    public void createOnGlThread(Context context) throws IOException {
        int vertexShader = ShaderUtil.loadGLShader(TAG, context, GLES30.GL_VERTEX_SHADER, VERTEX_SHADER_NAME);
        int fragmentShader = ShaderUtil.loadGLShader(TAG, context, GLES30.GL_FRAGMENT_SHADER, FRAGMENT_SHADER_NAME);

        programId = GLES30.glCreateProgram();
        GLES30.glAttachShader(programId, vertexShader);
        GLES30.glAttachShader(programId, fragmentShader);
        GLES30.glLinkProgram(programId);
        GLES30.glUseProgram(programId);

        trianglePosAttrib = GLES30.glGetAttribLocation(programId, "aPos");
        uniColorAttrib = GLES30.glGetUniformLocation(programId, "uniColor");
        ShaderUtil.checkGLError(TAG, "Program creation");

        buffer = ByteBuffer.allocateDirect(vertices.length * 4)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        buffer.put(vertices);
    }

    public void draw() {
        GLES30.glUseProgram(programId);
        random.setSeed(seed++);
        float x = random.nextFloat();
        float y = random.nextFloat();
        float z = random.nextFloat();
        Log.d(TAG, "x="+x+"; y="+y+"; z="+z);
        GLES30.glUniform4f(uniColorAttrib, x, y, z, 1.0f);
        GLES30.glEnableVertexAttribArray(trianglePosAttrib);
        buffer.rewind();
        GLES30.glVertexAttribPointer(trianglePosAttrib, 3, GLES20.GL_FLOAT, false, 0, buffer);
        GLES30.glDrawArrays(GLES30.GL_TRIANGLES, 0, buffer.remaining()/3);
        GLES30.glDisableVertexAttribArray(trianglePosAttrib);

        ShaderUtil.checkGLError(TAG, "Draw");
        GLES30.glUseProgram(0);
    }
 }
