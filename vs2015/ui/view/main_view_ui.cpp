#include "stdafx.h"
#include "main_view.h"

#include "resource.h"

namespace ray {
namespace app {
namespace view {

const std::wstring MainView::kClassName = L"MainView";

MainView::MainView()
{
}

MainView::~MainView()
{
}

std::wstring MainView::GetSkinFolder()
{
	return L"main";
}

std::wstring MainView::GetSkinFile()
{
	return L"main.xml";
}

std::wstring MainView::GetWindowClassName(void) const
{
	return kClassName;
}

void MainView::InitWindow()
{
	SetIcon(IDI_ICON);

	m_pRoot->AttachBubbledEvent(ui::kEventAll, nbase::Bind(&MainView::Notify, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, nbase::Bind(&MainView::OnClicked, this, std::placeholders::_1));
}

LRESULT MainView::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void MainView::ShowMainView()
{
	MainView *main_view = new MainView();
	main_view->Create(NULL, MainView::kClassName.c_str(), WS_OVERLAPPEDWINDOW & WS_MINIMIZEBOX, 0);

	main_view->CenterWindow();
	main_view->ShowWindow();
}

bool MainView::Notify(ui::EventArgs * msg)
{
	return false;
}

bool MainView::OnClicked(ui::EventArgs * msg)
{
	return false;
}

}
}
}