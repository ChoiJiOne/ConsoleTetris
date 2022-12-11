#pragma once

#include <Windows.h>
#include <Dbghelp.h>
#include <minidumpapiset.h>


/**
 * ����ȭ ���� ���� ���ܸ� ó���մϴ�.
 *
 * @param InExceptionInfo - ���ܰ� �߻��� ������ ���õ� �����Դϴ�.
 *
 * @return EXCEPTION_CONTINUE_SEARCH �⺻ ���� ��ȯ�մϴ�.
 */
LONG WINAPI UnhandledExceptionHandler(struct _EXCEPTION_POINTERS* InExceptionInfo);