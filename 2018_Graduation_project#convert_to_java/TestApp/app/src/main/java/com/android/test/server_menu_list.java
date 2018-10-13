package com.android.test;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.FragmentTransaction;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.app.FragmentManager;
import android.util.TypedValue;
import android.view.Gravity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.app.Fragment;
import android.widget.HorizontalScrollView;
import android.widget.ImageButton;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;

import static com.android.test.user_menu_list.GET_FROM_GALLERY;

public final class server_menu_list extends Activity {
    private ImageButton ImageTarget;
    private HorizontalScrollView tabs;
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
        this.setContentView(R.layout.activity_server_menu_list);

        Context context = this;
        curtab = 0;
        tabs = (HorizontalScrollView) this.findViewById(R.id.server_menu_list_tabs);
        setPage(this);
        TextView insertMenu = (TextView)this.findViewById(R.id.insert_menu);
        insertMenu.setOnClickListener((View.OnClickListener)(new View.OnClickListener() {
                public final void onClick(View it) {
                    AlertDialog.Builder alert = new AlertDialog.Builder((Context)server_menu_list.this);
                    alert.setTitle((CharSequence)"메뉴 추가");
                    alert.setMessage((CharSequence)"추가할 메뉴의 정보를 입력해주세요");
                    View dialogView = server_menu_list.this.getLayoutInflater().inflate(R.layout.dialog_insert_menu, (ViewGroup)null);
                    final EditText menu_name = (EditText)dialogView.findViewById(R.id.input_menu_name);
                    final EditText price = (EditText)dialogView.findViewById(R.id.input_menu_price);
                    final EditText tab_name = (EditText)dialogView.findViewById(R.id.input_tab_name);
                    final ImageButton image = (ImageButton)dialogView.findViewById(R.id.input_image);
                    image.setOnClickListener((View.OnClickListener)(new View.OnClickListener() {
                        public final void onClick(View it) {
                            Intent intent = new Intent();
                            intent.setType("image/*");
                            intent.setAction(Intent.ACTION_GET_CONTENT);
                            server_menu_list.this.startActivityForResult(Intent.createChooser(intent, "Select Picture"), GET_FROM_GALLERY);
                        }
                    }));
                    server_menu_list.this.ImageTarget = image;
                    if (tabsize > 0) {
                        tab_name.setText(curtitle);
                    }
                    alert.setView(dialogView);
                    alert.setPositiveButton((CharSequence)"추가", (android.content.DialogInterface.OnClickListener)(new android.content.DialogInterface.OnClickListener() {
                        public final void onClick(DialogInterface dialog, int whichButton) {
                            DatabaseHelper DB = new DatabaseHelper((Context)server_menu_list.this);
                            ContentValues values = new ContentValues();
                            BitmapDrawable drawable = (BitmapDrawable)image.getDrawable();
                            if (drawable != null) {
                                Bitmap bitmap = drawable.getBitmap();
                                ByteArrayOutputStream stream = new ByteArrayOutputStream();
                                bitmap.compress(Bitmap.CompressFormat.PNG, 100, (OutputStream)stream);
                                byte[] imagex = stream.toByteArray();
                                values.put("Image", imagex);
                            }

                            values.put("TabName", tab_name.getText().toString());
                            values.put("MenuName", menu_name.getText().toString());
                            if (price.getText().toString().length() > 0) {
                                values.put("Price", Integer.parseInt(price.getText().toString()));
                            }
                            String response = DB.InsertMenu(values);
                            if (response.equalsIgnoreCase("ok")) {
                                Toast.makeText((Context)server_menu_list.this, (CharSequence)"메뉴추가 성공", Toast.LENGTH_SHORT).show();
                                setPage((Context)server_menu_list.this);
                            } else {
                                Toast.makeText((Context)server_menu_list.this, (CharSequence)"메뉴추가 실패", Toast.LENGTH_SHORT).show();
                            }

                        }
                    }));
                    alert.setNegativeButton((CharSequence)"취소", (android.content.DialogInterface.OnClickListener)null);
                    alert.show();
                }
            }));
            TextView removeTab = (TextView)this.findViewById(R.id.remove_tab);
            removeTab.setOnClickListener((View.OnClickListener)(new View.OnClickListener() {
                public final void onClick(View it) {
                    DatabaseHelper DB = new DatabaseHelper((Context)server_menu_list.this);
                    int response = DB.RemoveTab(curtitle);
                    if(curtab>0)
                        curtab--;
                    setPage((Context)server_menu_list.this);
                    Toast.makeText((Context)server_menu_list.this, (CharSequence)(response + "개의 메뉴를 삭제했습니다"), Toast.LENGTH_SHORT).show();
                }
            }));
        }
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == GET_FROM_GALLERY && resultCode == Activity.RESULT_OK) {

            Uri selectedImage = data.getData();
            Bitmap bitmap = null;
            try {
                bitmap = MediaStore.Images.Media.getBitmap(getContentResolver(), selectedImage);
            } catch (IOException e) {
                e.printStackTrace();
            }
            ImageTarget.setImageBitmap(bitmap_rotate.Rotate(bitmap, 90));
        }

    }
}
