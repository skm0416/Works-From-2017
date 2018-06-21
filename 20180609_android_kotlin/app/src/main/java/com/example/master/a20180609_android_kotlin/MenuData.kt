package com.example.master.a20180609_android_kotlin
import android.media.Image

data class MenuData(var name: String, var price: Int) {
    var image: Image ?= null
    var comment: String ?= null
}

data class MenuList(var name: String){
    var list = mutableListOf<MenuData>()
    fun AddMenu(menu: MenuData){
        list.add(menu)
    }
    fun DelMenu(menu: MenuData){
        list.remove(menu)
    }
    fun Length() : Int{
        return list.size
    }
}