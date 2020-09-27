#pragma once

namespace ray {
namespace app {
namespace view {

class SettingView : public ModalWndBase,
	public ui::WindowImplBase {
public:
	SettingView(HWND parent) :parent_(parent) {}
	~SettingView() {}

	virtual std::wstring GetSkinFolder() override;

	virtual std::wstring GetSkinFile() override;

	virtual std::wstring GetWindowClassName(void) const override;

	virtual void InitWindow() override;

	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;

	// async show this, not use for now
	virtual void SyncShowModal() override;

private:
	bool Notify(ui::EventArgs* msg);

	bool OnClicked(ui::EventArgs* msg);

public:
	static void ShowSettingView(HWND parent, bool is_center = true);

private:
	static const std::wstring kClassName;

	HWND parent_;
};

}
}
}