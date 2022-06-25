package com.sl.java.opengl.rendering;

import android.content.Context;
import android.opengl.GLES20;
import android.opengl.GLES30;
import android.opengl.Matrix;

import com.sl.java.opengl.R;
import com.sl.java.opengl.utils.ShaderUtil;
import com.sl.java.opengl.utils.TextureUtil;

import java.io.IOException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

/*********************************************************************
 * Created by shenglei on 2022/6/23.
 *********************************************************************/
public class TexRectRenderer {
    private static final String TAG = TexRectRenderer.class.getSimpleName();

    private static final String VERTEX_NAME = "shaders/tex_rect.vert";
    private static final String FRAGMENT_NAME = "shaders/tex_rect.frag";
    private static final int COORDS_PER_VERTEX = 3;
    private static final int BYTES_PER_VERTEX = 4;
    private static final int BYTES_PER_INDEX = 2;

    private int programId;
    private int texture1Id;
    private int texture2Id;

    private static final int posAttrib = 0;
    private static final int colorAttrib = 1;
    private static final int texCoordAttrib = 2;
    private int texture1Uniform;
    private int texture2Uniform;
    private int modelMUniform;
    private int viewMUniform;
    private int projectionMUniform;

    private static final float[] posVertices = {
            //---- 位置 ----
            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,

            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f, -0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,

            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,

            -0.5f, -0.5f, -0.5f,
            0.5f, -0.5f, -0.5f,
            0.5f, -0.5f,  0.5f,
            0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f,  0.5f,
            -0.5f, -0.5f, -0.5f,

            -0.5f,  0.5f, -0.5f,
            0.5f,  0.5f, -0.5f,
            0.5f,  0.5f,  0.5f,
            0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f,  0.5f,
            -0.5f,  0.5f, -0.5f
    };
    private static final float[] colorVertices = {
            1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f,
    };
    private static final float[] texVertices = {
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            1.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            0.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f,
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            1.0f, 0.0f,
            0.0f, 0.0f,
            0.0f, 1.0f
    };
    private static final short[] indices = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };

    private FloatBuffer posBuffer; //顶点缓冲对象
    private FloatBuffer colorBuffer;
    private FloatBuffer texBuffer;
    private ShortBuffer ebo; //索引缓冲对象

    private FloatBuffer modelMatrixBuffer;
    private FloatBuffer viewMatrixBuffer;
    private FloatBuffer projectionMatrixBuffer;
    private float[] modelMatrix = new float[16];
    private float[] viewMatrix = new float[16];
    private float[] projectionMatrix = new float[16];


    public void createOnGlThread(Context context) throws IOException {
        int fragShader = ShaderUtil.loadGLShader(TAG, context, GLES30.GL_FRAGMENT_SHADER, FRAGMENT_NAME);
        int vertexShader = ShaderUtil.loadGLShader(TAG, context, GLES30.GL_VERTEX_SHADER, VERTEX_NAME);

        programId = GLES30.glCreateProgram();
        GLES30.glAttachShader(programId, fragShader);
        GLES30.glAttachShader(programId, vertexShader);
        GLES30.glLinkProgram(programId);
        GLES30.glUseProgram(programId);
        ShaderUtil.checkGLError(TAG, "Program creation");

        posBuffer = ByteBuffer.allocateDirect(posVertices.length * BYTES_PER_VERTEX)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        posBuffer.put(posVertices);
        posBuffer.position(0);

        colorBuffer = ByteBuffer.allocateDirect(colorVertices.length * BYTES_PER_VERTEX)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        colorBuffer.put(colorVertices);
        colorBuffer.position(0);

        texBuffer = ByteBuffer.allocateDirect(texVertices.length * BYTES_PER_VERTEX)
                .order(ByteOrder.nativeOrder()).asFloatBuffer();
        texBuffer.put(texVertices);
        texBuffer.position(0);

        ebo = ByteBuffer.allocateDirect(indices.length * BYTES_PER_INDEX).order(ByteOrder.nativeOrder()).asShortBuffer();
        ebo.put(indices);
        ebo.position(0);

        texture1Id = TextureUtil.loadTexture(context, R.mipmap.container);
        texture2Id = TextureUtil.loadTexture(context, R.mipmap.awesomeface);

        texture1Uniform = GLES30.glGetUniformLocation(programId, "texture1");
        texture2Uniform = GLES30.glGetUniformLocation(programId, "texture2");

        GLES30.glUniform1i(texture1Uniform, 0);
        GLES30.glUniform1i(texture2Uniform, 1);

        modelMUniform = GLES30.glGetUniformLocation(programId, "modelMatrix");
        viewMUniform = GLES30.glGetUniformLocation(programId, "viewMatrix");
        projectionMUniform = GLES30.glGetUniformLocation(programId, "projectionMatrix");
        modelMatrixBuffer = ByteBuffer.allocateDirect(4 * 16).order(ByteOrder.nativeOrder()).asFloatBuffer();
        viewMatrixBuffer = ByteBuffer.allocateDirect(4 * 16).order(ByteOrder.nativeOrder()).asFloatBuffer();
        projectionMatrixBuffer = ByteBuffer.allocateDirect(4 * 16).order(ByteOrder.nativeOrder()).asFloatBuffer();


    }

    public void onSizeChanged(int width, int height) {
        Matrix.setIdentityM(modelMatrix, 0);
        Matrix.setIdentityM(viewMatrix, 0);
        Matrix.setIdentityM(projectionMatrix, 0);

        Matrix.rotateM(modelMatrix, 0, -55f, 1.0f, 0.0f, 0.0f);
        Matrix.translateM(viewMatrix, 0, 0f, 0f, -5.0f);
        Matrix.perspectiveM(projectionMatrix, 0, 45f, (float) width / (float) height, 0.1f, 100f);

        modelMatrixBuffer.position(0);
        modelMatrixBuffer.put(modelMatrix);
        modelMatrixBuffer.position(0);
        GLES30.glUniformMatrix4fv(modelMUniform, 1, false, modelMatrixBuffer);

        viewMatrixBuffer.position(0);
        viewMatrixBuffer.put(viewMatrix);
        viewMatrixBuffer.position(0);
        GLES30.glUniformMatrix4fv(viewMUniform, 1, false, viewMatrixBuffer);

        projectionMatrixBuffer.position(0);
        projectionMatrixBuffer.put(projectionMatrix);
        projectionMatrixBuffer.position(0);
        GLES30.glUniformMatrix4fv(projectionMUniform, 1, false, projectionMatrixBuffer);
    }

    public void draw() {
        GLES30.glUseProgram(programId);
        GLES30.glEnableVertexAttribArray(posAttrib);
        GLES30.glEnableVertexAttribArray(colorAttrib);
        GLES30.glEnableVertexAttribArray(texCoordAttrib);

        GLES30.glVertexAttribPointer(posAttrib, 3, GLES20.GL_FLOAT, false, 0, posBuffer);
        GLES30.glVertexAttribPointer(colorAttrib, 3, GLES20.GL_FLOAT, false, 0, colorBuffer);
        GLES30.glVertexAttribPointer(texCoordAttrib, 2, GLES20.GL_FLOAT, false, 0, texBuffer);

        GLES30.glActiveTexture(GLES20.GL_TEXTURE0);
        GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, texture1Id);

        GLES30.glActiveTexture(GLES20.GL_TEXTURE1);
        GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, texture2Id);

        Matrix.rotateM(modelMatrix, 0, -5f, 1.0f, 1.0f, 1.0f);
        modelMatrixBuffer.position(0);
        modelMatrixBuffer.put(modelMatrix);
        modelMatrixBuffer.position(0);
        GLES30.glUniformMatrix4fv(modelMUniform, 1, false, modelMatrixBuffer);


        GLES30.glDrawArrays(GLES30.GL_TRIANGLES, 0, 36);
//        GLES30.glDrawElements(GLES30.GL_TRIANGLES, indices.length, GLES30.GL_UNSIGNED_SHORT, ebo);
        GLES30.glDisableVertexAttribArray(posAttrib);
        GLES30.glDisableVertexAttribArray(colorAttrib);
        GLES30.glDisableVertexAttribArray(texCoordAttrib);

    }
}
