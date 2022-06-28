package com.sl.java.opengl;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.opengl.GLES20;
import android.opengl.GLES30;
import android.opengl.GLSurfaceView;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.util.Log;
import android.view.View;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import com.sl.java.opengl.rendering.RectRenderer;
import com.sl.java.opengl.rendering.TexRectRenderer;
import com.sl.java.opengl.rendering.TriangleRenderer;
import com.sl.java.opengl.rendering.cnative.NativeRender;

import java.io.IOException;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class MainActivity extends AppCompatActivity implements GLSurfaceView.Renderer {

    private final static String TAG = MainActivity.class.getSimpleName();
    private GLSurfaceView surfaceView;
    private TriangleRenderer triangleRenderer;
    private RectRenderer rectRenderer;
    private TexRectRenderer texRectRenderer;
    private NativeRender nativeRender;
    private final Handler handler = new Handler(Looper.getMainLooper()) {
        @Override
        public void handleMessage(@NonNull Message msg) {
//            surfaceView.requestRender();
//            handler.sendEmptyMessageDelayed(0, 1000L);
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        initView();
    }

    @Override
    protected void onResume() {
        super.onResume();
        surfaceView.onResume();
    }

    @Override
    protected void onPause() {
        super.onPause();
        surfaceView.onPause();
    }

    private void initView() {
        surfaceView = findViewById(R.id.surfaceView);
        // Set up renderer.
        surfaceView.setPreserveEGLContextOnPause(true);
        surfaceView.setEGLContextClientVersion(3);
        surfaceView.setEGLConfigChooser(8, 8, 8, 8, 16, 0); // Alpha used for plane blending.
        surfaceView.setRenderer(this);
        surfaceView.setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);
        surfaceView.setWillNotDraw(false);

//        triangleRenderer = new TriangleRenderer();
//        rectRenderer = new RectRenderer();
//        texRectRenderer = new TexRectRenderer();

        handler.sendEmptyMessage(0);

        findViewById(R.id.front).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                nativeRender.moveCamera(TexRectRenderer.Direction.FRONT.ordinal());
                surfaceView.requestRender();
            }
        });

        findViewById(R.id.back).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                nativeRender.moveCamera(TexRectRenderer.Direction.BACK.ordinal());
                surfaceView.requestRender();
            }
        });

        findViewById(R.id.left).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                nativeRender.moveCamera(TexRectRenderer.Direction.LEFT.ordinal());
                surfaceView.requestRender();
            }
        });

        findViewById(R.id.right).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                nativeRender.moveCamera(TexRectRenderer.Direction.RIGHT.ordinal());
                surfaceView.requestRender();
            }
        });
    }

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config) {
        Log.d(TAG, "onSurfaceCreated...");
//        GLES30.glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        GLES30.glEnable(GLES30.GL_DEPTH_TEST);
        try {
//            triangleRenderer.createOnGlThread(this);
//            rectRenderer.createOnGlThread(this);
//            texRectRenderer.createOnGlThread(this);
            nativeRender = new NativeRender();
            nativeRender.onSurfaceCreated();

            BitmapFactory.Options options = new BitmapFactory.Options();
            options.inScaled = false;

            Bitmap bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.container, options);
            nativeRender.setBitmap(bitmap);
            bitmap = BitmapFactory.decodeResource(getResources(), R.mipmap.awesomeface, options);
            nativeRender.setBitmap(bitmap);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height) {
        Log.d(TAG, "onSurfaceChanged-->width=" + width + " height=" + height);
//        texRectRenderer.onSizeChanged(width, height);
//        GLES30.glViewport(0, 0, width, height);
        nativeRender.onSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(GL10 gl) {
        Log.d(TAG, "onDrawFrame");
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT | GLES20.GL_DEPTH_BUFFER_BIT);
//        rectRenderer.draw();
////        triangleRenderer.draw();
//        texRectRenderer.draw();
        nativeRender.onDrawFrame();
    }
}