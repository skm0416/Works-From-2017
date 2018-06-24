package com.example.master.a20180609_android_kotlin

import android.content.ContentValues
import android.content.Context
import android.database.sqlite.SQLiteDatabase
import android.database.sqlite.SQLiteOpenHelper
import android.database.sqlite.SQLiteQueryBuilder

class DatabaseHelper (context: Context) : SQLiteOpenHelper(context, DBName, null, DBversion) {

    companion object {
        val DBName = "MenuDB"
        val DBversion = 1

        val TableName = "MenuTable"
        val PrimaryKey = "RowId"

        val FirstColumn = "TabName"
        val SecondColumn = "MenuName"
        val ThirdColumn = "Price"
    }

    var context: Context = context
    var sqlObj: SQLiteDatabase = this.writableDatabase

    override fun onCreate(DB: SQLiteDatabase?) {
        var CREATE_TABLE_SQL : String = "CREATE TABLE IF NOT EXISTS " + TableName + " " +
                "(" + PrimaryKey + " INTEGER PRIMARY KEY," + FirstColumn + " TEXT," + SecondColumn + " TEXT," + ThirdColumn + " INTEGER);"
        DB!!.execSQL(CREATE_TABLE_SQL)
    }

    override fun onUpgrade(DB: SQLiteDatabase?, oldVersion : Int, newVersion: Int) {
        DB!!.execSQL("Drop table IF EXISTS "+ TableName)
        onCreate(DB)
    }

    fun InsertMenu(values: ContentValues): String{
        var Msg: String = "error"
        val ID = sqlObj!!.insert(TableName,null,values)

        if(ID > 0)
            Msg = "ok"
        return Msg
    }

    fun RemoveMenu(RowId : Int): String {

        var selectionArs = arrayOf(RowId.toString())

        val i = sqlObj!!.delete(TableName, "RowId=?", selectionArs)
        if (i > 0) {
            return "ok";
        } else {
            return "error";
        }
    }

    fun RemoveAll() : Int {
        return sqlObj!!.delete(TableName,null,null)
    }

    fun UpdateMenu(values: ContentValues, RowId: Int): String {

        var selectionArs = arrayOf(RowId.toString())

        val i = sqlObj!!.update(TableName, values, "RowId=?", selectionArs)
        if (i > 0) {
            return "ok";
        } else {
            return "error";
        }
    }

    fun FetchMenu(): ArrayList<MenuData> {

        var arraylist = ArrayList<MenuData>()

        val sqb = SQLiteQueryBuilder()
        sqb.tables = TableName
        val cols = arrayOf("RowId", "TabName", "MenuName", "Price")

        val cur = sqb.query(sqlObj, cols, null, null, null, null, "TabName")

        if (cur.moveToFirst()) {
            do {
                val RowId = cur.getInt(cur.getColumnIndex("RowId"))
                val TabName = cur.getString(cur.getColumnIndex("TabName"))
                val MenuName = cur.getString(cur.getColumnIndex("MenuName"))
                val Price = cur.getInt(cur.getColumnIndex("Price"))

                val temp:MenuData = MenuData(TabName,MenuName,Price)
                temp.RowId = RowId
                arraylist.add(temp)

            } while (cur.moveToNext())
        }
        return arraylist
    }


}