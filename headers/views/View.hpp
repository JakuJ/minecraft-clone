#pragma once

#include <vector>
#include <memory>

class View
{
public:
    virtual ~View() {};
    
    virtual void refresh() = 0;
};

class CompositeView : public View
{
    std::vector<std::unique_ptr<View>> subviews;

public:
    virtual void refresh() final;
    virtual void add(View *) final;
};
