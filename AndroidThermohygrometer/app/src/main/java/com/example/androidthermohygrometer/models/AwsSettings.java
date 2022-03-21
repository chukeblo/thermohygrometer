package com.example.androidthermohygrometer.models;

import com.google.gson.annotations.SerializedName;

public class AwsSettings {

    @SerializedName("clientId")
    private String clientId;
    @SerializedName("endpoint")
    private String endpoint;
    @SerializedName("rootCaPath")
    private String rootCaPath;
    @SerializedName("deviceCertPath")
    private String deviceCertPath;
    @SerializedName("privateKeyPath")
    private String privateKeyPath;

    public String getClientId() {
        return clientId;
    }

    public void setPort(String clientId) {
        this.clientId = clientId;
    }

    public String getEndpoint() {
        return endpoint;
    }

    public void setEndpoint(String endpoint) {
        this.endpoint = endpoint;
    }

    public String getRootCaPath() {
        return rootCaPath;
    }

    public void setRootCaPath(String rootCaPath) {
        this.rootCaPath = rootCaPath;
    }

    public String getDeviceCertPath() {
        return deviceCertPath;
    }

    public void setDeviceCertPath(String deviceCertPath) {
        this.deviceCertPath = deviceCertPath;
    }

    public String getPrivateKeyPath() {
        return privateKeyPath;
    }

    public void setPrivateKeyPath(String privateKeyPath) {
        this.privateKeyPath = privateKeyPath;
    }

}