#pragma once

#include <vector>
#include <memory>

class View {
    std::vector<std::unique_ptr<View>> subviews;

protected:
    View() = default;

public:
    virtual ~View() = default;

    virtual void refresh();

    void addView(View *);
};
