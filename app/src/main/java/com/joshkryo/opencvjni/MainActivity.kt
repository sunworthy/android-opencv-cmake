package com.joshkryo.opencvjni

import android.content.Context
import android.content.Intent
import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.activity_main.*

class MainActivity : AppCompatActivity() {
    var mContext: Context? = null
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        mContext = this
        bindView()
        bindListener()
        loadData()
    }

    private fun bindView() {
    }

    private fun bindListener() {
        btn_select_photo.setOnClickListener {

        }

        btn_func1.setOnClickListener {

        }
    }

    private fun loadData() {}
    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (resultCode == RESULT_OK) {

        }
    }
}