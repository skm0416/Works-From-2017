package com.android.test;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.Intent;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.provider.MediaStore;
import android.support.design.widget.TabLayout;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.EditText;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.TextView;

public final class MenuHolder extends RecyclerView.ViewHolder{
    private final ImageView MenuImage;
    private final TextView MenuName;
    private final TextView MenuPrice;
    private final TextView MenuNumber;

    public final void updateMenu(MenuData Menu) {
        if (Menu.getImage() != null) {
            byte[] var10000 = Menu.getImage();
            byte[] var10002 = Menu.getImage();

            Bitmap image = BitmapFactory.decodeByteArray(var10000, 0, var10002.length);
            this.MenuImage.setImageBitmap(image);
        }

        this.MenuNumber.setText((CharSequence)String.valueOf(Menu.getRowId()));
        this.MenuName.setText((CharSequence)Menu.getMenuName());
        this.MenuPrice.setText((CharSequence)(Menu.getPrice() + " 원"));
    }

    public MenuHolder(View itemView) {
        super(itemView);
        this.MenuImage = (ImageView)itemView.findViewById(R.id.MenuImageView);
        this.MenuName = (TextView)itemView.findViewById(R.id.MenuName);
        this.MenuPrice = (TextView)itemView.findViewById(R.id.MenuPrice);
        this.MenuNumber = (TextView)itemView.findViewById(R.id.MenuNumber);
    }



}
