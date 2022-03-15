#pragma once

#include <string>

// Class Names
const std::string kM5StackThermoHygrometer = "M5StackThermoHygrometer";
const std::string kCommunicationClient = "CommunicationClient";
const std::string kEventHandler = "EventHandler";
const std::string kGUIManager = "GUIManager";
const std::string kJsonHandler = "JsonHandler";
const std::string kLatestResultViewState = "LatestResultViewState";
const std::string kMeasurementResultManager = "MeasurementResultManager";
const std::string kResultListViewState = "ResultListViewState";
const std::string kSDCardController = "SDCardController";
const std::string kSettingsProvider = "SettingsProvider";
const std::string kThermohygroDataMeasurer = "ThermohygroDataMeasurer";
const std::string kThermohygrometerController = "ThermohygrometerController";
const std::string kViewController = "ViewController";

// Method Names
// CommunicationClient
const std::string kConnectToAws = "ConnectToAws";
const std::string kMqttCallback = "MqttCallback";
const std::string kSendThrmohygroData = "SendThermohygroData";

// EventHandler
const std::string kEventHandle = "EventHandle";
const std::string kAddEvent = "AddEvent";

// GUIManager
const std::string kCheckIfButtonsPressed = "CheckIfButtonsPressed";

// JsonHandler
const std::string kSerialize = "Serialize";
const std::string kParse = "Parse";
const std::string kExtractKeyValuePair = "ExtractKeyValuePair";

// MeasurementResultManager
const std::string kAddMeasurementResult = "AddMeasurementResult";

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

// ThermohygroDataMeasurer
const std::string kReadThermohygroData = "ReadThermohygroData";

// ViewController
const std::string kChangeState = "ChangeState";
const std::string kScrollUp = "ScrollUp";
const std::string kScrollDown = "ScrollDown";
const std::string kDisplayLatestResult = "DisplayLatestResult";
const std::string kDisplayResultList = "DisplayResultList";

// ViewStates
const std::string kInitialize = "Initialize";
const std::string kFinalize = "Finalize";
const std::string kOnMeasureEnvData = "OnMeasureEnvData";
const std::string kDoRightButtonAction = "DoRightButtonAction";
const std::string kDoMiddleButtonAction = "DoMiddleButtonAction";
const std::string kDoLeftButtonAction = "DoLeftButtonAction";