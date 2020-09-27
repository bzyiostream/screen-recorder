#include "stdafx.h"
#include "main_view.h"
#include "setting_view.h"



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

	m_pRoot->AttachBubbledEvent(ui::kEventAll, std::bind(&MainView::Notify, this, std::placeholders::_1));
	m_pRoot->AttachBubbledEvent(ui::kEventClick, std::bind(&MainView::OnClicked, this, std::placeholders::_1));
}

LRESULT MainView::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

bool MainView::Notify(ui::EventArgs * msg)
{
	return true;
}

bool MainView::OnClicked(ui::EventArgs * msg)
{
	auto name = msg->pSender->GetName();

	if (name == L"settings") {

		view::SettingView::ShowSettingView(m_hWnd);

		return true;

		nim_comp::Toast::ShowToast(L"TEST TOAST", 1000, m_hWnd);

		std::wstring file_type = L"文件格式";
		std::wstring text = nbase::StringPrintf(L"%s(*.db)", file_type.c_str());
		std::wstring file_exten = L".db";
		std::wstring file_name;

		nim_comp::CFileDialogEx* file_dlg = new nim_comp::CFileDialogEx();
		std::map<LPCTSTR, LPCTSTR> filters;
		filters[text.c_str()] = L"*.db";
		file_dlg->SetFilter(filters);
		file_dlg->SetFileName(file_name.c_str());
		file_dlg->SetDefExt(file_exten.c_str());
		file_dlg->SetParentWnd(GetHWND());

		auto msg_cb = [](nim_comp::MsgBoxRet) {

		};

		auto cb = [this,msg_cb](bool, std::wstring) {
		
			nim_comp::ShowMsgBox(this->GetHWND(), msg_cb,
				L"TEST MSG BOX", false,
				L"Try to show", false,
				L"ok", false,
				L"no", false);
		};

		file_dlg->AyncShowSaveFileDlg(cb);

	}

	return true;
}

void MainView::ShowMainView()
{
	MainView *main_view = new MainView();
	main_view->Create(NULL, MainView::kClassName.c_str(), WS_OVERLAPPEDWINDOW & WS_MINIMIZEBOX, 0);

	main_view->CenterWindow();
	main_view->ShowWindow();
}

}
}
}