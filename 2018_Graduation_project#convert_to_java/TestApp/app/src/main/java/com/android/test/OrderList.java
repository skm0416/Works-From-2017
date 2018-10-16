package com.android.test;

import java.util.ArrayList;

public class OrderList {
    private static OrderList instance;

    public static OrderList getInstance() {
        if (instance == null)
            instance = new OrderList();
        return instance;
    }

    private OrderList() {
    }

    private ArrayList<OrderData> OrderList;

    public ArrayList getOrderList() {
        return OrderList;
    }

    public void setOrderList(ArrayList orderList) {
        OrderList = orderList;
    }
}
