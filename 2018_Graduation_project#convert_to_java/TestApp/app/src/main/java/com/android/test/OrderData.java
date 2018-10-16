package com.android.test;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Objects;

public final class OrderData implements Serializable {

    private ArrayList<String> NameList;
    private ArrayList<Integer> AmountList;
    private int Price;
    private String time;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        OrderData orderData = (OrderData) o;
        return Price == orderData.Price &&
                Objects.equals(NameList, orderData.NameList) &&
                Objects.equals(AmountList, orderData.AmountList) &&
                Objects.equals(time, orderData.time);
    }

    @Override
    public int hashCode() {

        return Objects.hash(NameList, AmountList, Price, time);
    }

    public OrderData(ArrayList<String> NameList, ArrayList<Integer> AmountList, int Price, String time) {
        super();
        this.NameList = NameList;
        this.Price = Price;
        this.AmountList = AmountList;
        this.time = time;
    }
    public final int getPrice() {
        return this.Price;
    }
    public final void setPrice(int Price) {
        this.Price = Price;
    }
    public void setNameList(ArrayList<String> nameList) { NameList = nameList; }
    public void setAmountList(ArrayList<Integer> amountList) { AmountList = amountList; }
    public ArrayList<String> getNameList() { return NameList; }
    public ArrayList<Integer> getAmountList() { return AmountList; }
    public String getTime() { return time; }
    public void setTime(String time) { this.time = time; }
}
