#pragma once

template <typename T>
class RefPtr {
    private:
        struct ControlBlock {
            int ref_count;
            T* ptr;
        }

        ControlBlock* control;

    public:
        // constructor
        explict RefPtr(T* rawPtr);
        // copy constructor
        RefPtr(const RefPtr& other);
        // copy assignment operator
        RefPtr& operator=(const RefPtr& other);
        // destructor
        ~RefPtr();

        // dereference operator
        T& operator*() const;
        T* operator->() const;

        // get the number of references for debugging
        int use_count() const;
}