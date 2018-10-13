package com.android.test;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.service.samd.SAMDManager;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

import java.util.HashMap;

public final class server_order_list extends Activity {
    //SAMDManager S;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_server_order_list);
        //S = new SAMDManager(getApplicationContext());

        SharedPreferences pref = getSharedPreferences("pref", MODE_PRIVATE);
        final SharedPreferences.Editor editor = pref.edit();

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
                Intent userIntent = new Intent((Context)server_order_list.this, user_menu_list.class);
                server_order_list.this.startActivity(userIntent);
                //S.launchActivity("user_menu_list");
            }
        }));
    }
}
