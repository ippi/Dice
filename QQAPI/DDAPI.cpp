#include "DDAPI.h"

using std::string;
using std::unordered_map;
using namespace DD;

#define DDAPI(Name, ReturnType, ...) using Name##_TYPE = ReturnType (*)(__VA_ARGS__)

DDAPI(_DriverVer, const char*);
DDAPI(GetRootDir, const std::string&);
DDAPI(Reload, bool);
DDAPI(Remake, bool);
DDAPI(Killme, void);
DDAPI(DebugLog, void, const std::string&);
DDAPI(DebugMsg, void, long long, const std::string&);
DDAPI(IsDiceMaid, bool, long long);
DDAPI(GetDiceSisters, const std::set<long long>&);
DDAPI(DiceHeartbeat, void, long long, const std::string&);
DDAPI(DiceUploadBlack, int, long long, long long, long long, const std::string&, std::string&);
DDAPI(DiceUpdate, bool, const std::string&, std::string&);
DDAPI(GetNick, const std::string&, long long, long long);
DDAPI(GetTinyID, long long, long long);
DDAPI(SendPrivateMsg, void, long long, long long, const std::string&);
DDAPI(SendGroupMsg, void, long long, long long, const std::string&);
DDAPI(SendChannelMsg, void, long long, long long, long long, const std::string&);
DDAPI(SendDiscussMsg, void, long long, long long, const std::string&);
DDAPI(GetFriendQQList, const std::set<long long>&, long long);
DDAPI(GetGroupIDList, const std::set<long long>&, long long);
DDAPI(GetGroupMemberList, const std::set<long long>&, long long, long long);
DDAPI(GetGroupAdminList, const std::set<long long>&, long long, long long);
DDAPI(GetGroupAuth, int, long long, long long, long long);
DDAPI(IsGroupAdmin, bool, long long, long long, long long, bool);
DDAPI(IsGroupOwner, bool, long long, long long, long long, bool);
DDAPI(IsGroupMember, bool, long long, long long, long long, bool);
DDAPI(AnswerFriendRequest, void, long long, long long, int, const std::string&);
DDAPI(AnswerGroupInvited, void, long long, long long, int);
DDAPI(GetGroupSize, const GroupSize_t, long long, long long);
DDAPI(GetGroupName, const std::string&, long long, long long);
DDAPI(GetGroupNick, const std::string&, long long, long long, long long);
DDAPI(GetGroupLastMsg, long long, long long, long long, long long);
DDAPI(PrintGroupInfo, const std::string&, long long, long long);
DDAPI(SetGroupKick, void, long long, long long, long long);
DDAPI(SetGroupBan, void, long long, long long, long long, int);
DDAPI(SetGroupAdmin, void, long long, long long, long long, bool);
DDAPI(SetGroupCard, void, long long, long long, long long, const string&);
DDAPI(SetGroupTitle, void, long long, long long, long long, const string&);
DDAPI(SetGroupWholeBan, void, long long, long long, int);
DDAPI(SetGroupLeave, void, long long, long long);
DDAPI(SetDiscussLeave, void, long long, long long);

#define CALLVOID(Name, ...) if(ApiList.count(#Name))reinterpret_cast<Name##_TYPE>(ApiList[#Name])(__VA_ARGS__)
#define CALLGET(Name, ...) ApiList.count(#Name) ? reinterpret_cast<Name##_TYPE>(ApiList[#Name])(__VA_ARGS__)

namespace DD {
	const std::string& getDriVer() {
		static string ver{ CALLGET(_DriverVer) :"" };
		return ver;
	}
	const string& getRootDir() {
		static string dir{ CALLGET(GetRootDir) :"" };
		return dir;
	}
	bool reload() {
		return CALLGET(Reload) :false;
	}
	bool remake() {
		return CALLGET(Remake) :false;
	}
	void killme() {
		CALLVOID(Killme);
	}
	void debugLog(const std::string& log) {
		CALLVOID(DebugLog, log);
	}
	void debugMsg(const std::string& log) {
		CALLVOID(DebugMsg, loginID, log);
	}
	bool isDiceMaid(long long aimQQ){
		return CALLGET(IsDiceMaid, aimQQ) :false;
	}
	std::set<long long> getDiceSisters() {
		return CALLGET(GetDiceSisters) :std::set<long long>();
	}
	void heartbeat(const string& info) {
		CALLVOID(DiceHeartbeat, loginID, info);
	}
	int uploadBlack(long long DiceMaid, long long fromUID, long long fromGID, 
					 const std::string& type, std::string& info) {
		return CALLGET(DiceUploadBlack, DiceMaid, fromUID, fromGID, type, info) :-2;
	}
	bool updateDice(const std::string& ver, std::string& ret) {
		ret = "更新接口不存在";
		return CALLGET(DiceUpdate, ver, ret) :false;
	}
	long long getTinyID() {
		return CALLGET(GetTinyID, loginID) :0;

	}
	std::string getQQNick(long long aimQQ) {
		return CALLGET(GetNick, loginID, aimQQ) :"";
	}
	void sendPrivateMsg(long long rcvQQ, const std::string& msg) {
		if (msg.empty())return;
		CALLVOID(SendPrivateMsg, loginID, rcvQQ, msg);
	}
	void sendGroupMsg(long long rcvChat, const std::string& msg) {
		if (msg.empty())return;
		CALLVOID(SendGroupMsg, loginID, rcvChat, msg);
	}
	void sendChannelMsg(long long rcvGID, long long rcvChID, const std::string& msg) {
		if (msg.empty())return;
		CALLVOID(SendChannelMsg, loginID, rcvGID, rcvChID, msg);
	}
	void sendDiscussMsg(long long rcvChat, const std::string& msg) {
		if (msg.empty())return;
		CALLVOID(SendDiscussMsg, loginID, rcvChat, msg);
	}
	std::set<long long> getFriendQQList() {
		return CALLGET(GetFriendQQList, loginID) :std::set<long long>();
	}
	std::set<long long> getGroupIDList() {
		return CALLGET(GetGroupIDList, loginID) :std::set<long long>();
	}
	std::set<long long> getGroupMemberList(long long aimGroup) {
		return CALLGET(GetGroupMemberList, loginID, aimGroup) :std::set<long long>();
	}
	std::set<long long> getGroupAdminList(long long aimGroup) {
		return CALLGET(GetGroupAdminList, loginID, aimGroup) :std::set<long long>();
	}
	int getGroupAuth(long long llgroup, long long llQQ, int iDefault) {
		int auth{ CALLGET(GetGroupAuth, loginID, llgroup, llQQ) : iDefault };
		return auth < 0 ? iDefault : auth;
	}
	bool isGroupAdmin(long long llgroup, long long llQQ, bool bDefault) {
		return CALLGET(IsGroupAdmin, loginID, llgroup, llQQ, bDefault) :bDefault;
	}
	bool isGroupOwner(long long llgroup, long long llQQ, bool bDefault) {
		return CALLGET(IsGroupOwner, loginID, llgroup, llQQ, bDefault) :bDefault;
	}
	bool isGroupMember(long long llgroup, long long llQQ, bool bDefault) {
		return CALLGET(IsGroupMember, loginID, llgroup, llQQ, bDefault) :bDefault;
	}
	void answerFriendRequest(long long fromUID, int respon, const std::string& msg) {
		CALLVOID(AnswerFriendRequest, loginID, fromUID, respon, msg);
	}
	void answerGroupInvited(long long fromGID, int respon) {
		CALLVOID(AnswerGroupInvited, loginID, fromGID, respon);
	}
	GroupSize_t getGroupSize(long long aimGroup) {
		return CALLGET(GetGroupSize, loginID, aimGroup) :GroupSize_t();
	}
	std::string getGroupName(long long aimGroup) {
		return CALLGET(GetGroupName, loginID, aimGroup) :"";
	}
	std::string getGroupNick(long long aimGroup, long long aimQQ) {
		return CALLGET(GetGroupNick, loginID, aimGroup, aimQQ) :"";
	}
	long long getGroupLastMsg(long long aimGroup, long long aimQQ) {
		return CALLGET(GetGroupLastMsg, loginID, aimGroup, aimQQ) :-1;
	}
	std::string printGroupInfo(long long aimGroup) {
		return CALLGET(PrintGroupInfo, loginID, aimGroup) :"[" + getGroupName(aimGroup) + "](" + std::to_string(aimGroup) + ")[" + getGroupSize(aimGroup).tostring() + "]";
	}
	void setGroupKick(long long llGroup, long long llQQ) {
		CALLVOID(SetGroupKick, loginID, llGroup, llQQ);
	}
	void setGroupBan(long long llGroup, long long llQQ, int intTime) {
		CALLVOID(SetGroupBan, loginID, llGroup, llQQ, intTime);
	}
	void setGroupAdmin(long long llGroup, long long llQQ, bool bSet) {
		CALLVOID(SetGroupAdmin, loginID, llGroup, llQQ, bSet);
	}
	void setGroupCard(long long llGroup, long long llQQ, const string& card) {
		CALLVOID(SetGroupCard, loginID, llGroup, llQQ, card);
	}
	void setGroupTitle(long long llGroup, long long llQQ, const string& card){
		CALLVOID(SetGroupTitle, loginID, llGroup, llQQ, card);
	}
	void setGroupWholeBan(long long llGroup, int intTime){
		CALLVOID(SetGroupWholeBan, loginID, llGroup, intTime);
	}
	void setGroupLeave(long long llGroup){
		CALLVOID(SetGroupLeave, loginID, llGroup);
	}
	void setDiscussLeave(long long llGroup){
		CALLVOID(SetDiscussLeave, loginID, llGroup);
	}
}
