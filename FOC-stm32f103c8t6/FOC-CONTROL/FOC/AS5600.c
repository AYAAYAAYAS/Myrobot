#include "main.h"

long cpr; // 编码器每圈脉冲数
float full_rotation_offset; // 全圈偏移量
long angle_data, angle_data_prev; // 角度数据和前一次角度数据
unsigned long velocity_calc_timestamp; // 速度计算时间戳
float angle_prev; // 上一个角度

// I2C接口宏定义
#define IIC_SCL_GPIO_PORT               GPIOB
#define IIC_SCL_GPIO_PIN                GPIO_PIN_6
#define IIC_SDA_GPIO_PORT               GPIOB
#define IIC_SDA_GPIO_PIN                GPIO_PIN_7

#define IIC_SCL(x)        do{ x ? \
                              HAL_GPIO_WritePin(IIC_SCL_GPIO_PORT, IIC_SCL_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(IIC_SCL_GPIO_PORT, IIC_SCL_GPIO_PIN, GPIO_PIN_RESET); \
                          }while(0)       /* SCL */

#define IIC_SDA(x)        do{ x ? \
                              HAL_GPIO_WritePin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN, GPIO_PIN_SET) : \
                              HAL_GPIO_WritePin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN, GPIO_PIN_RESET); \
                          }while(0)       /* SDA */

#define IIC_READ_SDA     HAL_GPIO_ReadPin(IIC_SDA_GPIO_PORT, IIC_SDA_GPIO_PIN) /* 读SDA */

// 2微秒延时
static void iic_delay(void)
{
    for(uint32_t j=0;j<10;j++);
}

// 开始信号
void iic_start(void)
{
    IIC_SDA(1);
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(0);
    iic_delay();
    IIC_SCL(0);
    iic_delay();
}

// 停止信号
void iic_stop(void)
{
    IIC_SDA(0);     
    iic_delay();
    IIC_SCL(1);
    iic_delay();
    IIC_SDA(1);    
    iic_delay();
}

// 应答信号
void iic_ack(void)
{
    IIC_SDA(0);     
    iic_delay();
    IIC_SCL(1);     
    iic_delay();
    IIC_SCL(0);
    iic_delay();
    IIC_SDA(1);     
    iic_delay();
}

// 非应答信号
void iic_nack(void)
{
    IIC_SDA(1);     
    iic_delay();
    IIC_SCL(1);     
    iic_delay();
    IIC_SCL(0);
    iic_delay();
}

// 等待应答
uint8_t iic_wait_ack(void)
{
    uint8_t waittime = 0;
    uint8_t rack = 0;

    IIC_SDA(1);    
    iic_delay();
    IIC_SCL(1);    
    iic_delay();

    while (IIC_READ_SDA)   
    {
        waittime++;

        if (waittime > 250)
        {
            iic_stop();
            rack = 1;
            break;
        }
    }

    IIC_SCL(0);    
    iic_delay();
    return rack;
}

// 读一个字节
uint8_t iic_read_byte(uint8_t ack)
{
    uint8_t i, receive = 0;

    for (i = 0; i < 8; i++ )    
    {
        receive <<= 1;  
        IIC_SCL(1);
        iic_delay();

        if (IIC_READ_SDA)
        {
            receive++;
        }
        
        IIC_SCL(0);
        iic_delay();
    }

    if (!ack)
    {
        iic_nack();     
    }
    else
    {
        iic_ack();     
    }

    return receive;
}

// 发送一个字节
void iic_send_byte(uint8_t data)
{
    uint8_t t;
    
    for (t = 0; t < 8; t++)
    {
        IIC_SDA((data & 0x80) >> 7);    
        iic_delay();
        IIC_SCL(1);
        iic_delay();
        IIC_SCL(0);
        data <<= 1;     
    }
    IIC_SDA(1);       
}

// 读取AS5600两个字节
uint16_t AS5600_ReadTwoByte(uint16_t readAddr)
{
    uint16_t temp=0xFFFF;                                                                                   
    iic_start();  
    iic_send_byte((0X36<<1)|0x00);    
    iic_wait_ack(); 
    iic_send_byte(readAddr);   
    iic_wait_ack();        
    iic_start();              
    iic_send_byte((0X36<<1)|0x01);              
    iic_wait_ack();     
    temp=iic_read_byte(1);   
    temp=temp<<8|iic_read_byte(0); 
    iic_stop();     
    return temp;
}

// AS5600初始化
#define  AS5600_Address  0x36 // AS5600的I2C地址
#define  RAW_Angle_Hi    0x0C // 读取地址高位
#define  RAW_Angle_Lo    0x0D // 读取地址低位
#define  AS5600_CPR      4096 

// 返回旋转计数值
unsigned short getRawCount()
{
    return AS5600_ReadTwoByte(0x0C);
}

// 初始化
void AS5600_Init(void)
{
    cpr=AS5600_CPR;
    angle_data = angle_data_prev = getRawCount();  
    full_rotation_offset = 0;
    velocity_calc_timestamp=0;
}

float getAngle_Without_track()
{
  return getRawAngle()*0.08789* PI / 180;    //得到弧度制的角度
}


// 获取角度
float getAngle(void)
{
    float d_angle;
    
    angle_data = getRawCount();
    
    // 跟踪旋转次数以扩展角度范围
    d_angle = angle_data - angle_data_prev;
    // 如果溢出发生，则跟踪为完整旋转
    if(fabs(d_angle) > (0.8*cpr) ) full_rotation_offset += d_angle > 0 ? -_2PI : _2PI; 
    // 保存当前角度值以便下一步判断是否发生溢出
    angle_data_prev = angle_data;
    
    // 简单的一阶低通滤波器
    float alpha = 0.1; // 滤波器系数，可以根据需要调整
    float filtered_angle = alpha * angle_data + (1 - alpha) * angle_prev;
    angle_prev = filtered_angle;
    
    // 返回完整角度
    return  (full_rotation_offset + ( filtered_angle * 1.0 / cpr) * _2PI) ;
}

