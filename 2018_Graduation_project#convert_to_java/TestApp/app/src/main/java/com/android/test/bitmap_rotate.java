package com.android.test;


import android.graphics.Matrix;
import android.graphics.Bitmap;

public class bitmap_rotate {
    public static Bitmap Rotate(Bitmap source, int degree) {
        // Initialize a new matrix
        Matrix matrix = new Matrix();
        // Rotate the bitmap
        matrix.postRotate(((float) degree));
        return Bitmap.createBitmap(source, 0, 0, source.getWidth(), source.getHeight(), matrix, true);
    }
}