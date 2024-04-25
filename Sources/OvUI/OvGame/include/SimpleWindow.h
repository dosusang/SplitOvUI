#pragma once
#include <OvWindowing/Context/Device.h>
#include <OvWindowing/Window.h>
#include <OvUI/Core/UIManager.h>
#include <OvUI/Panels/PanelWindow.h>

class SimpleWindow
{
public:
	SimpleWindow();

	void Run();

	void SetupContext();
private:

	std::unique_ptr<OvWindowing::Context::Device>		m_device;
	std::unique_ptr<OvWindowing::Window>				m_window;
	std::unique_ptr<OvUI::Core::UIManager>				m_uiManager;
	OvUI::Modules::Canvas m_canvas;
	std::unique_ptr<OvUI::Panels::PanelWindow>			m_mainPanel;
};
