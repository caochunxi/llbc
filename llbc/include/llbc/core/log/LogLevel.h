// The MIT License (MIT)

// Copyright (c) 2013 lailongwei<lailongwei@126.com>
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy of 
// this software and associated documentation files (the "Software"), to deal in 
// the Software without restriction, including without limitation the rights to 
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of 
// the Software, and to permit persons to whom the Software is furnished to do so, 
// subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all 
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS 
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN 
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef __LLBC_LOG_LEVEL_H__
#define __LLBC_LOG_LEVEL_H__

#include "llbc/common/Common.h"

__LLBC_NS_BEGIN

/**
 * \brief The log level class encapsulation.
 */
class LLBC_EXPORT LLBC_LogLevel
{
public:
    /**
     * Level value enumeration.
     */
    enum
    {
        Begin,

        Debug = Begin,
        Info,
        Warn,
        Error,
        Fatal,

        End
    };

public:
    /**
     * Get Debug level string describe.
     * @return const LLBC_String & - Debug level describe.
     */
    static const LLBC_String &GetDebugDesc();

    /**
     * Get Info level string describe.
     * @return const LLBC_String & - Info level describe.
     */
    static const LLBC_String &GetInfoDesc();

    /**
     * Get Warn level string describe.
     * @return const LLBC_String & - Warn level describe.
     */
    static const LLBC_String &GetWarnDesc();

    /**
     * Get Error level string describe.
     * @return const LLBC_String & - Error level describe.
     */
    static const LLBC_String &GetErrorDesc();

    /**
     * Get Fatal level string describe.
     * @return const LLBC_String & - Fatal level describe.
     */
    static const LLBC_String &GetFatalDesc();

    /**
     * Get specific log level string describe.
     * @param[in] level - log level.
     * @return const LLBC_String & - level describe.
     */
    static const LLBC_String &GetLevelDesc(int level);

public:
    /**
     * Get specific log level by describe.
     * @param[in] str - log level describe.
     * @return int - log level.
     */
    static int Str2Level(const char *str);

    /**
     * Check giving log level is legal or not.
     * @param[in] level - the given log level.
     * @return bool - return if log level is legal, otherwise return false.
     */
    static bool IsLegal(int level);
};

__LLBC_NS_END

#endif // !__LLBC_LOG_LEVEL_H__
