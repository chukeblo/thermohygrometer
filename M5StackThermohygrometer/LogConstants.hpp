#pragma once

#include <string>

// Class Names
const std::string kM5StackThermoHygrometer = "M5StackThermoHygrometer";
const std::string kButtonInputWatcher = "ButtonInputWatcher";
const std::string kEventHandler = "EventHandler";
const std::string kJsonHandler = "JsonHandler";
const std::string kCommunicationClient = "CommunicationClient";
const std::string kSDCardController = "SDCardController";
const std::string kSettingsProvider = "SettingsProvider";
const std::string kThermohygrometerController = "ThermohygrometerController";
const std::string kThermohygroDataMeasurer = "ThermohygroDataMeasurer";

// Method Names
// ButtonInputWatcher
const std::string kSetUpButtonInterruption = "SetUpButtonInterruption";
const std::string kOnButtonPressed = "OnButtonPressed";

// EventHandler
const std::string kEventHandle = "EventHandle";
const std::string kAddEvent = "AddEvent";

// JsonHandler
const std::string kSerialize = "Serialize";
const std::string kParse = "Parse";
const std::string kExtractKeyValuePair = "ExtractKeyValuePair";

// CommunicationClient
const std::string kPrepare = "Prepare";
const std::string kConnectToWiFi = "ConnectToWiFi";

// SDCardController
const std::string kReadTextFromSDCard = "ReadTextFromSDCard";

// SettingsProvider
const std::string kReadThermohygrometerSettings = "ReadThermohygrometerSettings";
const std::string kReadCommunicationSettings = "CommunicationSettings";
const std::string kReadWiFiSettings = "ReadWiFiSettings";
const std::string kReadAWSSettings = "ReadAWSSettings";

// Thermohygrometer Module
const std::string kReadThermohygroData = "ReadThermohygroData";