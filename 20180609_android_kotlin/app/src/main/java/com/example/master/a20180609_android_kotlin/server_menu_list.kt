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
import android.content.Context
import android.graphics.BitmapFactory
import android.graphics.drawable.BitmapDrawable
import android.widget.*
import java.io.ByteArrayOutputStream
import java.io.FileNotFoundException
import java.io.IOException


val GET_FROM_GALLERY : Int = 1


class server_menu_list : AppCompatActivity() {
    private var mSectionsPagerAdapter: PageAdapter? = null
    private var mViewPager: ViewPager? = null
    private var ImageTarget: ImageButton? = null

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_server_menu_list)

        // Create the adapter that will return a fragment for each of the three
        // primary sections of the activity.
        mSectionsPagerAdapter = PageAdapter(supportFragmentManager, this)

        // Set up the ViewPager with the sections adapter.
        mViewPager = findViewById<ViewPager?>(R.id.server_menu_list_container)
        mViewPager!!.adapter = mSectionsPagerAdapter

        val tabLayout = findViewById<View>(R.id.server_menu_list_tabs) as TabLayout
        tabLayout.setupWithViewPager(mViewPager)







        val insertMenu = findViewById<TextView>(R.id.insert_menu)

        insertMenu.setOnClickListener{
            val alert = AlertDialog.Builder(this)
            alert.setTitle("메뉴 추가")
            alert.setMessage("추가할 메뉴의 정보를 입력해주세요")
            val dialogView = layoutInflater.inflate(R.layout.dialog_insert_menu, null)
            val menu_name = dialogView.findViewById<EditText>(R.id.input_menu_name)
            val price = dialogView.findViewById<EditText>(R.id.input_menu_price)
            val tab_name = dialogView.findViewById<EditText>(R.id.input_tab_name)
            val image = dialogView.findViewById<ImageButton>(R.id.input_image)
            image.setOnClickListener {
                startActivityForResult(Intent(Intent.ACTION_PICK, android.provider.MediaStore.Images.Media.INTERNAL_CONTENT_URI),GET_FROM_GALLERY)
            }
            ImageTarget = image

            if(tabLayout.tabCount>0)
                tab_name.setText(mSectionsPagerAdapter!!.getPageTitle(tabLayout.selectedTabPosition))
            alert.setView(dialogView)

            alert.setPositiveButton("추가") { dialog, whichButton ->
                val DB = DatabaseHelper(this)
                var values = ContentValues()

                val drawable = image.drawable as BitmapDrawable?
                if(drawable != null){
                    val bitmap = drawable.bitmap
                    val stream = ByteArrayOutputStream()
                    bitmap.compress(Bitmap.CompressFormat.PNG, 100, stream)
                    val image = stream.toByteArray()
                    values.put("Image",image)
                }

                values.put("TabName", tab_name.text.toString())
                values.put("MenuName", menu_name.text.toString())
                if(price.text.toString().isNotEmpty())
                    values.put("Price", price.text.toString().toInt())
                var response = DB.InsertMenu(values)
                if(response=="ok") {

                    Toast.makeText(this, "메뉴추가 성공", Toast.LENGTH_SHORT).show()
                    mSectionsPagerAdapter!!.notifyDataSetChanged()
                }else{
                    Toast.makeText(this, "메뉴추가 실패",
                            Toast.LENGTH_SHORT).show()
                }
            }
            alert.setNegativeButton("취소") { dialog, whichButton ->
            }
            alert.show()
        }



        val removeMenu = findViewById<TextView>(R.id.remove_menu)

        removeMenu.setOnClickListener{
            val DB = DatabaseHelper(this)
            var response = DB.RemoveAll()
            mSectionsPagerAdapter!!.notifyDataSetChanged()
            Toast.makeText(this, response.toString() + "개의 메뉴를 삭제했습니다", Toast.LENGTH_SHORT).show()
        }
    }

    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        //Detects request codes
        if (requestCode == GET_FROM_GALLERY && resultCode == Activity.RESULT_OK) {
            val selectedImage = data!!.data
            val bitmap = MediaStore.Images.Media.getBitmap(this.contentResolver, selectedImage)
            ImageTarget!!.setImageBitmap(bitmap)
        }
    }


}
