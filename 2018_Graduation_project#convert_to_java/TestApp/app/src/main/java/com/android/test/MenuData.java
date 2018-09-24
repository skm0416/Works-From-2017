package com.android.test;

public final class MenuData {
    private Integer RowId;
    private byte[] Image;
    private String TabName;
    private String MenuName;
    private int Price;

    public MenuData(String TabName, String MenuName, int Price) {
        super();
        this.TabName = TabName;
        this.MenuName = MenuName;
        this.Price = Price;
    }

    public final Integer getRowId() {
        return this.RowId;
    }
    public final void setRowId(Integer var1) {
        this.RowId = var1;
    }
    public final byte[] getImage() {
        return this.Image;
    }
    public final void setImage(byte[] var1) {
        this.Image = var1;
    }
    public final String getTabName() {
        return this.TabName;
    }
    public final void setTabName(String var1) { this.TabName = var1; }
    public final String getMenuName() {
        return this.MenuName;
    }
    public final void setMenuName(String var1) { this.MenuName = var1; }
    public final int getPrice() {
        return this.Price;
    }
    public final void setPrice(int var1) {
        this.Price = var1;
    }
}
