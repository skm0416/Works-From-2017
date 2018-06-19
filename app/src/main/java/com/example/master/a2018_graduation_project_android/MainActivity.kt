package com.example.master.a2018_graduation_project_android

import android.app.AlertDialog
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.TextView
import android.content.DialogInterface



class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val shopName = findViewById<TextView>(R.id.shop_name)

        shopName.setOnClickListener{
            val alert = AlertDialog.Builder(this)
            alert.setTitle("set shop name")
            alert.setMessage("or cancel it")

            val name = EditText(this)
            name.setText(shopName.text)
            alert.setView(name)

            alert.setPositiveButton("save") { dialog, whichButton -> shopName.text = name.text.toString() }
            alert.setNegativeButton("cancel") { dialog, whichButton ->}
            alert.show()
        }
    }
}
