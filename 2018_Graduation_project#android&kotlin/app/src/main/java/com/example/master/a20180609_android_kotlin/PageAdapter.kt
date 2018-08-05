package com.example.master.a20180609_android_kotlin

import android.content.Context
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v4.app.FragmentStatePagerAdapter
import android.support.v4.view.PagerAdapter

class PageAdapter(fm: FragmentManager, private val context: Context) : FragmentStatePagerAdapter(fm) {

    val DB = DatabaseHelper(context)
    var tabNameArray = DB.FetchTabName()

    override fun getItemPosition(`object`: Any): Int {
        return PagerAdapter.POSITION_NONE
    }

    override fun getItem(TabId : Int): Fragment {
        return MenuListFragment.newInstance(context,tabNameArray.get(TabId))
    }

    override fun getCount(): Int {
        tabNameArray = DB.FetchTabName()
        return tabNameArray.size
    }

    override fun getPageTitle(position: Int): CharSequence? {
        return tabNameArray.get(position)
    }

}