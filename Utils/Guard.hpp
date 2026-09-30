#ifndef GUARD_HPP
#define GUARD_HPP

#include <stdexcept>

class Guard {
    public:
        Guard(bool &flag) : flag(flag) {
            if (this->flag)
                throw std::logic_error("Guarded operation is already in progress");
            this->flag = true;
        }

        Guard(const Guard &) = delete;
        Guard &operator=(const Guard &) = delete;

        ~Guard() noexcept {
            this->flag = false;
        }
    private:
        bool &flag;
};

#endif /* !GUARD_HPP */