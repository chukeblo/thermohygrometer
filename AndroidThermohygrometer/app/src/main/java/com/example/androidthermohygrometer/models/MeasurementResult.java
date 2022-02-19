package com.example.androidthermohygrometer.models;

import com.google.gson.annotations.SerializedName;

public class MeasurementResult {

    @SerializedName("time")
    private String time;
    @SerializedName("temperature")
    private String temperature;
    @SerializedName("humidity")
    private String humidity;

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public String getTemperature() {
        return temperature;
    }

    public void setTemperature(String temperature) {
        this.temperature = temperature;
    }

    public String getHumidity() {
        return humidity;
    }

    public void setHumidity(String humidity) {
        this.humidity = humidity;
    }

}