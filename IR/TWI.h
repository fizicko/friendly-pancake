// �������� ������� �����
void I2C_StartCondition(void)
{
TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
while (!(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
}

// �������� ����
void I2C_StopCondition(void)
{
TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}

//�������� �����
void I2C_SendByte(unsigned char c)
{
TWDR = c;//�������� �������� � ������� ������
TWCR = (1<<TWINT)|(1<<TWEN);//������� �������� ����� ������
while (!(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
}

//������������� I2C ��� �����������
void I2C_Init (void)
{
TWBR=0xFF;//�������� ��������
}

//�������� SLA_W + ���� ������
void I2C_SendPocket (unsigned char value,unsigned char adres_rw)
{
I2C_StartCondition(); // ���������� ������� �����
I2C_SendByte(adres_rw); //��������� ����� ����������+��� ������
I2C_SendByte(value);//���������� ���� ������
I2C_StopCondition();//���������� ������� ����
}

//��������� ������� ������ �� I2C
//������ �����
unsigned char I2C_RecieveByte(void)
{
unsigned char dat;//���������� �������� ��������
TWCR |= (1<<TWINT)|(1<<TWEN)|(1<<TWEA);
while (!(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
dat = TWDR;//������ ������� ������
return dat;
}

//������ ���������� �����
unsigned char I2C_RecieveLastByte(void)
{
unsigned char dat;//���������� �������� ��������	
TWCR |= (1<<TWINT)|(1<<TWEN)|(0<<TWEA);//������ ���������� �����
while (!(TWCR & (1<<TWINT)));//�������� ��������� ���� TWIN
dat = TWDR;//������ ������� ������	
return dat;
}	