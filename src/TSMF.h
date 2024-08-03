// This code from https://github.com/radi-sh/BonDriver_BDA

#pragma once

#include <vector>
#include "typedef.h"
#include "Common.h"

class CTSMFParser
{
public:
	static constexpr BYTE TS_PACKET_SYNC_BYTE = 0x47;		// TSパケットヘッダ同期バイトコード

private:
	int slot_counter;										// TSMF多重フレームスロット番号
	WORD TSID;												// 抽出するストリームのTSIDまたは相対TS番号
	WORD ONID;												// 抽出するストリームのONID
	BOOL IsRelative;										// 相対TS番号で指定するかどうか FALSE..ONID/TSIDで指定, TRUE..相対TS番号で指定
	BOOL IsClearCalled;										// 解析処理のクリアが必要かどうか
	cCriticalSection csClear;								// クリア処理を排他
	size_t PacketSize;										// TSパケットサイズ
	std::vector<BYTE> readBuf;								// 前回処理したTSパケットバッファ(未処理半端分保存用)およびRead用
	std::vector<BYTE> tempBuf;								// Write用テンポラリバッファ
	struct {
		BYTE continuity_counter;							// 連続性指標
		BYTE version_number;								// 変更指示
		BYTE relative_stream_number_mode;					// スロット配置法の区別
		BYTE frame_type;									// 多重フレーム形式
		struct {
			BYTE stream_status;								// 相対ストリーム番号に対する有効、無効指示
			WORD stream_id;									// ストリーム識別／相対ストリーム番号対応情報
			WORD original_network_id;						// オリジナルネットワ－ク識別／相対ストリーム番号対応情報
			BYTE receive_status;							// 受信状態
		} stream_info[15];									// 相対ストリーム番号毎の情報
		BYTE emergency_indicator;							// 緊急警報指示
		BYTE relative_stream_number[52];					// 相対ストリーム番号対スロット対応情報
	} TSMFData;												// TSMF多重フレームヘッダ情報

public:
	// コンストラクタ
	CTSMFParser(void);
	// デストラクタ
	~CTSMFParser(void);
	// ストリーム識別子をセット
	void SetTSID(WORD onid, WORD tsid, BOOL relative);
	// TSMF処理を無効にする
	void Disable(void);
	// TSバッファのTSMF処理を行う
	void ParseTsBuffer(BYTE * buf, size_t len, BYTE ** newBuf, size_t * newBufLen, BOOL deleteNullPackets);
	// TSパケットの同期を行う
	static BOOL SyncPacket(const BYTE * buf, size_t len, size_t * truncate, size_t * packetSize);

private:
	// 全ての情報をクリア
	void Clear(WORD onid = 0xffff, WORD tsid = 0xffff, BOOL relative = FALSE);
	// TSMFヘッダの解析を行う
	BOOL ParseTSMFHeader(const BYTE * buf, size_t len);
	// 1パケット(1フレーム)の処理を行う
	BOOL ParseOnePacket(const BYTE * buf, size_t len, WORD onid, WORD tsid, BOOL relative);
};
