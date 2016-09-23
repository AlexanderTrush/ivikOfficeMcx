#include "stdui.c"
#include "sysdef.lib"
#include "mcxlib.lib"
#define CHANGE_TIME_ADRESS 914

//имена пунктов меню, значений параметров при именном редактировании пункта меню, постфиксов
const String Names(14)[]={"Меню","Чиллер","От чиллера","В чиллер","От потребителя","К потребителю","График","Понедельник","Вкл1","Выкл1","Вкл2","Выкл2","Вторник","Среда","Четверг","Пятница","Суббота","Воскресенье","Фанкойлы","Коммерческий","ТКомнаты","Задание","ТВоздух","ТВода","Скорость","Холл","Конференц1","Конференц2","Конференц3","Производ-й1","Производ-й2","Вентиляция","ЗаслонкиХолл","Прооизвод-й","CO2Коммерч","CO2Произ-й","Часы","Год","Месяц","Число","Час","Мин","Сек","Настройки","Корректировка","Производ-й","Гистерезис","ХолодС","ТеплоС","Гист-зисТруба","Выкл","Вкл ","1-я ","2-я ","3-я ","Авто","Закр","Откр","","°С","%"};

//Имена меню(указатель на Names)
const char Menu_name[]={0,1,6,7,12,13,14,15,16,17,18,19,20,24,25,20,24,26,20,24,27,20,24,28,20,24,29,20,24,30,20,24,31,36,43,44,18};
//Длины меню (Количество пунктов)
const char Menu_lenth[]={4,5,7,4,4,4,4,4,4,4,7,4,1,1,4,1,1,4,1,1,4,1,1,4,1,1,4,1,1,4,1,1,6,6,2,7,4};
//Номера меню-родителей
const char Menu_parent_menu[]={0,0,1,2,2,2,2,2,2,2,0,10,11,11,10,14,14,10,17,17,10,20,20,10,23,23,10,26,26,10,29,29,0,0,0,34,34};
//перечень пунктов для каждого меню
const short Menu_puncts[][]={{98,91,41,0,0,0,0},{5,4,3,2,1,0,0},{36,31,26,21,16,11,6},{10,9,8,7,0,0,0},{15,14,13,12,0,0,0},{20,19,18,17,0,0,0},{25,24,23,22,0,0,0},{30,29,28,27,0,0,0},{35,34,33,32,0,0,0},{40,39,38,37,0,0,0},{84,77,70,63,56,49,42},{47,46,45,43,0,0,0},{44,0,0,0,0,0,0},{48,0,0,0,0,0,0},{54,53,52,50,0,0,0},{51,0,0,0,0,0,0},{55,0,0,0,0,0,0},{61,60,59,57,0,0,0},{58,0,0,0,0,0,0},{62,0,0,0,0,0,0},{68,67,66,64,0,0,0},{65,0,0,0,0,0,0},{69,0,0,0,0,0,0},{75,74,73,71,0,0,0},{72,0,0,0,0,0,0},{76,0,0,0,0,0,0},{82,81,80,78,0,0,0},{79,0,0,0,0,0,0},{83,0,0,0,0,0,0},{89,88,87,85,0,0,0},{86,0,0,0,0,0,0},{90,0,0,0,0,0,0},{97,96,95,94,93,92,0},{104,103,102,101,100,99,0},{113,105,0,0,0,0,0},{112,111,110,109,108,107,106},{117,116,115,114,0,0,0}};

//Имя пунктов(указатель на Names)
const short Punct_name[]={1,2,3,4,5,6,7,8,9,10,11,12,8,9,10,11,13,8,9,10,11,14,8,9,10,11,15,8,9,10,11,16,8,9,10,11,17,8,9,10,11,18,19,20,21,22,23,24,21,25,20,21,22,23,24,21,26,20,21,22,23,24,21,27,20,21,22,23,24,21,28,20,21,22,23,24,21,29,20,21,22,23,24,21,30,20,21,22,23,24,21,31,19,25,32,33,34,35,36,37,38,39,40,41,42,44,2,3,4,5,19,25,45,18,46,47,48,49};
// - номер меню-ребенка(действителен, если TPunctMenu[].on_enter_change_menu=1)
const short Punct_children_menu[]={1,37,37,37,37,2,3,37,37,37,37,4,37,37,37,37,5,37,37,37,37,6,37,37,37,37,7,37,37,37,37,8,37,37,37,37,9,37,37,37,37,10,11,12,37,37,37,13,37,14,15,37,37,37,16,37,17,18,37,37,37,19,37,20,21,37,37,37,22,37,23,24,37,37,37,25,37,26,27,37,37,37,28,37,29,30,37,37,37,31,37,32,37,37,37,37,37,37,33,37,37,37,37,37,37,35,37,37,37,37,37,37,37,36,37,37,37,37};
// - Адрес Modbus переменной
const short Punct_parametr[]={0,100,101,102,103,132,0,104,105,106,107,0,108,109,110,111,0,112,113,114,115,0,116,117,118,119,0,120,121,122,123,0,124,125,126,127,0,128,129,130,131,0,0,140,141,142,143,144,145,0,150,151,152,153,154,155,0,160,161,162,163,164,165,0,170,171,172,173,174,175,0,180,181,182,183,184,185,0,190,191,192,193,194,195,0,200,201,202,203,204,205,0,210,211,212,213,214,215,0,894,895,896,897,898,899,0,900,901,902,903,904,905,906,0,910,911,912,913};
// ширина поля отображения переменной
const char Punct_value_width[]={0,5,5,5,5,4,0,5,5,5,5,0,5,5,5,5,0,5,5,5,5,0,5,5,5,5,0,5,5,5,5,0,5,5,5,5,0,5,5,5,5,0,0,5,4,5,5,1,4,0,5,4,5,5,1,4,0,5,4,5,5,1,4,0,5,4,5,5,1,4,0,5,4,5,5,1,4,0,5,4,5,5,1,4,0,5,4,5,5,1,4,0,1,1,4,1,5,5,0,4,2,2,2,2,2,0,4,4,4,4,4,4,4,0,4,4,4,3};
// количество символов после запятой
const char Punct_point_value_show[]={0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,1,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,1};
//этот пункт меняет дискретную переменную (включить/выключить), по адресу parametr
const char Punct_on_enter_change_value[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//пункт меню редактирует переменную графика (времени)
const char Punct_change_timer[]={0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//этот пункт предназначен для изменения времени;
const char Punct_change_time[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
//в случае пунта для редактирования переменной  - верхний предел значений этой переменной
const short Punct_up_limit[]={0,0,0,0,0,1,0,1440,1440,1440,1440,0,1440,1440,1440,1440,0,1440,1440,1440,1440,0,1440,1440,1440,1440,0,1440,1440,1440,1440,0,1440,1440,1440,1440,0,1440,1440,1440,1440,0,0,0,400,0,0,0,4,0,0,400,0,0,0,4,0,0,400,0,0,0,4,0,0,400,0,0,0,4,0,0,400,0,0,0,4,0,0,400,0,0,0,4,0,0,400,0,0,0,4,0,5,5,1,5,0,0,0,2100,12,31,23,59,59,0,99,99,99,99,99,99,99,0,100,250,500,99};
//в случае пунта для редактирования переменной  - нижний предел значений этой переменной
const short Punct_down_limit[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,100,0,0,0,0,0,0,100,0,0,0,0,0,0,100,0,0,0,0,0,0,100,0,0,0,0,0,0,100,0,0,0,0,0,0,100,0,0,0,0,0,0,100,0,0,0,0,0,0,0,0,0,0,0,0,2013,1,1,0,0,0,0,-99,-99,-99,-99,-99,-99,-99,0,0,0,251,1};
//именное редактирование пункта меню (если =1, каждому значению переменной меню присваивается текстовое имя)
const char Punct_by_name[]={0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
// - ряд имен в name_by_name (действителен, если Punct_by_name[]=1)
const short Punct_row_in_name_by_name[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,2,0,0,0,0,0,0,3,0,0,0,0,0,0,4,0,0,0,0,0,0,5,0,0,0,0,0,0,6,0,0,0,0,0,0,7,0,0,0,8,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
//Имена постфиксов (указатель на Names) не может быть равным 0 иначе постфикс не отображается
const short Punct_postfix[]={58,59,59,59,59,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,58,59,59,59,59,58,58,58,59,59,59,59,58,58,58,59,59,59,59,58,58,58,59,59,59,59,58,58,58,59,59,59,59,58,58,58,59,59,59,59,58,58,58,59,59,59,59,58,58,58,58,58,58,58,60,60,58,58,58,58,58,58,58,58,59,59,59,59,59,59,59,58,59,59,59,59};
//Имена при именном редактировании(указатель на Names)
const short name_by_name[][]={{50,51,0,0,0},{50,52,53,54,55},{50,52,53,54,55},{50,52,53,54,55},{50,52,53,54,55},{50,52,53,54,55},{50,52,53,54,55},{50,52,53,54,55},{56,57,0,0,0},};

TMenu Menu[37];
TPunct Punct[118];

void InitMenu()
{

current_menu=0;
temp_menu=1;

Menu[0].up=3;
Menu[0].current_punct=3;
Punct[0].on_enter_change_menu=1;
Punct[41].on_enter_change_menu=1;
Punct[91].on_enter_change_menu=1;
Punct[98].on_enter_change_menu=1;
Menu[1].up=4;
Menu[1].current_punct=4;
Punct[5].on_enter_change_menu=1;
if(MBRead(Punct_parametr[5])+4>Punct_up_limit[5]) Punct[5].up_by_name=Punct_up_limit[5]; else Punct[5].up_by_name=MBRead(Punct_parametr[5])+4;
Menu[2].up=6;
Menu[2].current_punct=6;
Punct[6].on_enter_change_menu=1;
Punct[11].on_enter_change_menu=1;
Punct[16].on_enter_change_menu=1;
Punct[21].on_enter_change_menu=1;
Punct[26].on_enter_change_menu=1;
Punct[31].on_enter_change_menu=1;
Punct[36].on_enter_change_menu=1;
Menu[3].up=3;
Menu[3].current_punct=3;
Punct[7].change_value=1;
Punct[8].change_value=1;
Punct[9].change_value=1;
Punct[10].change_value=1;
Menu[4].up=3;
Menu[4].current_punct=3;
Punct[12].change_value=1;
Punct[13].change_value=1;
Punct[14].change_value=1;
Punct[15].change_value=1;
Menu[5].up=3;
Menu[5].current_punct=3;
Punct[17].change_value=1;
Punct[18].change_value=1;
Punct[19].change_value=1;
Punct[20].change_value=1;
Menu[6].up=3;
Menu[6].current_punct=3;
Punct[22].change_value=1;
Punct[23].change_value=1;
Punct[24].change_value=1;
Punct[25].change_value=1;
Menu[7].up=3;
Menu[7].current_punct=3;
Punct[27].change_value=1;
Punct[28].change_value=1;
Punct[29].change_value=1;
Punct[30].change_value=1;
Menu[8].up=3;
Menu[8].current_punct=3;
Punct[32].change_value=1;
Punct[33].change_value=1;
Punct[34].change_value=1;
Punct[35].change_value=1;
Menu[9].up=3;
Menu[9].current_punct=3;
Punct[37].change_value=1;
Punct[38].change_value=1;
Punct[39].change_value=1;
Punct[40].change_value=1;
Menu[10].up=6;
Menu[10].current_punct=6;
Punct[42].on_enter_change_menu=1;
Punct[49].on_enter_change_menu=1;
Punct[56].on_enter_change_menu=1;
Punct[63].on_enter_change_menu=1;
Punct[70].on_enter_change_menu=1;
Punct[77].on_enter_change_menu=1;
Punct[84].on_enter_change_menu=1;
Menu[11].up=3;
Menu[11].current_punct=3;
Punct[43].on_enter_change_menu=1;
Punct[47].on_enter_change_menu=1;
Menu[12].up=0;
Menu[12].current_punct=0;
Punct[44].change_value=1;
Menu[13].up=0;
Menu[13].current_punct=0;
Punct[48].change_value=1;
if(MBRead(Punct_parametr[48])+4>Punct_up_limit[48]) Punct[48].up_by_name=Punct_up_limit[48]; else Punct[48].up_by_name=MBRead(Punct_parametr[48])+4;
Menu[14].up=3;
Menu[14].current_punct=3;
Punct[50].on_enter_change_menu=1;
Punct[54].on_enter_change_menu=1;
Menu[15].up=0;
Menu[15].current_punct=0;
Punct[51].change_value=1;
Menu[16].up=0;
Menu[16].current_punct=0;
Punct[55].change_value=1;
if(MBRead(Punct_parametr[55])+4>Punct_up_limit[55]) Punct[55].up_by_name=Punct_up_limit[55]; else Punct[55].up_by_name=MBRead(Punct_parametr[55])+4;
Menu[17].up=3;
Menu[17].current_punct=3;
Punct[57].on_enter_change_menu=1;
Punct[61].on_enter_change_menu=1;
Menu[18].up=0;
Menu[18].current_punct=0;
Punct[58].change_value=1;
Menu[19].up=0;
Menu[19].current_punct=0;
Punct[62].change_value=1;
if(MBRead(Punct_parametr[62])+4>Punct_up_limit[62]) Punct[62].up_by_name=Punct_up_limit[62]; else Punct[62].up_by_name=MBRead(Punct_parametr[62])+4;
Menu[20].up=3;
Menu[20].current_punct=3;
Punct[64].on_enter_change_menu=1;
Punct[68].on_enter_change_menu=1;
Menu[21].up=0;
Menu[21].current_punct=0;
Punct[65].change_value=1;
Menu[22].up=0;
Menu[22].current_punct=0;
Punct[69].change_value=1;
if(MBRead(Punct_parametr[69])+4>Punct_up_limit[69]) Punct[69].up_by_name=Punct_up_limit[69]; else Punct[69].up_by_name=MBRead(Punct_parametr[69])+4;
Menu[23].up=3;
Menu[23].current_punct=3;
Punct[71].on_enter_change_menu=1;
Punct[75].on_enter_change_menu=1;
Menu[24].up=0;
Menu[24].current_punct=0;
Punct[72].change_value=1;
Menu[25].up=0;
Menu[25].current_punct=0;
Punct[76].change_value=1;
if(MBRead(Punct_parametr[76])+4>Punct_up_limit[76]) Punct[76].up_by_name=Punct_up_limit[76]; else Punct[76].up_by_name=MBRead(Punct_parametr[76])+4;
Menu[26].up=3;
Menu[26].current_punct=3;
Punct[78].on_enter_change_menu=1;
Punct[82].on_enter_change_menu=1;
Menu[27].up=0;
Menu[27].current_punct=0;
Punct[79].change_value=1;
Menu[28].up=0;
Menu[28].current_punct=0;
Punct[83].change_value=1;
if(MBRead(Punct_parametr[83])+4>Punct_up_limit[83]) Punct[83].up_by_name=Punct_up_limit[83]; else Punct[83].up_by_name=MBRead(Punct_parametr[83])+4;
Menu[29].up=3;
Menu[29].current_punct=3;
Punct[85].on_enter_change_menu=1;
Punct[89].on_enter_change_menu=1;
Menu[30].up=0;
Menu[30].current_punct=0;
Punct[86].change_value=1;
Menu[31].up=0;
Menu[31].current_punct=0;
Punct[90].change_value=1;
if(MBRead(Punct_parametr[90])+4>Punct_up_limit[90]) Punct[90].up_by_name=Punct_up_limit[90]; else Punct[90].up_by_name=MBRead(Punct_parametr[90])+4;
Menu[32].up=5;
Menu[32].current_punct=5;
Punct[92].change_value=1;
Punct[93].change_value=1;
Punct[94].change_value=1;
if(MBRead(Punct_parametr[94])+4>Punct_up_limit[94]) Punct[94].up_by_name=Punct_up_limit[94]; else Punct[94].up_by_name=MBRead(Punct_parametr[94])+4;
Punct[95].change_value=1;
Menu[33].up=5;
Menu[33].current_punct=5;
Punct[99].change_value=1;
Punct[100].change_value=1;
Punct[101].change_value=1;
Punct[102].change_value=1;
Punct[103].change_value=1;
Punct[104].change_value=1;
Menu[34].up=1;
Menu[34].current_punct=1;
Punct[105].on_enter_change_menu=1;
Punct[113].on_enter_change_menu=1;
Menu[35].up=6;
Menu[35].current_punct=6;
Punct[106].change_value=1;
Punct[107].change_value=1;
Punct[108].change_value=1;
Punct[109].change_value=1;
Punct[110].change_value=1;
Punct[111].change_value=1;
Punct[112].change_value=1;
Menu[36].up=3;
Menu[36].current_punct=3;
Punct[114].change_value=1;
Punct[115].change_value=1;
Punct[116].change_value=1;
Punct[117].change_value=1;

};

bit red;
bit LCD_TYPE;
char current_menu;
char temp_menu=1;
short temp15[6];
TTimer nkp;
TTimer cont_disp_timer;


struct TPunct
{
bit on_enter_change_menu;//этот пункт помогает мерейти к другому меню
bit change_value;             //этот пункт меняет переменную, по адресу parametr
char up_by_name;   //Верхний предел именного редактора параметра меню
};

struct TMenu
{
    char up;           //Верхний предел меню
    char current_punct; //Текущий пункт меню
};


void on_updown()
{
    short current_punct;
    kbd.EditParam();//Если нажали вверх - kbd.Val++, если вниз - kbd.Val--

        if (red)//если меню редактируется
        {
            current_punct=Menu_puncts[current_menu][Menu[current_menu].current_punct];
            if (Punct_by_name[current_punct])//редктируется поименно
            {
                //вычисляем up_by_name для того, чтобы правильно отобразить поле поименного редактирования
                if (kbd.Val>Punct[current_punct].up_by_name) Punct[current_punct].up_by_name=kbd.Val;
                if (kbd.Val<Punct[current_punct].up_by_name-4) Punct[current_punct].up_by_name=kbd.Val+4;
                //отображаем поле поименного редактирования
                display();
            };
        }
        else
        {
            //если меню не редактируется вычисляем up для того, чтобы правильно отобразить видимую часть меню
            if (kbd.Val>Menu[current_menu].up) Menu[current_menu].up=kbd.Val;
            if (kbd.Val<Menu[current_menu].up-5) Menu[current_menu].up=kbd.Val+5;
            //отображаем видимую часть меню
                display();
        };


};

void on_enter()
{
    short send;
    short current_punct;
    if(red)
    {
        current_punct=Menu_puncts[current_menu][Menu[current_menu].current_punct];
        send=kbd.Val;
        MBSend(Punct_parametr[current_punct],send);
        if (Punct_change_time[current_punct]) MBSend(CHANGE_TIME_ADRESS,1);
        kbd.Min=0;
        kbd.Max=Menu_lenth[current_menu]-1;
        kbd.Val=Menu[current_menu].current_punct;
        if (kbd.Val>kbd.Max) kbd.Val=kbd.Max;
        if (kbd.Val<kbd.Min) kbd.Val=kbd.Min;
        red=0;
        display();
    }
    else
    {
        current_punct=Menu_puncts[current_menu][kbd.Val];
        if (Punct[current_punct].on_enter_change_menu)
        {
            Menu[current_menu].current_punct=kbd.Val;
            current_menu=Punct_children_menu[current_punct];
            reinit_menu();
        }
        else
        {
            if (Punct[current_punct].change_value)
            {
                if(Punct_on_enter_change_value[current_punct])
                {
                    if(MBRead(Punct_parametr[current_punct])>0) MBSend(Punct_parametr[current_punct],0)
                    else MBSend(Punct_parametr[current_punct],1);
                }
                else
                {
                    Menu[current_menu].current_punct=kbd.Val;
                    kbd.Min=Punct_down_limit[current_punct];
                    kbd.Max=Punct_up_limit[current_punct];
                    kbd.Val=MBRead(Punct_parametr[current_punct]);
                    if (kbd.Val>kbd.Max) kbd.Val=kbd.Max;
                    if (kbd.Val<kbd.Min) kbd.Val=kbd.Min;
                    red=1;
                    display();
                };
            };
        };
    };
};

void on_esc()
{
    if(red)
    {
        kbd.Min=0;
        kbd.Max=Menu_lenth[current_menu]-1;
        kbd.Val=Menu[current_menu].current_punct;
        if (kbd.Val>kbd.Max) kbd.Val=kbd.Max;
        if (kbd.Val<kbd.Min) kbd.Val=kbd.Min;
        red=0;
        display();
    }
    else
    {
        Menu[current_menu].current_punct = kbd.Val;
        current_menu=Menu_parent_menu[current_menu];
        reinit_menu();
    };
};

void display()
{
    char i;
    char j;
    char value_pos;
    short current_punct;
    short par;
    short par_h;
    short par_m;
    dsp.ClearDisplay();
    if (red)
    {
        current_punct=Menu_puncts[current_menu][Menu[current_menu].current_punct];
        dsp.DrawTextCenter(0,Names[Menu_name[current_menu]]);
        dsp.DrawTextCR(0,1,Names[Punct_name[current_punct]]);
        if (Punct_by_name[current_punct])
        {
            i=Punct[current_punct].up_by_name;
            while (i>=0 && i>Punct[current_punct].up_by_name-5)
            {
                if (i==kbd.Val) dsp.SetColor(0,1);
                dsp.DrawTextCR(0,Punct[current_punct].up_by_name-i+3,Names[name_by_name[Punct_row_in_name_by_name[current_punct]][i]]);
                if (i==kbd.Val) dsp.SetColor(1,0);
                if (Punct_postfix[current_punct]>0)
                {
                    dsp.DrawTextCR(Punct_value_width[current_punct]+1,Punct[current_punct].up_by_name-i+3,Names[Punct_postfix[current_punct]]);
                }
                i--;
            };
        }
        else
        {
            if (Punct_change_timer[current_punct])
            {
                par_h=kbd.Val/60;
                par_m=kbd.Val-par_h*60;
                if (par_h>=24)
                {
                    dsp.DrawTextCR(0,4,">--:--");
                }
                else
                {
                    dsp.DrawValueCR(0,4,">",par_h,2,0);
                    dsp.DrawValueCR(3,4,":",par_m,2,0);
                }
                if (Punct_postfix[current_punct]>0)
                {
                    dsp.DrawTextCR(7,4,Names[Punct_postfix[current_punct]]);
                }
            }
            else
            {
                //это не совсем правильно, но я надеюсь что больше 9 цифр в числе не будет
                dsp.DrawValueCR(0,4,">",kbd.Val,10,ToChar(Punct_point_value_show[current_punct]));

                if (Punct_postfix[current_punct]>0)
                {
                    dsp.DrawTextCR(11,4,Names[Punct_postfix[current_punct]]);
                }
            }
        };
    }
    else
    {
        dsp.DrawTextCenter(0,Names[Menu_name[current_menu]]);
        i=Menu[current_menu].up;
        while (i>=0 && i>Menu[current_menu].up-6)
        {
            current_punct=Menu_puncts[current_menu][i];
            if (i==kbd.Val) dsp.SetColor(0,1);
            dsp.DrawTextCR(0,Menu[current_menu].up-i+2,Names[Punct_name[current_punct]]);
            if (i==kbd.Val) dsp.SetColor(1,0);

            if (Punct_postfix[Menu_puncts[current_menu][i]]>0)
            {
                if (LCD_TYPE>0)
                dsp.DrawTextCR(21-Names[Punct_postfix[current_punct]].Len,Menu[current_menu].up-i+2,Names[Punct_postfix[current_punct]]);
                else
                dsp.DrawTextCR(16-Names[Punct_postfix[current_punct]].Len,Menu[current_menu].up-i+2,Names[Punct_postfix[current_punct]]);
            }
            i--;
        };
        for (i=2; i<8 && i<=Menu[current_menu].up+2; i++)
        {
            current_punct=Menu_puncts[current_menu][Menu[current_menu].up-i+2];
            if (Punct_value_width[current_punct]>0)
            {
                if (LCD_TYPE>0)
                {
                    if (Punct_postfix[current_punct]>0) value_pos=21-Names[Punct_postfix[current_punct]].Len-Punct_value_width[current_punct];
                    else value_pos=21-Punct_value_width[current_punct];
                }
                else
                {
                    if (Punct_postfix[current_punct]>0) value_pos=16-Names[Punct_postfix[current_punct]].Len-Punct_value_width[current_punct];
                    else value_pos=16-Punct_value_width[current_punct];
                }
                par=MBRead(Punct_parametr[current_punct]);
                if(Punct_by_name[current_punct])
                {
                    if(par>sizeof(name_by_name[0])/2-1 || par<0) par=0;
                    dsp.DrawTextCR(value_pos,i,Names[name_by_name[Punct_row_in_name_by_name[current_punct]][par]]);
                }
                else
                {
                    if (Punct_change_timer[current_punct])
                    {
                        par_h=par/60;
                        par_m=par-par_h*60;
                        if (par_h>=24) dsp.DrawTextCR(value_pos,i,"--:--");
                        else
                        {
                        dsp.DrawValueCR(value_pos,i,"",par_h,2,0);
                        dsp.DrawValueCR(value_pos+2,i,":",par_m,2,0);
                        }
                    }
                    else
                    {
                        if (par>-32767)
                        {
                            dsp.DrawValueCR(value_pos,i,"",par,Punct_value_width[current_punct],Punct_point_value_show[current_punct]);
                        }
                        else
                        {
                            for (j=0; j<Punct_value_width[current_punct]; j++)
                            {
                                dsp.DrawTextCR(value_pos+j,i,"-");
                            }
                        }
                    }
                };

            };
        };
    };

};

void cont_disp()
{
    char i;
    char j;
    char value_pos;
    short current_punct;
    short par;
    short par_h;
    short par_m;


    if (red)
    {
        current_punct=Menu_puncts[current_menu][Menu[current_menu].current_punct];
        if (!Punct_by_name[current_punct])
        {
            if (Punct_change_timer[current_punct])
            {
                par_h=kbd.Val/60;
                par_m=kbd.Val-par_h*60;
                if (par_h>=24)
                {
                    dsp.DrawTextCR(0,4,">--:--");
                }
                else
                {
                    dsp.DrawValueCR(0,4,">",par_h,2,0);
                    dsp.DrawValueCR(3,4,":",par_m,2,0);
                }
                if (Punct_postfix[current_punct]>0)
                {
                    dsp.DrawTextCR(7,4,Names[Punct_postfix[current_punct]]);
                }
            }
            else
            {
                //это не совсем правильно, но я надеюсь что больше 9 цифр в числе не будет
                dsp.DrawValueCR(0,4,">",kbd.Val,10,ToChar(Punct_point_value_show[current_punct]));
            }

        }
    }
    else
    {
        if (cont_disp_timer.Elapsedms>1000)
        {
            cont_disp_timer.Start();
            for (i=2; i<8 && i<=Menu[current_menu].up+2; i++)
            {
                current_punct=Menu_puncts[current_menu][Menu[current_menu].up-i+2];
                if (Punct_value_width[current_punct]>0)
                {
                    if (LCD_TYPE>0)
                    {
                        if (Punct_postfix[current_punct]>0) value_pos=21-Names[Punct_postfix[current_punct]].Len-Punct_value_width[current_punct];
                        else value_pos=21-Punct_value_width[current_punct];
                    }
                    else
                    {
                        if (Punct_postfix[current_punct]>0) value_pos=16-Names[Punct_postfix[current_punct]].Len-Punct_value_width[current_punct];
                        else value_pos=16-Punct_value_width[current_punct];
                    }
                    par=MBRead(Punct_parametr[current_punct]);
                    if(Punct_by_name[current_punct])
                    {
                        if(par>sizeof(name_by_name[0])/2-1 || par<0) par=0;
                        dsp.DrawTextCR(value_pos,i,Names[name_by_name[Punct_row_in_name_by_name[current_punct]][par]]);
                    }
                    else
                    {
                        if (Punct_change_timer[current_punct])
                        {
                            par_h=par/60;
                            par_m=par-par_h*60;
                            if (par_h>=24) dsp.DrawTextCR(value_pos,i,"--:--");
                            else
                            {
                                dsp.DrawValueCR(value_pos,i,"",par_h,2,0);
                                dsp.DrawValueCR(value_pos+2,i,":",par_m,2,0);
                            }
                        }
                        else
                        {
                            if (par>-32767)
                            {
                                dsp.DrawValueCR(value_pos,i,"",par,Punct_value_width[current_punct],Punct_point_value_show[current_punct]);
                            }
                            else
                            {
                                for (j=0; j<Punct_value_width[current_punct]; j++)
                                {
                                    dsp.DrawTextCR(value_pos+j,i,"-");
                                }
                            }
                        }
                    };
                }
            };
        };
    };

};


 void MBSend(int modbusind, short value)
{
    Can.SendMBVar(Can.GetUITarget(),modbusind,value);
};

short MBRead(long modbusind)
{
    int index;
    index=modbusind;
    return Can.RequestAndWaitMBVar(Can.GetUITarget(),index);
}
void keyboard()
{
if ((kbd.ActiveKey == KEY_DOWN + KEY_UP + KEY_ESC+ KEY_ENTER) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_DOWN + KEY_UP + KEY_ESC) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_DOWN + KEY_UP + KEY_ENTER) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_ESC + KEY_UP + KEY_ENTER) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_ESC + KEY_DOWN + KEY_ENTER) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_UP + KEY_DOWN) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=34;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_ESC + KEY_DOWN) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_ESC + KEY_UP) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_ENTER + KEY_DOWN) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_ENTER + KEY_UP) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

if ((kbd.ActiveKey == KEY_ENTER + KEY_ESC) && (kbd.ActiveTime >= 3000) && !red)
{
    current_menu=0;
    reinit_menu();
    nkp.Start();
    if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
else
{

   if (kbd.ActiveKey==KEY_UP || kbd.ActiveKey==KEY_DOWN)
    {
        on_updown();
        nkp.Start();
        if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
    }
    else
    {
        if (kbd.ReleasedKey==KEY_ENTER)
        {
            on_enter();
            nkp.Start();
            if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
        }
        else
        {
            if (kbd.ReleasedKey==KEY_ESC)
            {
                on_esc();
                nkp.Start();
                if(dsp.GetBrightness()!=100) dsp.SetBrightness(100);
            }
            else
            {
                if(nkp.ElapsedSec>300)                {
                    if(dsp.GetBrightness()!=0) dsp.SetBrightness(0);
                    if (!red){current_menu=0;
reinit_menu();}
}}}}}}}}}}}}}}}};
void reinit_menu()
{
    if(temp_menu!=current_menu)
    {
    temp_menu=current_menu;
    kbd.Max=Menu_lenth[current_menu]-1;
    kbd.Val=Menu[current_menu].current_punct;
    display();
    };
};

TTimer ini;

void App_Init()  {
dsp.Init();
kbd.Init();
kbd.Clear();
if (dsp.Width>98) LCD_TYPE=1;
else LCD_TYPE=0;
ini.Start();
};
void App_Run()
{
    if (ini.isClear()!=1 && ini.ElapsedSec>2)
    {
        ini.Clear();
        InitMenu();
        reinit_menu();
    }
    if (ini.isClear())
    {
        keyboard();
        cont_disp();
    }
};
