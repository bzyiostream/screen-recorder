#include "stdafx.h"
#include "setting_view.h"

namespace ray {
namespace app {
namespace view {

const std::wstring SettingView::kClassName = L"SettingView";

std::wstring SettingView::GetSkinFolder()
{
	return L"setting";
}

std::wstring SettingView::GetSkinFile()
{
	return L"setting.xml";
}

std::wstring SettingView::GetWindowClassName(void) const
{
	return kClassName;
}

void SettingView::InitWindow()
{

	m_pRoot->AttachBubbledEvent(ui::kEventAll, std::bind(&SettingView::Notify, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind(&SettingView::OnClicked, this, std::placeholders::_1));
}

LRESULT SettingView::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

//not use for now
void SettingView::SyncShowModal()
{
	ShowModalFake(parent_);
}


bool SettingView::Notify(ui::EventArgs * msg)
{
	return true;
}

bool SettingView::OnClicked(ui::EventArgs * msg)
{
	auto name = msg->pSender->GetName();
	if (name == L"closebtn") {
	}

	return true;
}

void SettingView::ShowSettingView(HWND parent, bool is_center)
{
	SettingView *setting_view = new SettingView(parent);
	setting_view->Create(parent, SettingView::kClassName.c_str(), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZE, 0);

	if(is_center)
		setting_view->CenterWindow();

	//nim_comp::AsyncDoModal(setting_view);

	setting_view->ShowModalFake(parent);
}

}
}
}