/*
 * file: result.hpp
 * author: filebin
 * date: 2022-10-19 12:06:34
 */

#pragma arguments

#include "stdafx.hpp"

NSP_NET_BEGIN

enum Result { Success = 0, SmallPacket = -1, DataNotFull = -2 };

NSP_NET_END