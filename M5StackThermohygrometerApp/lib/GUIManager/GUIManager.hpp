#pragma once

#include <ThermohygroDataMeasurer.hpp>
#include <ViewController.hpp>

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
	GUIManager(ViewController* view_controller);
	~GUIManager();

public:
	GUIManager::MeasureEnvDataListenerImpl* GetMeasureEnvDataListener();
	void CheckIfButtonsPressed();
	void NotifyEnvDataMeasured();

private:
	ViewController* view_controller_;
};
