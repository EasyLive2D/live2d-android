package com.arkueid.live2d

import android.annotation.SuppressLint
import android.opengl.GLSurfaceView
import android.os.Bundle
import android.util.Log
import android.view.MotionEvent
import androidx.appcompat.app.AppCompatActivity
import com.arkueid.live2d.Live2D_v3.LAppModel
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10


class MainActivity : AppCompatActivity() {

    private lateinit var glSurfaceView: GLSurfaceView
    private lateinit var renderer: MyRenderer

    @SuppressLint("ClickableViewAccessibility")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        glSurfaceView = GLSurfaceView(this)
        glSurfaceView.setEGLContextClientVersion(2)
        renderer = MyRenderer()
        glSurfaceView.setRenderer(renderer)
        glSurfaceView.renderMode = GLSurfaceView.RENDERMODE_CONTINUOUSLY
        setContentView(glSurfaceView)
    }

    override fun onTouchEvent(event: MotionEvent?): Boolean {
        event?.run {
            when (action) {
                MotionEvent.ACTION_MOVE -> {
                    glSurfaceView.queueEvent {
                        renderer.model.drag(x, y)
                    }
                }

                MotionEvent.ACTION_UP -> {
                    glSurfaceView.queueEvent {
                        renderer.model.touch(x, y) { group, no ->
                            Log.d(TAG, "started motion(${group}_$no)")
                        }
                    }
                }
            }
        }
        return super.onTouchEvent(event)
    }

    override fun onStart() {
        super.onStart()
        Live2D_v3.init(applicationContext)
    }

    override fun onResume() {
        super.onResume()
        glSurfaceView.onResume()
    }

    override fun onPause() {
        super.onPause()
        glSurfaceView.onPause()
    }

    override fun onStop() {
        super.onStop()
        // LAppModel 的内存会在虚拟机 gc 时释放，
        // 但 gc 时间不确定，如果在 Live2D_v3.dispose 后释放，
        // 会导致崩溃
        renderer.model.release()
        Live2D_v3.dispose()
    }
}

class MyRenderer : GLSurfaceView.Renderer {
    lateinit var model: LAppModel

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        model = LAppModel().apply {
            loadModelJson("assets://mianfeimox/llny.model3.json")
        }
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        model.resize(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        Live2D_v3.clearBuffer(0f, 1f, 0f, 0f)
        model.update()
        // 去水印
        model.setParameterValue("Param14", 1f)
        model.draw()
    }

}

private const val TAG = "MainActivity"


