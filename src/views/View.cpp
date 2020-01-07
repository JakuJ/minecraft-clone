#include "views/View.hpp"

void CompositeView::refresh()
{
    for (auto &view : subviews)
    {
        view->refresh();
    }
}

void CompositeView::add(View *view)
{
    subviews.push_back(std::unique_ptr<View>(view));
}