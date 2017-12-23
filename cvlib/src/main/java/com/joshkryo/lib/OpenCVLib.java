package com.joshkryo.lib;

/**
 * Created by king on 2017/12/23.
 */

public class OpenCVLib {
    static {
        System.loadLibrary("OpenCVLib");
    }

    public static native String  imageProcess(String mImagePath,String outDir);
}
