#ifndef VIEWS_STATE_HPP
#define VIEWS_STATE_HPP

#include <cstddef>

class ViewsState {
public:
    void viewAcquired() {
        ++activeViews;
    }
    void viewReleased() {
        --activeViews;
    }
    bool hasActiveViews() const {
        return activeViews > 0;
    }
private:
    std::size_t activeViews = 0;
};

#endif /* !VIEWS_STATE_HPP */