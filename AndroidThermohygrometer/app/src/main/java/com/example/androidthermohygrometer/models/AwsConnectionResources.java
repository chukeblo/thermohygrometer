package com.example.androidthermohygrometer.models;

public class AwsConnectionResources {
    private String clientId;
    private String endpoint;
    private String topic;
    private String rootCa;
    private String deviceCert;
    private String privateKey;

    public AwsConnectionResources(String clientId, String endpoint, String topic, String rootCa, String deviceCert, String privateKey) {
        this.clientId = clientId;
        this.endpoint = endpoint;
        this.topic = topic;
        this.rootCa = rootCa;
        this.deviceCert = deviceCert;
        this.privateKey = privateKey;
    }

    public String getClientId() { return this.clientId; }

    public void setClientId(String clientId) { this.clientId = clientId; }

    public String getEndpoint() { return this.endpoint; }

    public void setEndpoint(String endpoint) { this.endpoint = endpoint; }

    public String getTopic() { return this.topic; }

    public void setTopic(String topic) { this.topic = topic; }

    public String getRootCa() { return this.rootCa; }

    public void setRootCa(String rootCa) { this.rootCa = rootCa; }

    public String getDeviceCert() { return this.deviceCert; }

    public void setDeviceCert(String deviceCert) { this.deviceCert = deviceCert; }

    public String getPrivateKey() { return this.privateKey; }

    public void setPrivateKey(String privateKey) { this.privateKey = privateKey; }
}
