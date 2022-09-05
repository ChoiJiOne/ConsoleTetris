#pragma once

#include "Tetromino.h"
#include "Block.h"

#include <vector>


/**
 * 테트리스 보드 클래스입니다.
 */
class Board
{
public:
	/**
	 * 테트리스 보드 클래스의 생성자입니다.
	 *
	 * @param InWidth - 테트리스 보드의 가로 크기입니다.
	 * @param InHeight - 테트리스 보드의 세로 크기입니다.
	 */
	Board(const int32_t& InWidth, const int32_t& InHeight);


	/**
	 * 테트리스 보드 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사를 수행할 보드 객체입니다.
	 */
	Board(Board&& InInstance) noexcept;


	/**
	 * 테트리스 보드 클래스의 복사 생성자입니다.
	 *
	 * @param InInstance - 복사를 수행할 보드 객체입니다.
	 */
	Board(const Board& InInstance) noexcept;


	/**
	 * 테트리스 보드의 가상 소멸자입니다.
	 */
	virtual ~Board();


	/**
	 * 테트리스 보드 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사를 수행할 보드 객체입니다.
	 *
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	Board& operator=(Board&& InInstance) noexcept;


	/**
	 * 테트리스 보드 클래스의 대입 연산자입니다.
	 *
	 * @param InInstance - 복사를 수행할 보드 객체입니다.
	 *
	 * @return 대입을 수행한 객체의 참조자를 반환합니다.
	 */
	Board& operator=(const Board& InInstance) noexcept;


	/**
	 * 테트리스 보드에 테트로미노를 등록합니다.
	 *
	 * @param InTetromino - Board에 등록할 테트로미노입니다.
	 *
	 * @return 테트로미노를 등록할 수 있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool RegisterTetromino(const Tetromino& InTetromino);


	/**
	 * 테트리스 보드에 등록된 테트로미노를 등록 해제합니다.
	 *
	 * @param InTetromino - Board에 등록 해제할 테트로미노입니다.
	 */
	void UnregisterTetromino(const Tetromino& InTetromino);


	/**
	 * 테트리스 보드를 업데이트합니다.
	 * 이때, 채워진 라인은 삭제합니다.
	 *
	 * @return 테트리스 보드를 업데이트 하면서 삭제한 라인의 수를 반환합니다.
	 */
	int32_t Update();


	/**
	 * 테트리스 보드를 초기화합니다.
	 */
	void Reset();


	/**
	 * 테트리스 보드를 콘솔 화면에 그립니다.
	 *
	 * @param InPosition - 콘솔 화면상의 테트리스 보드의 왼쪽 상단 좌표입니다.
	 *
	 * @throws 콘솔 화면에 그리기를 실패하면 C++ 표준 예외를 던집니다.
	 */
	void Draw(const Vec2i& InPosition);


private:
	/**
	 * 2차원 배열의 Offset을 얻습니다.
	 *
	 * @param InPositionX - 2차원 배열의 x좌표입니다.
	 * @param InPositionY - 2차원 배열의 y좌표입니다.
	 * @param InWidth - 2차원 배열의 가로 크기입니다.
	 * @param InHeight - 2차원 배열의 세로 크기입니다.
	 *
	 * @throws 배열의 범위를 벗어나면 C++ 표준예외를 던집니다.
	 *
	 * @return (x, y)에 대응하는 2차원 배열의 Offset을 반환합니다.
	 */
	static int32_t GetOffset(int32_t InPositionX, int32_t InPositionY, int32_t InWidth, int32_t InHeight);


	/**
	 * 2차원 배열의 Offset을 얻습니다.
	 *
	 * @param InPosition - 2차원 배열의 좌표입니다.
	 * @param InWidth - 2차원 배열의 가로 크기입니다.
	 * @param InHeight - 2차원 배열의 세로 크기입니다.
	 *
	 * @throws 배열의 범위를 벗어나면 C++ 표준예외를 던집니다.
	 *
	 * @return (x, y)에 대응하는 2차원 배열의 Offset을 반환합니다.
	 */
	static int32_t GetOffset(const Vec2i& InPosition, int32_t InWidth, int32_t InHeight);


	/**
	 * 2차원 테트리스 보드의 블록을 생성합니다.
	 *
	 * @param InWidth - 2차원 테트리스 보드의 가로 크기입니다.
	 * @param InHeight - 2차원 테트리스 보드의 세로 크기입니다.
	 *
	 * @return - 생성된 2차원 테트리스 보드를 반환합니다.
	 */
	static std::vector<Block> CreateBlocks(int32_t InWidth, int32_t InHeight);


	/**
	 * 2차원 테트리스 보드의 블럭을 초기화합니다.
	 *
	 * @param InBlocks - 초기화할 테트리스 보드의 블럭입니다.
	 * @param InWidth - 테트리스 보드의 가로 크기입니다.
	 * @param InHeight - 테트리스 보드의 세로 크기입니다.
	 */
	static void SetupBlocks(std::vector<Block>& InBlocks, int32_t InWidth, int32_t InHeight);


	/**
	 * 2차원 좌표의 값이 2차원 배열 내에 있는지 검사합니다.
	 *
	 * @param InPosition - 검사를 수행할 2차원 좌표입니다.
	 * @param InWidth - 2차원 배열의 가로 크기입니다.
	 * @param InHeight - 2차원 배열의 세로 크기입니다.
	 *
	 * @return 좌표 값이 2차원 테트리스 보드 내에 있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	static bool DoseIncludePosition(const Vec2i& InPosition, int32_t InWidth, int32_t InHeight);


	/**
	 * 테트리스 보드에 테트로미노를 등록할 수 있는지 확인합니다.
	 *
	 * @param InTetromino - 검사를 수행할 테트로미노입니다.
	 *
	 * @return 테트로미노를 등록할 수 있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool CanRegisterTetromino(const Tetromino& InTetromino);


	/**
	 * 테트리스 보드의 가로줄 전체가 꽉 차있는지 확인합니다.
	 *
	 * @param InY - 꽉 차있는지 검사를 수행할 가로줄 번호 입니다.
	 *
	 * @return 가로줄이 꽉 차있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsFullFillLine(int32_t InY);


	/**
	 * 테트리스 보드의 가로줄 전체가 비워져있는지 확인합니다.
	 *
	 * @param InY - 비워져있는지 검사를 수행할 가로줄 번호입니다.
	 *
	 * @return 가로줄이 비워져있다면 true, 그렇지 않다면 false를 반환합니다.
	 */
	bool IsFullEmptyLine(int32_t InY);


	/**
	 * 테트리스 보드의 가로줄을 삭제합니다.
	 *
	 * @param InY - 삭제할 가로줄의 번호입니다.
	 */
	void RemoveLine(int32_t InY);


	/**
	 * 테트리스 보드의 채워진 가로줄들을 삭제합니다.
	 *
	 * @return 삭제한 가로줄 수를 반환합니다.
	 */
	int32_t RemoveFullFillLines();


	/**
	 * 테트리스 보드를 빈 공간을 채우는 업데이트합니다.
	 */
	void UpdateBoard();


private:
	/**
	 * 테트리스 보드의 가로 크기입니다.
	 */
	int32_t Width_;


	/**
	 * 테트리스 보드의 세로 크기입니다.
	 */
	int32_t Height_;


	/**
	 * 테트리스 보드의 블럭입니다.
	 */
	std::vector<Block> Blocks_;
};