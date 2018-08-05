package com.example.master.a20180609_android_kotlin

import android.content.Context
import android.support.constraint.ConstraintLayout
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.ViewGroup
import android.widget.TextView

class MenuAdapter(private val MenuList: ArrayList<MenuData>) : RecyclerView.Adapter<MenuHolder>() {

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MenuHolder {
        val menuItem = LayoutInflater.from(parent.context).inflate(R.layout.menu_item, parent, false) as ConstraintLayout
        return MenuHolder(menuItem)
    }

    override fun onBindViewHolder(holder: MenuHolder, position: Int) {
        holder.updateMenu(MenuList[position])
    }

    override fun getItemCount(): Int {
        return MenuList.toArray().count();
    }

}