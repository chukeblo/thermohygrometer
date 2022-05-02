#pragma once

#include <ButtonType.hpp>
#include <ThermohygroDataMeasurer.hpp>

class GUIManager
{
public:
	class MeasureEnvDataListenerImpl : public ThermohygroDataMeasurer::MeasureEnvDataListener
	{
	public:
		MeasureEnvDataListenerImpl(GUIManager* gui_manager);
		~MeasureEnvDataListenerImpl() override {}

	public:
		void OnMeasureEnvData() override;

	private:
		GUIManager* gui_manager_;
	};

	class GUIEventListener
	{
	public:
		GUIEventListener() {}
		virtual ~GUIEventListener() {}

	public:
		virtual void OnButtonPressed(ButtonType type) = 0;
		virtual void OnMeasureEnvData() = 0;
	};

public:
	GUIManager(GUIEventListener* gui_event_listener);
	~GUIManager();

public:
	GUIManager::MeasureEnvDataListenerImpl* GetMeasureEnvDataListener();
	void CheckIfButtonsPressed();
private:
	void NotifyEnvDataMeasured();

private:
	GUIEventListener* gui_event_listener_;
};
