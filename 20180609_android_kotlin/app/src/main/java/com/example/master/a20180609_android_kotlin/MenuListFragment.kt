package com.example.master.a20180609_android_kotlin

import android.annotation.SuppressLint
import android.content.Context
import android.os.Bundle
import android.support.v4.app.Fragment
import android.support.v7.widget.LinearLayoutManager
import android.support.v7.widget.RecyclerView
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.app.Activity
import android.app.AlertDialog
import android.content.ContentValues
import android.content.Intent
import android.graphics.Bitmap
import android.graphics.drawable.BitmapDrawable
import android.provider.MediaStore
import android.support.design.widget.TabLayout
import android.support.v4.view.ViewPager
import android.widget.*
import java.io.ByteArrayOutputStream


@SuppressLint("ValidFragment")
class MenuListFragment(passedContext: Context,TabName: String) : Fragment(){

    val passThroughContext : Context = passedContext
    val passName = TabName
    private var ImageTarget: ImageButton? = null

    override fun onCreateView(inflater: LayoutInflater, container: ViewGroup?, savedInstanceState: Bundle?): View? {
        val rootView = inflater!!.inflate(R.layout.menu_fragment, container, false)
        val recyclerView = rootView.findViewById(R.id.MenuRecyclerView) as RecyclerView

        val DB = DatabaseHelper(passThroughContext)

        val MenuList = DB.FetchMenu(passName)

        recyclerView.adapter = MenuAdapter(MenuList)
        recyclerView.layoutManager = LinearLayoutManager(passThroughContext)
        recyclerView.addOnItemClickListener(object : OnItemClickListener {
            override fun onItemClicked(position: Int, view: View) {
                val tabLayout = (passThroughContext as Activity).findViewById<View>(R.id.server_menu_list_tabs) as TabLayout
                val adapter = (passThroughContext as Activity).findViewById<ViewPager>(R.id.server_menu_list_container).adapter
                val rowid = view.findViewById<TextView>(R.id.MenuNumber).text.toString().toInt()
                val alert = AlertDialog.Builder(passThroughContext)
                alert.setTitle("메뉴 수정")
                alert.setMessage("수정할 메뉴의 정보를 입력해주세요")
                val dialogView = layoutInflater.inflate(R.layout.dialog_insert_menu, null)
                val menu_name = dialogView.findViewById<EditText>(R.id.input_menu_name)
                val price = dialogView.findViewById<EditText>(R.id.input_menu_price)
                val tab_name = dialogView.findViewById<EditText>(R.id.input_tab_name)
                val image = dialogView.findViewById<ImageButton>(R.id.input_image)
                image.setOnClickListener {
                    startActivityForResult(Intent(Intent.ACTION_PICK, MediaStore.Images.Media.INTERNAL_CONTENT_URI),GET_FROM_GALLERY)
                }
                ImageTarget = image

                tab_name.setText(adapter!!.getPageTitle(tabLayout.selectedTabPosition))
                price.setText(view.findViewById<TextView>(R.id.MenuPrice).text.toString())
                menu_name.setText(view.findViewById<TextView>(R.id.MenuName).text.toString())
                val drawable = view.findViewById<ImageView>(R.id.MenuImageView).drawable
                if(drawable != null)
                    image.setImageBitmap((drawable as BitmapDrawable).bitmap)

                alert.setView(dialogView)

                alert.setPositiveButton("수정") { dialog, whichButton ->
                    val DB = DatabaseHelper(passThroughContext)
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
                    var response = DB.UpdateMenu(values,rowid)
                    if(response=="ok") {
                        Toast.makeText(passThroughContext, "메뉴수정 성공", Toast.LENGTH_SHORT).show()
                        adapter!!.notifyDataSetChanged()
                    }else{
                        Toast.makeText(passThroughContext, "메뉴수정 실패",
                                Toast.LENGTH_SHORT).show()
                    }
                }
                alert.setNeutralButton("삭제"){ dialog, whichButton ->
                    val DB = DatabaseHelper(recyclerView.context)
                    var response = DB.RemoveMenu(rowid)
                    if(response=="ok") {
                        Toast.makeText(passThroughContext, "메뉴삭제 성공", Toast.LENGTH_SHORT).show()
                        adapter!!.notifyDataSetChanged()
                    }else{
                        Toast.makeText(passThroughContext, "메뉴삭제 실패",
                                Toast.LENGTH_SHORT).show()
                    }
                }
                alert.setNegativeButton("취소") { dialog, whichButton ->
                }
                alert.show()


            }
        })
        return rootView
    }
    companion object {
        fun newInstance(context: Context, TabName : String): MenuListFragment {
            return MenuListFragment(context,TabName)
        }
    }
    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        //Detects request codes
        if (requestCode == GET_FROM_GALLERY && resultCode == Activity.RESULT_OK) {
            val selectedImage = data!!.data
            val bitmap = MediaStore.Images.Media.getBitmap(passThroughContext.contentResolver, selectedImage)
            ImageTarget!!.setImageBitmap(bitmap.rotate(90))
        }
    }
}