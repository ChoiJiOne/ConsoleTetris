#pragma once

#include <Json/json.hpp>

using Json = nlohmann::json;

/**
 * Json ���Ϸ� ���� Json ��ü�� �ε��մϴ�.
 * �̶�, Json ������ ��δ� Content ������ �������� �մϴ�.
 * ���� Content ������ A.json ������ �ε��ϰ� ������ ���ڷ� "Content/A.json" �� �ƴ϶� "A.json" ���� �����ؾ� �մϴ�.
 * 
 * @param InPath - Content ������ Json ���� ����Դϴ�.
 * 
 * @throws 
 * - �Է� ���� ��ο� Json ������ �������� ������ C++ ǥ�� ���ܸ� �����ϴ�.
 * 
 * @return Json ��ü�� ��ȯ�մϴ�.
 */
Json LoadJsonFromFile(const std::string& InPath);