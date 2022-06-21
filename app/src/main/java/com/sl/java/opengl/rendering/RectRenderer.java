package com.sl.java.opengl.rendering;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLES30;

import com.sl.java.opengl.utils.ShaderUtil;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

/*********************************************************************
 * Created by shenglei on 2022/6/20.
 *********************************************************************/
public class RectRenderer {
    private static final String TAG = RectRenderer.class.getSimpleName();

    // Shader names.
    private static final String VERTEX_SHADER_NAME = "shaders/rect.vert";
    private static final String FRAGMENT_SHADER_NAME = "shaders/rect.frag";
    private static final int COORDS_PER_VERTEX = 3;
    private static final int BYTES_PER_VERTEX = 4;
    private static final int BYTES_PER_INDEX = 2;

    private int programId;
    private int posAttrib;
    private final float[] vertices = {
            0.5f, 0.5f, 0.0f,   // 右上角
            0.5f, -0.5f, 0.0f,  // 右下角
            -0.5f, -0.5f, 0.0f, // 左下角
            -0.5f, 0.5f, 0.0f   // 左上角
    };
    private final short[] indices = {
            0, 1, 3,
            1, 2, 3
    };

    private FloatBuffer vbo; //顶点缓冲对象
    private ShortBuffer ebo; //索引缓冲对象

    public void createOnGlThread(Context context) throws IOException {
        int vertexShader = ShaderUtil.loadGLShader(TAG, context, GLES30.GL_VERTEX_SHADER, VERTEX_SHADER_NAME);
        int fragmentShader = ShaderUtil.loadGLShader(TAG, context, GLES30.GL_FRAGMENT_SHADER, FRAGMENT_SHADER_NAME);

        programId = GLES30.glCreateProgram();
        GLES30.glAttachShader(programId, vertexShader);
        GLES30.glAttachShader(programId, fragmentShader);
        GLES30.glLinkProgram(programId);
        GLES30.glUseProgram(programId);

        posAttrib = GLES30.glGetAttribLocation(programId, "aPos");
        ShaderUtil.checkGLError(TAG, "Program creation");

        vbo = ByteBuffer.allocateDirect(vertices.length * BYTES_PER_VERTEX)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        vbo.put(vertices);
        vbo.position(0);

        ebo = ByteBuffer.allocateDirect(indices.length * BYTES_PER_INDEX).order(ByteOrder.nativeOrder()).asShortBuffer();
        ebo.put(indices);
        ebo.position(0);
    }

    public void draw() {
        GLES30.glUseProgram(programId);
        GLES30.glEnableVertexAttribArray(posAttrib);
        GLES30.glVertexAttribPointer(posAttrib, COORDS_PER_VERTEX, GLES20.GL_FLOAT, false, 0, vbo);
        GLES30.glDrawElements(GLES30.GL_TRIANGLES, indices.length, GLES30.GL_UNSIGNED_SHORT, ebo);

        GLES30.glDisableVertexAttribArray(posAttrib);

        ShaderUtil.checkGLError(TAG, "Draw");
        GLES30.glUseProgram(0);
    }
}
