#include "stdafx.h"

#include "app.h"
#include "view\main_view.h"

namespace ray {
namespace app {

void AppThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadApp);

	ui_thread_.reset(new MiscThread(kThreadUI, "UIThread"));
	ui_thread_->Start();

	misc_thread_.reset(new MiscThread(kThreadGlobalMisc, "MiscThread"));
	misc_thread_->Start();

	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();

#ifdef _DEBUG
	ui::GlobalManager::Startup(theme_dir + L"..\\..\\..\\src\\ui\\resources\\", ui::CreateControlCallback(), false,
		L"themes\\default", L"lang\\en_US");
#else
	ui::GlobalManager::Startup(theme_dir + L"resources\\", ui::CreateControlCallback(), false,
		L"themes\\default", L"lang\\zh_CN");
#endif

	view::MainView::ShowMainView();
}

void AppThread::Cleanup()
{
	ui::GlobalManager::Shutdown();

	misc_thread_->Stop();
	misc_thread_.reset(nullptr);

	ui_thread_->Stop();
	ui_thread_.reset(nullptr);

	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}

}
}

