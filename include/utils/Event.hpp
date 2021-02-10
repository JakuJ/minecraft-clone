#pragma once

#include <forward_list>
#include <functional>
#include <ostream>
#include <utility>

template<class ...Args>
using callback_t = std::function<void(Args...)>;
using handle_t = unsigned int;

template<class ...Args>
class Handler {
    static handle_t nextHandle;
public:
    explicit Handler(callback_t<Args...> callback);

    callback_t<Args...> callback;
    handle_t handle;
};

template<class... Args>
handle_t Handler<Args...>::nextHandle = 0;

template<class... Args>
Handler<Args...>::Handler(callback_t<Args...> callback) : callback(std::move(callback)), handle(nextHandle++) {}

template<class ...Args>
class Event {
    std::forward_list<Handler<Args...>> handlers;

public:
    handle_t subscribe(const callback_t<Args...> &callback) {
        handlers.emplace_front(callback);
        return handlers.front().handle;
    }

    void remove(handle_t handle) {
        handlers.remove_if([&handle](const Handler<Args...> &h) { return h.handle == handle; });
    }

    void raise(Args... targets) const {
        for (auto &handler : handlers) {
            handler.callback(targets...);
        }
    }
};
