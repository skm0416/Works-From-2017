package com.android.test;

import java.util.ArrayList;

public class MenuOrder {
    private static MenuOrder instance;

    public static MenuOrder getInstance() {
        if (instance == null)
            instance = new MenuOrder();
        return instance;
    }

    private MenuOrder() {
    }

    private ArrayList<Integer>MenuOrder;

    public ArrayList getMenuOrder() {
        return MenuOrder;
    }

    public void setMenuOrder(ArrayList menuOrder) {
        MenuOrder = menuOrder;
    }
}
