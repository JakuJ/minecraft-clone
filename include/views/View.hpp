#pragma once

#include <vector>
#include <memory>

class View {
public:
    virtual ~View() = default;

    virtual void refresh() = 0;
};

class CompositeView : public View {
    std::vector<std::unique_ptr<View>> subviews;

public:
    void refresh() final;

    void add(View *);
};
