package com.joshkryo.opencvjni

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.navigation.fragment.findNavController
import com.joshkryo.lib.CVLib4
import com.joshkryo.opencvjni.databinding.FragmentSecondBinding
import java.util.*

/**
 * A simple [Fragment] subclass as the second destination in the navigation.
 */
class SecondFragment : Fragment() {

    private var _binding: FragmentSecondBinding? = null

    // This property is only valid between onCreateView and
    // onDestroyView.
    private val binding get() = _binding!!

    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {
        _binding = FragmentSecondBinding.inflate(inflater, container, false)
        return binding.root
    }

    override fun onViewCreated(view: View, savedInstanceState: Bundle?) {
        super.onViewCreated(view, savedInstanceState)

        binding.buttonSecond.setOnClickListener {
            findNavController().navigate(R.id.action_SecondFragment_to_FirstFragment)
        }

        val resId = arguments?.getInt("imgResId")
        val position = arguments?.getInt("position") ?: 0
        Log.d(tag, "onViewCreated: $resId")
        if (Objects.nonNull(resId)) {
            val bitmap = resId?.let { BitmapFactory.decodeResource(resources, it) }
            Log.d(tag, "onViewCreated: $bitmap")

            val outBitmap = Bitmap.createBitmap(
                bitmap?.width ?: 0,
                bitmap?.height ?: 0,
                Bitmap.Config.ARGB_8888
            )
            CVLib4.process_bitmap(bitmap, position, outBitmap);
            binding.ivProcessed.setImageBitmap(outBitmap)
        }
    }

    override fun onDestroyView() {
        super.onDestroyView()
        _binding = null
    }
}