#pragma once

#define MAX_LINE_LENGTH 65536		// 16x1024

#ifndef ndebug
// production builds should set ndebug=1
#define ndebug false
#else
#define ndebug true
#endif
