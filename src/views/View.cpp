#include "views/View.hpp"

void View::refresh()
{
    render();
    for (auto &view : subviews)
    {
        view->refresh();
    }
}

void View::add(View *view)
{
    subviews.push_back(std::unique_ptr<View>(view));
}