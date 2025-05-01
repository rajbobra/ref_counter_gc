#pragma once

template <typename T>
class RefPtr {
    private:
        struct ControlBlock {
            int ref_count;
            T* ptr;

            ControlBlock(T* raw) : ptr(raw), ref_count(1) {}
        };

        ControlBlock* control;

    public:
        // constructor
        explicit RefPtr(T* rawPtr){
            this->control = new ControlBlock(rawPtr);
        }

        // copy constructor
        RefPtr(const RefPtr& other) {
            this->control = other.control;
            this->control->ref_count++;
        }

        // move
        RefPtr(RefPtr&&) noexcept;

        // copy assignment operator
        RefPtr& operator=(const RefPtr& other) {
            if(this != &other) {
                this->control->ref_count--;
                if(this->control->ref_count == 0) {
                    delete this->control->ptr;
                    delete this-> control;
                }

                this->control = other.control;
                this->control->ref_count++;
            }

            return *this;
        }

        // move assignment operator
        RefPtr& operator=(const RefPtr&& other);

        // destructor
        ~RefPtr() {
            this->control->ref_count--;
            if(this->control->ref_count == 0) {
                delete this->control->ptr;
                delete this-> control;
            }
        }

        T* operator->() const {
            return this->control->ptr;
        }

        // dereference operator
        T& operator*() const {
            return *(this->control->ptr);
        }

        // get the number of references for debugging
        int use_count() const {
            return this->control->ref_count;
        }
};