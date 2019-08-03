#ifndef __MPU6050_H__
#define __MPU6050_H__

#include "main.h"


#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h" 
#include <math.h>
#define ADDRESS_W 0xD0   //д��ַ 0x68
#define ADDRESS_R 0xD1   //����ַ  0x69
#define MPU_PWR_MGMT1_REG		0X6B	//��Դ����Ĵ���1
#define MPU_GYRO_CFG_REG		0X1B	//���������üĴ���
#define MPU_ACCEL_CFG_REG		0X1C	//���ٶȼ����üĴ���
#define MPU_SAMPLE_RATE_REG		0X19	//�����ǲ���Ƶ�ʷ�Ƶ��
#define MPU_INT_EN_REG			0X38	//�ж�ʹ�ܼĴ���
#define MPU_USER_CTRL_REG		0X6A	//�û����ƼĴ���
#define MPU_FIFO_EN_REG			0X23	//FIFOʹ�ܼĴ���
#define MPU_INTBP_CFG_REG		0X37	//�ж�/��·���üĴ���
#define MPU_DEVICE_ID_REG		0X75	//����ID�Ĵ���
#define MPU_PWR_MGMT2_REG		0X6C	//��Դ����Ĵ���2 
#define MPU_CFG_REG				0X1A	//���üĴ��� ��ͨ�˲������üĴ���
#define MPU_TEMP_OUTH_REG		0X41	//�¶�ֵ�߰�λ�Ĵ���
#define MPU_TEMP_OUTL_REG		0X42	//�¶�ֵ��8λ�Ĵ���

#define MPU_ACCEL_XOUTH_REG		0X3B	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_XOUTL_REG		0X3C	//���ٶ�ֵ,X���8λ�Ĵ���
#define MPU_ACCEL_YOUTH_REG		0X3D	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_YOUTL_REG		0X3E	//���ٶ�ֵ,Y���8λ�Ĵ���
#define MPU_ACCEL_ZOUTH_REG		0X3F	//���ٶ�ֵ,Z���8λ�Ĵ���
#define MPU_ACCEL_ZOUTL_REG		0X40	//���ٶ�ֵ,Z���8λ�Ĵ���

#define MPU_GYRO_XOUTH_REG		0X43	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_XOUTL_REG		0X44	//������ֵ,X���8λ�Ĵ���
#define MPU_GYRO_YOUTH_REG		0X45	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_YOUTL_REG		0X46	//������ֵ,Y���8λ�Ĵ���
#define MPU_GYRO_ZOUTH_REG		0X47	//������ֵ,Z���8λ�Ĵ���
#define MPU_GYRO_ZOUTL_REG		0X48	//������ֵ,Z���8λ�Ĵ���

//��������ٶ�
#define DEFAULT_MPU_HZ  (100)		//100Hz

//q30��ʽ,longתfloatʱ�ĳ���.
#define q30  1073741824.0f

static signed char gyro_orientation[9] = { 1, 0, 0,
                                           0, 1, 0,
                                           0, 0, 1};


/*
       XYZ  010_001_000 Identity Matrix
       XZY  001_010_000
       YXZ  010_000_001
       YZX  000_010_001
       ZXY  001_000_010
       ZYX  000_001_010
*/
																					 
//һ�׻����˲�����
#define FILTER_NUMBER 0.95



void MPU_6050_Init(void);
unsigned char  MPU_Set_LPF(unsigned short lpf);
void read_all(void);
unsigned char HAL_i2c_write(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char const *data);
unsigned char HAL_i2c_read(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char const *data);
void read_all(void);
unsigned short inv_orientation_matrix_to_scalar(const signed char *mtx);
unsigned short inv_row_2_scale(const signed char *row);
unsigned char run_self_test(void);
unsigned char mpu_dmp_init(void);
unsigned char mpu_dmp_get_data(float *pitch,float *roll,float *yaw);

float Comp_filter();

#endif