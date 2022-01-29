#pragma once

#include <string>

// Class Names
const std::string kM5StackThermoHygrometer = "M5StackThermoHygrometer";
const std::string kButtonInputWatcher = "ButtonInputWatcher";
const std::string kEnvironmentDataCollector = "EnvironmentDataCollector";
const std::string kEnvironmentDataReader = "EnvironmentDataReader";
const std::string kEventHandler = "EventHandler";
const std::string kJsonHandler = "JsonHandler";
const std::string kNetworkController = "NetworkController";
const std::string kSDCardController = "SDCardController";

// Method Names
// ButtonInputWatcher
const std::string kSetUpButtonInterruption = "SetUpButtonInterruption";
const std::string kOnButtonPressed = "OnButtonPressed";

// EnvironmentDataController
const std::string kCollectData = "CollectData";

// EnvironmentDataReader
const std::string kReadThermohydroData = "ReadThermohydroData";

// EventHandler
const std::string kEventHandle = "EventHandle";
const std::string kAddEvent = "AddEvent";

// JsonHandler
const std::string kParse = "Parse";
const std::string kExtractKeyValuePair = "ExtractKeyValuePair";

// NetworkController
const std::string kPrepare = "Prepare";
const std::string kConnectToWiFi = "ConnectToWiFi";

// SDCardController
const std::string kReadNetworkSettings = "ReadNetworkSettings";
const std::string kReadAWSConfig = "ReadAWSConfig";