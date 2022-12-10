package com.joshkryo.lib;

/**
 * Created by king on 2017/12/23.
 */

public class CVLib4 {
    static {
        System.loadLibrary("cv_lib4");
    }

    public static native String stringFromJNI();

//    /**
//     * process bitmap
//     *
//     * @param bitmap Bitmap
//     * @param method method
//     * @return result
//     */
//    public static native Bitmap process_bitmap(Bitmap bitmap, String method);
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
