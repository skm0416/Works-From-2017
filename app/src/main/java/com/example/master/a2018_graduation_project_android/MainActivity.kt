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
        val alert = AlertDialog.Builder(this)
        val shopName = findViewById<TextView>(R.id.shop_name)
        shopName.setOnClickListener{
            alert.show()
        }

        alert.setTitle("Input your name")
        alert.setMessage("Plz, input your name")

        val name = EditText(this)
        alert.setView(name)

        alert.setPositiveButton("ok") { dialog, whichButton -> shopName.text = name.text }
        alert.setNegativeButton("no") { dialog, whichButton -> }




    }
}
