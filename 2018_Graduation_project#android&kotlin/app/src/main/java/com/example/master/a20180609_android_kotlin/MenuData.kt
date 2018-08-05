package com.example.master.a20180609_android_kotlin
import android.graphics.Bitmap

data class MenuData(var TabName:String, var MenuName: String, var Price: Int) {
    var RowId: Int ?= null
    var Image: ByteArray ?= null
}
