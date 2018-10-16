package com.android.test;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.app.AlertDialog.Builder;
import android.app.Fragment;
import android.app.FragmentTransaction;
import android.content.ContentValues;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.Bitmap.CompressFormat;
import android.graphics.drawable.BitmapDrawable;
import android.graphics.drawable.Drawable;
import android.net.Uri;
import android.os.Bundle;
import android.provider.MediaStore.Images.Media;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.HorizontalScrollView;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Collections;

import static com.android.test.user_menu_list.GET_FROM_GALLERY;

@SuppressLint({"ValidFragment"})
public final class User_MenuListFragment extends Fragment {
    private String passName = null;
    private ArrayList passMenu = null;

    public View onCreateView(LayoutInflater inflater, final ViewGroup container, Bundle savedInstanceState) {
        final View rootView = inflater.inflate(R.layout.menu_fragment, container, false);
        final ListView listView = (ListView)rootView.findViewById(R.id.MenuListView);
        listView.setAdapter(new User_MenuAdapter(passMenu));
        return rootView;
    }
    public User_MenuListFragment(){}
    public User_MenuListFragment(String TabName, ArrayList MenuList) {
        super();
        this.passName = TabName;
        this.passMenu = MenuList;
    }
}
