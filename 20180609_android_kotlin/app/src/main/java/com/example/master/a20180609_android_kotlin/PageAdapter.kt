package com.example.master.a20180609_android_kotlin

import android.content.Context
import android.support.v4.app.Fragment
import android.support.v4.app.FragmentManager
import android.support.v4.app.FragmentPagerAdapter

class PageAdapter(fm: FragmentManager, private val context: Context) : FragmentPagerAdapter(fm) {

    override fun getItem(TabId : Int): Fragment {
        return MenuListFragment.newInstance(context)
    }

    override fun getCount(): Int {
        // Show 5 total pages.
        return 5
    }

    override fun getPageTitle(position: Int): CharSequence? {
        // return null to show no title.
        return null

    }

}