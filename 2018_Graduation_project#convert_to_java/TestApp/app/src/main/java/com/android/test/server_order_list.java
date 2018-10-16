package com.android.test;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Fragment;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.preference.PreferenceManager;
import android.service.samd.SAMDManager;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.widget.Adapter;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;

public final class server_order_list extends Activity {
    //SAMDManager S;
    private static final String TAG = "TestApp";
    private ArrayList<OrderData> OrderList = new ArrayList<OrderData>();
    private ListView listView;
    private OrderAdapter adapter;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_server_order_list);
        com.android.test.OrderList.getInstance().setOrderList(OrderList);
        //S = new SAMDManager(getApplicationContext());

        SharedPreferences pref = getSharedPreferences("pref", MODE_PRIVATE);
        final SharedPreferences.Editor editor = pref.edit();

        listView = (ListView)findViewById(R.id.server_order_list_container);
        adapter = new OrderAdapter(OrderList);
        listView.setAdapter(adapter);

        final TextView shopID = (TextView)this.findViewById(R.id.shop_name);
        shopID.setText(pref.getString("shopID", "이름 없음"));
        shopID.setOnClickListener((View.OnClickListener)(new View.OnClickListener() {
            public final void onClick(View it) {
                AlertDialog.Builder alert = new AlertDialog.Builder((Context)server_order_list.this);
                alert.setTitle((CharSequence)"ID를 정할 수 있습니다");
                alert.setMessage((CharSequence)"입력한 뒤 저장을 눌러주세요");
                final EditText name = new EditText((Context)server_order_list.this);
                name.setText(shopID.getText());
                alert.setView((View)name);
                alert.setPositiveButton((CharSequence)"저장", (android.content.DialogInterface.OnClickListener)(new android.content.DialogInterface.OnClickListener() {
                    public final void onClick(DialogInterface dialog, int whichButton) {
                        shopID.setText((CharSequence)name.getText().toString());
                        editor.putString("shopID",name.getText().toString());
                        editor.commit();
                    }
                }));
                alert.setNegativeButton((CharSequence)"취소", (android.content.DialogInterface.OnClickListener)null);
                alert.show();
            }
        }));
        TextView shopSetting = (TextView)this.findViewById(R.id.shop_setting);
        shopSetting.setOnClickListener((View.OnClickListener)(new View.OnClickListener() {
            public final void onClick(View it) {
                Intent secondIntent = new Intent((Context)server_order_list.this, server_menu_list.class);
                server_order_list.this.startActivity(secondIntent);
            }
        }));
        TextView userMenu = (TextView)this.findViewById(R.id.user_menu);
        userMenu.setOnClickListener((View.OnClickListener)(new View.OnClickListener() {
            public final void onClick(View it) {
                Context context = (Context)server_order_list.this;
                DatabaseHelper DB = new DatabaseHelper(context);
                ArrayList tabNameArray = DB.FetchTabName();
                int tabsize = tabNameArray.size();
                ArrayList Tabmenu = new ArrayList<>();
                int MenuIndex = 0;
                for(int i=0; i<tabsize; i++){
                    ArrayList MenuList = DB.FetchMenu((String)tabNameArray.get(i));
                    for(int j=0; j<MenuList.size(); j++){
                        int temp = ((MenuData)MenuList.get(j)).getRowId();
                        if(MenuIndex < temp)
                            MenuIndex = temp;
                    }
                    Tabmenu.add(MenuList);
                }
                MenuIndex = MenuIndex+1;



                Intent userIntent = new Intent((Context)server_order_list.this, user_menu_list.class);
                userIntent.putExtra("tabNameArray",tabNameArray);
                userIntent.putExtra("Tabmenu",Tabmenu);
                userIntent.putExtra("MenuIndex",MenuIndex);
                server_order_list.this.startActivityForResult(userIntent,0);
                //S.launchActivity("user_menu_list");



            }
        }));
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        if(resultCode == RESULT_OK) {
            ArrayList<Integer> MenuOrder = com.android.test.MenuOrder.getInstance().getMenuOrder();
            ArrayList<String> NameList = new ArrayList<String>();
            ArrayList<Integer> AmountList = new ArrayList<Integer>();
            int price = MenuOrder.get(0);

            long now = System.currentTimeMillis();
            Date date = new Date(now);
            SimpleDateFormat sdf = new SimpleDateFormat("h:mm a");
            String time = sdf.format(date);

            DatabaseHelper DB = new DatabaseHelper((Context)server_order_list.this);

            for(int i=1; i<MenuOrder.size(); i++){
                int amount = MenuOrder.get(i);
                if(amount > 0){
                    AmountList.add(amount);
                    String name = DB.FindName(i);
                    NameList.add(name);
                }
            }
            if(AmountList.size()>0){
                OrderList = com.android.test.OrderList.getInstance().getOrderList();
                OrderList.add(new OrderData(NameList,AmountList,price,time));
                adapter.notifyDataSetChanged();
            }


            String msg = new String();
            for(int i=0; i<MenuOrder.size(); i++)
                msg = msg + String.valueOf(MenuOrder.get(i)) + " ";
            Toast.makeText((Context)server_order_list.this, (CharSequence)msg, Toast.LENGTH_SHORT).show();
        }
    }
}
