#pragma once

class Input;

/**
 * ���� ���� �������� Ŭ�����Դϴ�.
 * �̶�, �� Ŭ������ �߻� Ŭ�����Դϴ�.
 */
class Stage
{
public:
	/**
	 * ���� ���� �������� Ŭ������ �������Դϴ�.
	 */
	Stage() = default;


	/**
	 * ���� ���� �������� Ŭ������ ���� �Ҹ����Դϴ�.
	 */
	virtual ~Stage();


	/**
	 * ���������� �Է� ó���� �����մϴ�.
	 * 
	 * @param InInput - �Է� ���¸� �����ϴ� ��ü�� �ν��Ͻ��Դϴ�.
	 */
	virtual void ProcessInput(const Input& InInput) = 0;


	/**
	 * ���������� ������Ʈ�մϴ�.
	 */
	virtual void Update() = 0;


	/**
	 * ���������� �ܼ� ȭ�鿡 �׸��ϴ�.
	 */
	virtual void Draw() = 0;
};