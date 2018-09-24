package com.android.test;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.drawable.BitmapDrawable;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.support.design.widget.TabLayout;
import android.support.v4.app.FragmentManager;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.HashMap;

import static com.android.test.user_menu_list.GET_FROM_GALLERY;

public final class server_menu_list extends AppCompatActivity {
    private PageAdapter mSectionsPagerAdapter;
    private ViewPager mViewPager;
    private ImageButton ImageTarget;
    private HashMap _$_findViewCache;

    public final PageAdapter getMSectionsPagerAdapter() {
        return this.mSectionsPagerAdapter;
    }
    public final void setMSectionsPagerAdapter(PageAdapter var1) {
        this.mSectionsPagerAdapter = var1;
    }

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_server_menu_list);
        FragmentManager var10003 = this.getSupportFragmentManager();
        this.mSectionsPagerAdapter = new PageAdapter(var10003, (Context)this);
        this.mViewPager = (ViewPager)this.findViewById(R.id.server_menu_list_container);
        mViewPager.setAdapter((PagerAdapter)this.mSectionsPagerAdapter);
        final TabLayout tabLayout = (TabLayout)this.findViewById(R.id.server_menu_list_tabs);
        tabLayout.setupWithViewPager(this.mViewPager);
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
                            server_menu_list.this.startActivityForResult(new Intent("android.intent.action.PICK", MediaStore.Images.Media.INTERNAL_CONTENT_URI), 1);
                        }
                    }));
                    server_menu_list.this.ImageTarget = image;
                    if (tabLayout.getTabCount() > 0) {
                        tab_name.setText(mSectionsPagerAdapter.getPageTitle(tabLayout.getSelectedTabPosition()));
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
                                mSectionsPagerAdapter.notifyDataSetChanged();
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
                    CharSequence tabName = mSectionsPagerAdapter.getPageTitle(tabLayout.getSelectedTabPosition());
                    int response = DB.RemoveTab(String.valueOf(tabName));
                    mSectionsPagerAdapter.notifyDataSetChanged();
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

    // $FF: synthetic method
    public static final ImageButton access$getImageTarget$p(server_menu_list $this) {
        return $this.ImageTarget;
    }

    public View _$_findCachedViewById(int var1) {
        if (this._$_findViewCache == null) {
            this._$_findViewCache = new HashMap();
        }

        View var2 = (View)this._$_findViewCache.get(var1);
        if (var2 == null) {
            var2 = this.findViewById(var1);
            this._$_findViewCache.put(var1, var2);
        }

        return var2;
    }

    public void _$_clearFindViewByIdCache() {
        if (this._$_findViewCache != null) {
            this._$_findViewCache.clear();
        }

    }
}
