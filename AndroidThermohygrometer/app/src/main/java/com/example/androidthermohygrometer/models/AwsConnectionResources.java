package com.example.androidthermohygrometer.models;

public class AwsConnectionResources {
    private String endpoint;
    private String port;
    private String rootCa;
    private String deviceCert;
    private String privateKey;

    public String getEndpoint() { return this.endpoint; }

    public void setEndpoint(String endpoint) { this.endpoint = endpoint; }

    public String getPort() { return this.port; }

    public void setPort(String port) { this.port = port; }

    public String getRootCa() { return this.rootCa; }

    public void setRootCa(String rootCa) { this.rootCa = rootCa; }

    public String getDeviceCert() { return this.deviceCert; }

    public void setDeviceCert(String deviceCert) { this.deviceCert = deviceCert; }

    public String getPrivateKey() { return this.privateKey; }

    public void setPrivateKey(String privateKey) { this.privateKey = privateKey; }
}
