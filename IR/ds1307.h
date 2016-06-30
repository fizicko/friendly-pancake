/*
������ ���������� ���������� ������� �� ���������� TWI.h 
�.� ������ ds1307 �������� � �� ��������� ������ TWI(I2C)
*/

//����� ���������� DS1307
#define DS1307_ADDR  0b01101000
//����� ���������� DS1307 + ��� ������
#define DS1307_ADDR_R  (DS1307_ADDR<<1)|1 
//����� ���������� DS1307 + ��� ������
#define DS1307_ADDR_W   DS1307_ADDR<<1

//������� �� ����������� �������
#define ds1307_SetAddress(x)  I2C_SendPocket(x,DS1307_ADDR_W)

//������� ������ ������ ��������
void ds1307_WriteReg (char n,char m)
{
I2C_StartCondition();
I2C_SendByte(DS1307_ADDR_W);
I2C_SendByte(n);
I2C_SendByte(m);
I2C_StopCondition();
}

//������ ����� ��� CH (seconds ����������)
#define ds1307_Start  ds1307_WriteReg(0,0)
//��������� ����� ��� CH (seconds ����������)
#define ds1307_Stop  ds1307_WriteReg(0,0b10000000)
//����� ������ 24 (����� ��� ������ ������) hours ����������
#define ds1307_Set24 ds1307_WriteReg(0x02,0)

//������� ������ ������ ��������
char ds1307_ReadReg (char n)
{
char bb;
I2C_StartCondition();
I2C_SendByte(DS1307_ADDR_R);
bb=I2C_RecieveLastByte();
I2C_StopCondition();
return bb;
}

//�������� ��������� �������
struct Time 
{
char seconds;  //�������
char minutes;  //������
char hours;    //����
char day;      //���� ������
char date;     //�����
char month;    //�����
int year;      //���
};

//������� ������ ��� ��������
void ds1307_GetTime(struct Time* ds)
{
ds1307_SetAddress(0);//��������� �� 0�00
I2C_StartCondition();
I2C_SendByte(DS1307_ADDR_R);
ds->seconds=I2C_RecieveByte();
ds->minutes=I2C_RecieveByte();
ds->hours=I2C_RecieveByte();
ds->day=I2C_RecieveByte();
ds->date=I2C_RecieveByte();
ds->month=I2C_RecieveByte();
ds->year=I2C_RecieveLastByte();
I2C_StopCondition();
}

//������� ���������� ��� �������� (������� � ����)
void ds1307_SetTime(struct Time* ds)
{
I2C_StartCondition();
I2C_SendByte(DS1307_ADDR_W);
I2C_SendByte(0);//��������� �� 0x00
I2C_SendByte(ds->seconds);
I2C_SendByte(ds->minutes);
I2C_SendByte(ds->hours);
I2C_SendByte(ds->day);
I2C_SendByte(ds->date);
I2C_SendByte(ds->month);
I2C_SendByte(ds->year);
I2C_StopCondition();
}

//�������������� �� �������- ���������� ������� � ��������
#define  ds1307_perev_for_me(x)  ((x>>4)*10)+(0b00001111&x)
//�������������� �� �������� � �������-���������� �������
#define  ds1307_perev_for_ds(x)  ((x/10)<<4)|(x%10)

//�������������� ���� ����� ���������
void ds1307_Conv_for_me(struct Time *k)
{
k->seconds=ds1307_perev_for_me(k->seconds);
k->minutes=ds1307_perev_for_me(k->minutes);
k->hours=ds1307_perev_for_me(k->hours);
k->day=ds1307_perev_for_me(k->day);
k->date=ds1307_perev_for_me(k->date);
k->month=ds1307_perev_for_me(k->month);
k->year=ds1307_perev_for_me(k->year);
}

//�������������� ���� ����� ���������
void ds1307_Conv_for_ds(struct Time *x)
{
x->seconds=ds1307_perev_for_ds(x->seconds);
x->minutes=ds1307_perev_for_ds(x->minutes);
x->hours=ds1307_perev_for_ds(x->hours);
x->day=ds1307_perev_for_ds(x->day);
x->date=ds1307_perev_for_ds(x->date);
x->month=ds1307_perev_for_ds(x->month);
x->year=ds1307_perev_for_ds(x->year);
}