package com.example.androidthermohygrometer;

import android.content.Context;
import android.util.Log;

import com.example.androidthermohygrometer.models.AwsConnectionResources;
import com.example.androidthermohygrometer.models.AwsSettings;
import com.google.gson.Gson;

import java.io.IOException;

public class AwsConnectionResourcesProvider {
    private static final String TAG = "AwsConnRscsProvider";
    private static final String SETTINGS_PATH = "aws_config.json";
    private static final String AWS_CONFIG_DIR = "aws_certs/";

    static AwsConnectionResources ProvideAwsConnectionResources(Context context) {
        try {
            String settingsJson = AssetsReader.ReadAssetFileFrom(context, SETTINGS_PATH);
            Log.d(TAG, settingsJson);
            Gson gson = new Gson();
            AwsSettings settings = gson.fromJson(settingsJson, AwsSettings.class);
            String rootCa = AssetsReader.ReadAssetFileFrom(context, AWS_CONFIG_DIR + settings.getRootCaPath());
            String deviceCert = AssetsReader.ReadAssetFileFrom(context, AWS_CONFIG_DIR + settings.getDeviceCertPath());
            String privateKey = AssetsReader.ReadAssetFileFrom(context, AWS_CONFIG_DIR + settings.getPrivateKeyPath());
            AwsConnectionResources resources = new AwsConnectionResources();
            resources.setEndpoint(settings.getEndpoint());
            resources.setPort(settings.getPort());
            resources.setRootCa(rootCa);
            resources.setDeviceCert(deviceCert);
            resources.setPrivateKey(privateKey);
            return resources;
        } catch (IOException e) {
            Log.e(TAG, e.toString());
        }
        return null;
    }
}
