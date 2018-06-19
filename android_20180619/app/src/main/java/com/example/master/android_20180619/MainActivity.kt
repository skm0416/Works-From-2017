package com.example.master.android_20180619

import android.app.AlertDialog
import android.support.v7.app.AppCompatActivity
import android.os.Bundle
import android.widget.EditText
import android.widget.TextView

class MainActivity : AppCompatActivity() {

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

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
    }
}
