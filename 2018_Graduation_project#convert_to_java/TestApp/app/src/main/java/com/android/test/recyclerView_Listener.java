package com.android.test;

import android.support.v7.widget.RecyclerView;
import android.view.View;

interface OnItemClickListener {
    void onItemClicked(int var1, View var2);
}
public final class recyclerView_Listener {
    public static final void addOnItemClickListener(final RecyclerView $receiver, final OnItemClickListener onClickListener) {
         $receiver.addOnChildAttachStateChangeListener((RecyclerView.OnChildAttachStateChangeListener)(new RecyclerView.OnChildAttachStateChangeListener() {
            public void onChildViewDetachedFromWindow(View view) {
                if (view != null) {
                    view.setOnClickListener((View.OnClickListener)null);
                }

            }

            public void onChildViewAttachedToWindow(final View view) {
                if (view != null) {
                    view.setOnClickListener((View.OnClickListener)(new View.OnClickListener() {
                        public final void onClick(View it) {
                            RecyclerView.ViewHolder holder = $receiver.getChildViewHolder(view);
                            onClickListener.onItemClicked(holder.getAdapterPosition(), view);
                        }
                    }));
                }

            }
        }));
    }
}
