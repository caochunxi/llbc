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

#ifndef __LLBC_COM_BASIC_CSTRING_H__
#define __LLBC_COM_BASIC_CSTRING_H__

#include "llbc/common/PFConfig.h"

#include "llbc/common/Macro.h"
#include "llbc/common/OSHeader.h"

__LLBC_NS_BEGIN

template <typename _Elem>
class LLBC_BasicCString
{
public:
    LLBC_BasicCString(const _Elem *cstr):_cstr(cstr) {  }

public:
    /**
     * Get const string.
     * @return const _Elem * - the const string.
     */
    const _Elem *GetCStr() const
    {
        return _cstr;
    }

    // operator <
    bool operator <(const LLBC_BasicCString<_Elem> &other) const
    {
        return ::strcmp(_cstr, other._cstr) < 0;
    }

    // operator ==
    bool operator ==(const LLBC_BasicCString<_Elem> &other) const
    {
        return ::strcmp(_cstr, other._cstr) == 0;
    }

    // operator !=
    bool operator !=(const LLBC_BasicCString<_Elem> &other) const
    {
        return ::strcmp(_cstr, other._cstr) != 0;
    }

    // operator <=
    bool operator <=(const LLBC_BasicCString<_Elem> &other) const
    {
        return ::strcmp(_cstr, other._cstr) <= 0;
    }

    // operator >
    bool operator >(const LLBC_BasicCString<_Elem> &other) const
    {
        return ::strcmp(_cstr, other._cstr) > 0;
    }

    // operator >=
    bool operator >=(const LLBC_BasicCString<_Elem> &other) const
    {
        return ::strcmp(_cstr, other._cstr) >= 0;
    }

private:
    const char *_cstr;
};

__LLBC_NS_END

#endif // !__LLBC_COM_BASIC_CSTRING_H__