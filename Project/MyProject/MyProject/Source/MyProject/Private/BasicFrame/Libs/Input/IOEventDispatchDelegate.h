#pragma once

#include "FastDelegate.h"

struct FKey;

/**
 * @file IOEventDispatchDelegate.h
 */
typedef fastdelegate::FastDelegate1<FKey, bool> KeyEventDispatchDelegate;