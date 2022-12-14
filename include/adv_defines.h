#ifndef ADV7280_RESET_H_
#define ADV7280_RESET_H_

#define ADV7280_ADDR						0x21
#define ADV7180_DEFAULT_CSI_I2C_ADDR		0x44
#define ADV7180_DEFAULT_VPP_I2C_ADDR		0x42

#define ADV7180_REG_INPUT_CONTROL			0x0000
#define ADV7180_REG_INPUT_VIDSEL			0x0002
#define ADV7180_REG_OUTPUT_CONTROL			0x0003
#define ADV7180_REG_EXTENDED_OUTPUT_CONTROL	0x0004
#define ADV7180_REG_AUTODETECT_ENABLE		0x0007
#define ADV7180_REG_CONTRAST				0x0008
#define ADV7180_REG_BRIGHTNESS				0x000A
#define ADV7180_REG_HUE						0x000B
#define ADV7180_REG_CTRL					0x000E
#define ADV7180_REG_PWR_MAN					0x000F
#define ADV7180_REG_STATUS1					0x0010
#define ADV7180_REG_IDENTITY				0x0011
#define ADV7180_REG_STATUS3					0x0013
#define ADV7180_REG_ANALOG_CLAMP_CTL		0x0014
#define ADV7180_REG_SHAP_FILTER_CTL_1		0x0017
#define ADV7180_REG_CTRL_2					0x001D
#define ADV7180_REG_VSYNC_FIELD_CTL_1		0x0031
#define ADV7180_REG_MANUAL_WIN_CTL_1		0x003D
#define ADV7180_REG_MANUAL_WIN_CTL_2		0x003E
#define ADV7180_REG_MANUAL_WIN_CTL_3		0x003F
#define ADV7180_REG_LOCK_CNT				0x0051
#define ADV7180_REG_CVBS_TRIM				0x0052
#define ADV7180_REG_CLAMP_ADJ				0x005A
#define ADV7180_REG_RES_CIR					0x005F
#define ADV7180_REG_DIFF_MODE				0x0060
#define ADV7180_REG_ICONF1					0x2040
#define ADV7180_REG_SD_SAT_CB				0x00E3
#define ADV7180_REG_SD_SAT_CR				0x00E4
#define ADV7180_REG_ISR1					0x2042
#define ADV7180_REG_ICR1					0x2043
#define ADV7180_REG_IMR1					0x2044
#define ADV7180_REG_IMR2					0x2048
#define ADV7180_REG_ISR3					0x204A
#define ADV7180_REG_ICR3					0x204B
#define ADV7180_REG_IMR3					0x204C
#define ADV7180_REG_IMR4					0x2050
#define ADV7180_REG_NTSC_V_BIT_END			0x00E6
#define ADV7180_REG_VPP_SLAVE_ADDR			0xFD
#define ADV7180_REG_CSI_SLAVE_ADDR			0xFE
#define ADV7180_REG_ACE_CTRL1				0x4080
#define ADV7180_REG_ACE_CTRL5				0x4084
#define ADV7180_REG_FLCONTROL				0x40E0
#define ADV7180_REG_RST_CLAMP				0x809C
#define ADV7180_REG_AGC_ADJ1				0x80B6
#define ADV7180_REG_AGC_ADJ2				0x80C0

#define ADV7182_REG_INPUT_VIDSEL			0x0002


// Power
#define ADV7180_PWR_MAN_ON					0x04
#define ADV7180_PWR_MAN_OFF					0x24
#define ADV7180_PWR_MAN_RES					0x80


// Standards
#define ADV7180_STD_NTSC_J					0x4
#define ADV7180_STD_NTSC_M					0x5
#define ADV7180_STD_PAL60					0x6
#define ADV7180_STD_NTSC_443				0x7
#define ADV7180_STD_PAL_BG					0x8
#define ADV7180_STD_PAL_N					0x9
#define ADV7180_STD_PAL_M					0xA

// Inputs
#define ADV7182_INPUT_CVBS_AIN1				0x00
#define ADV7182_INPUT_CVBS_AIN2				0x01
#define ADV7182_INPUT_CVBS_AIN3				0x02	
#define ADV7182_INPUT_CVBS_AIN4				0x03
#define ADV7182_INPUT_CVBS_AIN5				0x04
#define ADV7182_INPUT_CVBS_AIN6				0x05
#define ADV7182_INPUT_CVBS_AIN7				0x06
#define ADV7182_INPUT_CVBS_AIN8				0x07
#define ADV7182_INPUT_SVIDEO_AIN1_AIN2		0x08
#define ADV7182_INPUT_SVIDEO_AIN3_AIN4		0x09
#define ADV7182_INPUT_SVIDEO_AIN5_AIN6		0x0A
#define ADV7182_INPUT_SVIDEO_AIN7_AIN8		0x0B

enum input_type
{
	INPUT_TYPE_CVBS,
	INPUT_TYPE_DIFF_CVBS,
	INPUT_TYPE_SVIDEO,
	INPUT_TYPE_YPBPR
};



#endif
