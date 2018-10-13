package com.android.test;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.HorizontalScrollView;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.OutputStream;
import java.util.ArrayList;

import static com.android.test.user_menu_list.GET_FROM_GALLERY;

public final class user_menu_list extends Activity {
    public static final int GET_FROM_GALLERY = 1;
    private DatabaseHelper DB;
    private ArrayList tabNameArray;
    private String curtitle;
    private int curtab;
    private int tabsize;

    public void setPage(final Context context){
        this.DB = new DatabaseHelper(context);
        this.tabNameArray = this.DB.FetchTabName();
        this.tabsize = tabNameArray.size();
        if(tabsize == 0) {
            curtitle = "";
        }
        else {
            curtitle = (String) tabNameArray.get(curtab);
        }
        LinearLayout tabparent = (LinearLayout)findViewById(R.id.tab_parent);
        tabparent.removeAllViewsInLayout();
        for (int i = 0; i < tabNameArray.size(); i++) {
            TextView tv = new TextView(getApplicationContext());
            tv.setText((String)tabNameArray.get(i));
            tv.setTextColor(getResources().getColor(R.color.black));
            tv.setTextSize(TypedValue.COMPLEX_UNIT_SP,20);
            tv.setGravity(Gravity.CENTER);

            if(curtab == i)
                tv.setBackgroundColor(getResources().getColor(R.color.blue));
            else
                tv.setBackgroundColor(getResources().getColor(R.color.white));
            tv.setTextAlignment(View.TEXT_ALIGNMENT_CENTER);

            LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
                    LinearLayout.LayoutParams.WRAP_CONTENT,
                    LinearLayout.LayoutParams.MATCH_PARENT
            );
            params.setMargins(10, 0, 10, 0);
            tv.setLayoutParams(params);
            tabparent.addView(tv);
            final int now = i;
            tv.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    curtab = now;
                    setPage(context);
                }
            });


        }

        Fragment itemfragment = new MenuListFragment(curtitle);
        FragmentTransaction transaction = getFragmentManager().beginTransaction();
        transaction.setTransition(FragmentTransaction.TRANSIT_FRAGMENT_OPEN).replace(R.id.server_menu_list_container, itemfragment).commitAllowingStateLoss();
    }

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_user_menu_list);

        Context context = this;
        curtab = 0;
        setPage(this);
    }
}
