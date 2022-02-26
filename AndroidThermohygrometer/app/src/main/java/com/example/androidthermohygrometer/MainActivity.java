package com.example.androidthermohygrometer;

import androidx.appcompat.app.AppCompatActivity;

import android.graphics.Color;
import android.graphics.DashPathEffect;
import android.os.Bundle;

import com.example.androidthermohygrometer.databinding.ActivityMainBinding;
import com.example.androidthermohygrometer.models.AwsConnectionResources;
import com.example.androidthermohygrometer.models.AwsSettings;
import com.github.mikephil.charting.charts.LineChart;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.Entry;
import com.github.mikephil.charting.data.LineData;
import com.github.mikephil.charting.data.LineDataSet;
import com.github.mikephil.charting.interfaces.datasets.ILineDataSet;

import java.util.ArrayList;

public class MainActivity extends AppCompatActivity {
    private ActivityMainBinding binding;
    private LineChart lineChart;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        lineChart = binding.lineChart;

        lineChart.setDrawGridBackground(true);
        lineChart.getDescription().setEnabled(true);
        XAxis xAxis = lineChart.getXAxis();
        xAxis.enableAxisLineDashedLine(10.0f, 10.0f,0.0f);
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM);
        YAxis yAxis = lineChart.getAxisLeft();
        yAxis.setAxisMaximum(150.0f);
        yAxis.setAxisMinimum(0.0f);
        yAxis.enableGridDashedLine(10.0f, 10.0f, 0.0f);
        yAxis.setDrawZeroLine(true);
        lineChart.getAxisRight().setEnabled(false);

        setData();

        AwsConnectionResources resources = AwsConnectionResourcesProvider.ProvideAwsSettings(getApplicationContext());
    }

    private void setData() {
        // Entry()を使ってLineDataSetに設定できる形に変更してarrayを新しく作成
        int[] data = {116, 111, 112, 121, 102, 83,
                99, 101, 74, 105, 120, 112,
                109, 102, 107, 93, 82, 99, 110,
        };

        ArrayList<Entry> values = new ArrayList<>();

        for (int i = 0; i < data.length; i++) {
            values.add(new Entry(i, data[i], null, null));
        }

        LineDataSet set1;

        if (lineChart.getData() != null &&
                lineChart.getData().getDataSetCount() > 0) {

            set1 = (LineDataSet) lineChart.getData().getDataSetByIndex(0);
            set1.setValues(values);
            lineChart.getData().notifyDataChanged();
            lineChart.notifyDataSetChanged();
        } else {
            set1 = new LineDataSet(values, "DataSet");

            set1.setDrawIcons(false);
            set1.setColor(Color.BLACK);
            set1.setCircleColor(Color.BLACK);
            set1.setLineWidth(1f);
            set1.setCircleRadius(3f);
            set1.setDrawCircleHole(false);
            set1.setValueTextSize(0f);
            set1.setDrawFilled(true);
            set1.setFormLineWidth(1f);
            set1.setFormLineDashEffect(new DashPathEffect(new float[]{10f, 5f}, 0f));
            set1.setFormSize(15.f);

            set1.setFillColor(Color.BLUE);

            ArrayList<ILineDataSet> dataSets = new ArrayList<ILineDataSet>();
            dataSets.add(set1);

            LineData lineData = new LineData(dataSets);

            lineChart.setData(lineData);
        }
    }
}