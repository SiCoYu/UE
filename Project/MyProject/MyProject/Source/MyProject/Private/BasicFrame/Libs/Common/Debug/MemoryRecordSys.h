#pragma once

/**
 * @brief 检查并且记录内存使用，主要调试内存泄漏
 */
class MemoryRecordSys
{

};

// 静态提前构造，可以在所有 new 之前生成
static MemoryRecordSys GMemoryRecordSys;