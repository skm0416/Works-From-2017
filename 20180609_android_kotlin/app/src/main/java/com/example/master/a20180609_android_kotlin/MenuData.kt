package com.example.master.a20180609_android_kotlin
import android.graphics.drawable.Drawable

data class MenuData(var TabName:String, var MenuName: String, var Price: Int) {
    var RowId: Int ?= null
    var TabId: Int ?= null
    var image: Drawable ?= null
    var comment: String ?= null
}
