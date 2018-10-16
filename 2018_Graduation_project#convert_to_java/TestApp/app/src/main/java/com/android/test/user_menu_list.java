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
import android.util.Log;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.HorizontalScrollView;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import com.android.test.*;

import static com.android.test.user_menu_list.GET_FROM_GALLERY;

public final class user_menu_list extends Activity {
    public static final int GET_FROM_GALLERY = 1;
    private static final String TAG = "Dummy2";
    private ArrayList tabNameArray;
    private ArrayList fragArray;
    private ArrayList OrderNumber;
    private ArrayList<Integer> MenuOrder;
    private int curtab;
    private int tabsize;
    private int MenuIndex;


    public void setPage(final Context context){
        LinearLayout tabparent = (LinearLayout)findViewById(R.id.tab_parent2);
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
                    FragmentTransaction transaction = getFragmentManager().beginTransaction();
                    Fragment nowfrag = (Fragment)fragArray.get(curtab);
                    transaction.setTransition(FragmentTransaction.TRANSIT_NONE).hide(nowfrag);
                    curtab = now;
                    nowfrag = (Fragment)fragArray.get(curtab);
                    transaction.setTransition(FragmentTransaction.TRANSIT_NONE).show(nowfrag).commit();
                    setPage(context);
                }
            });


        }


    }

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_user_menu_list);
        setResult(RESULT_OK);

        Intent intent = getIntent();
        curtab = 0;
        MenuIndex = intent.getIntExtra("MenuIndex",0);
        tabNameArray = (ArrayList) intent.getSerializableExtra("tabNameArray");
        fragArray = new ArrayList();
        tabsize = tabNameArray.size();
        MenuOrder = new ArrayList<Integer>(Collections.nCopies(MenuIndex, 0));
        com.android.test.MenuOrder.getInstance().setMenuOrder(MenuOrder);
        ArrayList Tabmenu = (ArrayList) intent.getSerializableExtra("Tabmenu");

        for(int i=0; i<tabsize; i++){
            Fragment itemfragment = new User_MenuListFragment((String)tabNameArray.get(i),(ArrayList)Tabmenu.get(i));
            fragArray.add(itemfragment);
            FragmentTransaction transaction = getFragmentManager().beginTransaction();
            transaction.setTransition(FragmentTransaction.TRANSIT_NONE).add(R.id.user_menu_list_container, itemfragment).hide(itemfragment).commit();
        }

        FragmentTransaction transaction = getFragmentManager().beginTransaction();
        if(fragArray.size()>0){
            Fragment nowfrag = (Fragment)fragArray.get(curtab);
            transaction.setTransition(FragmentTransaction.TRANSIT_NONE).show(nowfrag).commit();
            setPage(this);

        }
        TextView order = (TextView)this.findViewById(R.id.calculate_order);
        order.setOnClickListener((View.OnClickListener)(new View.OnClickListener() {
            public final void onClick(View it) {
                MenuOrder = com.android.test.MenuOrder.getInstance().getMenuOrder();
                String msg = new String();
                for(int i=0; i<MenuOrder.size(); i++)
                    msg = msg + String.valueOf(MenuOrder.get(i)) + " ";
                Toast.makeText((Context)user_menu_list.this, (CharSequence)msg, Toast.LENGTH_SHORT).show();
            }
        }));
    }
}
