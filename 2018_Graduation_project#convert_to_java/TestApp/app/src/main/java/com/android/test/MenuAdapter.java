package com.android.test;

import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import java.util.ArrayList;

public final class MenuAdapter extends RecyclerView.Adapter {
    private final ArrayList MenuList;

    public MenuHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        View menuItem = LayoutInflater.from(parent.getContext()).inflate(R.layout.menu_item, parent, false);
        return new MenuHolder(menuItem);
    }

    public void onBindViewHolder(RecyclerView.ViewHolder var1, int var2) {
        this.onBindViewHolder((MenuHolder)var1, var2);
    }
    public void onBindViewHolder(MenuHolder holder, int position) {
        Object var10001 = this.MenuList.get(position);
        holder.updateMenu((MenuData)var10001);
    }

    public int getItemCount() {
        return this.MenuList.toArray().length;
    }

    public MenuAdapter(ArrayList MenuList) {
        super();
        this.MenuList = MenuList;
    }


}
