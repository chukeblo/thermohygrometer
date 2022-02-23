package com.example.androidthermohygrometer;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;

import com.example.androidthermohygrometer.databinding.ActivityMainBinding;
import com.example.androidthermohygrometer.models.AwsConnectionResources;
import com.example.androidthermohygrometer.models.AwsSettings;
import com.github.mikephil.charting.charts.LineChart;

public class MainActivity extends AppCompatActivity {
    private ActivityMainBinding binding;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        AwsConnectionResources resources = AwsConnectionResourcesProvider.ProvideAwsSettings(getApplicationContext());
    }
}