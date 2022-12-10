package com.joshkryo.opencvjni

import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.AdapterView
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.findNavController
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import com.joshkryo.opencvjni.adapter.ImageHolderItem
import com.joshkryo.opencvjni.adapter.ImageListAdapter
import com.joshkryo.opencvjni.databinding.FragmentFirstBinding

/**
 * A simple [Fragment] subclass as the default destination in the navigation.
 */
class FirstFragment : Fragment() {

    private var _binding: FragmentFirstBinding? = null

    // This property is only valid between onCreateView and
    // onDestroyView.
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentFirstBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        val linearLayoutManager = LinearLayoutManager(context)
        linearLayoutManager.orientation = RecyclerView.VERTICAL
        binding.recyclerView.layoutManager = linearLayoutManager

        val mData = mutableListOf<ImageHolderItem>()
        mData.add(ImageHolderItem(R.drawable.iv1))
        mData.add(ImageHolderItem(R.drawable.iv2))
        mData.add(ImageHolderItem(R.drawable.iv3))
        mData.add(ImageHolderItem(R.drawable.iv4))
        mData.add(ImageHolderItem(R.drawable.iv5))
        mData.add(ImageHolderItem(R.drawable.iv6))

        binding.recyclerView.adapter = ImageListAdapter(
            context, mData
        ) { _: AdapterView<*>?, _: View?, position: Int, _: Long ->
            val holderItem = mData[position]
            val bundle = Bundle()
            bundle.putInt("imgResId", holderItem.imgRes)
            bundle.putInt("position", position)
            Log.i(tag, "imgResId: ${holderItem.imgRes}")
            findNavController().navigate(R.id.action_FirstFragment_to_SecondFragment, bundle)
        }

        binding.recyclerView.setOnClickListener {
            findNavController().navigate(R.id.action_FirstFragment_to_SecondFragment)
        }

    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}