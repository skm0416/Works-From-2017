package com.example.master.a20180609_android_kotlin

import android.support.v7.widget.RecyclerView
import android.view.View
import android.widget.ImageView
import android.widget.TextView

class MenuHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
    private val MenuImage: ImageView = itemView.findViewById(R.id.MenuImageView)
    private val MenuName: TextView = itemView.findViewById(R.id.MenuName)
    private val MenuPrice: TextView = itemView.findViewById(R.id.MenuPrice)

    fun updateMenu(Menu : MenuData) {
        MenuImage.setImageDrawable(Menu.image)
        MenuName.text = Menu.MenuName
        MenuPrice.text = Menu.Price.toString()
    }
}