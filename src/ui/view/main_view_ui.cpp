#include "stdafx.h"
#include "main_view.h"

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
}

LRESULT MainView::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

}
}
}