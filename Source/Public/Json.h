#pragma once

#include <Json/json.hpp>

using Json = nlohmann::json;

/**
 * Json 파일로 부터 Json 객체를 로드합니다.
 * 이때, Json 파일의 경로는 Content 폴더를 기준으로 합니다.
 * 만약 Content 하위의 A.json 파일을 로딩하고 싶으면 인자로 "Content/A.json" 이 아니라 "A.json" 으로 전달해야 합니다.
 * 
 * @param InPath - Content 폴더의 Json 파일 경로입니다.
 * 
 * @throws 
 * - 입력 받은 경로에 Json 파일이 존재하지 않으면 C++ 표준 예외를 던집니다.
 * 
 * @return Json 객체를 반환합니다.
 */
Json LoadJsonFromFile(const std::string& InPath);