#include <iostream>
#include "message.h"
#include "fast_fields.h"
#include "utils.h"
#include "globex_fast.h"

namespace FIX {

class FastParserTest : public FastParser<BaseFastHandler> {
public:
	FastParserTest(BaseFastHandler& handler) : FastParser<BaseFastHandler>(handler) { }

	void generate_MDIncRefresh_112() {
		m_MDIncRefresh_112_.set_MsgSeqNum(4);
		m_MDIncRefresh_112_.set_SendingTime(6);
		m_MDIncRefresh_112_.set_PosDupFlag("ylspko");
		m_MDIncRefresh_112_.set_TradeDate(2);
		MDIncRefresh_112::MDEntries test_MDEntries;
		for(size_t i=0; i<1; ++i) {
			generate_MDIncRefresh_112_MDEntries(test_MDEntries);
			m_MDIncRefresh_112_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_112_MDEntries(MDIncRefresh_112::MDEntries& s) {
		s.set_MDUpdateAction(6);
		s.set_MDEntryType("acpk");
		s.set_SecurityID(2);
		s.set_RptSeq(0);
		s.set_MDEntryPx(1);
		s.set_MDEntrySize(11);
		s.set_NetChgPrevDay(18);
		s.set_TradeVolume(15);
		s.set_TickDirection("stj");
		s.set_TradeCondition("yzm");
		s.set_MDEntryTime(6);
		s.set_AggressorSide(16);
		s.set_MatchEventIndicator("gzfyjtmmvup");
	}
	void clear_MDIncRefresh_112() {
		m_MDIncRefresh_112_.clear();
	}
	void generate_MDIncRefresh_113() {
		m_MDIncRefresh_113_.set_MsgSeqNum(1);
		m_MDIncRefresh_113_.set_SendingTime(15);
		m_MDIncRefresh_113_.set_PosDupFlag("vnyktibodm");
		m_MDIncRefresh_113_.set_TradeDate(17);
		MDIncRefresh_113::MDEntries test_MDEntries;
		for(size_t i=0; i<11; ++i) {
			generate_MDIncRefresh_113_MDEntries(test_MDEntries);
			m_MDIncRefresh_113_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_113_MDEntries(MDIncRefresh_113::MDEntries& s) {
		s.set_MDUpdateAction(12);
		s.set_MDEntryType("lavtza");
		s.set_SecurityID(7);
		s.set_RptSeq(10);
		s.set_MDEntryPx(18);
		s.set_MDEntryTime(3);
		s.set_MDEntrySize(13);
		s.set_NetChgPrevDay(19);
		s.set_TradeVolume(15);
		s.set_TradeCondition("t");
		s.set_TickDirection("nqynbs");
		s.set_AggressorSide(15);
		s.set_MatchEventIndicator("iaqddeloeik");
	}
	void clear_MDIncRefresh_113() {
		m_MDIncRefresh_113_.clear();
	}
	void generate_MDSnapshotFullRefresh_114() {
		m_MDSnapshotFullRefresh_114_.set_MsgSeqNum(1);
		m_MDSnapshotFullRefresh_114_.set_PosDupFlag("bog");
		m_MDSnapshotFullRefresh_114_.set_SendingTime(17);
		m_MDSnapshotFullRefresh_114_.set_LastMsgSeqNumProcessed(17);
		m_MDSnapshotFullRefresh_114_.set_TotNumReports(2);
		m_MDSnapshotFullRefresh_114_.set_RptSeq(4);
		m_MDSnapshotFullRefresh_114_.set_MDBookType(3);
		m_MDSnapshotFullRefresh_114_.set_SecurityID(15);
		m_MDSnapshotFullRefresh_114_.set_MDSecurityTradingStatus(7);
		MDSnapshotFullRefresh_114::MDEntries test_MDEntries;
		for(size_t i=0; i<6; ++i) {
			generate_MDSnapshotFullRefresh_114_MDEntries(test_MDEntries);
			m_MDSnapshotFullRefresh_114_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDSnapshotFullRefresh_114_MDEntries(MDSnapshotFullRefresh_114::MDEntries& s) {
		s.set_MDEntryType("qbokzusbnv");
		s.set_MDEntryPx(11);
		s.set_MDEntrySize(13);
		s.set_QuoteCondition("t");
		s.set_MDPriceLevel(18);
		s.set_TradeVolume(6);
		s.set_TickDirection("b");
		s.set_NetChgPrevDay(11);
	}
	void clear_MDSnapshotFullRefresh_114() {
		m_MDSnapshotFullRefresh_114_.clear();
	}
	void generate_MDIncRefresh_115() {
		m_MDIncRefresh_115_.set_MsgSeqNum(15);
		m_MDIncRefresh_115_.set_SendingTime(15);
		m_MDIncRefresh_115_.set_PosDupFlag("qejwfgovue");
		m_MDIncRefresh_115_.set_TradeDate(9);
		MDIncRefresh_115::MDEntries test_MDEntries;
		for(size_t i=0; i<1; ++i) {
			generate_MDIncRefresh_115_MDEntries(test_MDEntries);
			m_MDIncRefresh_115_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_115_MDEntries(MDIncRefresh_115::MDEntries& s) {
		s.set_MDUpdateAction(16);
		s.set_MDPriceLevel(4);
		s.set_MDEntryType("ibsdijo");
		s.set_SecurityID(2);
		s.set_RptSeq(5);
		s.set_MDEntryPx(2);
		s.set_MDEntryTime(15);
		s.set_MDEntrySize(9);
		s.set_TickDirection("qcrgjcfqj");
		s.set_OpenCloseSettleFlag(3);
		s.set_TradeVolume(10);
	}
	void clear_MDIncRefresh_115() {
		m_MDIncRefresh_115_.clear();
	}
	void generate_MDIncRefresh_116() {
		m_MDIncRefresh_116_.set_MsgSeqNum(3);
		m_MDIncRefresh_116_.set_SendingTime(13);
		m_MDIncRefresh_116_.set_PosDupFlag("nnpsxs");
		m_MDIncRefresh_116_.set_TradeDate(14);
		MDIncRefresh_116::MDEntries test_MDEntries;
		for(size_t i=0; i<3; ++i) {
			generate_MDIncRefresh_116_MDEntries(test_MDEntries);
			m_MDIncRefresh_116_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_116_MDEntries(MDIncRefresh_116::MDEntries& s) {
		s.set_MDUpdateAction(9);
		s.set_MDPriceLevel(2);
		s.set_MDEntryType("ff");
		s.set_MDEntryTime(7);
		s.set_SecurityID(6);
		s.set_RptSeq(0);
		s.set_MDEntryPx(12);
		s.set_MDEntrySize(9);
		s.set_TradingSessionID("vpgyuwhpkmo");
		s.set_NumberOfOrders(3);
	}
	void clear_MDIncRefresh_116() {
		m_MDIncRefresh_116_.clear();
	}
	void generate_MDIncRefresh_117() {
		m_MDIncRefresh_117_.set_MsgSeqNum(5);
		m_MDIncRefresh_117_.set_SendingTime(19);
		m_MDIncRefresh_117_.set_PosDupFlag("ua");
		m_MDIncRefresh_117_.set_TradeDate(17);
		MDIncRefresh_117::MDEntries test_MDEntries;
		for(size_t i=0; i<6; ++i) {
			generate_MDIncRefresh_117_MDEntries(test_MDEntries);
			m_MDIncRefresh_117_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_117_MDEntries(MDIncRefresh_117::MDEntries& s) {
		s.set_MDUpdateAction(9);
		s.set_MDPriceLevel(18);
		s.set_MDEntryType("trko");
		s.set_MDEntryTime(7);
		s.set_SecurityID(2);
		s.set_RptSeq(5);
		s.set_MDEntryPx(16);
		s.set_MDEntrySize(7);
		s.set_NumberOfOrders(12);
		s.set_TradingSessionID("h");
	}
	void clear_MDIncRefresh_117() {
		m_MDIncRefresh_117_.clear();
	}
	void generate_MDSnapshotFullRefresh_118() {
		m_MDSnapshotFullRefresh_118_.set_MsgSeqNum(18);
		m_MDSnapshotFullRefresh_118_.set_PosDupFlag("gx");
		m_MDSnapshotFullRefresh_118_.set_SendingTime(12);
		m_MDSnapshotFullRefresh_118_.set_LastMsgSeqNumProcessed(4);
		m_MDSnapshotFullRefresh_118_.set_TotNumReports(7);
		m_MDSnapshotFullRefresh_118_.set_RptSeq(10);
		m_MDSnapshotFullRefresh_118_.set_MDBookType(0);
		m_MDSnapshotFullRefresh_118_.set_SecurityID(5);
		m_MDSnapshotFullRefresh_118_.set_MDSecurityTradingStatus(2);
		MDSnapshotFullRefresh_118::MDEntries test_MDEntries;
		for(size_t i=0; i<9; ++i) {
			generate_MDSnapshotFullRefresh_118_MDEntries(test_MDEntries);
			m_MDSnapshotFullRefresh_118_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDSnapshotFullRefresh_118_MDEntries(MDSnapshotFullRefresh_118::MDEntries& s) {
		s.set_MDEntryType("mvnrhsla");
		s.set_MDEntryPx(16);
		s.set_MDEntrySize(9);
		s.set_QuoteCondition("iwa");
		s.set_MDPriceLevel(18);
		s.set_NumberOfOrders(19);
		s.set_TradeVolume(10);
		s.set_TickDirection("b");
		s.set_NetChgPrevDay(17);
	}
	void clear_MDSnapshotFullRefresh_118() {
		m_MDSnapshotFullRefresh_118_.clear();
	}
	void generate_MDIncRefresh_119() {
		m_MDIncRefresh_119_.set_MsgSeqNum(3);
		m_MDIncRefresh_119_.set_SendingTime(11);
		m_MDIncRefresh_119_.set_PosDupFlag("qk");
		MDIncRefresh_119::MDEntries test_MDEntries;
		for(size_t i=0; i<3; ++i) {
			generate_MDIncRefresh_119_MDEntries(test_MDEntries);
			m_MDIncRefresh_119_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_119_MDEntries(MDIncRefresh_119::MDEntries& s) {
		s.set_MDUpdateAction(8);
		s.set_MDPriceLevel(15);
		s.set_MDEntryType("wems");
		s.set_SecurityID(6);
		s.set_RptSeq(3);
		s.set_MDEntryPx(19);
		s.set_MDEntryTime(0);
		s.set_MDEntrySize(12);
		s.set_QuoteCondition("osowqoi");
		s.set_NumberOfOrders(19);
		s.set_TradingSessionID("ah");
	}
	void clear_MDIncRefresh_119() {
		m_MDIncRefresh_119_.clear();
	}
	void generate_MDIncRefresh_120() {
		m_MDIncRefresh_120_.set_MsgSeqNum(6);
		m_MDIncRefresh_120_.set_SendingTime(3);
		m_MDIncRefresh_120_.set_PosDupFlag("lpuubsuywg");
		m_MDIncRefresh_120_.set_TradeDate(4);
		MDIncRefresh_120::MDEntries test_MDEntries;
		for(size_t i=0; i<4; ++i) {
			generate_MDIncRefresh_120_MDEntries(test_MDEntries);
			m_MDIncRefresh_120_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_120_MDEntries(MDIncRefresh_120::MDEntries& s) {
		s.set_MDUpdateAction(11);
		s.set_MDPriceLevel(3);
		s.set_MDEntryType("cxounnmevqb");
		s.set_SecurityID(13);
		s.set_RptSeq(19);
		s.set_QuoteCondition("xh");
		s.set_MDEntryPx(2);
		s.set_NumberOfOrders(0);
		s.set_MDEntryTime(9);
		s.set_MDEntrySize(12);
		s.set_TradingSessionID("vmquskigdj");
	}
	void clear_MDIncRefresh_120() {
		m_MDIncRefresh_120_.clear();
	}
	void generate_MDIncRefresh_121() {
		m_MDIncRefresh_121_.set_MsgSeqNum(12);
		m_MDIncRefresh_121_.set_SendingTime(11);
		m_MDIncRefresh_121_.set_PosDupFlag("esmqwkizhh");
		m_MDIncRefresh_121_.set_TradeDate(0);
		MDIncRefresh_121::MDEntries test_MDEntries;
		for(size_t i=0; i<6; ++i) {
			generate_MDIncRefresh_121_MDEntries(test_MDEntries);
			m_MDIncRefresh_121_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_121_MDEntries(MDIncRefresh_121::MDEntries& s) {
		s.set_MDUpdateAction(16);
		s.set_MDPriceLevel(2);
		s.set_MDEntryType("szlp");
		s.set_SecurityID(15);
		s.set_RptSeq(11);
		s.set_MDEntryPx(5);
		s.set_MDEntryTime(12);
		s.set_MDEntrySize(13);
		s.set_QuoteCondition("oqfw");
		s.set_TradingSessionID("ecqt");
	}
	void clear_MDIncRefresh_121() {
		m_MDIncRefresh_121_.clear();
	}
	void generate_MDIncRefresh_122() {
		m_MDIncRefresh_122_.set_MsgSeqNum(2);
		m_MDIncRefresh_122_.set_SendingTime(6);
		m_MDIncRefresh_122_.set_PosDupFlag("domkytbhovi");
		m_MDIncRefresh_122_.set_TradeDate(5);
		MDIncRefresh_122::MDEntries test_MDEntries;
		for(size_t i=0; i<11; ++i) {
			generate_MDIncRefresh_122_MDEntries(test_MDEntries);
			m_MDIncRefresh_122_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_122_MDEntries(MDIncRefresh_122::MDEntries& s) {
		s.set_MDUpdateAction(1);
		s.set_MDEntryType("w");
		s.set_SecurityID(13);
		s.set_RptSeq(9);
		s.set_MDEntryPx(4);
		s.set_MDEntrySize(13);
		s.set_NetChgPrevDay(19);
		s.set_TradeVolume(5);
		s.set_TickDirection("fbr");
		s.set_TradeCondition("wmjbpxqzyja");
		s.set_MDEntryTime(1);
		s.set_AggressorSide(19);
		s.set_MatchEventIndicator("nyiic");
	}
	void clear_MDIncRefresh_122() {
		m_MDIncRefresh_122_.clear();
	}
	void generate_MDSecurityDefinition_123() {
		m_MDSecurityDefinition_123_.set_MsgSeqNum(12);
		m_MDSecurityDefinition_123_.set_SendingTime(14);
		m_MDSecurityDefinition_123_.set_PosDupFlag("wfatxh");
		m_MDSecurityDefinition_123_.set_TotNumReports(6);
		MDSecurityDefinition_123::Events test_Events;
		for(size_t i=0; i<3; ++i) {
			generate_MDSecurityDefinition_123_Events(test_Events);
			m_MDSecurityDefinition_123_.append_Events(test_Events);
		}
		m_MDSecurityDefinition_123_.set_TradingReferencePrice(0);
		m_MDSecurityDefinition_123_.set_SettlePriceType("cowrlotj");
		m_MDSecurityDefinition_123_.set_HighLimitPx(5);
		m_MDSecurityDefinition_123_.set_LowLimitPx(7);
		m_MDSecurityDefinition_123_.set_SecurityGroup("ytdwdoaje");
		m_MDSecurityDefinition_123_.set_Symbol("hjwaidyxit");
		m_MDSecurityDefinition_123_.set_SecurityDesc("wstjgmvghl");
		m_MDSecurityDefinition_123_.set_SecurityID(0);
		m_MDSecurityDefinition_123_.set_CFICode("rdffdoj");
		m_MDSecurityDefinition_123_.set_UnderlyingProduct("vuvxdyy");
		m_MDSecurityDefinition_123_.set_SecurityExchange("irdgj");
		m_MDSecurityDefinition_123_.set_PricingModel("qsklauy");
		m_MDSecurityDefinition_123_.set_MinCabPrice(6);
		MDSecurityDefinition_123::SecurityAltIDs test_SecurityAltIDs;
		for(size_t i=0; i<5; ++i) {
			generate_MDSecurityDefinition_123_SecurityAltIDs(test_SecurityAltIDs);
			m_MDSecurityDefinition_123_.append_SecurityAltIDs(test_SecurityAltIDs);
		}
		m_MDSecurityDefinition_123_.set_ExpirationCycle(3);
		m_MDSecurityDefinition_123_.set_UnitOfMeasureQty("eu");
		m_MDSecurityDefinition_123_.set_StrikePrice(13);
		m_MDSecurityDefinition_123_.set_StrikeCurrency("fmschrhhp");
		m_MDSecurityDefinition_123_.set_MinTradeVol(13);
		m_MDSecurityDefinition_123_.set_MaxTradeVol(18);
		m_MDSecurityDefinition_123_.set_Currency("oau");
		m_MDSecurityDefinition_123_.set_SettlCurrency("smz");
		MDSecurityDefinition_123::MDFeedTypes test_MDFeedTypes;
		for(size_t i=0; i<2; ++i) {
			generate_MDSecurityDefinition_123_MDFeedTypes(test_MDFeedTypes);
			m_MDSecurityDefinition_123_.append_MDFeedTypes(test_MDFeedTypes);
		}
		m_MDSecurityDefinition_123_.set_MatchAlgo("vctutcaorwv");
		m_MDSecurityDefinition_123_.set_SecuritySubType("oxoigyx");
		MDSecurityDefinition_123::Underlyings test_Underlyings;
		for(size_t i=0; i<6; ++i) {
			generate_MDSecurityDefinition_123_Underlyings(test_Underlyings);
			m_MDSecurityDefinition_123_.append_Underlyings(test_Underlyings);
		}
		m_MDSecurityDefinition_123_.set_MaxPriceVariation("igsdtlruogs");
		m_MDSecurityDefinition_123_.set_ImpliedMarketIndicator("zmod");
		MDSecurityDefinition_123::InstrAttrib test_InstrAttrib;
		for(size_t i=0; i<9; ++i) {
			generate_MDSecurityDefinition_123_InstrAttrib(test_InstrAttrib);
			m_MDSecurityDefinition_123_.append_InstrAttrib(test_InstrAttrib);
		}
		m_MDSecurityDefinition_123_.set_MaturityMonthYear(0);
		m_MDSecurityDefinition_123_.set_MinPriceIncrement(15);
		m_MDSecurityDefinition_123_.set_MinPriceIncrementAmount(2);
		m_MDSecurityDefinition_123_.set_LastUpdateTime(1);
		m_MDSecurityDefinition_123_.set_SecurityUpdateAction("bzrj");
		m_MDSecurityDefinition_123_.set_DisplayFactor(19);
		MDSecurityDefinition_123::Legs test_Legs;
		for(size_t i=0; i<6; ++i) {
			generate_MDSecurityDefinition_123_Legs(test_Legs);
			m_MDSecurityDefinition_123_.append_Legs(test_Legs);
		}
		m_MDSecurityDefinition_123_.set_ApplID("xhrdzu");
		m_MDSecurityDefinition_123_.set_PriceRatio(8);
		m_MDSecurityDefinition_123_.set_ContractMultiplierType(6);
		m_MDSecurityDefinition_123_.set_FlowScheduleType(11);
		m_MDSecurityDefinition_123_.set_ContractMultiplier(14);
		m_MDSecurityDefinition_123_.set_UnitofMeasure("tmvu");
		m_MDSecurityDefinition_123_.set_DecayQuantity(6);
		m_MDSecurityDefinition_123_.set_DecayStartDate(11);
		m_MDSecurityDefinition_123_.set_OriginalContractSize(18);
		m_MDSecurityDefinition_123_.set_ClearedVolume(18);
		m_MDSecurityDefinition_123_.set_OpenInterestQty(3);
		m_MDSecurityDefinition_123_.set_TradingReferenceDate(13);
		MDSecurityDefinition_123::LotTypeRules test_LotTypeRules;
		for(size_t i=0; i<1; ++i) {
			generate_MDSecurityDefinition_123_LotTypeRules(test_LotTypeRules);
			m_MDSecurityDefinition_123_.append_LotTypeRules(test_LotTypeRules);
		}
	}
	void generate_MDSecurityDefinition_123_Events(MDSecurityDefinition_123::Events& s) {
		s.set_EventType(17);
		s.set_EventDate(3);
		s.set_EventTime(12);
	}
	void generate_MDSecurityDefinition_123_SecurityAltIDs(MDSecurityDefinition_123::SecurityAltIDs& s) {
		s.set_SecurityAltID("sjtjrs");
	}
	void generate_MDSecurityDefinition_123_MDFeedTypes(MDSecurityDefinition_123::MDFeedTypes& s) {
		s.set_MDFeedType("kvuetgu");
		s.set_MarketDepth(4);
	}
	void generate_MDSecurityDefinition_123_Underlyings(MDSecurityDefinition_123::Underlyings& s) {
		s.set_UnderlyingSecurityID(15);
	}
	void generate_MDSecurityDefinition_123_InstrAttrib(MDSecurityDefinition_123::InstrAttrib& s) {
		s.set_InstrAttribType(13);
		s.set_InstrAttribValue("fkbqmrgjqv");
	}
	void generate_MDSecurityDefinition_123_Legs(MDSecurityDefinition_123::Legs& s) {
		s.set_LegSymbol("s");
		s.set_LegRatioQty(9);
		s.set_LegSecurityID(5);
		s.set_LegSecurityDesc("eovxjfudmq");
		s.set_LegSide("ig");
		s.set_LegSecurityGroup("xiajlqvdygt");
		s.set_LegCFICode("toeyplomkxu");
		s.set_LegSecuritySubType("cgwoqc");
		s.set_LegCurrency("nnjxybuba");
		s.set_LegMaturityMonthYear(11);
		s.set_LegStrikePrice(5);
		s.set_LegSecurityExchange("ula");
		s.set_LegStrikeCurrency("cnirxildk");
		s.set_LegPrice(19);
		s.set_LegOptionDelta(0);
	}
	void generate_MDSecurityDefinition_123_LotTypeRules(MDSecurityDefinition_123::LotTypeRules& s) {
		s.set_LotType("j");
		s.set_MinLotSize(8);
	}
	void clear_MDSecurityDefinition_123() {
		m_MDSecurityDefinition_123_.clear();
	}
	void generate_MDLogon_124() {
		m_MDLogon_124_.set_MsgSeqNum(19);
		m_MDLogon_124_.set_SendingTime(18);
		m_MDLogon_124_.set_HeartbeatInt(5);
	}
	void clear_MDLogon_124() {
		m_MDLogon_124_.clear();
	}
	void generate_MDIncRefresh_125() {
		m_MDIncRefresh_125_.set_MsgSeqNum(4);
		m_MDIncRefresh_125_.set_SendingTime(19);
		m_MDIncRefresh_125_.set_PosDupFlag("ss");
		m_MDIncRefresh_125_.set_TradeDate(11);
		MDIncRefresh_125::MDEntries test_MDEntries;
		for(size_t i=0; i<9; ++i) {
			generate_MDIncRefresh_125_MDEntries(test_MDEntries);
			m_MDIncRefresh_125_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_125_MDEntries(MDIncRefresh_125::MDEntries& s) {
		s.set_MDUpdateAction(9);
		s.set_SecurityID(8);
		s.set_RptSeq(19);
		s.set_MDEntryType("fphkcrb");
		s.set_MDEntryPx(13);
		s.set_MDEntrySize(3);
		s.set_MDEntryTime(0);
		s.set_OpenCloseSettleFlag(15);
		s.set_SettlDate(4);
		s.set_FixingBracket("fkulssdkqvc");
	}
	void clear_MDIncRefresh_125() {
		m_MDIncRefresh_125_.clear();
	}
	void generate_MDLogout_126() {
		m_MDLogout_126_.set_MsgSeqNum(4);
		m_MDLogout_126_.set_SendingTime(16);
		m_MDLogout_126_.set_Text("djmsqdzag");
	}
	void clear_MDLogout_126() {
		m_MDLogout_126_.clear();
	}
	void generate_MDSecurityStatus_127() {
		m_MDSecurityStatus_127_.set_MsgSeqNum(0);
		m_MDSecurityStatus_127_.set_SendingTime(5);
		m_MDSecurityStatus_127_.set_PosDupFlag("s");
		m_MDSecurityStatus_127_.set_SecurityID(17);
		m_MDSecurityStatus_127_.set_TradeDate(12);
		m_MDSecurityStatus_127_.set_HighPx(0);
		m_MDSecurityStatus_127_.set_LowPx(8);
		m_MDSecurityStatus_127_.set_Symbol("oyhitmt");
		m_MDSecurityStatus_127_.set_SecurityTradingStatus(9);
		m_MDSecurityStatus_127_.set_HaltReason(1);
		m_MDSecurityStatus_127_.set_SecurityTradingEvent(7);
	}
	void clear_MDSecurityStatus_127() {
		m_MDSecurityStatus_127_.clear();
	}
	void generate_MDQuoteRequest_128() {
		m_MDQuoteRequest_128_.set_MsgSeqNum(5);
		m_MDQuoteRequest_128_.set_SendingTime(17);
		m_MDQuoteRequest_128_.set_PosDupFlag("wiko");
		m_MDQuoteRequest_128_.set_QuoteReqID("npzvhf");
		MDQuoteRequest_128::RelatedSym test_RelatedSym;
		for(size_t i=0; i<9; ++i) {
			generate_MDQuoteRequest_128_RelatedSym(test_RelatedSym);
			m_MDQuoteRequest_128_.append_RelatedSym(test_RelatedSym);
		}
	}
	void generate_MDQuoteRequest_128_RelatedSym(MDQuoteRequest_128::RelatedSym& s) {
		s.set_OrderQty(3);
		s.set_Side(6);
		s.set_TransactTime(1);
		s.set_QuoteType(3);
		s.set_SecurityID(7);
	}
	void clear_MDQuoteRequest_128() {
		m_MDQuoteRequest_128_.clear();
	}
	void generate_MDIncRefresh_129() {
		m_MDIncRefresh_129_.set_MsgSeqNum(1);
		m_MDIncRefresh_129_.set_SendingTime(8);
		m_MDIncRefresh_129_.set_PosDupFlag("acumxft");
		m_MDIncRefresh_129_.set_TradeDate(9);
		MDIncRefresh_129::MDEntries test_MDEntries;
		for(size_t i=0; i<6; ++i) {
			generate_MDIncRefresh_129_MDEntries(test_MDEntries);
			m_MDIncRefresh_129_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_129_MDEntries(MDIncRefresh_129::MDEntries& s) {
		s.set_MDUpdateAction(6);
		s.set_MDPriceLevel(9);
		s.set_MDEntryType("bdkcszdq");
		s.set_SecurityID(3);
		s.set_RptSeq(0);
		s.set_QuoteCondition("ijs");
		s.set_MDEntryPx(2);
		s.set_NumberOfOrders(6);
		s.set_MDEntryTime(19);
		s.set_MDEntrySize(2);
		s.set_TradingSessionID("j");
		s.set_NetChgPrevDay(18);
		s.set_TickDirection("xmtqjuleq");
		s.set_OpenCloseSettleFlag(4);
		s.set_SettlDate(3);
	}
	void clear_MDIncRefresh_129() {
		m_MDIncRefresh_129_.clear();
	}
	void generate_MDSecurityStatus_130() {
		m_MDSecurityStatus_130_.set_MsgSeqNum(11);
		m_MDSecurityStatus_130_.set_SendingTime(12);
		m_MDSecurityStatus_130_.set_PosDupFlag("cvtlg");
		m_MDSecurityStatus_130_.set_SecurityID(16);
		m_MDSecurityStatus_130_.set_TradeDate(16);
		m_MDSecurityStatus_130_.set_HighPx(7);
		m_MDSecurityStatus_130_.set_LowPx(7);
		m_MDSecurityStatus_130_.set_Symbol("dwwsgkg");
		m_MDSecurityStatus_130_.set_SecurityTradingStatus(13);
		m_MDSecurityStatus_130_.set_HaltReason(2);
		m_MDSecurityStatus_130_.set_SecurityTradingEvent(18);
	}
	void clear_MDSecurityStatus_130() {
		m_MDSecurityStatus_130_.clear();
	}
	void generate_MDIncRefresh_131() {
		m_MDIncRefresh_131_.set_MsgSeqNum(18);
		m_MDIncRefresh_131_.set_SendingTime(3);
		m_MDIncRefresh_131_.set_PosDupFlag("jlmzunry");
		m_MDIncRefresh_131_.set_TradeDate(10);
		MDIncRefresh_131::MDEntries test_MDEntries;
		for(size_t i=0; i<1; ++i) {
			generate_MDIncRefresh_131_MDEntries(test_MDEntries);
			m_MDIncRefresh_131_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_131_MDEntries(MDIncRefresh_131::MDEntries& s) {
		s.set_MDUpdateAction(19);
		s.set_MDPriceLevel(7);
		s.set_MDEntryType("kzhvlkr");
		s.set_OpenCloseSettleFlag(17);
		s.set_SettlDate(3);
		s.set_SecurityID(11);
		s.set_RptSeq(8);
		s.set_MDEntryPx(13);
		s.set_MDEntryTime(5);
		s.set_MDEntrySize(10);
		s.set_NumberOfOrders(11);
		s.set_TradingSessionID("cjopy");
		s.set_NetChgPrevDay(9);
		s.set_TradeVolume(12);
		s.set_TradeCondition("ekf");
		s.set_TickDirection("bjlnkuky");
		s.set_QuoteCondition("eho");
		s.set_AggressorSide(19);
		s.set_MatchEventIndicator("bkyrpca");
	}
	void clear_MDIncRefresh_131() {
		m_MDIncRefresh_131_.clear();
	}
	void generate_MDNewsMessage_132() {
		m_MDNewsMessage_132_.set_MsgSeqNum(15);
		m_MDNewsMessage_132_.set_SendingTime(5);
		m_MDNewsMessage_132_.set_Headline("ubmalttpcg");
		m_MDNewsMessage_132_.set_PosDupFlag("pcpnjtwxyc");
		MDNewsMessage_132::LinesOfText test_LinesOfText;
		for(size_t i=0; i<5; ++i) {
			generate_MDNewsMessage_132_LinesOfText(test_LinesOfText);
			m_MDNewsMessage_132_.append_LinesOfText(test_LinesOfText);
		}
	}
	void generate_MDNewsMessage_132_LinesOfText(MDNewsMessage_132::LinesOfText& s) {
		s.set_text("csceuk");
	}
	void clear_MDNewsMessage_132() {
		m_MDNewsMessage_132_.clear();
	}
	void generate_MDHeartbeat_133() {
		m_MDHeartbeat_133_.set_MsgSeqNum(3);
		m_MDHeartbeat_133_.set_SendingTime(17);
		m_MDHeartbeat_133_.set_PosDupFlag("zjfmc");
	}
	void clear_MDHeartbeat_133() {
		m_MDHeartbeat_133_.clear();
	}
	void generate_MDIncRefresh_134() {
		m_MDIncRefresh_134_.set_MsgSeqNum(10);
		m_MDIncRefresh_134_.set_SendingTime(15);
		m_MDIncRefresh_134_.set_PosDupFlag("iiwkzl");
		m_MDIncRefresh_134_.set_TradeDate(18);
		MDIncRefresh_134::MDEntries test_MDEntries;
		for(size_t i=0; i<9; ++i) {
			generate_MDIncRefresh_134_MDEntries(test_MDEntries);
			m_MDIncRefresh_134_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_134_MDEntries(MDIncRefresh_134::MDEntries& s) {
		s.set_MDUpdateAction(15);
		s.set_NumberOfOrders(5);
		s.set_MDEntryType("luhpomtj");
		s.set_OpenCloseSettleFlag(4);
		s.set_SettlDate(5);
		s.set_SecurityID(6);
		s.set_RptSeq(14);
		s.set_TradingSessionID("nhcpjg");
		s.set_MDEntrySize(18);
		s.set_MDEntryTime(7);
		s.set_MDPriceLevel(12);
		s.set_MDEntryPx(2);
		s.set_NetChgPrevDay(0);
		s.set_TradeVolume(7);
		s.set_TickDirection("ylr");
		s.set_QuoteCondition("fcqpsebnn");
		s.set_TradeCondition("etzugjzwsh");
		s.set_AggressorSide(18);
		s.set_MatchEventIndicator("xpqqwq");
	}
	void clear_MDIncRefresh_134() {
		m_MDIncRefresh_134_.clear();
	}
	void generate_MDIncRefresh_135() {
		m_MDIncRefresh_135_.set_MsgSeqNum(11);
		m_MDIncRefresh_135_.set_SendingTime(19);
		m_MDIncRefresh_135_.set_PosDupFlag("i");
		m_MDIncRefresh_135_.set_TradeDate(14);
		MDIncRefresh_135::MDEntries test_MDEntries;
		for(size_t i=0; i<9; ++i) {
			generate_MDIncRefresh_135_MDEntries(test_MDEntries);
			m_MDIncRefresh_135_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_135_MDEntries(MDIncRefresh_135::MDEntries& s) {
		s.set_MDUpdateAction(9);
		s.set_MDPriceLevel(12);
		s.set_MDEntryType("azvx");
		s.set_OpenCloseSettleFlag(8);
		s.set_SettlDate(15);
		s.set_SecurityID(13);
		s.set_RptSeq(6);
		s.set_QuoteCondition("iztcgqqffg");
		s.set_MDEntryPx(5);
		s.set_NumberOfOrders(3);
		s.set_MDEntryTime(8);
		s.set_MDEntrySize(16);
		s.set_TradingSessionID("i");
		s.set_NetChgPrevDay(17);
		s.set_TradeVolume(17);
		s.set_TradeCondition("ivr");
		s.set_TickDirection("wpiagjddr");
		s.set_AggressorSide(12);
		s.set_MatchEventIndicator("wnpmswvszr");
	}
	void clear_MDIncRefresh_135() {
		m_MDIncRefresh_135_.clear();
	}
	void generate_MDIncRefresh_136() {
		m_MDIncRefresh_136_.set_MsgSeqNum(14);
		m_MDIncRefresh_136_.set_SendingTime(4);
		m_MDIncRefresh_136_.set_PosDupFlag("b");
		m_MDIncRefresh_136_.set_TradeDate(13);
		MDIncRefresh_136::MDEntries test_MDEntries;
		for(size_t i=0; i<2; ++i) {
			generate_MDIncRefresh_136_MDEntries(test_MDEntries);
			m_MDIncRefresh_136_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_136_MDEntries(MDIncRefresh_136::MDEntries& s) {
		s.set_MDUpdateAction(10);
		s.set_MDPriceLevel(2);
		s.set_MDEntryType("xvt");
		s.set_OpenCloseSettleFlag(7);
		s.set_SettlDate(19);
		s.set_TradingSessionID("ra");
		s.set_NetChgPrevDay(9);
		s.set_TradeVolume(4);
		s.set_NumberOfOrders(11);
		s.set_SecurityID(18);
		s.set_RptSeq(18);
		s.set_MDEntryTime(16);
		s.set_MDEntryPx(5);
		s.set_MDEntrySize(7);
		s.set_TradeCondition("pqeqjxh");
		s.set_TickDirection("akwohc");
		s.set_QuoteCondition("ewvb");
		s.set_AggressorSide(19);
		s.set_MatchEventIndicator("ccy");
	}
	void clear_MDIncRefresh_136() {
		m_MDIncRefresh_136_.clear();
	}
	void generate_MDIncRefresh_138() {
		m_MDIncRefresh_138_.set_MsgSeqNum(17);
		m_MDIncRefresh_138_.set_SendingTime(6);
		m_MDIncRefresh_138_.set_PosDupFlag("b");
		m_MDIncRefresh_138_.set_TradeDate(3);
		MDIncRefresh_138::MDEntries test_MDEntries;
		for(size_t i=0; i<1; ++i) {
			generate_MDIncRefresh_138_MDEntries(test_MDEntries);
			m_MDIncRefresh_138_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_138_MDEntries(MDIncRefresh_138::MDEntries& s) {
		s.set_MDUpdateAction(1);
		s.set_MDPriceLevel(6);
		s.set_MDEntryType("ujd");
		s.set_OpenCloseSettleFlag(13);
		s.set_SettlDate(16);
		s.set_SecurityID(8);
		s.set_RptSeq(5);
		s.set_QuoteCondition("mijpvnnspm");
		s.set_MDEntryPx(12);
		s.set_NumberOfOrders(17);
		s.set_MDEntryTime(11);
		s.set_MDEntrySize(11);
		s.set_TradingSessionID("xqdz");
		s.set_NetChgPrevDay(16);
		s.set_TradeVolume(12);
		s.set_TradeCondition("okat");
		s.set_TickDirection("sizvwhgnew");
		s.set_AggressorSide(12);
		s.set_MatchEventIndicator("nn");
	}
	void clear_MDIncRefresh_138() {
		m_MDIncRefresh_138_.clear();
	}
	void generate_MDSecurityDefinition_139() {
		m_MDSecurityDefinition_139_.set_MsgSeqNum(17);
		m_MDSecurityDefinition_139_.set_SendingTime(16);
		m_MDSecurityDefinition_139_.set_PosDupFlag("oideleydyo");
		m_MDSecurityDefinition_139_.set_TotNumReports(18);
		MDSecurityDefinition_139::Events test_Events;
		for(size_t i=0; i<2; ++i) {
			generate_MDSecurityDefinition_139_Events(test_Events);
			m_MDSecurityDefinition_139_.append_Events(test_Events);
		}
		m_MDSecurityDefinition_139_.set_TradingReferencePrice(2);
		m_MDSecurityDefinition_139_.set_SettlePriceType("ts");
		m_MDSecurityDefinition_139_.set_HighLimitPx(14);
		m_MDSecurityDefinition_139_.set_LowLimitPx(10);
		m_MDSecurityDefinition_139_.set_SecurityGroup("dweks");
		m_MDSecurityDefinition_139_.set_Symbol("jftqlzfvd");
		m_MDSecurityDefinition_139_.set_SecurityDesc("ghkmfac");
		m_MDSecurityDefinition_139_.set_SecurityID(8);
		m_MDSecurityDefinition_139_.set_CFICode("zzcu");
		m_MDSecurityDefinition_139_.set_UnderlyingProduct("txnxjgb");
		m_MDSecurityDefinition_139_.set_SecurityExchange("nxjbw");
		m_MDSecurityDefinition_139_.set_PricingModel("wzdfjprqqv");
		m_MDSecurityDefinition_139_.set_MinCabPrice(10);
		MDSecurityDefinition_139::SecurityAltIDs test_SecurityAltIDs;
		for(size_t i=0; i<7; ++i) {
			generate_MDSecurityDefinition_139_SecurityAltIDs(test_SecurityAltIDs);
			m_MDSecurityDefinition_139_.append_SecurityAltIDs(test_SecurityAltIDs);
		}
		m_MDSecurityDefinition_139_.set_ExpirationCycle(4);
		m_MDSecurityDefinition_139_.set_UnitOfMeasureQty("bqowq");
		m_MDSecurityDefinition_139_.set_StrikePrice(4);
		m_MDSecurityDefinition_139_.set_StrikeCurrency("z");
		m_MDSecurityDefinition_139_.set_MinTradeVol(0);
		m_MDSecurityDefinition_139_.set_MaxTradeVol(18);
		m_MDSecurityDefinition_139_.set_Currency("xtdyqtxrwca");
		m_MDSecurityDefinition_139_.set_SettlCurrency("tre");
		MDSecurityDefinition_139::MDFeedTypes test_MDFeedTypes;
		for(size_t i=0; i<6; ++i) {
			generate_MDSecurityDefinition_139_MDFeedTypes(test_MDFeedTypes);
			m_MDSecurityDefinition_139_.append_MDFeedTypes(test_MDFeedTypes);
		}
		m_MDSecurityDefinition_139_.set_MatchAlgo("e");
		m_MDSecurityDefinition_139_.set_SecuritySubType("phbfdrh");
		MDSecurityDefinition_139::Underlyings test_Underlyings;
		for(size_t i=0; i<11; ++i) {
			generate_MDSecurityDefinition_139_Underlyings(test_Underlyings);
			m_MDSecurityDefinition_139_.append_Underlyings(test_Underlyings);
		}
		m_MDSecurityDefinition_139_.set_MaxPriceVariation("ttktm");
		m_MDSecurityDefinition_139_.set_ImpliedMarketIndicator("tci");
		MDSecurityDefinition_139::InstrAttrib test_InstrAttrib;
		for(size_t i=0; i<2; ++i) {
			generate_MDSecurityDefinition_139_InstrAttrib(test_InstrAttrib);
			m_MDSecurityDefinition_139_.append_InstrAttrib(test_InstrAttrib);
		}
		m_MDSecurityDefinition_139_.set_MaturityMonthYear(10);
		m_MDSecurityDefinition_139_.set_MinPriceIncrement(5);
		m_MDSecurityDefinition_139_.set_MinPriceIncrementAmount(16);
		m_MDSecurityDefinition_139_.set_LastUpdateTime(16);
		m_MDSecurityDefinition_139_.set_SecurityUpdateAction("lp");
		m_MDSecurityDefinition_139_.set_DisplayFactor(3);
		MDSecurityDefinition_139::Legs test_Legs;
		for(size_t i=0; i<1; ++i) {
			generate_MDSecurityDefinition_139_Legs(test_Legs);
			m_MDSecurityDefinition_139_.append_Legs(test_Legs);
		}
		m_MDSecurityDefinition_139_.set_ApplID("d");
		m_MDSecurityDefinition_139_.set_PriceRatio(4);
		m_MDSecurityDefinition_139_.set_ContractMultiplierType(0);
		m_MDSecurityDefinition_139_.set_FlowScheduleType(11);
		m_MDSecurityDefinition_139_.set_ContractMultiplier(15);
		m_MDSecurityDefinition_139_.set_UnitofMeasure("qi");
		m_MDSecurityDefinition_139_.set_DecayQuantity(15);
		m_MDSecurityDefinition_139_.set_DecayStartDate(3);
		m_MDSecurityDefinition_139_.set_OriginalContractSize(6);
		m_MDSecurityDefinition_139_.set_ClearedVolume(12);
		m_MDSecurityDefinition_139_.set_OpenInterestQty(2);
		m_MDSecurityDefinition_139_.set_TradingReferenceDate(15);
		MDSecurityDefinition_139::LotTypeRules test_LotTypeRules;
		for(size_t i=0; i<3; ++i) {
			generate_MDSecurityDefinition_139_LotTypeRules(test_LotTypeRules);
			m_MDSecurityDefinition_139_.append_LotTypeRules(test_LotTypeRules);
		}
	}
	void generate_MDSecurityDefinition_139_Events(MDSecurityDefinition_139::Events& s) {
		s.set_EventType(16);
		s.set_EventDate(8);
		s.set_EventTime(11);
	}
	void generate_MDSecurityDefinition_139_SecurityAltIDs(MDSecurityDefinition_139::SecurityAltIDs& s) {
		s.set_SecurityAltID("jltsernrh");
	}
	void generate_MDSecurityDefinition_139_MDFeedTypes(MDSecurityDefinition_139::MDFeedTypes& s) {
		s.set_MDFeedType("vqtjogyr");
		s.set_MarketDepth(9);
	}
	void generate_MDSecurityDefinition_139_Underlyings(MDSecurityDefinition_139::Underlyings& s) {
		s.set_UnderlyingSymbol("ckilstmk");
		s.set_UnderlyingSecurityID(6);
	}
	void generate_MDSecurityDefinition_139_InstrAttrib(MDSecurityDefinition_139::InstrAttrib& s) {
		s.set_InstrAttribType(13);
		s.set_InstrAttribValue("ftcx");
	}
	void generate_MDSecurityDefinition_139_Legs(MDSecurityDefinition_139::Legs& s) {
		s.set_LegSymbol("umqda");
		s.set_LegRatioQty(3);
		s.set_LegSecurityID(5);
		s.set_LegSecurityDesc("uhcuyzcdllq");
		s.set_LegSide("gcpckzjfdg");
		s.set_LegSecurityGroup("xsucugvo");
		s.set_LegCFICode("esxf");
		s.set_LegSecuritySubType("bkeoajvey");
		s.set_LegCurrency("ozjtfrz");
		s.set_LegMaturityMonthYear(8);
		s.set_LegStrikePrice(14);
		s.set_LegSecurityExchange("hece");
		s.set_LegStrikeCurrency("elmdqffcl");
		s.set_LegPrice(9);
		s.set_LegOptionDelta(10);
	}
	void generate_MDSecurityDefinition_139_LotTypeRules(MDSecurityDefinition_139::LotTypeRules& s) {
		s.set_LotType("qgvqxw");
		s.set_MinLotSize(17);
	}
	void clear_MDSecurityDefinition_139() {
		m_MDSecurityDefinition_139_.clear();
	}
	void generate_MDSecurityDefinition_140() {
		m_MDSecurityDefinition_140_.set_MsgSeqNum(0);
		m_MDSecurityDefinition_140_.set_SendingTime(17);
		m_MDSecurityDefinition_140_.set_PosDupFlag("sieo");
		m_MDSecurityDefinition_140_.set_TotNumReports(19);
		MDSecurityDefinition_140::Events test_Events;
		for(size_t i=0; i<3; ++i) {
			generate_MDSecurityDefinition_140_Events(test_Events);
			m_MDSecurityDefinition_140_.append_Events(test_Events);
		}
		m_MDSecurityDefinition_140_.set_TradingReferencePrice(8);
		m_MDSecurityDefinition_140_.set_SettlePriceType("fweua");
		m_MDSecurityDefinition_140_.set_HighLimitPx(18);
		m_MDSecurityDefinition_140_.set_LowLimitPx(19);
		m_MDSecurityDefinition_140_.set_SecurityGroup("ypy");
		m_MDSecurityDefinition_140_.set_Symbol("jrjgjifkaie");
		m_MDSecurityDefinition_140_.set_SecurityDesc("qjifu");
		m_MDSecurityDefinition_140_.set_SecurityID(10);
		m_MDSecurityDefinition_140_.set_CFICode("z");
		m_MDSecurityDefinition_140_.set_UnderlyingProduct("hv");
		m_MDSecurityDefinition_140_.set_SecurityExchange("gxcemcjxtu");
		m_MDSecurityDefinition_140_.set_PricingModel("ccloevtzme");
		m_MDSecurityDefinition_140_.set_MinCabPrice(1);
		MDSecurityDefinition_140::SecurityAltIDs test_SecurityAltIDs;
		for(size_t i=0; i<5; ++i) {
			generate_MDSecurityDefinition_140_SecurityAltIDs(test_SecurityAltIDs);
			m_MDSecurityDefinition_140_.append_SecurityAltIDs(test_SecurityAltIDs);
		}
		m_MDSecurityDefinition_140_.set_ExpirationCycle(8);
		m_MDSecurityDefinition_140_.set_UnitOfMeasureQty("uzfe");
		m_MDSecurityDefinition_140_.set_StrikePrice(5);
		m_MDSecurityDefinition_140_.set_StrikeCurrency("kug");
		m_MDSecurityDefinition_140_.set_MinTradeVol(10);
		m_MDSecurityDefinition_140_.set_MaxTradeVol(6);
		m_MDSecurityDefinition_140_.set_Currency("xhernivax");
		m_MDSecurityDefinition_140_.set_SettlCurrency("yszkwiduqav");
		MDSecurityDefinition_140::MDFeedTypes test_MDFeedTypes;
		for(size_t i=0; i<7; ++i) {
			generate_MDSecurityDefinition_140_MDFeedTypes(test_MDFeedTypes);
			m_MDSecurityDefinition_140_.append_MDFeedTypes(test_MDFeedTypes);
		}
		m_MDSecurityDefinition_140_.set_MatchAlgo("qzom");
		m_MDSecurityDefinition_140_.set_SecuritySubType("euscewv");
		MDSecurityDefinition_140::Underlyings test_Underlyings;
		for(size_t i=0; i<11; ++i) {
			generate_MDSecurityDefinition_140_Underlyings(test_Underlyings);
			m_MDSecurityDefinition_140_.append_Underlyings(test_Underlyings);
		}
		m_MDSecurityDefinition_140_.set_MaxPriceVariation("twftuxse");
		m_MDSecurityDefinition_140_.set_ImpliedMarketIndicator("cjr");
		MDSecurityDefinition_140::InstrAttrib test_InstrAttrib;
		for(size_t i=0; i<11; ++i) {
			generate_MDSecurityDefinition_140_InstrAttrib(test_InstrAttrib);
			m_MDSecurityDefinition_140_.append_InstrAttrib(test_InstrAttrib);
		}
		m_MDSecurityDefinition_140_.set_MarketSegmentID(11);
		m_MDSecurityDefinition_140_.set_MaturityMonthYear(13);
		m_MDSecurityDefinition_140_.set_MinPriceIncrement(0);
		m_MDSecurityDefinition_140_.set_MinPriceIncrementAmount(1);
		m_MDSecurityDefinition_140_.set_LastUpdateTime(19);
		m_MDSecurityDefinition_140_.set_SecurityUpdateAction("bs");
		m_MDSecurityDefinition_140_.set_DisplayFactor(11);
		MDSecurityDefinition_140::Legs test_Legs;
		for(size_t i=0; i<11; ++i) {
			generate_MDSecurityDefinition_140_Legs(test_Legs);
			m_MDSecurityDefinition_140_.append_Legs(test_Legs);
		}
		m_MDSecurityDefinition_140_.set_ApplID("tkurh");
		m_MDSecurityDefinition_140_.set_PriceRatio(2);
		m_MDSecurityDefinition_140_.set_ContractMultiplierType(10);
		m_MDSecurityDefinition_140_.set_FlowScheduleType(18);
		m_MDSecurityDefinition_140_.set_ContractMultiplier(14);
		m_MDSecurityDefinition_140_.set_UnitofMeasure("tednky");
		m_MDSecurityDefinition_140_.set_DecayQuantity(10);
		m_MDSecurityDefinition_140_.set_DecayStartDate(5);
		m_MDSecurityDefinition_140_.set_OriginalContractSize(16);
		m_MDSecurityDefinition_140_.set_ClearedVolume(13);
		m_MDSecurityDefinition_140_.set_OpenInterestQty(17);
		m_MDSecurityDefinition_140_.set_TradingReferenceDate(9);
		MDSecurityDefinition_140::LotTypeRules test_LotTypeRules;
		for(size_t i=0; i<7; ++i) {
			generate_MDSecurityDefinition_140_LotTypeRules(test_LotTypeRules);
			m_MDSecurityDefinition_140_.append_LotTypeRules(test_LotTypeRules);
		}
	}
	void generate_MDSecurityDefinition_140_Events(MDSecurityDefinition_140::Events& s) {
		s.set_EventType(18);
		s.set_EventDate(0);
		s.set_EventTime(13);
	}
	void generate_MDSecurityDefinition_140_SecurityAltIDs(MDSecurityDefinition_140::SecurityAltIDs& s) {
		s.set_SecurityAltID("gzavsmrk");
	}
	void generate_MDSecurityDefinition_140_MDFeedTypes(MDSecurityDefinition_140::MDFeedTypes& s) {
		s.set_MDFeedType("fkurnpvsffr");
		s.set_MarketDepth(1);
	}
	void generate_MDSecurityDefinition_140_Underlyings(MDSecurityDefinition_140::Underlyings& s) {
		s.set_UnderlyingSecurityID(9);
	}
	void generate_MDSecurityDefinition_140_InstrAttrib(MDSecurityDefinition_140::InstrAttrib& s) {
		s.set_InstrAttribType(13);
		s.set_InstrAttribValue("eqnwelqlmsi");
	}
	void generate_MDSecurityDefinition_140_Legs(MDSecurityDefinition_140::Legs& s) {
		s.set_LegSymbol("ezqyfa");
		s.set_LegRatioQty(6);
		s.set_LegSecurityID(14);
		s.set_LegSecurityDesc("luiqbbpc");
		s.set_LegSide("ziepf");
		s.set_LegSecurityGroup("cxuo");
		s.set_LegCFICode("cuudluinqh");
		s.set_LegSecuritySubType("cdmuepkjcl");
		s.set_LegCurrency("iay");
		s.set_LegMaturityMonthYear(15);
		s.set_LegStrikePrice(4);
		s.set_LegSecurityExchange("nsorniva");
		s.set_LegStrikeCurrency("fnvotz");
		s.set_LegPrice(13);
		s.set_LegOptionDelta(7);
	}
	void generate_MDSecurityDefinition_140_LotTypeRules(MDSecurityDefinition_140::LotTypeRules& s) {
		s.set_LotType("y");
		s.set_MinLotSize(14);
	}
	void clear_MDSecurityDefinition_140() {
		m_MDSecurityDefinition_140_.clear();
	}
	void generate_MDIncRefresh_141() {
		m_MDIncRefresh_141_.set_MsgSeqNum(10);
		m_MDIncRefresh_141_.set_SendingTime(15);
		m_MDIncRefresh_141_.set_PosDupFlag("rajubay");
		m_MDIncRefresh_141_.set_TradeDate(9);
		MDIncRefresh_141::MDEntries test_MDEntries;
		for(size_t i=0; i<1; ++i) {
			generate_MDIncRefresh_141_MDEntries(test_MDEntries);
			m_MDIncRefresh_141_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_141_MDEntries(MDIncRefresh_141::MDEntries& s) {
		s.set_MDUpdateAction(3);
		s.set_MDEntryType("hgxcickxayq");
		s.set_SecurityID(7);
		s.set_RptSeq(10);
		s.set_MDEntryPx(17);
		s.set_MDEntrySize(13);
		s.set_NetChgPrevDay(6);
		s.set_TradeVolume(4);
		s.set_TickDirection("zwtbf");
		s.set_TradeCondition("cipdyiqh");
		s.set_MDEntryTime(6);
		s.set_AggressorSide(6);
		s.set_MatchEventIndicator("y");
		s.set_TradeID(8);
		s.set_NumberOfOrders(6);
	}
	void clear_MDIncRefresh_141() {
		m_MDIncRefresh_141_.clear();
	}
	void generate_MDIncRefresh_142() {
		m_MDIncRefresh_142_.set_MsgSeqNum(4);
		m_MDIncRefresh_142_.set_SendingTime(18);
		m_MDIncRefresh_142_.set_PosDupFlag("ouom");
		m_MDIncRefresh_142_.set_TradeDate(11);
		MDIncRefresh_142::MDEntries test_MDEntries;
		for(size_t i=0; i<4; ++i) {
			generate_MDIncRefresh_142_MDEntries(test_MDEntries);
			m_MDIncRefresh_142_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_142_MDEntries(MDIncRefresh_142::MDEntries& s) {
		s.set_MDUpdateAction(0);
		s.set_MDEntryType("hgm");
		s.set_SecurityID(1);
		s.set_RptSeq(18);
		s.set_MDEntryPx(3);
		s.set_MDEntryTime(7);
		s.set_MDEntrySize(10);
		s.set_NetChgPrevDay(18);
		s.set_TradeVolume(3);
		s.set_TradeCondition("bhdrxpsslo");
		s.set_TickDirection("icgy");
		s.set_AggressorSide(6);
		s.set_MatchEventIndicator("farmjd");
		s.set_TradeID(1);
		s.set_NumberOfOrders(19);
	}
	void clear_MDIncRefresh_142() {
		m_MDIncRefresh_142_.clear();
	}
	void generate_MDIncRefresh_143() {
		m_MDIncRefresh_143_.set_MsgSeqNum(6);
		m_MDIncRefresh_143_.set_SendingTime(9);
		m_MDIncRefresh_143_.set_PosDupFlag("aepbnuvlkn");
		m_MDIncRefresh_143_.set_TradeDate(19);
		MDIncRefresh_143::MDEntries test_MDEntries;
		for(size_t i=0; i<4; ++i) {
			generate_MDIncRefresh_143_MDEntries(test_MDEntries);
			m_MDIncRefresh_143_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_143_MDEntries(MDIncRefresh_143::MDEntries& s) {
		s.set_MDUpdateAction(13);
		s.set_MDEntryType("fhaeyylapz");
		s.set_SecurityID(13);
		s.set_RptSeq(0);
		s.set_MDEntryPx(11);
		s.set_MDEntrySize(12);
		s.set_NetChgPrevDay(6);
		s.set_TradeVolume(0);
		s.set_TickDirection("eouibpd");
		s.set_TradeCondition("zq");
		s.set_MDEntryTime(3);
		s.set_AggressorSide(8);
		s.set_MatchEventIndicator("leclicjvdau");
		s.set_TradeID(10);
		s.set_NumberOfOrders(10);
	}
	void clear_MDIncRefresh_143() {
		m_MDIncRefresh_143_.clear();
	}
	void generate_MDIncRefresh_144() {
		m_MDIncRefresh_144_.set_MsgSeqNum(7);
		m_MDIncRefresh_144_.set_SendingTime(15);
		m_MDIncRefresh_144_.set_PosDupFlag("beepbo");
		m_MDIncRefresh_144_.set_TradeDate(3);
		MDIncRefresh_144::MDEntries test_MDEntries;
		for(size_t i=0; i<3; ++i) {
			generate_MDIncRefresh_144_MDEntries(test_MDEntries);
			m_MDIncRefresh_144_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_144_MDEntries(MDIncRefresh_144::MDEntries& s) {
		s.set_MDUpdateAction(11);
		s.set_MDPriceLevel(7);
		s.set_MDEntryType("jzrekvh");
		s.set_OpenCloseSettleFlag(15);
		s.set_SettlDate(9);
		s.set_SecurityID(3);
		s.set_RptSeq(16);
		s.set_MDEntryPx(8);
		s.set_MDEntryTime(0);
		s.set_MDEntrySize(6);
		s.set_NumberOfOrders(5);
		s.set_TradingSessionID("goi");
		s.set_NetChgPrevDay(16);
		s.set_TradeVolume(4);
		s.set_TradeCondition("mhpbajui");
		s.set_TickDirection("e");
		s.set_QuoteCondition("uktptqvf");
		s.set_TradeID(18);
		s.set_AggressorSide(5);
		s.set_MatchEventIndicator("gsaojiub");
	}
	void clear_MDIncRefresh_144() {
		m_MDIncRefresh_144_.clear();
	}
	void generate_MDIncRefresh_145() {
		m_MDIncRefresh_145_.set_MsgSeqNum(1);
		m_MDIncRefresh_145_.set_SendingTime(10);
		m_MDIncRefresh_145_.set_PosDupFlag("ojlygtckc");
		m_MDIncRefresh_145_.set_TradeDate(14);
		MDIncRefresh_145::MDEntries test_MDEntries;
		for(size_t i=0; i<8; ++i) {
			generate_MDIncRefresh_145_MDEntries(test_MDEntries);
			m_MDIncRefresh_145_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_145_MDEntries(MDIncRefresh_145::MDEntries& s) {
		s.set_MDUpdateAction(3);
		s.set_NumberOfOrders(10);
		s.set_MDEntryType("nlvlk");
		s.set_OpenCloseSettleFlag(0);
		s.set_SettlDate(19);
		s.set_SecurityID(3);
		s.set_RptSeq(17);
		s.set_TradingSessionID("mddnalxrxi");
		s.set_MDEntrySize(11);
		s.set_MDEntryTime(5);
		s.set_MDPriceLevel(3);
		s.set_MDEntryPx(13);
		s.set_NetChgPrevDay(11);
		s.set_TradeVolume(15);
		s.set_TickDirection("leidr");
		s.set_QuoteCondition("aefrxim");
		s.set_TradeCondition("wpllsxljw");
		s.set_TradeID(15);
		s.set_AggressorSide(4);
		s.set_MatchEventIndicator("br");
	}
	void clear_MDIncRefresh_145() {
		m_MDIncRefresh_145_.clear();
	}
	void generate_MDIncRefresh_146() {
		m_MDIncRefresh_146_.set_MsgSeqNum(2);
		m_MDIncRefresh_146_.set_SendingTime(6);
		m_MDIncRefresh_146_.set_PosDupFlag("dnrh");
		m_MDIncRefresh_146_.set_TradeDate(12);
		MDIncRefresh_146::MDEntries test_MDEntries;
		for(size_t i=0; i<5; ++i) {
			generate_MDIncRefresh_146_MDEntries(test_MDEntries);
			m_MDIncRefresh_146_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_146_MDEntries(MDIncRefresh_146::MDEntries& s) {
		s.set_MDUpdateAction(15);
		s.set_MDPriceLevel(15);
		s.set_MDEntryType("cicorbecowb");
		s.set_OpenCloseSettleFlag(11);
		s.set_SettlDate(11);
		s.set_SecurityID(15);
		s.set_RptSeq(7);
		s.set_QuoteCondition("yayoiksvdb");
		s.set_MDEntryPx(18);
		s.set_NumberOfOrders(10);
		s.set_MDEntryTime(16);
		s.set_MDEntrySize(13);
		s.set_TradingSessionID("nxqdqrh");
		s.set_NetChgPrevDay(15);
		s.set_TradeVolume(8);
		s.set_TradeCondition("wjmw");
		s.set_TickDirection("tuisltefoh");
		s.set_TradeID(10);
		s.set_AggressorSide(8);
		s.set_MatchEventIndicator("sflfd");
	}
	void clear_MDIncRefresh_146() {
		m_MDIncRefresh_146_.clear();
	}
	void generate_MDIncRefresh_147() {
		m_MDIncRefresh_147_.set_MsgSeqNum(16);
		m_MDIncRefresh_147_.set_SendingTime(11);
		m_MDIncRefresh_147_.set_PosDupFlag("vsofalrmhzi");
		m_MDIncRefresh_147_.set_TradeDate(11);
		MDIncRefresh_147::MDEntries test_MDEntries;
		for(size_t i=0; i<7; ++i) {
			generate_MDIncRefresh_147_MDEntries(test_MDEntries);
			m_MDIncRefresh_147_.append_MDEntries(test_MDEntries);
		}
	}
	void generate_MDIncRefresh_147_MDEntries(MDIncRefresh_147::MDEntries& s) {
		s.set_MDUpdateAction(12);
		s.set_MDPriceLevel(14);
		s.set_MDEntryType("gttpbmpurcz");
		s.set_OpenCloseSettleFlag(14);
		s.set_SettlDate(0);
		s.set_TradingSessionID("qefg");
		s.set_NetChgPrevDay(3);
		s.set_TradeVolume(9);
		s.set_NumberOfOrders(5);
		s.set_SecurityID(2);
		s.set_RptSeq(9);
		s.set_MDEntryTime(14);
		s.set_MDEntryPx(0);
		s.set_MDEntrySize(5);
		s.set_TradeCondition("odutjqozra");
		s.set_TickDirection("l");
		s.set_QuoteCondition("unq");
		s.set_TradeID(17);
		s.set_AggressorSide(3);
		s.set_MatchEventIndicator("hepsjivdl");
	}
	void clear_MDIncRefresh_147() {
		m_MDIncRefresh_147_.clear();
	}
};

}

int main() {
	FIX::BaseFastHandler fast_handler;
	FIX::FastParserTest fast_parser(fast_handler);

	fast_parser.generate_MDIncRefresh_112();
	fast_parser.generate_MDIncRefresh_113();
	fast_parser.generate_MDSnapshotFullRefresh_114();
	fast_parser.generate_MDIncRefresh_115();
	fast_parser.generate_MDIncRefresh_116();
	fast_parser.generate_MDIncRefresh_117();
	fast_parser.generate_MDSnapshotFullRefresh_118();
	fast_parser.generate_MDIncRefresh_119();
	fast_parser.generate_MDIncRefresh_120();
	fast_parser.generate_MDIncRefresh_121();
	fast_parser.generate_MDIncRefresh_122();
	fast_parser.generate_MDSecurityDefinition_123();
	fast_parser.generate_MDLogon_124();
	fast_parser.generate_MDIncRefresh_125();
	fast_parser.generate_MDLogout_126();
	fast_parser.generate_MDSecurityStatus_127();
	fast_parser.generate_MDQuoteRequest_128();
	fast_parser.generate_MDIncRefresh_129();
	fast_parser.generate_MDSecurityStatus_130();
	fast_parser.generate_MDIncRefresh_131();
	fast_parser.generate_MDNewsMessage_132();
	fast_parser.generate_MDHeartbeat_133();
	fast_parser.generate_MDIncRefresh_134();
	fast_parser.generate_MDIncRefresh_135();
	fast_parser.generate_MDIncRefresh_136();
	fast_parser.generate_MDIncRefresh_138();
	fast_parser.generate_MDSecurityDefinition_139();
	fast_parser.generate_MDSecurityDefinition_140();
	fast_parser.generate_MDIncRefresh_141();
	fast_parser.generate_MDIncRefresh_142();
	fast_parser.generate_MDIncRefresh_143();
	fast_parser.generate_MDIncRefresh_144();
	fast_parser.generate_MDIncRefresh_145();
	fast_parser.generate_MDIncRefresh_146();
	fast_parser.generate_MDIncRefresh_147();

	char buf[1048576];
	char* end = buf+1048576;
	char* p(buf);

	fast_parser.encode_MDIncRefresh_112(p, end);
	fast_parser.encode_MDIncRefresh_113(p, end);
	fast_parser.encode_MDSnapshotFullRefresh_114(p, end);
	fast_parser.encode_MDIncRefresh_115(p, end);
	fast_parser.encode_MDIncRefresh_116(p, end);
	fast_parser.encode_MDIncRefresh_117(p, end);
	fast_parser.encode_MDSnapshotFullRefresh_118(p, end);
	fast_parser.encode_MDIncRefresh_119(p, end);
	fast_parser.encode_MDIncRefresh_120(p, end);
	fast_parser.encode_MDIncRefresh_121(p, end);
	fast_parser.encode_MDIncRefresh_122(p, end);
	fast_parser.encode_MDSecurityDefinition_123(p, end);
	fast_parser.encode_MDLogon_124(p, end);
	fast_parser.encode_MDIncRefresh_125(p, end);
	fast_parser.encode_MDLogout_126(p, end);
	fast_parser.encode_MDSecurityStatus_127(p, end);
	fast_parser.encode_MDQuoteRequest_128(p, end);
	fast_parser.encode_MDIncRefresh_129(p, end);
	fast_parser.encode_MDSecurityStatus_130(p, end);
	fast_parser.encode_MDIncRefresh_131(p, end);
	fast_parser.encode_MDNewsMessage_132(p, end);
	fast_parser.encode_MDHeartbeat_133(p, end);
	fast_parser.encode_MDIncRefresh_134(p, end);
	fast_parser.encode_MDIncRefresh_135(p, end);
	fast_parser.encode_MDIncRefresh_136(p, end);
	fast_parser.encode_MDIncRefresh_138(p, end);
	fast_parser.encode_MDSecurityDefinition_139(p, end);
	fast_parser.encode_MDSecurityDefinition_140(p, end);
	fast_parser.encode_MDIncRefresh_141(p, end);
	fast_parser.encode_MDIncRefresh_142(p, end);
	fast_parser.encode_MDIncRefresh_143(p, end);
	fast_parser.encode_MDIncRefresh_144(p, end);
	fast_parser.encode_MDIncRefresh_145(p, end);
	fast_parser.encode_MDIncRefresh_146(p, end);
	fast_parser.encode_MDIncRefresh_147(p, end);

	size_t encoded_len = p-buf;
	std::cout << "Encoded " << encoded_len << " bytes.\n";

	fast_parser.clear_MDIncRefresh_112();
	fast_parser.clear_MDIncRefresh_113();
	fast_parser.clear_MDSnapshotFullRefresh_114();
	fast_parser.clear_MDIncRefresh_115();
	fast_parser.clear_MDIncRefresh_116();
	fast_parser.clear_MDIncRefresh_117();
	fast_parser.clear_MDSnapshotFullRefresh_118();
	fast_parser.clear_MDIncRefresh_119();
	fast_parser.clear_MDIncRefresh_120();
	fast_parser.clear_MDIncRefresh_121();
	fast_parser.clear_MDIncRefresh_122();
	fast_parser.clear_MDSecurityDefinition_123();
	fast_parser.clear_MDLogon_124();
	fast_parser.clear_MDIncRefresh_125();
	fast_parser.clear_MDLogout_126();
	fast_parser.clear_MDSecurityStatus_127();
	fast_parser.clear_MDQuoteRequest_128();
	fast_parser.clear_MDIncRefresh_129();
	fast_parser.clear_MDSecurityStatus_130();
	fast_parser.clear_MDIncRefresh_131();
	fast_parser.clear_MDNewsMessage_132();
	fast_parser.clear_MDHeartbeat_133();
	fast_parser.clear_MDIncRefresh_134();
	fast_parser.clear_MDIncRefresh_135();
	fast_parser.clear_MDIncRefresh_136();
	fast_parser.clear_MDIncRefresh_138();
	fast_parser.clear_MDSecurityDefinition_139();
	fast_parser.clear_MDSecurityDefinition_140();
	fast_parser.clear_MDIncRefresh_141();
	fast_parser.clear_MDIncRefresh_142();
	fast_parser.clear_MDIncRefresh_143();
	fast_parser.clear_MDIncRefresh_144();
	fast_parser.clear_MDIncRefresh_145();
	fast_parser.clear_MDIncRefresh_146();
	fast_parser.clear_MDIncRefresh_147();

	const char* p1(buf);
	while(p1<p)
		fast_parser.scan(p1,p);

	fast_parser.encode_MDIncRefresh_112(p, end);
	fast_parser.encode_MDIncRefresh_113(p, end);
	fast_parser.encode_MDSnapshotFullRefresh_114(p, end);
	fast_parser.encode_MDIncRefresh_115(p, end);
	fast_parser.encode_MDIncRefresh_116(p, end);
	fast_parser.encode_MDIncRefresh_117(p, end);
	fast_parser.encode_MDSnapshotFullRefresh_118(p, end);
	fast_parser.encode_MDIncRefresh_119(p, end);
	fast_parser.encode_MDIncRefresh_120(p, end);
	fast_parser.encode_MDIncRefresh_121(p, end);
	fast_parser.encode_MDIncRefresh_122(p, end);
	fast_parser.encode_MDSecurityDefinition_123(p, end);
	fast_parser.encode_MDLogon_124(p, end);
	fast_parser.encode_MDIncRefresh_125(p, end);
	fast_parser.encode_MDLogout_126(p, end);
	fast_parser.encode_MDSecurityStatus_127(p, end);
	fast_parser.encode_MDQuoteRequest_128(p, end);
	fast_parser.encode_MDIncRefresh_129(p, end);
	fast_parser.encode_MDSecurityStatus_130(p, end);
	fast_parser.encode_MDIncRefresh_131(p, end);
	fast_parser.encode_MDNewsMessage_132(p, end);
	fast_parser.encode_MDHeartbeat_133(p, end);
	fast_parser.encode_MDIncRefresh_134(p, end);
	fast_parser.encode_MDIncRefresh_135(p, end);
	fast_parser.encode_MDIncRefresh_136(p, end);
	fast_parser.encode_MDIncRefresh_138(p, end);
	fast_parser.encode_MDSecurityDefinition_139(p, end);
	fast_parser.encode_MDSecurityDefinition_140(p, end);
	fast_parser.encode_MDIncRefresh_141(p, end);
	fast_parser.encode_MDIncRefresh_142(p, end);
	fast_parser.encode_MDIncRefresh_143(p, end);
	fast_parser.encode_MDIncRefresh_144(p, end);
	fast_parser.encode_MDIncRefresh_145(p, end);
	fast_parser.encode_MDIncRefresh_146(p, end);
	fast_parser.encode_MDIncRefresh_147(p, end);

	std::cout << memcmp(buf, p1, encoded_len) << std::endl;

	return 0;
}
