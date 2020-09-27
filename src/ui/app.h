#pragma once
namespace ray {
namespace app {

class MiscThread : public nbase::FrameworkThread
{
public:
	MiscThread(enum ThreadId thread_id, const char *name)
		: FrameworkThread(name)
		, thread_id_(thread_id) {}

	~MiscThread(void) {}

private:
	virtual void Init() override { nbase::ThreadManager::RegisterThread(thread_id_); }

	virtual void Cleanup() override { nbase::ThreadManager::UnregisterThread(); }

private:
	enum ThreadId thread_id_;
};

class AppThread :public nbase::FrameworkThread
{
public:
	AppThread() :nbase::FrameworkThread("AppThread") {}

	virtual ~AppThread() {}

private:
	virtual void Init() override;

	virtual void Cleanup() override;

private:
	std::unique_ptr<MiscThread>	ui_thread_;
	std::unique_ptr<MiscThread>	misc_thread_;
};

} // namespace app
} // namespace ray