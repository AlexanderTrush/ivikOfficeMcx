
#define MODBUS_THREAD
#define nvmcc_ApplicationID 1
#include "nvmcc_headers.h"
#include "stdalgo.c"
#include "pid.lib"



TTimer for_time_change;
TDateTime dt;
char change_time;
short Year;
char Month;
char Day;
char Hours;
char Minutes;
char Seconds;
char week;

short from_chiller;
short to_chiller;
short from_user;
short to_user;
short chiller;

struct TParams: public TStdParams{

short from_chiller_c=0;
short to_chiller_c=0;
short from_user_c=0;
short to_user_c=0;

short on1[]={0,0,0,0,0,0,0};
short off1[]={0,0,0,0,0,0,0};
short on2[]={0,0,0,0,0,0,0};
short off2[]={0,0,0,0,0,0,0};

};
persistent TParams Params;

modbusdecl(ModbusTable, modbusRW, 100, from_chiller);    //Меню -> От чиллера
modbusdecl(ModbusTable, modbusRW, 101, to_chiller);    //Меню -> В чиллер
modbusdecl(ModbusTable, modbusRW, 102, from_user);    //Меню -> От потребителя
modbusdecl(ModbusTable, modbusRW, 103, to_user);    //Меню -> К потребителю
modbusdecl(ModbusTable, modbusRW, 104, Params.on1[0]);    //Меню -> График -> Понедельник -> Вкл1
modbusdecl(ModbusTable, modbusRW, 105, Params.off1[0]);    //Меню -> График -> Понедельник -> Выкл1
modbusdecl(ModbusTable, modbusRW, 106, Params.on2[0]);    //Меню -> График -> Понедельник -> Вкл2
modbusdecl(ModbusTable, modbusRW, 107, Params.off2[0]);    //Меню -> График -> Понедельник -> Выкл2
modbusdecl(ModbusTable, modbusRW, 108, Params.on1[1]);    //Меню -> График -> Вторник -> Вкл1
modbusdecl(ModbusTable, modbusRW, 109, Params.off1[1]);    //Меню -> График -> Вторник -> Выкл1
modbusdecl(ModbusTable, modbusRW, 110, Params.on2[1]);    //Меню -> График -> Вторник -> Вкл2
modbusdecl(ModbusTable, modbusRW, 111, Params.off2[1]);    //Меню -> График -> Вторник -> Выкл2
modbusdecl(ModbusTable, modbusRW, 112, Params.on1[2]);    //Меню -> График -> Среда -> Вкл1
modbusdecl(ModbusTable, modbusRW, 113, Params.off1[2]);    //Меню -> График -> Среда -> Выкл1
modbusdecl(ModbusTable, modbusRW, 114, Params.on2[2]);    //Меню -> График -> Среда -> Вкл2
modbusdecl(ModbusTable, modbusRW, 115, Params.off2[2]);    //Меню -> График -> Среда -> Выкл2
modbusdecl(ModbusTable, modbusRW, 116, Params.on1[3]);    //Меню -> График -> Четверг -> Вкл1
modbusdecl(ModbusTable, modbusRW, 117, Params.off1[3]);    //Меню -> График -> Четверг -> Выкл1
modbusdecl(ModbusTable, modbusRW, 118, Params.on2[3]);    //Меню -> График -> Четверг -> Вкл2
modbusdecl(ModbusTable, modbusRW, 119, Params.off2[3]);    //Меню -> График -> Четверг -> Выкл2
modbusdecl(ModbusTable, modbusRW, 120, Params.on1[4]);    //Меню -> График -> Пятница -> Вкл1
modbusdecl(ModbusTable, modbusRW, 121, Params.off1[4]);    //Меню -> График -> Пятница -> Выкл1
modbusdecl(ModbusTable, modbusRW, 122, Params.on2[4]);    //Меню -> График -> Пятница -> Вкл2
modbusdecl(ModbusTable, modbusRW, 123, Params.off2[4]);    //Меню -> График -> Пятница -> Выкл2
modbusdecl(ModbusTable, modbusRW, 124, Params.on1[5]);    //Меню -> График -> Суббота -> Вкл1
modbusdecl(ModbusTable, modbusRW, 125, Params.off1[5]);    //Меню -> График -> Суббота -> Выкл1
modbusdecl(ModbusTable, modbusRW, 126, Params.on2[5]);    //Меню -> График -> Суббота -> Вкл2
modbusdecl(ModbusTable, modbusRW, 127, Params.off2[5]);    //Меню -> График -> Суббота -> Выкл2
modbusdecl(ModbusTable, modbusRW, 128, Params.on1[6]);    //Меню -> График -> Воскресенье -> Вкл1
modbusdecl(ModbusTable, modbusRW, 129, Params.off1[6]);    //Меню -> График -> Воскресенье -> Выкл1
modbusdecl(ModbusTable, modbusRW, 130, Params.on2[6]);    //Меню -> График -> Воскресенье -> Вкл2
modbusdecl(ModbusTable, modbusRW, 131, Params.off2[6]);    //Меню -> График -> Воскресенье -> Выкл2
modbusdecl(ModbusTable, modbusRW, 132, Year);    //Меню -> Часы -> Год
modbusdecl(ModbusTable, modbusRW, 133, Month);    //Меню -> Часы -> Месяц
modbusdecl(ModbusTable, modbusRW, 134, Day);    //Меню -> Часы -> Число
modbusdecl(ModbusTable, modbusRW, 135, Hours);    //Меню -> Часы -> Час
modbusdecl(ModbusTable, modbusRW, 136, Minutes);    //Меню -> Часы -> Мин
modbusdecl(ModbusTable, modbusRW, 137, Seconds);    //Меню -> Часы -> Сек
modbusdecl(ModbusTable, modbusRW, 900, Params.from_chiller_c);    //Настройки -> Корректировка -> От чиллера
modbusdecl(ModbusTable, modbusRW, 901, Params.to_chiller_c);    //Настройки -> Корректировка -> В чиллер
modbusdecl(ModbusTable, modbusRW, 902, Params.from_user_c);    //Настройки -> Корректировка -> От потребителя
modbusdecl(ModbusTable, modbusRW, 903, Params.to_user_c);    //Настройки -> Корректировка -> К потребителю


void Time()
{
    if (change_time>0)
    {
        dt.SetTime( DateSerial(Year,Month,Day,Hours,Minutes,Seconds) );
        dt.SaveRTC();
        change_time=0;
    }
    else
    {
        if (for_time_change.ElapsedSec()>0)
        {
        for_time_change.Start();
        dt.LoadRTC();
        dt.Explode();
        Year=dt.Year;
        Month=dt.Month;
        Day=dt.Day;
        Hours=dt.Hours;
        Minutes=dt.Minutes;
        Seconds=dt.Seconds;
        week=dt.WDay();
        };
    };
};

char Timer2(short on1, short off1, short on2, short off2)
{

    if
     (
        (
            (
                    (((dt.Hours*60+dt.Minutes)>=on1 || (dt.Hours*60+dt.Minutes)<off1) && (on1>off1))
                || (on1==off1)
                || ((dt.Hours*60+dt.Minutes)>=on1 && (dt.Hours*60+dt.Minutes)<off1)
            )
            && on1!=1440
            && off1!=1440
        )
        ||
        (
            (
                    (((dt.Hours*60+dt.Minutes)>=on2 || (dt.Hours*60+dt.Minutes)<off2) && (on2>off2))
                || (on2==off2)
                || ((dt.Hours*60+dt.Minutes)>=on2 && (dt.Hours*60+dt.Minutes)<off2)
            )
            && on2!=1440
            && off2!=1440
        )
    ) return 1;
    else return 0;

};

short ai_read(char number, short min, short max, short offset)
{
    short t_t;
    t_t = IO.GetFilteredAI(number);
    if (t_t<min || t_t>max)
    {
        return -32767;
    }
    else
    {
         return t_t + offset;
    }
}



void IOInit()
{
    IO.Init();
    IO.SetAIType(1,ioTypeNTC,0);
    IO.SetAIType(2,ioTypeNTC,0);
    IO.SetAIType(3,ioTypeNTC,0);
    IO.SetAIType(4,ioTypeNTC,0);
};

void IOReadWrite()
{
    from_chiller = ai_read(1, -300, 990, Params.from_chiller_c);
    to_chiller = ai_read(2, -300, 990, Params.to_chiller_c);
    from_user = ai_read(3, -300, 990, Params.from_user_c);
    to_user = ai_read(4, -300, 990, Params.to_user_c);
    IO.SetDO(4,chiller)
}


void App_Init()  {

IOInit();
Params.InitParams();
};


// this is the control loop procedure, and will be called continuously
void App_Run()  {
Time();
IOReadWrite();
chiller = Timer2(Params.on1[week],Params.off1[week],Params.on2[week],Params.off2[week]);
};
