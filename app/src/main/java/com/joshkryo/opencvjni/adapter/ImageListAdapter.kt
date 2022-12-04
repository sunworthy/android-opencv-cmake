package com.joshkryo.opencvjni.adapter

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.AdapterView.OnItemClickListener
import android.widget.ImageView
import androidx.recyclerview.widget.RecyclerView
import com.joshkryo.opencvjni.R

class ImageListAdapter(
    private val mContext: Context?,
    private val mData: List<ImageHolderItem>,
    private val itemClickListener: OnItemClickListener
) :
    RecyclerView.Adapter<ImageListAdapter.ViewHolder>() {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(mContext).inflate(R.layout.item_img, parent, false)
        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val imgRes = mData[position].imgRes
        holder.imageView.setImageResource(imgRes)
        holder.imageView.setOnClickListener(View.OnClickListener {
            itemClickListener.onItemClick(null, holder.imageView, position, 0)
        })
    }

    override fun getItemCount(): Int {
        return mData.size
    }

    class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val imageView: ImageView

        init {
            imageView = itemView.findViewById(R.id.item_iv_image)
        }
    }
}