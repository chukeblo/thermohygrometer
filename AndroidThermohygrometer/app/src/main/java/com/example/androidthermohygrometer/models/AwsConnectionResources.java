package com.example.androidthermohygrometer.models;

public class AwsConnectionResources {
    private final String clientId;
    private final String endpoint;
    private final String topic;
    private final String rootCa;
    private final String deviceCert;
    private final String privateKey;

    public AwsConnectionResources(String clientId, String endpoint, String topic, String rootCa, String deviceCert, String privateKey) {
        this.clientId = clientId;
        this.endpoint = endpoint;
        this.topic = topic;
        this.rootCa = rootCa;
        this.deviceCert = deviceCert;
        this.privateKey = privateKey;
    }

    public String getClientId() {
        return this.clientId;
    }

    public String getEndpoint() {
        return this.endpoint;
    }

    public String getTopic() {
        return this.topic;
    }

    public String getRootCa() {
        return this.rootCa;
    }

    public String getDeviceCert() {
        return this.deviceCert;
    }

    public String getPrivateKey() {
        return this.privateKey;
    }
}
