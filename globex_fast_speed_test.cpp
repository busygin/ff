#include <iostream>
#include <vector>
#include "message.h"
#include "fast_fields.h"
#include "utils.h"
#include "globex_fast.h"

#include <chrono>

constexpr size_t n_trades_per_message(18);
constexpr size_t n_messages(10000);
constexpr size_t buf_size(10*1024*1024);

namespace FIX {

class FastHandlerTest : public BaseFastHandler {
public:
	/* it has a wierd compilation bug if you try to override only some on_first_MDEntry methods here.
	It stops seeing non-overriden on_first_MDEntry methods in Base class!!
	I will investigate it further and report a gcc bug if necessary!
	The workaround for now is to override ALL on_first_MDEntry methods here.*/
	bool on_first_MDEntry(const MDIncRefresh_112& m) { return true; }  // return true if you want to stop at first trade
	bool on_first_MDEntry(const MDIncRefresh_113& m) { return false; }
	bool on_first_MDEntry(const MDSnapshotFullRefresh_114& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_115& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_116& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_117& m) { return false; }
	bool on_first_MDEntry(const MDSnapshotFullRefresh_118& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_119& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_120& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_121& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_122& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_125& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_129& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_131& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_134& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_135& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_136& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_138& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_141& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_142& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_143& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_144& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_145& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_146& m) { return false; }
	bool on_first_MDEntry(const MDIncRefresh_147& m) { return false; }
};

class FastParserTest : public FastParser<FastHandlerTest> {
public:
	FastParserTest(FastHandlerTest& handler) : FastParser<FastHandlerTest>(handler), lastMsgSeqNum_(0), lastTradeVolume_(0) { }

	void generate_MDIncRefresh_112() {
		m_MDIncRefresh_112_.set_MsgSeqNum(++lastMsgSeqNum_);
		std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
		std::chrono::system_clock::duration d = t.time_since_epoch();
		m_MDIncRefresh_112_.set_SendingTime(d.count());
		m_MDIncRefresh_112_.set_PosDupFlag("N");
		m_MDIncRefresh_112_.set_TradeDate(20140820);
		MDIncRefresh_112::MDEntries test_MDEntries;
		for(size_t i=0; i<n_trades_per_message; ++i) {
			generate_MDIncRefresh_112_MDEntries(test_MDEntries);
			m_MDIncRefresh_112_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_112_MDEntries(MDIncRefresh_112::MDEntries& s) {
		s.set_MDUpdateAction(0);
		s.set_MDEntryType("2");
		s.set_SecurityID(876673);
		s.set_RptSeq(1);
		s.set_MDEntryPx(Decimal(12356,-2));
		s.set_MDEntrySize(10);
		s.set_NetChgPrevDay(Decimal(1023,-2));
		lastTradeVolume_ += 10;
		s.set_TradeVolume(lastTradeVolume_);
		s.set_TickDirection("3");
		s.set_TradeCondition("C");
		std::chrono::high_resolution_clock::time_point t = std::chrono::high_resolution_clock::now();
		std::chrono::system_clock::duration d = t.time_since_epoch();
		s.set_MDEntryTime(d.count());
		s.set_AggressorSide(1);
		//s.set_MatchEventIndicator("event");
	}

private:
	uint32_t lastMsgSeqNum_;
	uint32_t lastTradeVolume_;
};

}

int main() {
	FIX::FastHandlerTest fast_handler;
	FIX::FastParserTest fast_parser(fast_handler);

	fast_parser.generate_MDIncRefresh_112();

	char* buf = new char[buf_size];
	char* end = buf+buf_size;
	char* p(buf);
	std::vector<char*> msg_begins(n_messages);

	for(size_t i=0; i<n_messages; ++i) {
		msg_begins[i] = p;
		fast_parser.encode_MDIncRefresh_112(p, end);
	}

	size_t encoded_len = p-buf;
	std::cout << encoded_len << " bytes encoded\n";

	std::cout << "Decoding FAST " << n_messages << " messages with " << n_trades_per_message << " trades per message\n";

	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	std::chrono::system_clock::duration d1 = t1.time_since_epoch();

	/*const char* p1(buf);
	while(p1<p)
		fast_handler.scan(p1,p);*/
	for(size_t i=0; i<n_messages; ++i) {
		const char* p1 = msg_begins[i];
		fast_parser.scan(p1,p);
	}

	std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
	std::chrono::system_clock::duration d2 = t2.time_since_epoch();

	double elapsed = (double(d2.count() - d1.count()) * std::chrono::system_clock::period::num / std::chrono::system_clock::period::den) * 1e6;
	std::cout << elapsed << " microseconds elapsed.\n";
	elapsed /= n_messages;
	std::cout << elapsed << " microseconds per message.\n";
	elapsed /= n_trades_per_message;
	std::cout << elapsed << " microseconds per trade.\n";

	delete[] buf;

	return 0;
}
