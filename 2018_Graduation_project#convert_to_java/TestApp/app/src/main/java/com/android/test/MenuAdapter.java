package com.android.test;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.ArrayList;

public final class MenuAdapter extends BaseAdapter {
    private ArrayList<MenuData> MenuList;


    public MenuAdapter(ArrayList<MenuData> MenuList) {
        super();
        this.MenuList = MenuList;
    }

    @Override
    public int getCount() {
        return this.MenuList.toArray().length;
    }

    @Override
    public Object getItem(int i) {
        return this.MenuList.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup viewGroup) {
        if(convertView==null){
            convertView = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.menu_item, viewGroup, false);
        }
        convertView.setTag(String.valueOf(position));
        MenuData Menu =MenuList.get(position);
        ImageView MenuImage = (ImageView)convertView.findViewById(R.id.MenuImageView);
        TextView MenuName = (TextView)convertView.findViewById(R.id.MenuName);
        TextView MenuPrice = (TextView)convertView.findViewById(R.id.MenuPrice);
        TextView MenuNumber = (TextView)convertView.findViewById(R.id.MenuNumber);

        if (Menu.getImage() != null) {
            byte[] imagebyte = Menu.getImage();
            Bitmap image = BitmapFactory.decodeByteArray(imagebyte, 0, imagebyte.length);
            MenuImage.setImageBitmap(image);
        }
        MenuNumber.setText((CharSequence)String.valueOf(Menu.getRowId()));
        MenuName.setText((CharSequence)Menu.getMenuName());
        MenuPrice.setText((CharSequence)(Menu.getPrice() + " 원"));

        final ArrayList<Integer> MenuOrder = com.android.test.MenuOrder.getInstance().getMenuOrder();
        final TextView menuamount = (TextView) convertView.findViewById(R.id.MenuAmount);
        TextView menuplus = (TextView) convertView.findViewById(R.id.MenuPlus);
        TextView menuminus = (TextView) convertView.findViewById(R.id.MenuMinus);

        final int id = Integer.parseInt(MenuNumber.getText().toString())-1;
        menuplus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int amount = MenuOrder.get(id);
                amount = amount+1;
                MenuOrder.set(id,amount);
                com.android.test.MenuOrder.getInstance().setMenuOrder(MenuOrder);
                menuamount.setText(String.valueOf(amount));
            }
        });
        menuminus.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                int amount = MenuOrder.get(id);
                if(amount > 0){
                    amount = amount -1;
                    MenuOrder.set(id,amount);
                    menuamount.setText(String.valueOf(amount));
                    com.android.test.MenuOrder.getInstance().setMenuOrder(MenuOrder);
                }
            }
        });
        return convertView;
    }
}
