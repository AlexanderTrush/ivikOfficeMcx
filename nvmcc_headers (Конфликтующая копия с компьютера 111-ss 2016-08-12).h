
// This is an automatic generated file, please do not edit
//#ifdef nvmcc_comp_v1
// nvmcc does not need this file
//#else

;
;
;
;
;
;
signed long RoundDiv(signed long a, signed long b);
struct Pointer: object  {
    signed long ptr;
};
struct TBitPointer: object  {
    signed long ptr;
    signed char bitoffset;
};
struct bit: signed_char  {
    signed char super;
    bit ll_primitivebit;
};
struct ArrayBasicType: object  {
};
struct Array: object  {
    void data;
    ArrayBasicType geti(signed long n);
};
struct String: object  {
    unsigned char Len;
    unsigned short MaxItems;
    unsigned char Txt[200];
    signed long isEmpty();
    unsigned char geti(signed long n);
    void Clear();
    void set(String cSource);
    void sum_set(String cSource);
    String SubStr(signed long iStart, signed long iLength);
    void AddSubStr(String cSource, signed long iStart, signed long iLength);
    void AddFormatNum(signed long n, signed char lpad, signed char iDec, signed char sgn);
    void AddFormatNumHex(signed long iNum, signed char iDig);
    void AddFormatNumBase(signed long iNum, signed char iDig, signed char cPad, signed char iBase);
    void AddFormat(String format, signed long n);
    void Format(String format, signed long n);
    signed long ToIntEx(signed long iStart, signed long iBase);
    signed long ToInt();
    signed long Equal(String s2);
    signed long NotEqual(String s2);
    signed long IndexOfChar(unsigned char c);
};
signed char ToChar(signed char n);
unsigned char ToByte(unsigned char n);
unsigned short ToWord(unsigned short n);
signed short ToShort(signed short n);
signed long sub(signed long n);
void SetReference(void subj, void val);
void SysCall(signed long FnCode);
signed long GetSysParam(signed long iIndex);
signed long SetSysParam(signed long iIndex, signed long iValue);
void CANsetNodeID(signed short iNodeID);
signed short CANgetNodeID();
signed long CANgetSpeed();
signed short CANgetUITarget();
void CANsetUITarget(signed long iDevice);
void MMIConnectToDevice(signed long iDevice);
signed long GetUILanguage();
void SetUILanguage(signed long iLang);
void OutputDebugString(String cMsg);
void OutputDebugNum(String cMsg, signed long iNum);
void SetWatchdog(unsigned short iTimeout);
void Reboot(signed char iRebootMode);
;
;
;
signed long min(signed long nV1, signed long nV2);
signed long max(signed long nV1, signed long nV2);
signed long abs(signed long nVal);
signed long between(signed long nVal, signed long nMin, signed long nMax);
signed long strcmp(String a, String b);
signed long strncmp(String a, String b, signed long len);
unsigned short CRC16(void a, signed long iSize, unsigned short StartCRC);
struct TSysDeviceInfo  {
    unsigned char StructVersion;
    signed long ProductCode;
    signed long SerialNumber;
    unsigned short CustomProdutCode;
    signed long BiosDate;
    unsigned char BiosVersion;
    unsigned short VendorID;
    unsigned short AppID;
    signed long AppDate;
    unsigned short AppMaxSize;
    unsigned short AppMaxStore;
    unsigned short AppMaxE2P_KB;
    unsigned short AppRamSize;
    unsigned char ioNumDI;
    unsigned char ioNumAI;
    unsigned char ioNumDO;
    unsigned char ioNumAO;
    unsigned char ioNumPWM;
    signed long AppMaxE2P();
    void GetInfo();
    unsigned short GetBiosVer();
    signed long isMCX08();
    signed long isMCX06();
    signed long isMMIGRS();
    void GetDeviceFamilyDescr(String Descr);
};
struct TSysDeviceInfo_v2  {
    unsigned char StructVersion;
    signed long ProductCode;
    signed long SerialNumber;
    unsigned short CustomProdutCode;
    signed long BiosDate;
    unsigned char BiosVersion;
    unsigned short VendorID;
    unsigned short AppID;
    signed long AppDate;
    unsigned short BiosVer;
    unsigned short BiosSCode;
    signed long AppMaxSize;
    signed long AppMaxStore;
    signed long AppMaxE2P;
    signed long AppRamSize;
    signed long UploadAreaSize;
    unsigned short SupportedFunctions;
    unsigned char ioNumDI;
    unsigned char ioNumAI;
    unsigned char ioNumDO;
    unsigned char ioNumAO;
    void GetInfo();
    unsigned short GetBiosVer();
    void GetBiosVerStr(String Ver);
    signed long isMCX08();
    signed long isMCX06();
    signed long isMMIGRS();
    signed long isMMIMYK();
    void GetDeviceFamilyDescr(String Descr);
    signed long SupportFloat();
    signed long SupportMultitask();
};
struct TTimerSec: object  {
    signed long Sec;
    void set(TTimerSec b);
    void Start();
    void Clear();
    signed long isClear();
    signed long ElapsedSec();
    void SetTime(signed long iSec);
    signed long GetTime();
    void AddSec(signed long iSec);
    void Addms(signed long iMilliseconds);
    void EarlyStart(signed long iOffset);
};
struct TStoppableTimerSec: TTimerSec  {
    TTimerSec super;
    signed long ElapsedSec();
    signed long isPaused();
    void Pause();
    void Resume();
};
struct TTimer: TTimerSec  {
    TTimerSec super;
    unsigned short MilliSec;
    void set(TTimer b);
    TTimer sub(TTimer time2);
    void sub_set(TTimer time2);
    void Start();
    void Clear();
    signed long isClear();
    signed long CheckAndRestartTimer(signed long iCheck);
    signed long Elapsedms();
    signed long GetElapsedmsAndRestart();
    void Addms(signed long iMilliseconds);
    void EarlyStart(signed long iOffset);
};
struct TReverseTimer: TTimer  {
    TTimer super;
    void ReverseCountms(signed long iCountms);
    signed long Remainingms();
};
struct TSysInfo: object  {
    unsigned char SysInfoVersion;
    unsigned char LastVMError;
    signed long LastVMErrorPC;
    TTimer SysTime;
    signed long SysMaxLoopTime;
    signed long MaxStackSize;
    bit PersistentMemChanged;
    bit DisableDownload;
    void GetInfo();
    void SetInfo();
};
void Sleep(signed long iMillisec);
void Suspend(signed long iMillisec, signed long WakeUpEvents);
TSysInfo Sys;
struct TComEvent: signed_long  {
    signed long super;
};
struct TComQueue  {
    unsigned char QueueHandle;
    unsigned short ObjectSize;
    unsigned short MaxBuffSize;
    signed long BufferPtr;
    unsigned char geti(signed long n);
    signed long Len();
    signed long MaxLen();
};
struct TCom: object  {
    unsigned char ComPort;
    unsigned short BytesTx;
    unsigned short BytesRx;
    unsigned short Errors;
    unsigned short OverrunErrors;
    TComQueue dummy_RxQueue;
    TComQueue dummy_TxQueue;
    TComQueue RxQueue();
    TComQueue TxQueue();
    signed long Init(signed long iSpeed, unsigned short iFlags);
    void InitComEx(signed char iComPort, unsigned char xBufferRx, signed long iRxSize, unsigned char xBufferTx, signed long iTxSize);
    signed long ReadLN(String line);
    signed long ReadB(void buff, signed long iSize);
    signed long WriteStr(String line);
    signed long WriteB(void buff, signed long iSize);
    signed long CheckAndClearEvent(signed long iEvCode);
    signed long GetInfo();
    signed long ClearBuffer();
    signed long SetSuspend(signed long iStatus);
    signed long SetRxTimeout(unsigned short iTimeout);
    void WriteStrNum(String cMsg, signed long iNum);
};
signed long RequestAndWaitVar_tmp;
struct TCanMessage: object  {
    unsigned short SrcNode;
    unsigned short DestNode;
    unsigned short Index;
    unsigned char SubIndex;
    signed long Value;
    void set(TCanMessage b);
};
struct TCANFrame  {
    signed long CobID;
    unsigned char Sz;
    unsigned char Data[8];
};
struct TCANopen: TCom  {
    TCom super;
    unsigned short NodeID;
    void InitCanObject();
    signed long CurrSpeed();
    signed short GetUITarget();
    signed long RequestAndWaitVar(unsigned short iNodeID, unsigned short iIndex, unsigned char iSubIndex, signed long iDefault, signed long Timeout);
    signed long RequestAndWaitVarSz(unsigned short iNodeID, unsigned short iIndex, unsigned char iSubIndex, signed char iSize, signed long iDefault, signed long Timeout);
    signed long SetExportTable(void ExportTbl, void ModbusObjectDictionary);
    signed long SendVar(unsigned short DestNode, unsigned short Index, unsigned char SubIndex, signed long Value, signed long iSize);
    void SendVarAndWait(unsigned short DestNode, unsigned short Index, unsigned char SubIndex, signed long Value);
    signed long SendMessage(unsigned short DestNode, unsigned short Index, unsigned char SubIndex, signed long Value, signed long iSize);
    signed long RequestVar(unsigned short iNodeID, unsigned short iIndex, unsigned char iSubIndex, signed long DestVar, signed long iSize);
    signed long SendVarConfirmed(unsigned short DestNode, unsigned short Index, unsigned char SubIndex, signed long Value, signed long iSize);
    signed long Run(signed long MaxCanMsgToProcess);
    signed long coReqOrWrite(unsigned short DestNode, unsigned short Index, unsigned char SubIndex, signed long Value, signed long iMaxSize, unsigned char iDir, unsigned char iConfirm);
    signed long coPopConfirmQueue(unsigned short DestNode, unsigned short Index, unsigned char SubIndex, signed long Result);
    signed long SendFile(unsigned short DestNode, unsigned short Index, unsigned char SubIndex, signed long FileID);
    signed long coReqOrWriteMB(unsigned short DestNode, unsigned char MB2CANBaseIndex, unsigned short Index, signed long Value, signed long iMaxSize, unsigned char iDir, unsigned char iConfirm);
    signed long SendMBVar(unsigned short DestNode, unsigned short Index, signed long Value);
    signed long RequestAndWaitMBVar(unsigned short iNodeID, unsigned short iIndex, signed long iDefault);
    signed long RequestMBVar(unsigned short iNodeID, unsigned short iIndex, signed long DestVar);
    signed long SendFrame(TCANFrame msg);
    signed long ReadFrame(TCANFrame msg);
    void SetNetworkSpeed(signed long iNewSpeed);
    void SetRemoteNodeID(signed long iNewNodeID, signed long iSerialNumber);
    void SetCanParams(signed long iNewCanSpeed, signed long iNewNodeID, signed long iSerialNumber);
    signed long SendMBVarF(unsigned short DestNode, unsigned short Index, float Value);
    float RequestAndWaitMBVarF(unsigned short iNodeID, unsigned short iIndex, float iDefault);
    signed long IsNodeActive(signed long iNode);
    signed long IsNodeIDAlreadyInUse();
};
struct TCan: TCANopen  {
    TCANopen super;
    TCanMessage msg;
    signed long CanOpenError;
    signed char WriteOnBroadcast;
    signed long Run(signed long MaxCanMsgToProcess);
    signed long WriteReq(void ModbusTable, unsigned short iModbusAddress, unsigned short iCount, unsigned char RxPtr);
    signed long SendFrameExt(signed long CobID, unsigned char FrameType, unsigned char Length, void obj);
    signed char SendSDO(signed long CobID, unsigned char Flags, unsigned short Index, unsigned char SubIndex, signed long Value);
    signed long ReadFrameEx(TCANFrame frame, TCanMessage msg);
    signed long ReadMessage(TCanMessage msg);
};
struct TE2p: object  {
    signed char e2pfn(signed char Fn, signed long iAddr, unsigned char iVal, signed long iSize);
    signed long Save(signed long iAddr, void a, signed long iSize);
    signed long Load(signed long iAddr, void a, signed long iSize);
    void ClearAllEEprom(unsigned char iDefault);
};
struct TIO: object  {
    signed long LastError;
    bit DOStatus[21];
    signed char AIType[17];
    signed char AOType[7];
    unsigned short AOStatus[7];
    bit LedStatus[8];
    void Init();
    void Run();
    signed long GetIO(signed char iType, signed char iIndex, signed char iTransform);
    signed long SetIO(signed char iFn, signed char iIndex, signed char iType, signed long iValue, signed long iAdv);
    signed long GetDI(signed char iIndex);
    signed long GetNDI(signed char iIndex);
    signed long GetDO(signed char iIndex);
    signed long SetDO(signed char iIndex, signed long iValue);
    signed long SetLed(signed char iIndex, signed long iValue);
    signed long GetLed(signed char iIndex);
    signed long SetBuzzer(signed long iOn);
    signed long GetBuzzer();
    signed long GetAI(signed char iIndex);
    signed long SetAO(signed char iIndex, signed long iValue);
    signed long SetAIType(signed char iIndex, signed char iType, signed long iParam);
    signed long GetAIType(signed char iIndex);
    signed long SetAOType(signed char iIndex, signed char iType, signed long iParam, signed long iAdv);
    signed long GetAOType(signed char iIndex);
    signed long GetAO(signed char iIndex);
    signed long SetDIType(signed char iIndex, signed char iType, signed long iParam);
    signed long GetRawAI(signed char iIndex);
    signed long SetRawAO(signed char iIndex, signed long iValue);
    signed long GetRawAO(signed char iIndex);
    void Clear();
};
struct TFilteredAI: TIO  {
    TIO super;
    signed long AIFilter;
    signed long AIBuffer[16];
    signed char AIFilterOverflow[16];
    void Init();
    void SetAIFilter(signed long iFilter);
    signed long GetFilteredAI(signed char iIndex);
    signed long GetFilteredAIEx(signed char iIndex, signed long iFilter);
    signed long GetCurrAI(signed char iIndex);
    signed long SetAIType(signed char iIndex, signed char iType, signed long iParam);
    signed long SetAOType(signed char iIndex, signed char iType, signed long iParam, signed long iAdv);
};
struct TFilteredIO: TFilteredAI  {
    TFilteredAI super;
    bit ReverseDI[22];
    bit DisableOUT;
    signed long GetDI(signed char iIndex);
    void SetDIPolarity(signed char iIndex, signed char iCloseValue);
    signed long GetDIPolarity(signed char iIndex);
    signed long SetDO(signed char iIndex, signed long iValue);
    signed long SetAO(signed char iIndex, signed long iValue);
};
signed short StdInConv[8];
struct TConvTableItem  {
    signed long Rad;
    signed short m;
    signed short q;
};
struct TConvTable  {
    TConvTableItem ConvTable[18];
};
TConvTable CNTCConvTable;
signed long TranslateVal(signed long nVal, TConvTable xConvTable);
;
void SetBuzzerVolume(signed long iVolume);
void SetBuzzer(signed long iOn, signed long iOnTime);
signed long GetBuzzer();
signed long isLocalApp();
Array  {
    signed char ArrayOf;
} ytab[2];
struct TDateTime: TTimerSec  {
    TTimerSec super;
    signed char Seconds;
    signed char Minutes;
    signed char Hours;
    signed char Day;
    signed char Month;
    signed short Year;
    signed char WDay();
    void ExplodeTime();
    void Explode();
    void Implode();
    signed long GetRTC();
    void SetRTC(signed long iTime);
    signed char LoadRTC();
    void SaveRTC();
    void AddFormatDate(String s, String format);
};
signed long DateSerial(signed short iYear, signed char iMonth, signed char iDay, signed char iHours, signed char iMinutes, signed char iSeconds);
struct TRTCEmulator: TDateTime  {
    TDateTime super;
    signed long TimeOffset;
    unsigned short CurrDay;
    TTimerSec tmr;
    signed char RTCError();
    signed char LoadRTC();
    void SaveRTC();
    void Explode();
    void UpdateRTC();
};
signed long Saturation(signed long nVal, signed long nMin, signed long nMax);
signed long LimitRange(signed long nVal, signed long nMin, signed long nMax);
signed long AddFromStringTable(String str, signed long iIndex);
signed long LoadFromStringTable(String str, signed long iIndex);
signed long CreateImage(String cName);
unsigned short GetRemoteBiosVer(unsigned short iNodeID);
void DisplayDeviceInfoOnCom(TCom com);
unsigned char Com1BufferR[128];
unsigned char Com1BufferW[128];
unsigned char CanBufferR[128];
unsigned char CanBufferW[128];
bit RunningIntoSimulation;
TE2p e2p;
;
struct TStdParams: object  {
    unsigned short VendorID;
    unsigned short AppID;
    unsigned short VersionID;
    signed long VerifyParams();
    signed long InitParams();
    void LoadDefaultParams();
};
struct TStdParamsCompile: object  {
    signed long ParVersion;
    signed long VerifyParams();
    signed long InitParams();
    void LoadDefaultParams();
};
struct TStdAlgo: object  {
};
TMyAlgo Algo;
void Main();
struct TMyAlgo  {
    void Init();
    void MainLoop();
};
void nvmlib_Startup();
struct TModbus: TCom  {
    TCom super;
    unsigned char Ident;
    unsigned short Timeout;
    unsigned short FnCode;
    unsigned short StartAddress;
    unsigned short Count;
    unsigned char ReceivedPacket;
    bit IllegalFunctionError;
    bit IllegalDataAddress;
    bit IllegalDataValue;
    bit OutputBufferOverflow;
    bit CRCError;
    void CheckPacket();
    void ProcessPacket();
    void Run();
    signed short Value();
    void StartAnswer();
    void EndAnswer();
    void SetExceptionCode(signed long iCode);
    void WriteValue(signed long iValue, signed long iLen);
    signed long AnswerReq(void ModbusTable, unsigned short iModbusAddress, unsigned short iCount, signed long RxPtr);
    signed long WriteReq(void ModbusTable, unsigned short iModbusAddress, unsigned short iCount, unsigned char RxPtr);
    unsigned short CRCModbus(void a, signed long iSize);
    signed long Init(signed long iSpeed, unsigned short iFlags);
};
TCANopen Can;
TModbus Com1;
struct nvm_thread_function_prototype  {
    signed long fnaddr;
    signed long ReqStack;
};
signed long nvm_thread_create(nvm_thread_function_prototype fnThreadFn, signed long iParam);
struct nvm_thread_method_prototype  {
    signed long fnaddr;
    signed long ReqStack;
    signed long Subject;
};
signed long nvm_thread_createM(nvm_thread_method_prototype fnThreadFn);
struct TMutex  {
    signed char LockStatus;
    signed long Lock(signed long iWaitms);
    signed long Unlock();
};
signed long SetEvent(signed long EventMask);
signed long CheckEvent(signed long EventMask);
signed long CheckAndClearEvent(signed long EventMask);
signed long sysSetEvent(signed long EventMask);
void stdalgo_ModbusThread(signed long Param);
TFilteredIO IO;
void Algo_Init();
void Algo_MainLoop();
struct TFIFOQueue  {
    signed long Queue[20];
    signed char MaxLen;
    signed char Head;
    signed char Tail;
    signed char Len;
    void Clear();
    void SetMaxLen(signed char iLen);
    signed char GetMaxLen();
    void Add(signed long iValue);
    void AddAndOverwrite(signed long iValue);
    signed long Remove();
    signed long Peek(signed char i);
};
signed char CheckRange(signed long var, signed long min, signed long max);
struct filt1pole  {
    signed long filt;
    signed long res;
    void Reset();
    void FiltCalc(signed long u, signed char a);
};
struct c_interp  {
    signed long x[21];
    signed long y[21];
    unsigned char maxIdx;
    unsigned char lastIdx;
    signed long out;
    signed long interp(signed long val);
};
struct c_pid  {
    signed char en;
    signed char en_i;
    signed char en_d;
    signed char en_sc;
    signed long Kp;
    signed long P_x;
    signed long I_Ti;
    signed long I_max;
    signed long I_min;
    signed long I_Ktr;
    signed long I_x;
    signed long I_res_x;
    signed long D_Td;
    signed char D_nSamples;
    filt1pole D_x;
    signed long D_filtFact;
    signed long dxTmp;
    signed long D_max;
    signed long D_min;
    TFIFOQueue D_cBuff;
    signed long Ts;
    signed long maxOut;
    signed long minOut;
    signed long deadBand;
    signed long idleOut;
    signed long u_ctrl_sat;
    signed long u_ctrl;
    signed long paramDiv;
    signed long tr;
    signed long Kp_ref;
    signed long gain_ref;
    void PID_Reset();
    void Set_G_Params(signed long sampleTime, signed long min, signed long max, signed long dead, signed short dv);
    void Set_P_Params(signed long kp, signed long gain);
    void Set_D_Params(signed long Td, signed char nSamples, signed long filtFact, signed long min, signed long max);
    void Set_I_Params(signed long Ti, signed long min, signed long max, signed long Ktr);
    void Enable(signed char enable, signed char enable_i, signed char enable_d, signed char enable_sc);
    signed long PID_Controller(signed long setpoint, signed long feedb, signed long gain);
};
struct c_autoTune_pid: c_pid  {
    c_pid super;
    signed long AT_PAR_maxDiffOut;
    signed long AT_PAR_hyst;
    signed char AT_PAR_n_startCycles;
    signed char AT_PAR_n_relayCycles;
    signed char AT_PAR_diffReduction;
    signed char AT_PAR_PhaseMarg;
    signed char AT_PAR_Ku_CalcMode;
    signed long AT_out;
    signed long AT_outOffset;
    signed char AT_stat;
    signed char AT_statOld;
    signed char AT_tune;
    signed char AT_startCyclesCnt;
    signed char AT_relayCyclesCnt;
    signed long AT_setpoint;
    signed long AT_outHi;
    signed long AT_outLo;
    signed long AT_diffOut;
    signed long AT_Tu_acc_pos;
    signed long AT_Tu_acc_neg;
    signed long AT_ampl_acc_pos;
    signed long AT_ampl_acc_neg;
    signed long AT_gain_acc;
    signed long AT_maxAbs_E;
    signed long AT_max_E;
    signed long AT_min_E;
    TTimer AT_timer;
    signed long AT_Tu;
    signed long AT_Ku;
    signed long AT_gain_ref;
    signed long AT_Kp;
    signed long AT_Ti;
    signed long AT_Td;
    signed short AT_progress;
    void Reset();
    void _AT_Reset();
    void AT_Tune();
    signed char AT_CheckFinished();
    void Set_AT_ProcParams(signed char startCyc, signed char relayCyc, signed long diffOut, signed long hyst, signed char diffReduction);
    void Set_AT_CalcParams(signed char phaseMarg, signed char ku_calcMode);
    void _AT_SetupRelay(signed long diff);
    void _AT_HandleStartCycles(signed long e, signed long gain);
    void _AT_HandleMeasCycles(signed long e, signed long gain);
    void _AT_CalcPID();
    void _AT_Autotune(signed long setpoint, signed long e, signed long gain);
    signed long AT_PID_Controller(signed long setpoint, signed long feedb, signed long Kg);
};
unsigned char ComBufferRx[512];
unsigned char ComBufferTx[512];
TTimer for_time_change;
TDateTime dt;
signed char change_time;
signed short Year;
signed char Month;
signed char Day;
signed char Hours;
signed char Minutes;
signed char Seconds;
signed char week;
signed short from_chiller;
signed short to_chiller;
signed short from_user;
signed short to_user;
signed short chiller;
struct TParams: TStdParams  {
    TStdParams super;
    signed short from_chiller_c;
    signed short to_chiller_c;
    signed short from_user_c;
    signed short to_user_c;
    signed short on1[7];
    signed short off1[7];
    signed short on2[7];
    signed short off2[7];
};
TParams Params;
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    from_chiller;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    to_chiller;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    from_user;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    to_user;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    geti  {
        signed char ;
    };
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    Year;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    Month;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    Day;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    Hours;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    Minutes;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    unsigned char ;
    Seconds;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed short ;
    from_chiller_c;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed short ;
    to_chiller_c;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed short ;
    from_user_c;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed short ;
    to_user_c;
};
modbusdecl  {
    ModbusTable;
    unsigned char ;
    signed short ;
    change_time;
};
void Time();
signed char Timer2(signed short on1, signed short off1, signed short on2, signed short off2);
signed short ai_read(signed char number, signed short min, signed short max, signed short offset);
void IOInit();
void IOReadWrite();
void App_Init();
void App_Run();

//#endif
