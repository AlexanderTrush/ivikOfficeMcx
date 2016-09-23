
#define MODBUS_THREAD
#define nvmcc_ApplicationID 1
#include "nvmcc_headers.h"
#include "stdalgo.c"
#include "pid.lib"

byte ComBufferRx[512];
byte ComBufferTx[512];

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

short fancoil_t_out_air[7];
short fancoil_t_room[7];
short fancoil_t_in_water[7];
short fancoil_speed[7];
short fancoil_mode[7];

short co2_commer;
short co2_work;

short empty;

struct TParams: public TStdParams{

    short from_chiller_c=0;
    short to_chiller_c=0;
    short from_user_c=0;
    short to_user_c=0;
    short fancoil_t_room_correct[]={0,0,0,0,0,0,0};

    short chill_on1[]={0,0,0,0,0,0,0};
    short chill_off1[]={0,0,0,0,0,0,0};
    short chill_on2[]={1440,1440,1440,1440,1440,1440,1440};
    short chill_off2[]={1440,1440,1440,1440,1440,1440,1440};

    short fancoil_speed_stp[]={0,0,0,0,0,0,0};
    short fancoil_t_stp[]={220,220,220,220,220,220,220};
    short fancoil_t_stp_hyst=20;
    short fancoil_t_pipe_hyst=20;
    short fancoil_t_in_water_heat=350;
    short fancoil_t_in_water_cool=180;


    short ex_fan_speed[]={0,0,0};
    short flaps=0;


};
persistent TParams Params;

modbusdecl(ModbusTable, modbusRW, 100, from_chiller);    //Меню -> Чиллер -> От чиллера
modbusdecl(ModbusTable, modbusRW, 101, to_chiller);    //Меню -> Чиллер -> В чиллер
modbusdecl(ModbusTable, modbusRW, 102, from_user);    //Меню -> Чиллер -> От потребителя
modbusdecl(ModbusTable, modbusRW, 103, to_user);    //Меню -> Чиллер -> К потребителю
modbusdecl(ModbusTable, modbusRW, 104, Params.chill_on1[0]);    //Меню -> Чиллер -> График -> Понедельник -> Вкл1
modbusdecl(ModbusTable, modbusRW, 105, Params.chill_off1[0]);    //Меню -> Чиллер -> График -> Понедельник -> Выкл1
modbusdecl(ModbusTable, modbusRW, 106, Params.chill_on2[0]);    //Меню -> Чиллер -> График -> Понедельник -> Вкл2
modbusdecl(ModbusTable, modbusRW, 107, Params.chill_off2[0]);    //Меню -> Чиллер -> График -> Понедельник -> Выкл2
modbusdecl(ModbusTable, modbusRW, 108, Params.chill_on1[1]);    //Меню -> Чиллер -> График -> Вторник -> Вкл1
modbusdecl(ModbusTable, modbusRW, 109, Params.chill_off1[1]);    //Меню -> Чиллер -> График -> Вторник -> Выкл1
modbusdecl(ModbusTable, modbusRW, 110, Params.chill_on2[1]);    //Меню -> Чиллер -> График -> Вторник -> Вкл2
modbusdecl(ModbusTable, modbusRW, 111, Params.chill_off2[1]);    //Меню -> Чиллер -> График -> Вторник -> Выкл2
modbusdecl(ModbusTable, modbusRW, 112, Params.chill_on1[2]);    //Меню -> Чиллер -> График -> Среда -> Вкл1
modbusdecl(ModbusTable, modbusRW, 113, Params.chill_off1[2]);    //Меню -> Чиллер -> График -> Среда -> Выкл1
modbusdecl(ModbusTable, modbusRW, 114, Params.chill_on2[2]);    //Меню -> Чиллер -> График -> Среда -> Вкл2
modbusdecl(ModbusTable, modbusRW, 115, Params.chill_off2[2]);    //Меню -> Чиллер -> График -> Среда -> Выкл2
modbusdecl(ModbusTable, modbusRW, 116, Params.chill_on1[3]);    //Меню -> Чиллер -> График -> Четверг -> Вкл1
modbusdecl(ModbusTable, modbusRW, 117, Params.chill_off1[3]);    //Меню -> Чиллер -> График -> Четверг -> Выкл1
modbusdecl(ModbusTable, modbusRW, 118, Params.chill_on2[3]);    //Меню -> Чиллер -> График -> Четверг -> Вкл2
modbusdecl(ModbusTable, modbusRW, 119, Params.chill_off2[3]);    //Меню -> Чиллер -> График -> Четверг -> Выкл2
modbusdecl(ModbusTable, modbusRW, 120, Params.chill_on1[4]);    //Меню -> Чиллер -> График -> Пятница -> Вкл1
modbusdecl(ModbusTable, modbusRW, 121, Params.chill_off1[4]);    //Меню -> Чиллер -> График -> Пятница -> Выкл1
modbusdecl(ModbusTable, modbusRW, 122, Params.chill_on2[4]);    //Меню -> Чиллер -> График -> Пятница -> Вкл2
modbusdecl(ModbusTable, modbusRW, 123, Params.chill_off2[4]);    //Меню -> Чиллер -> График -> Пятница -> Выкл2
modbusdecl(ModbusTable, modbusRW, 124, Params.chill_on1[5]);    //Меню -> Чиллер -> График -> Суббота -> Вкл1
modbusdecl(ModbusTable, modbusRW, 125, Params.chill_off1[5]);    //Меню -> Чиллер -> График -> Суббота -> Выкл1
modbusdecl(ModbusTable, modbusRW, 126, Params.chill_on2[5]);    //Меню -> Чиллер -> График -> Суббота -> Вкл2
modbusdecl(ModbusTable, modbusRW, 127, Params.chill_off2[5]);    //Меню -> Чиллер -> График -> Суббота -> Выкл2
modbusdecl(ModbusTable, modbusRW, 128, Params.chill_on1[6]);    //Меню -> Чиллер -> График -> Воскресенье -> Вкл1
modbusdecl(ModbusTable, modbusRW, 129, Params.chill_off1[6]);    //Меню -> Чиллер -> График -> Воскресенье -> Выкл1
modbusdecl(ModbusTable, modbusRW, 130, Params.chill_on2[6]);    //Меню -> Чиллер -> График -> Воскресенье -> Вкл2
modbusdecl(ModbusTable, modbusRW, 131, Params.chill_off2[6]);    //Меню -> Чиллер -> График -> Воскресенье -> Выкл2
modbusdecl(ModbusTable, modbusRW, 132, chiller);    //Меню -> Чиллер -> График
modbusdecl(ModbusTable, modbusRW, 133, empty);
modbusdecl(ModbusTable, modbusRW, 134, empty);
modbusdecl(ModbusTable, modbusRW, 135, empty);
modbusdecl(ModbusTable, modbusRW, 136, empty);
modbusdecl(ModbusTable, modbusRW, 137, empty);
modbusdecl(ModbusTable, modbusRW, 138, empty);
modbusdecl(ModbusTable, modbusRW, 139, empty);
modbusdecl(ModbusTable, modbusRW, 140, fancoil_t_room[0]);    //Меню -> Фанкойлы -> Коммерческий -> ТКомнаты
modbusdecl(ModbusTable, modbusRW, 141, Params.fancoil_t_stp[0]);    //Меню -> Фанкойлы -> Коммерческий -> ТКомнаты -> Задание
modbusdecl(ModbusTable, modbusRW, 142, fancoil_t_out_air[0]);    //Меню -> Фанкойлы -> Коммерческий -> ТВоздух
modbusdecl(ModbusTable, modbusRW, 143, fancoil_t_in_water[0]);    //Меню -> Фанкойлы -> Коммерческий -> ТВода
modbusdecl(ModbusTable, modbusRW, 144, fancoil_speed[0]);    //Меню -> Фанкойлы -> Коммерческий -> Скорость
modbusdecl(ModbusTable, modbusRW, 145, Params.fancoil_speed_stp[0]);    //Меню -> Фанкойлы -> Коммерческий -> Скорость -> Задание
modbusdecl(ModbusTable, modbusRW, 146, empty);
modbusdecl(ModbusTable, modbusRW, 147, empty);
modbusdecl(ModbusTable, modbusRW, 148, empty);
modbusdecl(ModbusTable, modbusRW, 149, empty);
modbusdecl(ModbusTable, modbusRW, 150, fancoil_t_room[1]);    //Меню -> Фанкойлы -> Холл -> ТКомнаты
modbusdecl(ModbusTable, modbusRW, 151, Params.fancoil_t_stp[1]);    //Меню -> Фанкойлы -> Холл -> ТКомнаты -> Задание
modbusdecl(ModbusTable, modbusRW, 152, fancoil_t_out_air[1]);    //Меню -> Фанкойлы -> Холл -> ТВоздух
modbusdecl(ModbusTable, modbusRW, 153, fancoil_t_in_water[1]);    //Меню -> Фанкойлы -> Холл -> ТВода
modbusdecl(ModbusTable, modbusRW, 154, fancoil_speed[1]);    //Меню -> Фанкойлы -> Холл -> Скорость
modbusdecl(ModbusTable, modbusRW, 155, Params.fancoil_speed_stp[1]);    //Меню -> Фанкойлы -> Холл -> Скорость -> Задание
modbusdecl(ModbusTable, modbusRW, 156, empty);
modbusdecl(ModbusTable, modbusRW, 157, empty);
modbusdecl(ModbusTable, modbusRW, 158, empty);
modbusdecl(ModbusTable, modbusRW, 159, empty);
modbusdecl(ModbusTable, modbusRW, 160, fancoil_t_room[2]);    //Меню -> Фанкойлы -> Конференц1 -> ТКомнаты
modbusdecl(ModbusTable, modbusRW, 161, Params.fancoil_t_stp[2]);    //Меню -> Фанкойлы -> Конференц1 -> ТКомнаты -> Задание
modbusdecl(ModbusTable, modbusRW, 162, fancoil_t_out_air[2]);    //Меню -> Фанкойлы -> Конференц1 -> ТВоздух
modbusdecl(ModbusTable, modbusRW, 163, fancoil_t_in_water[2]);    //Меню -> Фанкойлы -> Конференц1 -> ТВода
modbusdecl(ModbusTable, modbusRW, 164, fancoil_speed[2]);    //Меню -> Фанкойлы -> Конференц1 -> Скорость
modbusdecl(ModbusTable, modbusRW, 165, Params.fancoil_speed_stp[2]);    //Меню -> Фанкойлы -> Конференц1 -> Скорость -> Задание
modbusdecl(ModbusTable, modbusRW, 166, empty);
modbusdecl(ModbusTable, modbusRW, 167, empty);
modbusdecl(ModbusTable, modbusRW, 168, empty);
modbusdecl(ModbusTable, modbusRW, 169, empty);
modbusdecl(ModbusTable, modbusRW, 170, fancoil_t_room[3]);    //Меню -> Фанкойлы -> Конференц2 -> ТКомнаты
modbusdecl(ModbusTable, modbusRW, 171, Params.fancoil_t_stp[3]);    //Меню -> Фанкойлы -> Конференц2 -> ТКомнаты -> Задание
modbusdecl(ModbusTable, modbusRW, 172, fancoil_t_out_air[3]);    //Меню -> Фанкойлы -> Конференц2 -> ТВоздух
modbusdecl(ModbusTable, modbusRW, 173, fancoil_t_in_water[3]);    //Меню -> Фанкойлы -> Конференц2 -> ТВода
modbusdecl(ModbusTable, modbusRW, 174, fancoil_speed[3]);    //Меню -> Фанкойлы -> Конференц2 -> Скорость
modbusdecl(ModbusTable, modbusRW, 175, Params.fancoil_speed_stp[3]);    //Меню -> Фанкойлы -> Конференц2 -> Скорость -> Задание
modbusdecl(ModbusTable, modbusRW, 176, empty);
modbusdecl(ModbusTable, modbusRW, 177, empty);
modbusdecl(ModbusTable, modbusRW, 178, empty);
modbusdecl(ModbusTable, modbusRW, 179, empty);
modbusdecl(ModbusTable, modbusRW, 180, fancoil_t_room[4]);    //Меню -> Фанкойлы -> Конференц3 -> ТКомнаты
modbusdecl(ModbusTable, modbusRW, 181, Params.fancoil_t_stp[4]);    //Меню -> Фанкойлы -> Конференц3 -> ТКомнаты -> Задание
modbusdecl(ModbusTable, modbusRW, 182, fancoil_t_out_air[4]);    //Меню -> Фанкойлы -> Конференц3 -> ТВоздух
modbusdecl(ModbusTable, modbusRW, 183, fancoil_t_in_water[4]);    //Меню -> Фанкойлы -> Конференц3 -> ТВода
modbusdecl(ModbusTable, modbusRW, 184, fancoil_speed[4]);    //Меню -> Фанкойлы -> Конференц3 -> Скорость
modbusdecl(ModbusTable, modbusRW, 185, Params.fancoil_speed_stp[4]);    //Меню -> Фанкойлы -> Конференц3 -> Скорость -> Задание
modbusdecl(ModbusTable, modbusRW, 186, empty);
modbusdecl(ModbusTable, modbusRW, 187, empty);
modbusdecl(ModbusTable, modbusRW, 188, empty);
modbusdecl(ModbusTable, modbusRW, 189, empty);
modbusdecl(ModbusTable, modbusRW, 190, fancoil_t_room[5]);    //Меню -> Фанкойлы -> Производ-й1 -> ТКомнаты
modbusdecl(ModbusTable, modbusRW, 191, Params.fancoil_t_stp[5]);    //Меню -> Фанкойлы -> Производ-й1 -> ТКомнаты -> Задание
modbusdecl(ModbusTable, modbusRW, 192, fancoil_t_out_air[5]);    //Меню -> Фанкойлы -> Производ-й1 -> ТВоздух
modbusdecl(ModbusTable, modbusRW, 193, fancoil_t_in_water[5]);    //Меню -> Фанкойлы -> Производ-й1 -> ТВода
modbusdecl(ModbusTable, modbusRW, 194, fancoil_speed[5]);    //Меню -> Фанкойлы -> Производ-й1 -> Скорость
modbusdecl(ModbusTable, modbusRW, 195, Params.fancoil_speed_stp[5]);    //Меню -> Фанкойлы -> Производ-й1 -> Скорость -> Задание
modbusdecl(ModbusTable, modbusRW, 196, empty);
modbusdecl(ModbusTable, modbusRW, 197, empty);
modbusdecl(ModbusTable, modbusRW, 198, empty);
modbusdecl(ModbusTable, modbusRW, 199, empty);
modbusdecl(ModbusTable, modbusRW, 200, fancoil_t_room[6]);    //Меню -> Фанкойлы -> Производ-й2 -> ТКомнаты
modbusdecl(ModbusTable, modbusRW, 201, Params.fancoil_t_stp[6]);    //Меню -> Фанкойлы -> Производ-й2 -> ТКомнаты -> Задание
modbusdecl(ModbusTable, modbusRW, 202, fancoil_t_out_air[6]);    //Меню -> Фанкойлы -> Производ-й2 -> ТВоздух
modbusdecl(ModbusTable, modbusRW, 203, fancoil_t_in_water[6]);    //Меню -> Фанкойлы -> Производ-й2 -> ТВода
modbusdecl(ModbusTable, modbusRW, 204, fancoil_speed[6]);    //Меню -> Фанкойлы -> Производ-й2 -> Скорость
modbusdecl(ModbusTable, modbusRW, 205, Params.fancoil_speed_stp[6]);    //Меню -> Фанкойлы -> Производ-й2 -> Скорость -> Задание
modbusdecl(ModbusTable, modbusRW, 206, empty);
modbusdecl(ModbusTable, modbusRW, 207, empty);
modbusdecl(ModbusTable, modbusRW, 208, empty);
modbusdecl(ModbusTable, modbusRW, 209, empty);
modbusdecl(ModbusTable, modbusRW, 210, Params.ex_fan_speed[0]);    //Меню -> Вентиляция -> Коммерческий
modbusdecl(ModbusTable, modbusRW, 211, Params.ex_fan_speed[1]);    //Меню -> Вентиляция -> Холл
modbusdecl(ModbusTable, modbusRW, 212, Params.flaps);    //Меню -> Вентиляция -> ЗаслонкиХолл
modbusdecl(ModbusTable, modbusRW, 213, Params.ex_fan_speed[2]);    //Меню -> Вентиляция -> Прооизвод-й
modbusdecl(ModbusTable, modbusRW, 214, co2_commer);    //Меню -> Вентиляция -> CO2Коммерч
modbusdecl(ModbusTable, modbusRW, 215, co2_work);    //Меню -> Вентиляция -> CO2Произ-й
modbusdecl(ModbusTable, modbusRW, 894, Year);    //Меню -> Часы -> Год
modbusdecl(ModbusTable, modbusRW, 895, Month);    //Меню -> Часы -> Месяц
modbusdecl(ModbusTable, modbusRW, 896, Day);    //Меню -> Часы -> Число
modbusdecl(ModbusTable, modbusRW, 897, Hours);    //Меню -> Часы -> Час
modbusdecl(ModbusTable, modbusRW, 898, Minutes);    //Меню -> Часы -> Мин
modbusdecl(ModbusTable, modbusRW, 899, Seconds);    //Меню -> Часы -> Сек
modbusdecl(ModbusTable, modbusRW, 900, Params.from_chiller_c);    //Настройки -> Корректировка -> От чиллера
modbusdecl(ModbusTable, modbusRW, 901, Params.to_chiller_c);    //Настройки -> Корректировка -> В чиллер
modbusdecl(ModbusTable, modbusRW, 902, Params.from_user_c);    //Настройки -> Корректировка -> От потребителя
modbusdecl(ModbusTable, modbusRW, 903, Params.to_user_c);    //Настройки -> Корректировка -> К потребителю
modbusdecl(ModbusTable, modbusRW, 904, Params.fancoil_t_room_correct[0]);    //Настройки -> Корректировка -> Коммерческий
modbusdecl(ModbusTable, modbusRW, 905, Params.fancoil_t_room_correct[1]);    //Настройки -> Корректировка -> Холл
modbusdecl(ModbusTable, modbusRW, 906, Params.fancoil_t_room_correct[5]);    //Настройки -> Корректировка -> Производ-й
modbusdecl(ModbusTable, modbusRW, 910, Params.fancoil_t_stp_hyst);    //Настройки -> Фанкойлы -> Гистерезис
modbusdecl(ModbusTable, modbusRW, 911, Params.fancoil_t_in_water_cool);    //Настройки -> Фанкойлы -> ХолодС
modbusdecl(ModbusTable, modbusRW, 912, Params.fancoil_t_in_water_heat);    //Настройки -> Фанкойлы -> ТеплоС
modbusdecl(ModbusTable, modbusRW, 913, Params.fancoil_t_pipe_hyst);    //Настройки -> Фанкойлы -> Гист-зисТруба
modbusdecl(ModbusTable, modbusRW, 914, change_time);

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

void fancoils()
{
    short i;
    for (i=0;i<7;i++)
    {
        if (
            fancoil_t_in_water[i]>Params.fancoil_t_in_water_heat+Params.fancoil_t_pipe_hyst
            ||
            (fancoil_t_in_water[i]>Params.fancoil_t_in_water_heat && fancoil_mode[i]==2)
            ) fancoil_mode[i]=2;
        else if (
                    fancoil_t_in_water[i]<Params.fancoil_t_in_water_cool-Params.fancoil_t_pipe_hyst
                    ||
                    (fancoil_t_in_water[i]<Params.fancoil_t_in_water_cool && fancoil_mode[i]==1)
                ) fancoil_mode[i]=1;
        else
        {
            fancoil_mode[i]=0;
            fancoil_speed[i]=0;
        }
        if (fancoil_mode[i]==2)
        {
            if (Params.fancoil_speed_stp[i]>=4)
            {
                if (fancoil_t_room[i]<Params.fancoil_t_stp[i]-Params.fancoil_t_stp_hyst*3/2
                    ||
                    (fancoil_t_room[i]<Params.fancoil_t_stp[i]-Params.fancoil_t_stp_hyst && fancoil_speed[i]==3)
                    ) fancoil_speed[i]=3;
                else if (fancoil_t_room[i]<Params.fancoil_t_stp[i]-Params.fancoil_t_stp_hyst
                    ||
                    (fancoil_t_room[i]<Params.fancoil_t_stp[i]-Params.fancoil_t_stp_hyst/2 && fancoil_speed[i]>=2)
                    ) fancoil_speed[i]=2;
                else if (fancoil_t_room[i]<Params.fancoil_t_stp[i]-Params.fancoil_t_stp_hyst/2
                    ||
                    (fancoil_t_room[i]<Params.fancoil_t_stp[i]+Params.fancoil_t_stp_hyst/2 && fancoil_speed[i]>=1)
                    ) fancoil_speed[i]=1;
                else fancoil_speed[i]=0;
            }
            else
            {
                if (fancoil_t_room[i]<Params.fancoil_t_stp[i]-Params.fancoil_t_stp_hyst/2) fancoil_speed[i]=Params.fancoil_speed_stp[i];
                if (fancoil_t_room[i]>Params.fancoil_t_stp[i]+Params.fancoil_t_stp_hyst/2 || fancoil_speed[i]!=Params.fancoil_speed_stp[i]) fancoil_speed[i]=0;
            }
        }
        else if (fancoil_mode[i]==1)
        {
            if (Params.fancoil_speed_stp[i]>=4)
            {
                if (fancoil_t_room[i]>Params.fancoil_t_stp[i]+Params.fancoil_t_stp_hyst*3/2
                    ||
                    (fancoil_t_room[i]>Params.fancoil_t_stp[i]+Params.fancoil_t_stp_hyst && fancoil_speed[i]==3)
                    ) fancoil_speed[i]=3;
                else if (fancoil_t_room[i]>Params.fancoil_t_stp[i]+Params.fancoil_t_stp_hyst
                    ||
                    (fancoil_t_room[i]>Params.fancoil_t_stp[i]+Params.fancoil_t_stp_hyst/2 && fancoil_speed[i]>=2)
                    ) fancoil_speed[i]=2;
                else if (fancoil_t_room[i]>Params.fancoil_t_stp[i]+Params.fancoil_t_stp_hyst/2
                    ||
                    (fancoil_t_room[i]>Params.fancoil_t_stp[i]-Params.fancoil_t_stp_hyst/2 && fancoil_speed[i]>=1)
                    ) fancoil_speed[i]=1;
                else fancoil_speed[i]=0;
            }
            else
            {
                if (fancoil_t_room[i]<Params.fancoil_t_stp[i]-Params.fancoil_t_stp_hyst/2 || fancoil_speed[i]!=Params.fancoil_speed_stp[i]) fancoil_speed[i]=0;
                if (fancoil_t_room[i]>Params.fancoil_t_stp[i]+Params.fancoil_t_stp_hyst/2) fancoil_speed[i]=Params.fancoil_speed_stp[i];
            }
        }
    }
}



void IOInit()
{
    IO.Init();
    IO.SetAIType(1,ioTypePT1000,0);
    IO.SetAIType(2,ioTypeNTC,0);
    IO.SetAIType(3,ioTypePT1000,0);
    IO.SetAIType(4,ioType0_10V,0);
    IO.SetAIType(5,ioTypeNTC,0);
    IO.SetAIType(6,ioTypeNTC,0);
    IO.SetAIType(7,ioTypeNTC,0);
    IO.SetAIType(8,ioTypeNTC,0);
};

void IOReadWrite()
{
    from_chiller = ai_read(5, -20, 800, Params.from_chiller_c);
    to_chiller = ai_read(6, -20, 800, Params.to_chiller_c);
    from_user = ai_read(7, -20, 800, Params.from_user_c);
    to_user = ai_read(8, -20, 800, Params.to_user_c);
    fancoil_t_room[0] = ai_read(1, -20, 800, Params.fancoil_t_room_correct[0]);
    fancoil_t_room[1] = ai_read(2, -20, 800, Params.fancoil_t_room_correct[1]);
    fancoil_t_room[2] = fancoil_t_room[1];
    fancoil_t_room[3] = fancoil_t_room[1];
    fancoil_t_room[4] = fancoil_t_room[1];
    fancoil_t_room[5] = ai_read(3, -20, 800, Params.fancoil_t_room_correct[5]);
    fancoil_t_room[6] = fancoil_t_room[5];
    co2_commer = -32767;
    co2_work = IO.GetAI(4);

    IO.SetDO(4,chiller)
}


void App_Init()  {
Can.NodeID = 1;
    Can.Init(50000,0);

    Com1.InitComEx(1,ComBufferRx[0],ASize(ComBufferRx),ComBufferTx[0],ASize(ComBufferTx));
    Com1.Init(38400,comSerFlag_8N1);
    Com1.Ident = 1;
    Com1.SetRxTimeout(1);


IOInit();
Params.InitParams();
};


// this is the control loop procedure, and will be called continuously
void App_Run()  {
int i;
Time();
IOReadWrite();
chiller = Timer2(Params.chill_on1[week],Params.chill_off1[week],Params.chill_on2[week],Params.chill_off2[week]);
fancoils();
    /*
    for (i=0; i<7; i++)
    {
        if (Params.chill_on1[i]>1440) Params.chill_on1[i]=1440;
        if (Params.chill_on1[i]<0) Params.chill_on1[i]=0;
        if (Params.chill_off1[i]>1440) Params.chill_off1[i]=1440;
        if (Params.chill_off1[i]<0) Params.chill_off1[i]=0;
        if (Params.chill_on2[i]>1440) Params.chill_on2[i]=1440;
        if (Params.chill_on2[i]<0) Params.chill_on2[i]=0;
        if (Params.chill_off2[i]>1440) Params.chill_off2[i]=1440;
        if (Params.chill_off2[i]<0) Params.chill_off2[i]=0;
        if (Params.fancoil_speed_stp[i]<0) Params.fancoil_speed_stp[i]=0;
        if (Params.fancoil_speed_stp[i]>4) Params.fancoil_speed_stp[i]=4;
        if (Params.fancoil_t_stp[i]<100) Params.fancoil_t_stp[i]=100;
        if (Params.fancoil_t_stp[i]>400) Params.fancoil_t_stp[i]=400;
    }
    */
};
