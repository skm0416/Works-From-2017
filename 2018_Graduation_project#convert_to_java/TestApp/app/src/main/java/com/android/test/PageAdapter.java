package com.android.test;

import android.content.Context;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentStatePagerAdapter;
import android.support.v4.view.PagerAdapter;

import java.util.ArrayList;

public final class PageAdapter extends FragmentStatePagerAdapter{

    private final DatabaseHelper DB;
    private ArrayList tabNameArray;
    private final Context context;
    public final DatabaseHelper getDB() {
        return this.DB;
    }
    public final ArrayList getTabNameArray() {
        return this.tabNameArray;
    }
    public final void setTabNameArray(ArrayList var1) { this.tabNameArray = var1; }
    public int getItemPosition(Object object) { return PagerAdapter.POSITION_NONE; }
    public Fragment getItem(int TabId) {
        return (Fragment)new MenuListFragment(context, (String)tabNameArray.get(TabId));
    }
    public int getCount() {
        this.tabNameArray = this.DB.FetchTabName();
        return this.tabNameArray.size();
    }
    public CharSequence getPageTitle(int position) {
        if(position<0)
            return null;
        return (CharSequence)this.tabNameArray.get(position);
    }
    public PageAdapter(FragmentManager fm, Context context) {
        super(fm);
        this.context = context;
        this.DB = new DatabaseHelper(this.context);
        this.tabNameArray = this.DB.FetchTabName();
    }
}
