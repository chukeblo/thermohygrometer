#pragma once

#include <GUIContext.hpp>
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

public:
	GUIManager(GUIContext* context);
	~GUIManager();

public:
	GUIManager::MeasureEnvDataListenerImpl* GetMeasureEnvDataListener();
	void CheckIfButtonsPressed();
	void NotifyEnvDataMeasured();

private:
	GUIContext* gui_context_;
};
