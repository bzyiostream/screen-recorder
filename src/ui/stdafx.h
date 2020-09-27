#pragma once

#include <SDKDDKVer.h>

// C runtime header
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// base header
#include "base\base.h"


// duilib
#include "duilib\UIlib.h"

// ui components
#include "ui_components\ui_components.h"

enum ThreadId {
	kThreadApp,
	kThreadUI,
	kThreadGlobalMisc
};