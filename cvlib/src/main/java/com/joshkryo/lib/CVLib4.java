package com.joshkryo.lib;

import android.graphics.Bitmap;

/**
 * Created by king on 2017/12/23.
 */

public class CVLib4 {
    static {
        System.loadLibrary("cv_lib4");
    }

    /**
     * process bitmap
     *
     * @param bitmap Bitmap
     * @param type   method
     */
    public static native void process_bitmap(Bitmap bitmap, int type, Bitmap bitmap_out);
//
//    /**
//     * process bitmap
//     *
//     * @param img_path img_path
//     * @param method   method
//     * @return result
//     */
//    public static native String process_image(String img_path, String method);
}
