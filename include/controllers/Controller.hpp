#pragma once

/// An abstract class responsible for handling user input.
class Controller {
public:
    /// Process user input.
    virtual void update() = 0;
};