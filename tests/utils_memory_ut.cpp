/******************************************************************************
 * iSula-libutils: ut for utils_memory.c
 *
 * Copyright (c) Huawei Technologies Co., Ltd. 2023. All rights reserved.
 *
 * Authors:
 * Haozi007 <liuhao27@huawei.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 ********************************************************************************/

#include <gtest/gtest.h>

#include <iostream>
#include <string.h>

#include "utils_memory.h"

#if __WORDSIZE == 64
// current max user memory for 64-machine is 2^47 B
#define MAX_MEMORY_SIZE ((size_t)1 << 47)
#else
// current max user memory for 32-machine is 2^31 B
#define MAX_MEMORY_SIZE ((size_t)1 << 31)
#endif

TEST(isula_memory_testcase, test__isula_smart_calloc_s)
{
    void *ib = nullptr;

    ib = isula_smart_calloc_s(MAX_MEMORY_SIZE, 2);
    ASSERT_EQ(ib, nullptr);

    ib = isula_smart_calloc_s(0, 2);
    ASSERT_EQ(ib, nullptr);

    ib = isula_smart_calloc_s(1, 2);
    ASSERT_NE(ib, nullptr);

    isula_free_s(ib);
}

TEST(isula_memory_testcase, test__isula_common_calloc_s)
{
    void *ib = nullptr;

    ib = isula_common_calloc_s(MAX_MEMORY_SIZE + 1);
    ASSERT_EQ(ib, nullptr);

    ib = isula_common_calloc_s(0);
    ASSERT_EQ(ib, nullptr);

    ib = isula_common_calloc_s(2);
    ASSERT_NE(ib, nullptr);

    isula_free_s(ib);
}

TEST(isula_memory_testcase, test__isula_strdup_s)
{
    char *new_str = nullptr;

    new_str = isula_strdup_s(nullptr);
    ASSERT_EQ(new_str, nullptr);

    new_str = isula_strdup_s("hello world");
    ASSERT_NE(new_str, nullptr);
    ASSERT_STREQ(new_str, "hello world");

    isula_free_s(new_str);
}

TEST(isula_memory_testcase, test__isula_mem_realloc)
{
    char *new_str = nullptr;
    char *old_str = isula_strdup_s("hello world");
    int ret;

    ret = isula_mem_realloc(nullptr, strlen(old_str) + 1, (void **)&old_str, strlen(old_str) + 1);
    ASSERT_NE(ret, 0);
    ASSERT_EQ(new_str, nullptr);
    ASSERT_NE(old_str, nullptr);

    ret = isula_mem_realloc((void **)&new_str, 0, (void **)&old_str, strlen(old_str) + 1);
    ASSERT_NE(ret, 0);
    ASSERT_EQ(new_str, nullptr);
    ASSERT_NE(old_str, nullptr);

    ret = isula_mem_realloc((void **)&new_str, 1 + 1, (void **)&old_str, strlen(old_str) + 1);
    ASSERT_NE(ret, 0);
    ASSERT_EQ(new_str, nullptr);
    ASSERT_NE(old_str, nullptr);

    ret = isula_mem_realloc((void **)&new_str, strlen(old_str) + 2, (void **)&old_str, strlen(old_str) + 1);
    ASSERT_EQ(ret, 0);
    ASSERT_NE(new_str, nullptr);
    ASSERT_EQ(old_str, nullptr);
    ASSERT_STREQ(new_str, "hello world");

    isula_free_s(new_str);
}
