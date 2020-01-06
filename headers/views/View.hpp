#pragma once

#include <vector>
#include <memory>

class View
{
    std::vector<std::unique_ptr<View>> subviews;

public:
    virtual ~View() {};
    virtual void render() {};
    virtual void refresh() final;
    virtual void add(View *) final;
};
