#pragma once

#include <utility>
#include <exception>
#include <memory>
#include "../types/Exception.hpp"

template<typename T>
class Try {

    template <typename Func>
    using returns_void = typename std::is_same<typename std::result_of<Func(T&)>::type, void>;

public:

    bool IsSuccess() const {
        return err ? false : true;
    }

    bool IsFailure() const {
        return err ? true : false;
    }

    template<typename Func>
    static Try<T> Of(Func f) noexcept {
        try {
            T res = f();
            return Success(res);
        } catch (const Exception &e) {
            return Failure(e);
        } catch (const std::exception &e) {
            return Failure(e);
        } catch (...) {
            return Failure(std::exception());
        }
    }

    T Value() {
        if (err)
            throw *err;
        return val;
    }

    const Exception& Error() {
        if (err)
            return *err;
        throw std::exception();
    }

    template<typename U, typename Func>
    Try<U> Map(Func f) noexcept {
        if (err)
            return Try<U>::Failure(std::move(err));
        try {
            auto res = f(Value());
            return Try<U>::Success(res);
        } catch (const Exception &e) {
            return Try<U>::Failure(e);
        } catch (...) {
            return Try<U>::Failure(std::exception());
        }
    };

    template<typename Func>
    Try<T> Map(Func f) {
        return Map<T>(f);
    };

    template<typename Func>
    Try<T> Accept(Func f) noexcept {
        static_assert(returns_void<Func>::value, "Using Accept with function returning a value.");
        if (err)
            return Try<T>::Failure(std::move(err));
        try {
            f(Value());
            return Try<T>::Success(val);
        } catch (const std::exception &e) {
            return Try<T>::Failure(e);
        } catch (...) {
            return Try<T>::Failure(std::exception());
        }
    };

    template<typename Func>
    Try<T> Recover(Func f) noexcept {
        if (!err)
            return *this;
        try {
            auto res = f(*err);
            return Success(res);
        } catch (const Exception &e) {
            return Failure(e);
        } catch (...) {
            return Failure(std::exception());
        }
    };

    T OrElse(const T &v) {
        if (err)
            return v;
        return Value();
    }

    static Try Failure(std::shared_ptr<Exception> &&e) {
        return Try(std::move(e));
    }

    static Try Failure(const Exception &e) {
        return Try(std::make_shared<Exception>(e));
    }

    static Try Failure(const std::exception &e) {
        return Try(std::make_shared<Exception>(e.what()));
    }

    static Try<T> Success(const T &value) {
        return Try<T>(value);
    }

    static Try<T> Success(const Try<T> &value) {
        return value;
    }

private:
    explicit Try(const T &value) : val(value) {}
    explicit Try(std::shared_ptr<Exception> &&e) : err(std::move(e)) {}

    T val;
    std::shared_ptr<Exception> err;
};
