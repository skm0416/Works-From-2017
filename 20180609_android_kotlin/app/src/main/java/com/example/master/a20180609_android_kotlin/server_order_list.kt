package com.example.master.a20180609_android_kotlin

import android.app.AlertDialog
import android.content.Intent
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.TextView

class server_order_list : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_server_order_list)

        val shopID = findViewById<TextView>(R.id.shop_name)

        shopID.setOnClickListener{
            val alert = AlertDialog.Builder(this)
            alert.setTitle("ID를 정할 수 있습니다")
            alert.setMessage("입력한 뒤 저장을 눌러주세요")

            val name = EditText(this)
            name.setText(shopID.text)
            alert.setView(name)

            alert.setPositiveButton("저장") { dialog, whichButton -> shopID.text = name.text.toString() }
            alert.setNegativeButton("취소") { dialog, whichButton ->}
            alert.show()
        }

        val shopSetting = findViewById<TextView>(R.id.shop_setting)
        shopSetting.setOnClickListener{
            val secondIntent = Intent(this, server_menu_list::class.java)
            startActivity(secondIntent)
        }

        val userMenu = findViewById<TextView>(R.id.user_menu)
        userMenu.setOnClickListener {
            val userIntent = Intent(this,user_menu_list::class.java)
            startActivity(userIntent)
        }


    }
}
