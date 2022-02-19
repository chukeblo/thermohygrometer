package com.example.androidthermohygrometer;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.Nullable;

import com.amazonaws.mobileconnectors.iot.AWSIotKeystoreHelper;
import com.amazonaws.mobileconnectors.iot.AWSIotMqttManager;
import com.amazonaws.regions.Region;
import com.amazonaws.regions.Regions;
import com.example.androidthermohygrometer.models.AwsSettings;
import com.google.gson.Gson;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.security.KeyStore;

public class AwsIotCommunicationService extends Service {
    private AWSIotMqttManager mqttManager;
    private AwsSettings awsSettings = null;
    private InputStream inputStream = null;
    private BufferedReader bufferedReader = null;

    private static final String SETTINGS_FILENAME = "aws_config.json";
    private static final String CLIENT_ID = "M5StackThermohygrometer";
    private static final String CERT_ID = "m5stack_thermohygrometer_cert";
    private static final String KEY_STORE_NAME = "m5stack_thermohygrometer_key_store";
    private static final String KEY_STORE_PASSWORD = "m5stack_thermohygrometer_key_store_password";

    @Override
    public void onCreate() {
        super.onCreate();

        String settingsJson = assetsFileToString(SETTINGS_FILENAME);
        Gson gson = new Gson();
        awsSettings = gson.fromJson(settingsJson, AwsSettings.class);

        if (awsSettings != null) {
            mqttManager = new AWSIotMqttManager(CLIENT_ID, Region.getRegion(Regions.US_EAST_1), awsSettings.getEndpoint());
        }
        String keyStorePath = getFilesDir().getAbsolutePath();
        if (!AWSIotKeystoreHelper.isKeystorePresent(keyStorePath, KEY_STORE_NAME)) {
            saveCertificateAndPrivateKey(keyStorePath);
        }
        KeyStore keyStore = AWSIotKeystoreHelper.getIotKeystore(CERT_ID, keyStorePath, KEY_STORE_NAME, KEY_STORE_PASSWORD);
        mqttManager.connect(keyStore, (status, throwable) -> Log.d("AwsIotCommunicationSvc", "AWSMqttClientStatusChanged."));
    }

    private void saveCertificateAndPrivateKey(String keyStorePath) {
        String deviceCert = assetsFileToString(awsSettings.getDeviceCertPath());
        String privateKey = assetsFileToString(awsSettings.getPrivateKeyPath());
        AWSIotKeystoreHelper.saveCertificateAndPrivateKey(CERT_ID, deviceCert, privateKey, keyStorePath, KEY_STORE_NAME, KEY_STORE_PASSWORD);
    }

    private String assetsFileToString(String filePath) {
        StringBuilder assetsText = new StringBuilder();
        try {
            inputStream = getApplicationContext().getAssets().open(filePath);
            bufferedReader = new BufferedReader(new InputStreamReader(inputStream));
            String tmp;
            while ((tmp = bufferedReader.readLine()) != null) {
                assetsText.append(tmp);
            }
        } catch (IOException e) {
            System.out.println("exception occurred in reading asset file. filePath="+ filePath + ",reason=" + e.getMessage());
        } finally {
            if (inputStream != null) {
                inputStream = null;
            }
            if (bufferedReader != null) {
                bufferedReader = null;
            }
        }
        return assetsText.toString();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        return START_NOT_STICKY;
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        if (mqttManager != null) {
            mqttManager.disconnect();
        }
    }

    @Nullable
    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }
}
