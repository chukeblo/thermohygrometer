package com.example.androidthermohygrometer;

import android.content.Context;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

public class AssetsReader {
    static String ReadAssetFileFrom(Context context, String path) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(context.getAssets().open(path)));
        StringBuilder settingsJson = new StringBuilder();
        String tmp;
        while ((tmp = reader.readLine()) != null) {
            settingsJson.append(tmp + "\n");
        }
        return settingsJson.toString();
    }
}
