package com.example.androidthermohygrometer;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.util.Log;

import com.example.androidthermohygrometer.models.MeasurementResult;
import com.google.gson.Gson;

public class MeasurementResultReceiver extends BroadcastReceiver {
    private final MeasurementResultCallback callback;
    private static final String TAG = "MeasurementResultRcver";

    public MeasurementResultReceiver(MeasurementResultCallback callback) {
        this.callback = callback;
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        String json = intent.getExtras().getString(IntentServiceConstants.ExtraKey.MEASUREMENT_RESULT);
        MeasurementResult result = new Gson().fromJson(json, MeasurementResult.class);
        Log.d(TAG, "onReceive: time=" + result.getTime() + ",temperature=" + result.getTemperature() + ",humidity=" + result.getHumidity());
        callback.onMeasurementResult(result);
    }

    public interface MeasurementResultCallback {
        void onMeasurementResult(MeasurementResult result);
    }
}
