package com.example.master.a20180609_android_kotlin

import android.app.AlertDialog
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast

class server_edit : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_server_edit)

        val insertMenu = findViewById<TextView>(R.id.insert_menu)

        val MenuList = MenuList("temp")
        val list = MenuList.list

        insertMenu.setOnClickListener{
            Toast.makeText(this,"현재 길이 :"+MenuList.Length(),Toast.LENGTH_LONG).show()
            val alert = AlertDialog.Builder(this)
            alert.setTitle("추가할 메뉴의 정보를 입력해주세요")
            alert.setMessage("입력한 뒤 추가를 눌러주세요")

            val dialogView = layoutInflater.inflate(R.layout.dialog_insert_menu, null)
            val name = dialogView.findViewById<EditText>(R.id.input_menu_name)
            val price = dialogView.findViewById<EditText>(R.id.input_menu_price)
            alert.setView(dialogView)

            alert.setPositiveButton("추가") { dialog, whichButton ->
                val MenuData = MenuData(name.text.toString(),price.text.toString().toInt())
                MenuList.AddMenu(MenuData)
                Toast.makeText(this,"현재 길이 :"+MenuList.Length(),Toast.LENGTH_LONG).show()
            }
            alert.setNegativeButton("취소") { dialog, whichButton ->}
            alert.show()
        }
    }
}
