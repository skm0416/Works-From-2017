package com.android.test;

import android.content.Context;
import android.os.Bundle;
import android.support.design.widget.TabLayout;
import android.support.v4.app.FragmentManager;
import android.support.v4.view.PagerAdapter;
import android.support.v4.view.ViewPager;
import android.support.v7.app.AppCompatActivity;
import android.view.View;

import java.util.HashMap;

public final class user_menu_list extends AppCompatActivity {

    public static final int GET_FROM_GALLERY = 1;

    private PageAdapter mSectionsPagerAdapter;
    private ViewPager mViewPager;
    private HashMap _$_findViewCache;

    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_user_menu_list);
        this.mSectionsPagerAdapter = new PageAdapter(this.getSupportFragmentManager(), (Context)this);
        this.mViewPager = (ViewPager)this.findViewById(R.id.user_menu_list_container);
        mViewPager.setAdapter((PagerAdapter)this.mSectionsPagerAdapter);
        TabLayout tabLayout =(TabLayout) this.findViewById(R.id.user_menu_list_tabs);
        tabLayout.setupWithViewPager(this.mViewPager);
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
