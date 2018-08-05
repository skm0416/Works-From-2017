package com.example.master.a20180609_android_kotlin

import android.graphics.BitmapFactory
import android.support.v7.widget.RecyclerView
import android.view.View
import android.widget.ImageView
import android.widget.TextView

class MenuHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
    private val MenuImage: ImageView = itemView.findViewById(R.id.MenuImageView)
    private val MenuName: TextView = itemView.findViewById(R.id.MenuName)
    private val MenuPrice: TextView = itemView.findViewById(R.id.MenuPrice)
    private val MenuNumber: TextView = itemView.findViewById(R.id.MenuNumber)

    fun updateMenu(Menu : MenuData) {
        if(Menu.Image != null){
            var image = BitmapFactory.decodeByteArray(Menu.Image,0,Menu.Image!!.size)
            MenuImage.setImageBitmap(image)
        }
        MenuNumber.text =  Menu.RowId.toString()
        MenuName.text = Menu.MenuName
        MenuPrice.text = Menu.Price.toString() + " 원"
    }
}