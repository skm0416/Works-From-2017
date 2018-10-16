package com.android.test;

import android.content.ContentValues;
import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;
import android.database.sqlite.SQLiteQueryBuilder;

import java.util.ArrayList;

public final class DatabaseHelper extends SQLiteOpenHelper {
    private Context context = this.getContext();
    private SQLiteDatabase sqlObj = this.getWritableDatabase();
    private static final String DBName = "MenuDB";
    private static final int DBversion = 2;
    private static final String TableName = "MenuTable";
    private static final String PrimaryKey = "RowId";
    private static final String FirstColumn = "TabName";
    private static final String SecondColumn = "MenuName";
    private static final String ThirdColumn = "Price";
    private static final String FourthColumn = "Image";

    public DatabaseHelper(Context context) {
        super(context, DBName, (SQLiteDatabase.CursorFactory)null, DBversion);
        this.context = context;
        SQLiteDatabase sqlObj= this.getWritableDatabase();
        this.sqlObj = sqlObj;
    }

    public final Context getContext() { return this.context; }

    public void onCreate(SQLiteDatabase DB) {
        String CREATE_TABLE_SQL = "CREATE TABLE IF NOT EXISTS " + TableName +
                " " + "(" + PrimaryKey + " INTEGER PRIMARY KEY," + FirstColumn + " TEXT," +
                SecondColumn + " TEXT," + ThirdColumn + " INTEGER," + FourthColumn + " BLOB);";
        DB.execSQL(CREATE_TABLE_SQL);
    }

    public void onUpgrade(SQLiteDatabase DB, int oldVersion, int newVersion) {
        DB.execSQL("Drop table IF EXISTS " + TableName);
        this.onCreate(DB);
    }

    public final String InsertMenu(ContentValues values) {
        String Msg = "error";
        long ID = sqlObj.insert(TableName, (String)null, values);
        if (ID > 0L) {
            Msg = "ok";
        }
        return Msg;
    }

    public final String RemoveMenu(int RowId) {
        String[] selectionArs = new String[]{String.valueOf(RowId)};
        int i = sqlObj.delete(TableName, "RowId=?", selectionArs);
        return i > 0 ? "ok" : "error";
    }

    public final int RemoveAll() {
        return sqlObj.delete(TableName, (String)null, (String[])null);
    }

    public final String UpdateMenu(ContentValues values, int RowId) {
        String[] selectionArgs = new String[]{String.valueOf(RowId)};
        int i = sqlObj.update(TableName, values, "RowId=?", selectionArgs);
        return i > 0 ? "ok" : "error";
    }

    public final int RemoveTab(String TabName) {
        String[] selectionArgs = new String[]{TabName};
        return sqlObj.delete(TableName, "TabName=?", selectionArgs);
    }

    public final ArrayList FetchTabName() {
        ArrayList arraylist = new ArrayList();
        SQLiteQueryBuilder sqb = new SQLiteQueryBuilder();
        sqb.setTables(TableName);
        sqb.setDistinct(true);
        String[] cols = new String[]{"TabName"};
        Cursor cur = sqb.query(this.sqlObj, cols, (String)null, (String[])null, (String)null, (String)null, "TabName");
        if (cur.moveToFirst()) {
            do {
                String TabName = cur.getString(cur.getColumnIndex("TabName"));
                arraylist.add(TabName);
            } while(cur.moveToNext());
        }

        return arraylist;
    }

    public final ArrayList FetchMenu(String TabName) {
        ArrayList arraylist = new ArrayList();
        SQLiteQueryBuilder sqb = new SQLiteQueryBuilder();
        sqb.setTables(TableName);
        String[] cols = new String[]{"RowId", "MenuName", "Price", "Image"};
        String[] SelArg = new String[]{TabName};
        Cursor cur = sqb.query(this.sqlObj, cols, "TabName like ?", SelArg, (String)null, (String)null, "TabName");
        if (cur.moveToFirst()) {
            do {
                int RowId = cur.getInt(cur.getColumnIndex("RowId"));
                String MenuName = cur.getString(cur.getColumnIndex("MenuName"));
                int Price = cur.getInt(cur.getColumnIndex("Price"));
                byte[] Image = cur.getBlob(cur.getColumnIndex("Image"));
                MenuData temp = new MenuData(TabName, MenuName, Price);
                if (Image != null) {
                    temp.setImage(Image);
                }

                temp.setRowId(RowId);
                arraylist.add(temp);
            } while(cur.moveToNext());
        }

        return arraylist;
    }

    public final String FindName(int rowid){
        String returnname = new String();
        SQLiteQueryBuilder sqb = new SQLiteQueryBuilder();
        sqb.setTables(TableName);
        String[] cols = new String[]{"RowId", "MenuName", "Price", "Image"};
        String[] SelArg = new String[]{Integer.toString(rowid)};
        Cursor cur = sqb.query(this.sqlObj, cols, "RowId like ?", SelArg, (String)null, (String)null, null);
        if (cur.moveToFirst()) {
            do {
                returnname = cur.getString(cur.getColumnIndex("MenuName"));
            } while(cur.moveToNext());
        }
        return returnname;
    }


}
