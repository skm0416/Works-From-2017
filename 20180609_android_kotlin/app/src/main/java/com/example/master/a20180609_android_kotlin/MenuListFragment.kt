package com.example.master.a20180609_android_kotlin

import android.annotation.SuppressLint
import android.content.Context
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast

@SuppressLint("ValidFragment")
class MenuListFragment(passedContext: Context,TabName: String) : Fragment(){

    val passThroughContext : Context = passedContext
    val passName = TabName


    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val rootView = inflater!!.inflate(R.layout.menu_fragment, container, false)
        val recyclerView = rootView.findViewById(R.id.MenuRecyclerView) as RecyclerView

        val DB = DatabaseHelper(passThroughContext)

        val MenuList = DB.FetchMenu(passName)

        if(MenuList.size>0) {

            val MenuAdapter = MenuAdapter(MenuList)
            recyclerView.adapter = MenuAdapter

        }else{
            Toast.makeText(passThroughContext,"저장된 메뉴가 없습니다",Toast.LENGTH_LONG).show()
        }

        recyclerView.adapter = MenuAdapter(MenuList)
        recyclerView.layoutManager = LinearLayoutManager(passThroughContext)
        return rootView
    }
    companion object {
        fun newInstance(context: Context, TabName : String): MenuListFragment {
            return MenuListFragment(context,TabName)
        }
    }

}