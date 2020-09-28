#ifndef RAY_REFPTR_H
#define RAY_REFPTR_H

namespace ray {

template<class T>
class ray_refptr {
public:
	typedef T element_type;

	ray_refptr() : ptr_(NULL) {}

	ray_refptr(T* p) : ptr_(p) {
		if (ptr_)
			ptr_->AddRef();
	}

	ray_refptr(const ray_refptr<T>& r) : ptr_(r.ptr_) {
		if (ptr_)
			ptr_->AddRef();
	}

	template <typename U>
	ray_refptr(const ray_refptr<U>& r) : ptr_(r.get()) {
		if (ptr_)
			ptr_->AddRef();
	}

	~ray_refptr() {
		if (ptr_)
			ptr_->Release();
	}

	T* get() const { return ptr_; }

	// Allow ray_refptr<C> to be used in boolean expression
	// and comparison operations.
	operator T*() const { return ptr_; }

	T* operator->() const {
		assert(ptr_ != NULL);
		return ptr_;
	}

	ray_refptr<T>& operator=(T* p) {
		// AddRef first so that self assignment should work
		if (p)
			p->AddRef();
		T* old_ptr = ptr_;
		ptr_ = p;
		if (old_ptr)
			old_ptr->Release();
		return *this;
	}

	ray_refptr<T>& operator=(const ray_refptr<T>& r) {
		return *this = r.ptr_;
	}

	template <typename U>
	ray_refptr<T>& operator=(const ray_refptr<U>& r) {
		return *this = r.get();
	}

	void swap(T** pp) {
		T* p = ptr_;
		ptr_ = *pp;
		*pp = p;
	}

	void swap(ray_refptr<T>& r) { swap(&r.ptr_); }

protected:
	T* ptr_;
};

template <typename T>
ray_refptr<T> make_ray_refptr(T* t) {
	return ray_refptr<T>(t);
}

} //namespace ray




#endif
