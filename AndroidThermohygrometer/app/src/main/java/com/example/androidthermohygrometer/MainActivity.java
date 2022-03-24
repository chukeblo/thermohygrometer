package com.example.androidthermohygrometer;

import android.content.Intent;
import android.content.IntentFilter;
import android.graphics.Color;
import android.graphics.DashPathEffect;
import android.os.Bundle;
import android.util.Log;

import androidx.appcompat.app.AppCompatActivity;

import com.example.androidthermohygrometer.databinding.ActivityMainBinding;
import com.example.androidthermohygrometer.models.MeasurementResult;
import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;

public class MainActivity extends AppCompatActivity {
    private ActivityMainBinding binding;
    private LineChart lineChart;
    private MeasurementResultReceiver receiver;

    private static final int MAX_LABEL_COUNTS = 2;
    private static final String[] LABELS = {"temperature", "humidity"};
    private static final int[] COLORS = {Color.RED, Color.BLUE};

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        lineChart = binding.lineChart;

        prepareChart();

        receiver = new MeasurementResultReceiver((result -> {
            Log.d("MeasurementResultCb", "onMeasurementResult: in");
            addChartEntry(result);
        }));
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction(IntentServiceConstants.ActionName.RECEIVE_MEASUREMENT_RESULT);
        registerReceiver(receiver, intentFilter);

        binding.subscribeButton.setOnClickListener(view -> {
            Log.d("subscribeButton", "onClick: request subscribing topic");
            startService(new Intent(getBaseContext(), AwsIotCommunicationService.class));
        });

        binding.unsubscribeButton.setOnClickListener(view -> {
            Log.d("unsubscribeButton", "onClick: request unsubscribing topic");
            stopService(new Intent(getBaseContext(), AwsIotCommunicationService.class));
        });
    }

    private void prepareChart() {
        lineChart.setDrawGridBackground(true);
        lineChart.getDescription().setEnabled(true);
        XAxis xAxis = lineChart.getXAxis();
        xAxis.enableAxisLineDashedLine(10.0f, 10.0f, 0.0f);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        YAxis yAxis = lineChart.getAxisLeft();
        yAxis.setAxisMaximum(150.0f);
        yAxis.setAxisMinimum(0.0f);
        yAxis.enableGridDashedLine(10.0f, 10.0f, 0.0f);
        yAxis.setDrawZeroLine(true);
        lineChart.getAxisRight().setEnabled(false);
        lineChart.setData(new LineData());
    }

    private void addChartEntry(MeasurementResult result) {
        float[] data = {Float.parseFloat(result.getTemperature()), Float.parseFloat(result.getHumidity())};

        LineData lineData = lineChart.getLineData();
        if (lineData == null) {
            return;
        }

        for (int i = 0; i < MAX_LABEL_COUNTS; i++) {
            ILineDataSet dataSet = lineData.getDataSetByIndex(i);
            if (dataSet == null) {
                dataSet = createLineDataSet(LABELS[i], COLORS[i]);
                lineData.addDataSet(dataSet);
            }
            lineData.addEntry(new Entry(dataSet.getEntryCount(), data[i]), i);
            lineData.notifyDataChanged();
        }
        lineChart.notifyDataSetChanged();
        lineChart.setVisibleXRangeMaximum(50.f);
        lineChart.moveViewToX(lineData.getEntryCount());
    }

    private LineDataSet createLineDataSet(String label, int color) {
        LineDataSet lineDataSet = new LineDataSet(null, label);

        // set properties for LineDataSet instance
        lineDataSet.setDrawIcons(false);
        lineDataSet.setColor(color);
        lineDataSet.setCircleColor(color);
        lineDataSet.setLineWidth(1f);
        lineDataSet.setCircleRadius(3f);
        lineDataSet.setDrawCircleHole(false);
        lineDataSet.setValueTextSize(0f);
        lineDataSet.setDrawFilled(true);
        lineDataSet.setFormLineWidth(1f);
        lineDataSet.setFormLineDashEffect(new DashPathEffect(new float[]{10f, 5f}, 0f));
        lineDataSet.setFormSize(15.f);

        return lineDataSet;
    }
}