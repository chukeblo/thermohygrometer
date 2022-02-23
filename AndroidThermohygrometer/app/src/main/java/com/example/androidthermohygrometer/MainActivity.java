package com.example.androidthermohygrometer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.example.androidthermohygrometer.databinding.ActivityMainBinding;
import com.github.mikephil.charting.charts.LineChart;

public class MainActivity extends AppCompatActivity {
    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
    }
}