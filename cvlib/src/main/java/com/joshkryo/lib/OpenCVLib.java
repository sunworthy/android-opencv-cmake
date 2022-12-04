package com.joshkryo.lib;

import android.graphics.Bitmap;

/**
 * Created by king on 2017/12/23.
 */

public class OpenCVLib {
    static {
        System.loadLibrary("OpenCVLib");
    }

    public static native String imageProcess(String mImagePath, String outDir);

    /**
     * process bitmap
     *
     * @param bitmap Bitmap
     * @param method method
     * @return result
     */
    public static native Bitmap processBitmap(Bitmap bitmap, String method);
}
