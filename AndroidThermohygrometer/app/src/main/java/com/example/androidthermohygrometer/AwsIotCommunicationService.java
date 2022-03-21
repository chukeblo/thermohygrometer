package com.example.androidthermohygrometer;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;
import android.util.Log;

import androidx.annotation.Nullable;

import com.amazonaws.mobileconnectors.iot.AWSIotKeystoreHelper;
import com.amazonaws.mobileconnectors.iot.AWSIotMqttClientStatusCallback;
import com.amazonaws.mobileconnectors.iot.AWSIotMqttManager;
import com.amazonaws.mobileconnectors.iot.AWSIotMqttQos;
import com.amazonaws.regions.Region;
import com.amazonaws.regions.Regions;
import com.example.androidthermohygrometer.models.AwsConnectionResources;

import java.security.KeyStore;

public class AwsIotCommunicationService extends Service {
    private AWSIotMqttManager mqttManager;
    private AwsConnectionResources awsConnectionResources = null;
    private KeyStore keyStore;
    private boolean isConnected = false;

    private static final String TAG = "AwsIotCommService";
    private static final String CERT_ID = "m5stack_thermohygrometer_cert";
    private static final String KEY_STORE_NAME = "m5stack_thermohygrometer_key_store";
    private static final String KEY_STORE_PASSWORD = "m5stack_thermohygrometer_key_store_password";
    private static final String ACTION_NAME = "RECEIVE_MEASUREMENT_RESULT";

    @Override
    public void onCreate() {
        super.onCreate();
        Log.i(TAG, "onCreate: in");

        awsConnectionResources = AwsConnectionResourcesProvider.ProvideAwsConnectionResources(getApplicationContext());

        if (awsConnectionResources != null) {
            mqttManager = new AWSIotMqttManager(awsConnectionResources.getClientId(), Region.getRegion(Regions.US_EAST_1), awsConnectionResources.getEndpoint());
        }
        String keyStorePath = getFilesDir().getAbsolutePath();
        if (!AWSIotKeystoreHelper.isKeystorePresent(keyStorePath, KEY_STORE_NAME)) {
            saveCertificateAndPrivateKey(keyStorePath);
        }
        keyStore = AWSIotKeystoreHelper.getIotKeystore(CERT_ID, keyStorePath, KEY_STORE_NAME, KEY_STORE_PASSWORD);
        mqttManager.connect(keyStore, (status, throwable) -> {
            Log.d(TAG, "onStatusChanged: status=" + status);
            isConnected = status == AWSIotMqttClientStatusCallback.AWSIotMqttClientStatus.Connected;
        });

        while (!isConnected) {
            try {
                Thread.sleep(10);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        mqttManager.subscribeToTopic(awsConnectionResources.getTopic(), AWSIotMqttQos.QOS0, (topic, data) -> {
            String message = new String(data);
            Log.i(TAG, "onMessageArrived: topic=" + topic + ", data=" + message);
            Intent intent = new Intent();
            intent.putExtra("json", message);
            intent.setAction(ACTION_NAME);
            getBaseContext().sendBroadcast(intent);
        });
    }

    private void saveCertificateAndPrivateKey(String keyStorePath) {
        String deviceCert = awsConnectionResources.getDeviceCert();
        String privateKey = awsConnectionResources.getPrivateKey();
        AWSIotKeystoreHelper.saveCertificateAndPrivateKey(CERT_ID, deviceCert, privateKey, keyStorePath, KEY_STORE_NAME, KEY_STORE_PASSWORD);
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
