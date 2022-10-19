#pragma once

#include "stdafx.hpp"

NSP_NET_BEGIN

template <typename T, typename D = std::default_delete<T>> using uptr = std::unique_ptr<T, D>;
template <typename T> using ptr = std::shared_ptr<T>;
template <typename T> using wptr = std::weak_ptr<T>;

NSP_NET_END