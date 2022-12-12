#pragma once

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>


/**
 * 문자열 관련 기능을 제공하는 클래스입니다.
 * 이때 이 클래스는 정적 클래스로 헤더 선언만 하면
 * 인스턴스 생성 없이 바로 사용할 수 있습니다.
 */
class Text
{
public:
	/**
	 * 형식화된 문자열을 반환합니다.
	 * 이 메서드는 snprintf를 대체하기 위한 메서드입니다.
	 *
	 * @param InFormat - 형식 문자열입니다.
	 * @param ... InArgs - 포멧팅을 수행할 데이터를 지정하는 인수입니다.
	 *
	 * @return 포멧팅이 완료된 문자열을 반환합니다.
	 *
	 * @see https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
	 */
	template<typename ... Args>
	static inline std::string Format(const std::string& InFormat, Args ... InArgs_)
	{
		size_t Size = static_cast<size_t>(std::snprintf(nullptr, 0, InFormat.c_str(), InArgs_ ...)) + 1;

		auto Buffer = std::make_unique<char[]>(Size);
		std::snprintf(Buffer.get(), Size, InFormat.c_str(), InArgs_ ...);

		return std::string(Buffer.get(), Buffer.get() + Size - 1);
	}


	/**
	 * 형식화된 문자열을 반환합니다.
	 * 이 메서드는 swprintf를 대체하기 위한 메서드입니다.
	 *
	 * @param InFormat - 형식 문자열입니다.
	 * @param ... InArgs - 포멧팅을 수행할 데이터를 지정하는 인수입니다.
	 *
	 * @return 포멧팅이 완료된 문자열을 반환합니다.
	 *
	 * @see https://stackoverflow.com/questions/2342162/stdstring-formatting-like-sprintf
	 */
	template<typename ... Args>
	static inline std::wstring Format(const std::wstring& InFormat, Args ... InArgs_)
	{
		size_t Size = static_cast<size_t>(std::swprintf(nullptr, 0, InFormat.c_str(), InArgs_ ...)) + 1;

		auto Buffer = std::make_unique<wchar_t[]>(Size);
		std::swprintf(Buffer.get(), Size, InFormat.c_str(), InArgs_ ...);

		return std::wstring(Buffer.get(), Buffer.get() + Size - 1);
	}


	/**
	 * 문자열의 Hash 값을 반환합니다.
	 *
	 * @param InText - Hash 값으로 변환할 문자열입니다.
	 *
	 * @return 입력 받은 문자열의 Hash 값입니다.
	 */
	static inline std::size_t GetHash(const std::string& InText)
	{
		return std::hash<std::string>{}(InText);
	}


	/**
	 * 문자열의 Hash 값을 얻습니다.
	 *
	 * @param InText - Hash 값으로 변환할 문자열입니다.
	 *
	 * @return 입력 받은 문자열의 Hash 값입니다.
	 */
	static inline std::size_t GetHash(const std::wstring& InText)
	{
		return std::hash<std::wstring>{}(InText);
	}


	/**
	 * 문자열을 특정 기준으로 나누어서 벡터로 만듭니다.
	 *
	 * @param InText - 특정 기준으로 나누어서 벡터로 만들 문자열입니다.
	 * @param InDelimiter - 문자열을 나눌 기준입니다.
	 *
	 * @return 나누어진 문자열의 벡터를 반환합니다.
	 */
	static inline std::vector<std::string> Split(std::string InText, const std::string& InDelimiter)
	{
		std::vector<std::string> Tokens;
		std::size_t Position = 0;

		while ((Position = InText.find(InDelimiter)) != std::string::npos)
		{
			Tokens.push_back(InText.substr(0, Position));
			InText.erase(0, Position + InDelimiter.length());
		}

		Tokens.push_back(InText);
		return Tokens;
	}


	/**
	 * 문자열을 특정 기준으로 나누어서 벡터로 만듭니다.
	 *
	 * @param InText - 특정 기준으로 나누어서 벡터로 만들 문자열입니다.
	 * @param InDelimiter - 문자열을 나눌 기준입니다.
	 *
	 * @return 나누어진 문자열의 벡터를 반환합니다.
	 */
	static inline std::vector<std::wstring> Split(std::wstring InText, const std::wstring& InDelimiter)
	{
		std::vector<std::wstring> Tokens;
		std::size_t Position = 0;

		while ((Position = InText.find(InDelimiter)) != std::wstring::npos)
		{
			Tokens.push_back(InText.substr(0, Position));
			InText.erase(0, Position + InDelimiter.length());
		}

		Tokens.push_back(InText);
		return Tokens;
	}
};