#pragma once


namespace task {

    template<class T>
    class UniquePtr {
        T *ptr;

    public:
        explicit UniquePtr(T *ptr = nullptr) noexcept: ptr(ptr) {}

        UniquePtr(UniquePtr &&other) noexcept: ptr(other.ptr) {
            other.ptr = nullptr;
        }

        UniquePtr &operator=(UniquePtr &&other) noexcept {
            if (&other != this) {
                delete ptr;
                ptr = other.ptr;
                other.ptr = nullptr;
            }
            return *this;
        }

        UniquePtr(UniquePtr &other) = delete;

        UniquePtr &operator=(const UniquePtr &other) = delete;

        ~UniquePtr() {
            delete ptr;
        }

        T &operator*() {
            return *ptr;
        }

        T *operator->() {
            return get();
        }

        T *get() {
            return ptr;
        }

        T *release() noexcept {
            T *temp = ptr;
            ptr = nullptr;
            return temp;
        }

        void reset(T *newPtr) {
            swap(ptr, newPtr);
            if (ptr == newPtr) {
                ptr = nullptr;
            }
            delete ptr;
        }

        void swap(UniquePtr &other) noexcept {
            std::swap(ptr, other.ptr);
        }
    };

    template<class T>
    class WeakPtr;

    template<class T>
    struct ControlBlock {
        T *ptr;
        size_t shared_count;
        size_t weak_count;

        explicit ControlBlock(T *ptr) : ptr(ptr), shared_count(1), weak_count(0) {}
    };

    template<class T>
    class SharedPtr {
    public:
        ControlBlock<T> *cb;

        explicit SharedPtr(T *ptr = nullptr) noexcept {
            cb = new ControlBlock<T>(ptr);
        }

        SharedPtr(const SharedPtr &other) noexcept: cb(other.cb) {
            ++cb->shared_count;
        }

        SharedPtr(SharedPtr &&other) noexcept: cb(other.cb) {
            other.cb = nullptr;
        }

        explicit SharedPtr(const WeakPtr<T> &other) noexcept: cb(other.cb) {
            ++cb->shared_count;
        }

        SharedPtr &operator=(SharedPtr &&other) noexcept {
            if (&other != this) {
                dealloc();
                cb = other.cb;
                other.cb = nullptr;
            }
            return *this;
        }

        SharedPtr &operator=(const SharedPtr &other) noexcept {
            if (&other != this) {
                dealloc();
                cb = other.cb;
                ++cb->shared_count;
            }
            return *this;
        }

        ~SharedPtr() {
            dealloc();
        }

        T &operator*() noexcept {
            return *cb->ptr;
        }

        T *operator->() noexcept {
            return get();
        }

        T *get() noexcept {
            return cb->ptr;
        }

        size_t use_count() const noexcept {
            return cb->shared_count;
        }

        void reset(T *ptr = nullptr) noexcept {
            if (cb && cb->ptr != ptr) {
                dealloc();
                cb = new ControlBlock<T>(ptr);
            }
        }

        void swap(SharedPtr &other) noexcept {
            std::swap(cb, other.cb);
        }

    protected:
        void dealloc() {
            if (cb) {
                if (cb->shared_count <= 1) {
                    delete cb->ptr;
                    cb->ptr = nullptr;
                }
                --cb->shared_count;
                if (cb->shared_count <= 0 && cb->weak_count <= 0) {
                    delete cb;
                    cb = nullptr;
                }
            }
        }
    };

    template<class T>
    class WeakPtr {
    public:
        ControlBlock<T> *cb;

        WeakPtr(const SharedPtr<T> &other = SharedPtr<T>()) noexcept: cb(other.cb) {
            ++cb->weak_count;
        }

        WeakPtr(const WeakPtr &other) noexcept: cb(other.cb) {
            ++cb->weak_count;
        }

        WeakPtr(WeakPtr &&other) noexcept: cb(other.cb) {
            other.cb = nullptr;
        }

        WeakPtr &operator=(WeakPtr &&other) noexcept {
            if (&other != this) {
                dealloc();
                cb = other.cb;
                other.cb = nullptr;
            }
            return *this;
        }

        WeakPtr &operator=(const WeakPtr &other) noexcept {
            if (&other != this) {
                dealloc();
                cb = other.cb;
                ++cb->weak_count;
            }
            return *this;
        }

        WeakPtr &operator=(const SharedPtr<T> &other) noexcept {
            dealloc();
            cb = other.cb;
            ++cb->weak_count;
            return *this;
        }

        size_t use_count() const noexcept {
            if (cb) {
                return cb->shared_count;
            } else {
                return 0;
            }
        }

        bool expired() const noexcept {
            return use_count() == 0;
        }

        SharedPtr<T> lock() {
            return (expired() ? SharedPtr<T>() : SharedPtr<T>(*this));
        }

        void swap(WeakPtr<T> &other) {
            std::swap(cb, other.cb);
        }

        void reset() {
            dealloc();
            *this = SharedPtr<T>();
        }

    protected:
        void dealloc() {
            --cb->weak_count;
        }
    };


// Your template function definitions may go here...

}  // namespace task


#include "smart_pointers.tpp"
