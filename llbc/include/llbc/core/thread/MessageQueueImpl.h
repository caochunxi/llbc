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


#ifdef __LLBC_CORE_THREAD_MESSAGE_QUEUE_H__

__LLBC_NS_BEGIN

inline void LLBC_MessageQueue::PushFront(LLBC_MessageBlock *block)
{
    Push(block, true);
}

inline void LLBC_MessageQueue::PushBack(LLBC_MessageBlock *block)
{
    Push(block, false);
}

inline void LLBC_MessageQueue::PopFront(LLBC_MessageBlock *&block)
{
    Pop(block, LLBC_INFINITE, true);
}

inline void LLBC_MessageQueue::PopBack(LLBC_MessageBlock *&block)
{
    Pop(block, LLBC_INFINITE, false);
}

inline bool LLBC_MessageQueue::TryPopFront(LLBC_MessageBlock *&block)
{
    return Pop(block, 0, true);
}

inline bool LLBC_MessageQueue::TryPopBack(LLBC_MessageBlock *&block)
{
    return Pop(block, 0, false);
}

inline bool LLBC_MessageQueue::TimedPopFront(LLBC_MessageBlock *&block, int interval)
{
    return Pop(block, interval, true);
}

inline bool LLBC_MessageQueue::TimedPopBack(LLBC_MessageBlock *&block, int interval)
{
    return Pop(block, interval, false);
}

inline void LLBC_MessageQueue::PushNonLock(LLBC_MessageBlock *block, bool front)
{
    if (front)
        PushFrontNonLock(block);
    else
        PushBackNonLock(block);
}

inline void LLBC_MessageQueue::PopNonLock(LLBC_MessageBlock *&block, bool front)
{
    if (front)
        PopFrontNonLock(block);
    else
        PopBackNonLock(block);
}

__LLBC_NS_END

#endif // __LLBC_CORE_THREAD_MESSAGE_QUEUE_H__
