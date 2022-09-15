// Standard library includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Linux includes
#include <linux/i2c-dev.h>
#include <i2c/smbus.h>
#include <sys/ioctl.h>
#include <sys/fcntl.h>

// User includes
#include "adv_defines.h"

/*
 * Init order: set_power_pin -> write pwrman, man_res -> wait 5000 uS -> init -> program_std -> set_field_mode -> set interrupts
 * 
 * 
 */


// Prototypes
void print_help(void);

int initialize_power(void);
int initialize_chip(void);
int set_input_type(int std);
int set_field_mode(int mode);
int set_input_channel(int input);

int adv7280_select_page(unsigned int page);
int adv_read(unsigned int reg);
int adv_write(unsigned int reg, unsigned int value);

// Typedefs
typedef struct
{
	int fd;
	int current_reg_page;
	char filename[20];
} t_adv_data;

// Variables
static unsigned int lbias_settings[][3] = 
{
	[INPUT_TYPE_CVBS] = {0xCD, 0x4E, 0x80},
	[INPUT_TYPE_DIFF_CVBS] = {0xC0, 0x4E, 0x80},
	[INPUT_TYPE_SVIDEO] = {0x0B, 0xCE, 0x80},
	[INPUT_TYPE_YPBPR] = {0x0B, 0x4E, 0xC0}
};

t_adv_data adv_data = {0};

// Definitions
int main(int argc, char *argv[])
{	
	int opt;
	int adv_device;
	int input_type;
	int input_channel;
	
	if(7 != argc)
	{
		print_help();
		return -1;
	}
	
	while((opt = getopt(argc, argv, "a:i:c:")) != -1)
	{
		switch(opt)
		{
			case 'a':
			{
				adv_device = atoi(optarg);
				
			}break;
			
			case 'i':
			{
				input_type = atoi(optarg);
				
				switch(input_type)
				{
					case 0:
					{
						input_type = ADV7180_STD_PAL_BG;
					}break;
					
					case 1:
					{
						input_type = ADV7180_STD_NTSC_J;
					}break;
					
					default:{
						input_type = ADV7180_STD_PAL_BG;
					}
				}
			}break;
			
			case 'c':
			{
				input_channel = atoi(optarg);
			}break;
			
			default:
			{
				printf("Unknown option: %c\r\n", optopt);
			}
		}
	}
	
	
	snprintf(adv_data.filename, 19, "/dev/i2c-%d", adv_device);
	
	// Open file
	adv_data.fd = open(adv_data.filename, O_RDWR);
	if(0 > adv_data.fd)
	{
		printf("Failed to open device.\r\n");
		return -1;
	}
	
	// Select device addr
	if(ioctl(adv_data.fd, I2C_SLAVE, ADV7280_ADDR))
	{
		printf("Set device address failed.\r\n");
		return -1;
	}

	if(0 != initialize_power())
	{
		printf("Initialize power failed.\r\n");
		return -1;
	}

	if(0 != initialize_chip())
	{
		printf("Initialize chip failed.\r\n");
		return -1;
	}

	if(0 != set_input_type(input_type))
	{
		printf("Program video std failed.\r\n");
		return -1;
	}

	if(0 != set_field_mode(0))
	{
		printf("Set field mode failed.\r\n");
		return -1;
	}

	if(0 != set_input_channel(input_channel))
	{
		printf("Set input channel failed.\r\n");
		return -1;
	}

	return 0;
}

void print_help(void)
{
	printf("Usage:\r\n");
	printf("\tadvctrli2c -a <i2c number> -i <input_type> -c <input_channel>\r\n");
	printf("\tinput types: 0: PAL, 1: NTSC\r\n");
	printf("\tinput channels: CVBS: 0-7, SVIDEO: 8-11\r\n");
}

int initialize_power(void)
{
	adv_write(ADV7180_REG_PWR_MAN, ADV7180_PWR_MAN_RES);
	usleep(10000);
	return 0;
}

int initialize_chip(void)
{
	adv_write(ADV7180_REG_VPP_SLAVE_ADDR, ADV7180_DEFAULT_VPP_I2C_ADDR << 1);
	
	adv_write(0x0080, 0x51);
	adv_write(0x0081, 0x51);
	adv_write(0x0082, 0x68);
	
	adv_write(ADV7180_REG_EXTENDED_OUTPUT_CONTROL, 0x17);
	adv_write(ADV7180_REG_OUTPUT_CONTROL, 0x0C);
	adv_write(ADV7180_REG_CTRL_2, 0x40);
	
	adv_write(0x0013, 0x00);
	
	return 0;
}

int set_input_type(int std)
{
	return adv_write(ADV7182_REG_INPUT_VIDSEL, std << 4);
}

int set_field_mode(int mode)
{
	return 0;
}

int set_input_channel(int input)
{
	int ret_val = 0;
	unsigned int *lbias;
	
	adv_write(ADV7180_REG_RST_CLAMP, 0x00);
	adv_write(ADV7180_REG_RST_CLAMP, 0xFF);
	
	ret_val = adv_write(ADV7180_REG_INPUT_CONTROL, input);
	if(0 != ret_val)
	{
		printf("Input channel selection failed.\r\n");
		return -1;
	}
	
	if(input <= ADV7182_INPUT_CVBS_AIN8)
	{
		adv_write(ADV7180_REG_SHAP_FILTER_CTL_1, 0x41);
		lbias = lbias_settings[INPUT_TYPE_CVBS];
	}
	else
	{
		adv_write(ADV7180_REG_SHAP_FILTER_CTL_1, 0x01);
		lbias = lbias_settings[INPUT_TYPE_SVIDEO];
	}
	
	for(int i = 0; i < 3; i++)
	{
		adv_write(ADV7180_REG_CVBS_TRIM + i, lbias[i]);
	}
	
	if(input <= ADV7182_INPUT_CVBS_AIN8)
	{
		adv_write(ADV7180_REG_RES_CIR, 0xF0);
		adv_write(ADV7180_REG_CLAMP_ADJ, 0xD0);
		adv_write(ADV7180_REG_DIFF_MODE, 0x10);
		adv_write(ADV7180_REG_AGC_ADJ1, 0x9C);
		adv_write(ADV7180_REG_AGC_ADJ2, 0x00);
	}
	
	return 0;
}

int adv7280_select_page(unsigned int page)
{
	if(page != adv_data.current_reg_page)
	{
		i2c_smbus_write_byte_data(adv_data.fd, ADV7180_REG_CTRL, page);
		adv_data.current_reg_page = page;
	}
	
	return 0;
}

int adv_read(unsigned int reg)
{
	adv7280_select_page(reg >> 8);
	return i2c_smbus_read_byte_data(adv_data.fd, reg >> 8);
}

int adv_write(unsigned int reg, unsigned int value)
{
	adv7280_select_page(reg >> 8);
	return i2c_smbus_write_byte_data(adv_data.fd, reg & 0xFF, value);
}
