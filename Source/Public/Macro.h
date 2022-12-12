#pragma once

#include <Text.hpp>


/**
 * 평가식을 검사합니다.
 * 이때, 평가식이 거짓으로 평가되면 C++ 표준 예외를 던집니다.
 *
 * @param EXPRESSION - 검사할 평가식입니다.
 * @param MESSAGE - 평가식이 거짓으로 평가될 경우의 메시지입니다.
 *
 * @throws 평가식이 거짓으로 평가될 경우, C++ 표준 예외를 던집니다.
 */
#ifndef CHECK
#define CHECK(EXPRESSION, MESSAGE)\
{\
	if(!EXPRESSION)\
	{\
		throw std::exception(\
			Text::Format(\
			"file : %s, line : %d, function : %s, message : %s",\
				__FILE__, __LINE__, __FUNCTION__, MESSAGE).c_str()\
		);\
	}\
}
#endif


/**
 * 강제로 C++ 표준 예외를 던집니다.
 *
 * @param MESSAGE - 예외가 발생했을 때의 메시지입니다.
 *
 * @throws C++ 표준 예외를 던집니다.
 */
#ifndef ENFORCE_THROW_EXCEPTION
#define ENFORCE_THROW_EXCEPTION(MESSAGE)\
{\
	throw std::exception(\
		Text::Format(\
		"file : %s, line : %d, function : %s, message : %s",\
			__FILE__, __LINE__, __FUNCTION__, MESSAGE).c_str()\
	);\
}
#endif


/**
 * 클래스의 복사 생성자 및 대입 연산자를 사용하지 못하도록 삭제합니다.
 * 이 매크로를 사용하지 않는 클래스는 반드시 명시적으로 대입 연산자와 복사 생성자를 정의해야 합니다.
 *
 * @param CLASS - 복사 생성자 및 대입 연산자를 삭제할 클래스입니다.
 */
#ifndef DISALLOW_COPY_AND_ASSIGN
#define DISALLOW_COPY_AND_ASSIGN(CLASS)\
CLASS(CLASS&&) = delete;\
CLASS(const CLASS&) = delete;\
CLASS& operator=(CLASS&&) = delete;\
CLASS& operator=(const CLASS&) = delete;
#endif