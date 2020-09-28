#ifndef RAY_REFPTR_OBJECT_H
#define RAY_REFPTR_OBJECT_H

namespace ray {
namespace utils {

#include <atomic>

class RayRefCounter {
public:
	explicit RayRefCounter(int count) :count_(count) {}

	RayRefCounter() = delete;
	RayRefCounter(RayRefCounter&) = delete;
	RayRefCounter& operator=(RayRefCounter&) = delete;

	void Inc() const { count_.fetch_add(1); }

	bool Dec() const { return (count_.fetch_sub(1) == 1); }

	bool HasOneRef() const { return count_.load() == 1; }

private:
	mutable std::atomic<int> count_;
};

class RayRefObject {
public:


	virtual void AddRef() const { counter_.Inc(); }

	virtual void Release() const {
		if (counter_.Dec())
			delete this;
	}

	virtual bool HasOneRef() const { return counter_.HasOneRef(); }

protected:
	virtual ~RayRefObject() {}

protected:
	mutable RayRefCounter counter_{ 0 };
};

} // namespace utils
} // namespace ray




#endif
