package com.android.test;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;

public final class OrderAdapter extends BaseAdapter {
    private ArrayList<OrderData> OrderList;


    public OrderAdapter(ArrayList<OrderData> OrderList) {
        super();
        this.OrderList = OrderList;
    }

    @Override
    public int getCount() {
        return this.OrderList.toArray().length;
    }

    @Override
    public Object getItem(int i) {
        return this.OrderList.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int position, View convertView, ViewGroup viewGroup) {
        if(convertView==null){
            convertView = LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.order_fragment, viewGroup, false);
        }
        final OrderData Order =OrderList.get(position);
        TextView OrderPrice = (TextView)convertView.findViewById(R.id.OrderPrice);
        OrderPrice.setText((CharSequence)(Order.getPrice() + " 원"));

        LinearLayout OrderDetail = (LinearLayout)convertView.findViewById(R.id.OrderListView);
        ArrayList<String> namelist = Order.getNameList();
        ArrayList<Integer> amountlist = Order.getAmountList();
        OrderDetail.removeAllViewsInLayout();
        for(int i=0; i<namelist.size();i++){
            LinearLayout item = (LinearLayout)LayoutInflater.from(viewGroup.getContext()).inflate(R.layout.order_item,null);
            String name = namelist.get(i);
            int amount = amountlist.get(i);
            TextView OrderName = (TextView)item.findViewById(R.id.OrderName);
            TextView OrderAmount = (TextView)item.findViewById(R.id.OrderAmount);
            OrderName.setText(name);
            OrderAmount.setText((CharSequence)(Integer.toString(amount) + " 개"));
            OrderDetail.addView(item);
        }

        TextView OrderComplete = (TextView)convertView.findViewById(R.id.OrderComplete);
        OrderComplete.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                ArrayList<OrderData> G_OrderList = com.android.test.OrderList.getInstance().getOrderList();
                G_OrderList.remove(Order);
                com.android.test.OrderList.getInstance().setOrderList(G_OrderList);
                notifyDataSetChanged();
            }
        });

        TextView OrderTime = (TextView)convertView.findViewById(R.id.OrderTime);
        OrderTime.setText(Order.getTime());
        return convertView;
    }
}
