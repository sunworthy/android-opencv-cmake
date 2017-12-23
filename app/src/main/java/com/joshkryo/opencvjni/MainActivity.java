package com.joshkryo.opencvjni;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.AppCompatImageView;
import android.text.TextUtils;
import android.view.View;
import android.widget.Toast;
import com.bumptech.glide.Glide;
import com.joshkryo.lib.OpenCVLib;
import com.luck.picture.lib.PictureSelector;
import com.luck.picture.lib.config.PictureConfig;
import com.luck.picture.lib.config.PictureMimeType;
import com.luck.picture.lib.entity.LocalMedia;

import org.json.JSONException;
import org.json.JSONObject;

import java.util.List;

public class MainActivity extends AppCompatActivity {
    Context mContext;
    String mImagePath;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mContext=this;
        bindView();
        bindListener();
        loadData();
    }

    AppCompatImageView ivImage;
    private void bindView() {
        ivImage=findViewById(R.id.iv_image);
    }

    private void bindListener() {
        findViewById(R.id.btn_select_photo).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                PictureSelector.create(MainActivity.this)
                        .openGallery(PictureMimeType.ofImage())
                        .forResult(PictureConfig.CHOOSE_REQUEST);

            }
        });
        findViewById(R.id.btn_func1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if(TextUtils.isEmpty(mImagePath)){
                    Toast.makeText(mContext, "请选择图片", Toast.LENGTH_SHORT).show();
                    return;
                }
                String outputDir=getCacheDir().getAbsolutePath().toString()+"/";
                String result = OpenCVLib.imageProcess(mImagePath,outputDir);
                try {
                    JSONObject json=new JSONObject(result);
                    String outputImagePath=json.optString("outputImagePath");
                    if(!TextUtils.isEmpty(outputImagePath)){
                        Glide.with(mContext).load(outputImagePath).into(ivImage);
                    }
                } catch (JSONException e) {
                    e.printStackTrace();
                }
                Toast.makeText(MainActivity.this, result, Toast.LENGTH_SHORT).show();
            }
        });
    }

    private void loadData() {

    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (resultCode == RESULT_OK) {
            switch (requestCode) {
                case PictureConfig.CHOOSE_REQUEST:
                    // 图片选择结果回调
                    List<LocalMedia> selectList = PictureSelector.obtainMultipleResult(data);
                    // 例如 LocalMedia 里面返回三种path
                    // 1.media.getPath(); 为原图path
                    // 2.media.getCutPath();为裁剪后path，需判断media.isCut();是否为true
                    // 3.media.getCompressPath();为压缩后path，需判断media.isCompressed();是否为true
                    // 如果裁剪并压缩了，以取压缩路径为准，因为是先裁剪后压缩的
                    if(selectList!=null && selectList.size()>0){
                        mImagePath=selectList.get(0).getPath();
                        Glide.with(mContext).load(mImagePath).into(ivImage);
                    }
                    break;
            }
        }
    }


}
