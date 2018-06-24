package com.example.master.a20180609_android_kotlin

import android.app.AlertDialog
import android.content.ContentValues
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.support.design.widget.TabLayout
import android.support.v4.view.ViewPager
import android.view.View
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast

class server_menu_list : AppCompatActivity() {
    private var mSectionsPagerAdapter: PageAdapter? = null
    private var mViewPager: ViewPager? = null

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
            //Toast.makeText(this,"현재 길이 :"+MenuList.Length(),Toast.LENGTH_LONG).show()
            val alert = AlertDialog.Builder(this)
            alert.setTitle("추가할 메뉴의 정보를 입력해주세요")
            alert.setMessage("입력한 뒤 추가를 눌러주세요")
            val dialogView = layoutInflater.inflate(R.layout.dialog_insert_menu, null)
            val menu_name = dialogView.findViewById<EditText>(R.id.input_menu_name)
            val price = dialogView.findViewById<EditText>(R.id.input_menu_price)
            alert.setView(dialogView)

            alert.setPositiveButton("추가") { dialog, whichButton ->
                val DB = DatabaseHelper(this)
                var values = ContentValues()
                values.put("TabName", "기본탭")
                values.put("MenuName", menu_name.text.toString())
                values.put("Price", price.text.toString().toInt())
                var response = DB.InsertMenu(values);
                if(response=="ok") {

                    Toast.makeText(this, "메뉴추가 성공",
                            Toast.LENGTH_SHORT).show()

                    /*var intent = Intent(this, server_menu_list::class.java)
                    startActivity(intent)
                    finish()*/

                }else{
                    Toast.makeText(this, "메뉴추가 실패",
                            Toast.LENGTH_SHORT).show()
                }
            }
            alert.setNegativeButton("취소") { dialog, whichButton ->}
            alert.show()
        }
    }
}
