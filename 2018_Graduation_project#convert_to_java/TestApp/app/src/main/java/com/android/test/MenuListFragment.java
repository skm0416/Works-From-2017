package com.android.test;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog;
import android.app.AlertDialog.Builder;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.BitmapFactory;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore;
import android.provider.MediaStore.Images.Media;
import android.support.design.widget.TabLayout;
import android.support.v4.app.Fragment;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v7.widget.LinearLayoutManager;
import android.support.v7.widget.RecyclerView;
import android.support.v7.widget.RecyclerView.Adapter;
import android.support.v7.widget.RecyclerView.LayoutManager;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.View.OnClickListener;
import android.widget.AdapterView;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.HashMap;

import static com.android.test.user_menu_list.GET_FROM_GALLERY;

@SuppressLint({"ValidFragment"})
public final class MenuListFragment extends Fragment {
    private final Context passThroughContext;
    private final String passName;
    private ImageButton ImageTarget;
    private HashMap _$_findViewCache;

    public final Context getPassThroughContext() {
        return this.passThroughContext;
    }
    public final String getPassName() {
        return this.passName;
    }

    public View onCreateView(LayoutInflater inflater,ViewGroup container, Bundle savedInstanceState) {
        final View rootView = inflater.inflate(R.layout.menu_fragment, container, false);
        final RecyclerView recyclerView = (RecyclerView)rootView.findViewById(R.id.MenuRecyclerView);
        DatabaseHelper DB = new DatabaseHelper(this.passThroughContext);
        ArrayList MenuList = DB.FetchMenu(this.passName);
        recyclerView.setAdapter((Adapter)(new MenuAdapter(MenuList)));
        recyclerView.setLayoutManager((LayoutManager)(new LinearLayoutManager(this.passThroughContext)));
        recyclerView_Listener.addOnItemClickListener(recyclerView, (OnItemClickListener)(new OnItemClickListener() {
            public void onItemClicked(int position, View view) {
                Context context = MenuListFragment.this.getPassThroughContext();
                Activity activity = (Activity) context;
                TabLayout tabLayout = (TabLayout) activity.findViewById(R.id.server_menu_list_tabs);
                ViewPager pager = (ViewPager) activity.findViewById(R.id.server_menu_list_container);
                final PagerAdapter adapter = pager.getAdapter();
                TextView menunumber = (TextView) view.findViewById(R.id.MenuNumber);
                final int rowid = Integer.parseInt(menunumber.getText().toString());
                AlertDialog.Builder alert = new AlertDialog.Builder(context);
                alert.setTitle("메뉴 수정");
                alert.setMessage("수정할 메뉴의 정보를 입력해주세요");
                LayoutInflater inflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);

                View dialogView = inflater.inflate(R.layout.dialog_insert_menu, (ViewGroup) null);
                final EditText menu_name = (EditText) dialogView.findViewById(R.id.input_menu_name);
                final EditText price = (EditText) dialogView.findViewById(R.id.input_menu_price);
                final EditText tab_name = (EditText) dialogView.findViewById(R.id.input_tab_name);
                final ImageButton image = (ImageButton) dialogView.findViewById(R.id.input_image);
                image.setOnClickListener((OnClickListener) (new OnClickListener() {
                    public final void onClick(View it) {
                        MenuListFragment.this.startActivityForResult(new Intent("android.intent.action.PICK", Media.INTERNAL_CONTENT_URI), 1);
                    }
                }));
                MenuListFragment.this.ImageTarget = image;

                tab_name.setText(adapter.getPageTitle(tabLayout.getSelectedTabPosition()));
                TextView temp = (TextView) view.findViewById(R.id.MenuPrice);
                String tempstr = temp.getText().toString();
                price.setText(tempstr.substring(0,tempstr.length()-2));
                temp = (TextView) view.findViewById(R.id.MenuName);
                menu_name.setText(temp.getText().toString());
                Drawable drawable = ((ImageView) view.findViewById(R.id.MenuImageView)).getDrawable();
                if (drawable != null) {
                    image.setImageBitmap(((BitmapDrawable) drawable).getBitmap());
                }

                alert.setView(dialogView);
                alert.setPositiveButton((CharSequence) "수정", (android.content.DialogInterface.OnClickListener) (new android.content.DialogInterface.OnClickListener() {
                    public final void onClick(DialogInterface dialog, int whichButton) {
                        DatabaseHelper DB = new DatabaseHelper(MenuListFragment.this.getPassThroughContext());
                        ContentValues values = new ContentValues();
                        BitmapDrawable drawable = (BitmapDrawable) image.getDrawable();
                        if (drawable != null) {
                            Bitmap bitmap = drawable.getBitmap();
                            ByteArrayOutputStream stream = new ByteArrayOutputStream();
                            bitmap.compress(CompressFormat.PNG, 100, (OutputStream) stream);
                            byte[] imagex = stream.toByteArray();
                            values.put("Image", imagex);
                        }

                        values.put("TabName", tab_name.getText().toString());
                        values.put("MenuName", menu_name.getText().toString());
                        String price_test = price.getText().toString();
                        String response;
                        if (price_test.length() > 1) {
                            Integer tempint = Integer.parseInt(price_test);
                            values.put("Price", tempint.toString());
                        }

                        response = DB.UpdateMenu(values, rowid);
                        if (response.equalsIgnoreCase("ok")) {
                            Toast.makeText(MenuListFragment.this.getPassThroughContext(), (CharSequence) "메뉴수정 성공", Toast.LENGTH_SHORT).show();
                            adapter.notifyDataSetChanged();
                        } else {
                            Toast.makeText(MenuListFragment.this.getPassThroughContext(), (CharSequence) "메뉴수정 실패", Toast.LENGTH_SHORT).show();
                        }

                    }
                }));
                alert.setNeutralButton((CharSequence) "삭제", (android.content.DialogInterface.OnClickListener) (new android.content.DialogInterface.OnClickListener() {
                    public final void onClick(DialogInterface dialog, int whichButton) {
                        DatabaseHelper DB = new DatabaseHelper(recyclerView.getContext());
                        String response = DB.RemoveMenu(rowid);
                        if (response.equalsIgnoreCase("ok")) {
                            Toast.makeText(MenuListFragment.this.getPassThroughContext(), (CharSequence) "메뉴삭제 성공", Toast.LENGTH_SHORT).show();
                            adapter.notifyDataSetChanged();
                        } else {
                            Toast.makeText(MenuListFragment.this.getPassThroughContext(), (CharSequence) "메뉴삭제 실패", Toast.LENGTH_SHORT).show();
                        }

                    }
                }));
                alert.setNegativeButton((CharSequence) "취소", (android.content.DialogInterface.OnClickListener) null);
                alert.show();
            }
        }));
        return rootView;
    }


    public void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == GET_FROM_GALLERY && resultCode == Activity.RESULT_OK) {
            Uri selectedImage = data.getData();
            Bitmap bitmap = null;
            try {
                bitmap = Media.getBitmap(this.getContext().getContentResolver(), selectedImage);
            } catch (IOException e) {
                e.printStackTrace();
            }
            this.ImageTarget.setImageBitmap(bitmap_rotate.Rotate(bitmap, 90));
        }

    }

    public MenuListFragment(Context passedContext,  String TabName) {
        super();
        this.passThroughContext = passedContext;
        this.passName = TabName;
    }

    // $FF: synthetic method
    public static final ImageButton access$getImageTarget$p(MenuListFragment $this) {
        return $this.ImageTarget;
    }

    public View _$_findCachedViewById(int var1) {
        if (this._$_findViewCache == null) {
            this._$_findViewCache = new HashMap();
        }

        View var2 = (View)this._$_findViewCache.get(var1);
        if (var2 == null) {
            View var10000 = this.getView();
            if (var10000 == null) {
                return null;
            }

            var2 = var10000.findViewById(var1);
            this._$_findViewCache.put(var1, var2);
        }

        return var2;
    }

    public void _$_clearFindViewByIdCache() {
        if (this._$_findViewCache != null) {
            this._$_findViewCache.clear();
        }

    }

    // $FF: synthetic method
    public void onDestroyView() {
        super.onDestroyView();
        this._$_clearFindViewByIdCache();
    }
}
