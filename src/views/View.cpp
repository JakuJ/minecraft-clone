#include "views/View.hpp"

void View::refresh() {
    for (auto &view : subviews) {
        view->refresh();
    }
}

void View::addView(View *view) {
    subviews.emplace_back(view);
}
