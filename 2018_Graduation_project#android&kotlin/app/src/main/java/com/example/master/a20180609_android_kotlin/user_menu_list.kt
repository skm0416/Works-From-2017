package com.example.master.a20180609_android_kotlin

import android.app.AlertDialog
import android.content.ContentValues
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.design.widget.TabLayout
import android.support.v4.view.ViewPager
import android.view.View
import android.content.Intent
import android.provider.MediaStore
import android.graphics.Bitmap
import android.app.Activity
import android.graphics.drawable.BitmapDrawable
import android.widget.*
import java.io.ByteArrayOutputStream


const val GET_FROM_GALLERY : Int = 1


class user_menu_list : AppCompatActivity() {
    private var mSectionsPagerAdapter: PageAdapter? = null
    private var mViewPager: ViewPager? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_user_menu_list)

        // Create the adapter that will return a fragment for each of the three
        // primary sections of the activity.
        mSectionsPagerAdapter = PageAdapter(supportFragmentManager, this)

        // Set up the ViewPager with the sections adapter.
        mViewPager = findViewById<ViewPager?>(R.id.user_menu_list_container)
        mViewPager!!.adapter = mSectionsPagerAdapter

        val tabLayout = findViewById<View>(R.id.user_menu_list_tabs) as TabLayout
        tabLayout.setupWithViewPager(mViewPager)
    }
}
