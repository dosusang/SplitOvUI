#include "SimpleWindow.h"
#include <OvUI/Widgets/Texts/Text.h>
#include <OvUI/Widgets/Visual/Separator.h>
#include <OvUI/Widgets/Layout/Columns.h>
#include <OvUI/Widgets/Layout/Spacing.h>
#include <OvUI/Widgets/Layout/Group.h>
#include <OvUI/Widgets/Buttons/Button.h>
#include <OvUI/Widgets/InputFields/InputText.h>


#include <GL/glew.h>
class RenderDriver {
public:
	RenderDriver() {
		glewInit();
	}

	~RenderDriver() {
	}
};


class MainPanel : public OvUI::Panels::PanelWindow {
public:

	MainPanel() {
		resizable = false;
		movable = false;
		titleBar = false;

		SetSize({ 1000, 580 });
		SetPosition({ 0.f, 0.f });

		auto& openProjectButton = CreateWidget<OvUI::Widgets::Buttons::Button>("Open Project");
		auto& newProjectButton = CreateWidget<OvUI::Widgets::Buttons::Button>("New Project");
		auto& pathField = CreateWidget<OvUI::Widgets::InputFields::InputText>("");
		auto& m_goButton = CreateWidget<OvUI::Widgets::Buttons::Button>("GO");
	}

	void Draw() override
	{
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, { 50.f, 50.f });
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);

		OvUI::Panels::PanelWindow::Draw();

		ImGui::PopStyleVar(2);
	}
};

SimpleWindow::SimpleWindow() {
	SetupContext();
	m_mainPanel = std::make_unique<MainPanel>();

	m_uiManager->SetCanvas(m_canvas);
	m_canvas.AddPanel(*m_mainPanel);
};

void SimpleWindow::SetupContext() {
	/* Settings */
	OvWindowing::Settings::DeviceSettings deviceSettings;
	OvWindowing::Settings::WindowSettings windowSettings;
	windowSettings.title = "TestWindow";
	windowSettings.width = 1000;
	windowSettings.height = 580;
	windowSettings.maximized = false;
	windowSettings.resizable = false;
	windowSettings.decorated = true;

	/* Window creation */
	m_device = std::make_unique<OvWindowing::Context::Device>(deviceSettings);
	m_window = std::make_unique<OvWindowing::Window>(*m_device, windowSettings);
	m_window->MakeCurrentContext();

	auto [monWidth, monHeight] = m_device->GetMonitorSize();
	auto [winWidth, winHeight] = m_window->GetSize();
	m_window->SetPosition(monWidth / 2 - winWidth / 2, monHeight / 2 - winHeight / 2);

	/* Graphics context creation */
	// 其实这里对于渲染API的封装不是很有意义，OvUI本身是基于GlfwWindow的，也就是依赖于OpenGL，如果不修改window其实是无法支持更多的渲染API的
	auto driver = std::make_unique<RenderDriver>();

	m_uiManager = std::make_unique<OvUI::Core::UIManager>(m_window->GetGlfwWindow(), OvUI::Styling::EStyle::ALTERNATIVE_DARK);
	//m_uiManager->LoadFont("Ruda_Big", "Data\\Editor\\Fonts\\Ruda-Bold.ttf", 18);
	//m_uiManager->UseFont("Ruda_Big");
	m_uiManager->EnableEditorLayoutSave(false);
	m_uiManager->EnableDocking(false);
};

void SimpleWindow::Run() {
	while (!m_window->ShouldClose())
	{
		m_device->PollEvents();
		m_uiManager->Render();
		m_window->SwapBuffers();

		if (!m_mainPanel->IsOpened())
			m_window->SetShouldClose(true);
	}
};
